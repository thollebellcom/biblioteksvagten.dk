<?php

/**
 * @file
 * Public page callback functions.
 */

/**
 * Page callback to create questions.
 *
 * Used by Open Question to create questions
 */
function vopros_question_create_service() {
  $question = vopros_question_new();
  $question_wrapper = entity_metadata_wrapper('vopros_question', $question);
  $post_data = array();
  // Reformat all the post data to not use CamelCase.
  foreach ($_POST as $key => $value) {
    $post_data[strtolower(preg_replace('/(?<=\\w)(?=[A-Z])/', "_$1", $key))] = $value;
  }
  $properties = $question_wrapper->getPropertyInfo();
  // Populate the question with the needed info.
  foreach (array_keys($properties) as $property) {
    if (isset($post_data[$property])) {
      $question->{$property} = $post_data[$property];
    }
  }
  if (!empty($_POST['questionAttachmentData'])) {
    $file = file_save_data(base64_decode($_POST['questionAttachmentData']));
    if ($file) {
      $file_data = array(
        'fid' => $file->fid,
        'display' => 1,
        'description' => '',
      );
      $question_wrapper->vopros_question_attachment[0] = $file_data;
    }
  }

  // Map qanda and agency to client and channel.
  $mappings = _vopros_question_qanda_mapping();
  $full_key = $question->qanda_service_name . '|' . $question->agency;
  // Fall back to mapping with empty agency.
  $qanda_key = $question->qanda_service_name . '|';
  if (($mapping = $mappings[$full_key]) || ($mapping = $mappings[$qanda_key])) {
    if ($mapping['client']) {
      $question->client_id = $mapping['client'];
    }
    if ($mapping['channel']) {
      $question->channel = $mapping['channel'];
    }
  }

  if (module_exists('vopros_editorial') && !empty($_POST['vopros_editorial'])) {
    unset($question->vopros_editorial);
    $vocab = taxonomy_vocabulary_machine_name_load('vopros_editorial');
    $terms = taxonomy_term_load_multiple(FALSE, array('name' => $_POST['vopros_editorial'], 'vid' => $vocab->vid));
    if ($terms) {
      $term = array_shift($terms);
      $question_wrapper->vopros_editorial = $term;
    }
  }
  if (!empty($post_data)) {
    $validation = vopros_question_validate_data($question);
    if ($validation['status'] == 'valid') {
      $question_wrapper->save();
      print 'Question created';
      return;
    }
    drupal_add_http_header('Status', '400');
    $errors = array();
    foreach ($validation['errors'] as $value) {
      $errors[] = $value[0];
    }
    $message = 'Could not create vopros question, invalid data for: %fields. Validation object: %validation, POST data: %post';
    $args = array(
      '%fields' => implode(', ', $errors),
      '%validation' => print_r($validation, TRUE),
      '%post' => print_r($_POST, TRUE),
    );
    watchdog('vopros_question', $message, $args, WATCHDOG_ERROR);
  }
  print 'Question not created';
}
