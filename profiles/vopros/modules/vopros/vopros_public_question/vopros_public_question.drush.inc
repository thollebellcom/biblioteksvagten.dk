<?php

/**
 * @file
 * Drush commands for vopros_public_question.
 */

/**
 * Implements hook_dursh_command().
 */
function vopros_public_question_drush_command() {
  $items['vopros-public-question-push-all'] = array(
    'description' => 'Publish all public questions.',
    'options' => array(
      'start' => 'Start at the public question with this id or higher',
      'limit' => 'Only process this many public questions',
      'batch' => 'Size of batch',
      'update' => 'Update questions instead of creating them',
      'delete' => 'Delete questions instead of creating them',
      'no-ftp' => "Don't actually FTP files. Useful with --no-cleanup.",
      'no-cleanup' => "Don't remove generated files in /tmp/. Useful for debugging.",
    ),
  );

  return $items;
}

/**
 * Command callback.
 */
function drush_vopros_public_question_push_all() {
  $query = db_select('vopros_public_question', 'vpq')
         ->fields('vpq', array('public_question_id'))
         ->condition('public_question_id', (int) drush_get_option('start', 0), '>=');

  if ($limit = (int) drush_get_option('limit', 0)) {
    $query->range(0, $limit);
  }

  $total = $query->countQuery()->execute()->fetchField();
  drush_print(dt('Processing @count public questions.', array('@count' => $total)));

  $action = drush_get_option('update', FALSE) ? 'update' : 'create';
  if (drush_get_option('delete', FALSE)) {
    $action = 'delete';
  }
  // We process the questions in batches.
  $batch = array();
  $batch_size = (int) drush_get_option('batch', 5000);
  if (!$batch_size) {
    return drush_set_error('Invalid batch size.');
  }

  $tempdir = '/tmp/vopros_public_question_batch_' . getmypid() . '/';
  mkdir($tempdir);
  if (!drush_get_option('no-cleanup', FALSE)) {
    drush_register_file_for_deletion($tempdir);
  }
  $files = array();
  $agency  = variable_get('ting_agency', '');
  $file_base = $agency . '.' . REQUEST_TIME;
  $file_counter = 1;

  $current = 0;
  foreach ($query->execute() as $row) {
    $percent = sprintf("%.2f", ($current++ / $total) * 100);
    drush_print(dt('@percent% Processing @id                ', array('@percent' => $percent, '@id' => $row->public_question_id)), 0, NULL, FALSE);
    drush_print("\r", 0, NULL, FALSE);
    $batch[] = vopros_public_question_load($row->public_question_id);
    if ((count($batch) >= $batch_size) || ($current >= $total)) {
      // Full batch or end of line, process.
      $xml = _vopros_public_question_generate_xml(array($action => $batch));
      $filename = $file_base . $file_counter++ . '.xml';
      file_put_contents($tempdir . $filename, $xml);
      $files[] = $filename;
      $batch = array();
    }
  }

  $transfer = _vopros_public_question_generate_transfer($files);
  $transfer_filename = $file_base . '.trans';
  // Save transfer file to temp dir for debugging.
  file_put_contents($tempdir . $transfer_filename, $transfer);

  drush_print('100% Done generating.                          ');

  $ftp = variable_get('vopros_public_question_ftp', '');
  if (!drush_get_option('no-ftp') && empty($ftp)) {
    return drush_set_error('FTP not configured.');
  }
  else {
    $ftp = 'ftp://' . rtrim($ftp, '/') . '/';
    $total = count($files) + 1;
    $current = 0;
    foreach ($files as $xml_filename) {
      $xml = file_get_contents($tempdir . $xml_filename);
      $percent = sprintf("%.2f", ($current++ / $total) * 100);
      drush_print(dt('@percent% Uploading @file                ', array('@percent' => $percent, '@file' => $xml_filename)), 0, NULL, FALSE);
      drush_print("\r", 0, NULL, FALSE);
      if (!drush_get_option('no-ftp')) {
        if (file_put_contents($ftp . $xml_filename, $xml) === FALSE) {
          return drush_set_error(dt('Could not upload XML file @file.', array('@file' => $xml_filename)));
        }
      }
      else {
        sleep(1);
      }
    }
    $percent = sprintf("%.2f", ($current++ / $total) * 100);
    drush_print(dt('@percent% Uploading @file                ', array('@percent' => $percent, '@file' => $transfer_filename)), 0, NULL, FALSE);
    drush_print("\r", 0, NULL, FALSE);
    if (!drush_get_option('no-ftp')) {
      if (file_put_contents($ftp . $transfer_filename, $transfer) === FALSE) {
        return drush_set_error(dt('Could not upload trans file @file.', array('@file' => $transfer_filename)));
      }
    }
    else {
      sleep(1);
    }
  }

  drush_print('100% Done uploading.                          ');
}
