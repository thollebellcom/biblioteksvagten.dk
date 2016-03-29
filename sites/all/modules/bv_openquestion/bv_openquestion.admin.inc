<?php

/**
 * @file
 * Admin pages for the BV Openquestion module.
 */

/**
 * Migrate questions from QandA service to clients.
 */
function bv_openquestion_client_migrate_form($form, &$form_state) {
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
    '#description' => t('Leave empty to migrate all un-migrated questions.'),
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
function bv_openquestion_client_migrate_form_submit($form, &$form_state) {
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
        'bv_openquestion_client_migrate_batch_operation',
        array($per_run, $count),
      ),
    ),
    'file' => drupal_get_path('module', 'bv_openquestion') . '/bv_openquestion.admin.inc',
    'title' => t('Migrating questions'),
  );
  batch_set($batch);
}

/**
 * Batch callback for migration.
 */
function bv_openquestion_client_migrate_batch_operation($per_run, $number, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['last'] = 0;
    $context['sandbox']['max'] = $number;
    $context['sandbox']['mapping'] = _bv_openquestion_qanda_mapping();
    $context['sandbox']['clients'] = array();
    foreach (vopros_question_client_load_multiple() as $client) {
      $context['sandbox']['clients'][$client->agency] = $client->client_id;
    }
  }

  $questions = db_select('vopros_question', 'vq')
             ->fields('vq', array(
                 'question_id',
                 'qanda_service_name',
                 'agency_id',
               ))
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
