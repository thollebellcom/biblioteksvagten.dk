<?php

/**
 * @ file
 * Admin forms and callback functions for client admin.
 */

/**
 * Client settings form
 */
function vopros_question_client_settings_form($form, &$form_state) {
  $mapping = _vopros_question_qanda_mapping();

  // Check the db to see if there's any unmapped services, and add them in.
  $questions = db_select('vopros_question', 'vq')
    ->fields('vq', array('qanda_service_name', 'agency_id'))
    ->groupBy('qanda_service_name')
    ->groupBy('agency_id')
    ->orderBy('qanda_service_name')
    ->orderBy('agency_id');
  $count_field = $questions->addExpression('COUNT(question_id)', 'count');
  $migrated_field = $questions->addExpression("(client_id <> 0 AND channel <> '')", 'migrated');
  $questions->groupBy($migrated_field);

  foreach ($questions->execute() as $row) {
    $key = $row->qanda_service_name . '|' . $row->agency_id;
    if (!isset($mapping[$key])) {
      $mapping[$key] = array('client' => '', 'channel' => '');
    }
    $mapping[$key] += array(
      'unmigrated' => 0,
      'migrated' => 0,
    );
    $field = 'unmigrated';
    if ($row->{$migrated_field}) {
      $field = 'migrated';
    }
    $mapping[$key][$field] = $row->{$count_field};
  }

  // Revert to textual representation.
  $mapping_string = '';
  foreach ($mapping as $key => $val) {
    $mapping_string .= $key . ' -> ' . $val['client'] . '|' . $val['channel'] . ' # ' . $val['unmigrated'] . '/' . $val['migrated'] . "\n";
  }

  $form['vopros_question_qanda_mapping'] = array(
    '#type' => 'textarea',
    '#title' => t('QandA mapping'),
    '#rows' => 30,
    '#default_value' => $mapping_string,
    '#description' => t('Mapping of QandA sevice names to clients in the form of <em>qanda|agency_id -> client|channel</em>. Everything after a # is ignored, and are populated with the number of pending/migrated questions.'),
  );

  $channels = vopros_question_channels();
  $channel_list = '<dl>';
  foreach ($channels as $name => $channel) {
    $channel_list .= '<dt>' . check_plain($channel['name']) . '</dt><dd>' .
      $name . '</dd>';
  }
  $channel_list .= '</dl>';
  $form['vopros_question_channels'] = array(
    '#type' => 'item',
    '#title' => t('Known channels'),
    '#markup' => $channel_list,
  );

  return system_settings_form($form);
}

/**
 * Validation handler for vopros_question_client_settings_form().
 *
 * Checks that the configured clients and channels exists.
 */
function vopros_question_client_settings_form_validate($form, &$form_state) {
  $mapping = preg_replace('/\s+#[^\n]*$/m', '', $form_state['values']['vopros_question_qanda_mapping']);
  // Allow for empty submission. It's the way to clear the mapping and build it
  // up again.
  if (empty($mapping)) {
    return;
  }

  $clients = array();
  foreach (vopros_question_client_load_multiple() as $client) {
    $clients[$client->agency] = $client;
  }
  $channels = vopros_question_channels();

  $parsed = _vopros_question_parse_qanda_mapping($mapping);
  if (!$parsed) {
    form_error($form['vopros_question_qanda_mapping'], t('Error parsing mapping.'));
  }
  foreach ($parsed as $to) {
    if (!empty($to['client']) && !isset($clients[$to['client']])) {
      form_error($form['vopros_question_qanda_mapping'], t('Unknown client @client.', array('@client' => $to['client'])));
    }
    if (!empty($to['channel']) && !isset($channels[$to['channel']])) {
      form_error($form['vopros_question_qanda_mapping'], t('Unknown channel @channel.', array('@channel' => $to['channel'])));
    }
  }

  // Set the value to the comment-stripped version.
  form_set_value($form['vopros_question_qanda_mapping'], $mapping, $form_state);
}

/**
 * Migrate questions from QandA service to clients.
 */
function vopros_question_client_migrate_form($form, &$form_state) {
  // Get a count of un-migrated questions.
  $count = db_select('vopros_question', 'vq')
    ->condition(db_or()
      ->condition('client_id', 0)
      ->condition('channel', ''))
    ->countQuery()
    ->execute()
    ->fetchField();

  $form['count'] = array(
    '#type' => 'value',
    '#value' => $count,
  );

  $form['count_info'] = array(
    '#type' => 'item',
    '#title' => t('Un-migrated questions'),
    '#markup' => number_format($count),
  );

  $form['migrate_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number to migrate'),
    '#size' => 7,
    '#description' => t('Leave empty to migrate all un-migrated questions.')
  );

  $form['actions']['migrate'] = array(
    '#type' => 'submit',
    '#value' => t('Migrate questions'),
    '#weight' => 50,
    '#migrate_button' => TRUE,
  );

  return $form;
}

/**
 * Button submit callback.
 *
 * Starts the migrate batch job.
 */
function vopros_question_client_migrate_form_submit($form, &$form_state) {
  // Get a count of un-migrated questions.
  $count = $form_state['values']['count'];

  $process = (int) $form_state['values']['migrate_number'];
  if ($process > 0) {
    $count = min($count, $process);
  }

  // Calibrate the chunk size so the progressbar updates in small steps, but
  // limit the chunk size to 50 questions per chunk.
  $per_run = min(ceil($count / 100), 50);

  $batch = array(
    'operations' => array(
      array(
        'vopros_question_client_migrate_batch_operation',
        array($per_run, $count),
      ),
    ),
    'file' => drupal_get_path('module', 'vopros_question') . '/includes/vopros_question_client.admin.inc',
    'title' => t('Migrating questions'),
  );
  batch_set($batch);
}

/**
 * Batch callback for migration.
 */
function vopros_question_client_migrate_batch_operation($per_run, $number, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['last'] = 0;
    $context['sandbox']['max'] = $number;
    $context['sandbox']['mapping'] = _vopros_question_qanda_mapping();
    $context['sandbox']['clients'] = array();
    foreach (vopros_question_client_load_multiple() as $client) {
      $context['sandbox']['clients'][$client->agency] = $client->client_id;
    }
  }

  $questions = db_select('vopros_question', 'vq')
    ->fields('vq', array('question_id', 'qanda_service_name', 'agency_id'))
    ->condition(db_or()
      ->condition('client_id', 0)
      ->condition('channel', '')
    )
    ->condition('question_id', $context['sandbox']['last'], '>')
    ->range(0, $per_run)
    ->execute();

  $last = $context['sandbox']['last'];
  foreach ($questions as $question) {
    $fields = array();
    $key = $question->qanda_service_name . '|' . $question->agency_id;
    if (isset($context['sandbox']['mapping'][$key])) {
      $mapping = $context['sandbox']['mapping'][$key];
      if (!empty($mapping['client']) &&
        isset($context['sandbox']['clients'][$mapping['client']])) {
        $fields['client_id'] = $context['sandbox']['clients'][$mapping['client']];
      }
      if (!empty($mapping['channel'])) {
        $fields['channel'] = $mapping['channel'];
      }
    }

    if (!empty($fields)) {
      db_update('vopros_question')
        ->fields($fields)
        ->condition('question_id', $question->question_id)
        ->execute();
    }
    $context['sandbox']['progress']++;
    $context['sandbox']['last'] = $question->question_id;
  }

  // Cop out if we didn't process anything (another runner might have eaten
  // them).
  if ($last == $context['sandbox']['last']) {
    // $context['finished'] is prepopulated with 1, so we can just return.
    return;
  }

  // Update progress.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Form to edit or create a client.
 */
function vopros_question_client_form($form, &$form_state, $client, $op = 'edit') {
  if ($op == 'clone') {
    $client->agency .= '_new';
    $client->label .= ' (cloned)';
  }

  $form['client'] = array(
    '#type' => 'value',
    '#value' => $client,
  );

  $form['agency'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name'),
    '#required' => TRUE,
    '#default_value' => !empty($client->agency) ? $client->agency : '',
    '#description' => t('The ID of the client. For libraries this is their agency ID in the form <em>DK-123456</em>. For other clients it can be any unique (preferably lowercase) string.'),
  );

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Label'),
    '#required' => TRUE,
    '#default_value' => !empty($client->label) ? $client->label : '',
    '#description' => t('Human readable label for this client.'),
  );

  field_attach_form('vopros_question_client', $client, $form, $form_state);

  $form['buttons'] = array(
    '#type' => 'actions',
    '#weight' => 100,
  );

  $form['buttons']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array('class' => array('primary-action')),
  );

  return $form;
}

/**
 * Validation handler for vopros_question_client_form().
 *
 * Checks for agency uniqueness.
 */
function vopros_question_client_form_validate(&$form, &$form_state) {
  $client = $form_state['values']['client'];
  $query = db_select('vopros_question_client', 'vqc')
    ->fields('vqc', array('client_id'))
    ->condition('agency', $form_state['values']['agency']);

  if (!isset($client->is_new)) {
    $query->condition('client_id', $client->client_id, '<>');
  }
  $clients = $query->execute()
      ->fetchAll();

  if (!empty($clients)) {
    form_error($form['agency'], t('Machine name must be unique.'));
  }

  field_attach_validate('vopros_client', $client, $form, $form_state);
}

/**
 * Submit handler for vopros_question_client_form().
 */
function vopros_question_client_form_submit(&$form, &$form_state) {
  $client = $form_state['values']['client'];

  $info = entity_get_property_info('vopros_question_client');
  foreach (array_keys($info['properties']) as $key) {
    if (isset($form_state['values'][$key])) {
      $client->{$key} = $form_state['values'][$key];
    }
  }

  // Notify field widgets.
  field_attach_submit('vopros_question_client', $client, $form, $form_state);

  $client->save();

  // Add the client to the $form_state for other modules to use.
  $form_state['client'] = $client;
  $form_state['redirect'] = 'admin/vopros/clients/' . $client->client_id;
}
