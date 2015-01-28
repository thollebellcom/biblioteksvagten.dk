<?php

// Needed during install.
module_load_include('inc', 'vopros_base', 'includes/vopros.controller');

/**
 * Entity controller class for vopros question.
 */
class VoprosQuestionEntityController extends VoprosAPIEntityController {
  public function save($question, DatabaseTransaction $transaction = NULL) {
    if (in_array($question->question_status, array('answered', 'closed'))) {
      $question->uid = 0;
    }
    $created = !empty($question->created) ? $question->created : REQUEST_TIME;
    if ($question->question_deadline == -1) {
      // We set the deadline quite high: 1 year from creation.
      $question->question_deadline_timestamp = 86400 * 365 + $created;
    }
    else {
      // Set the deadline to x hours from creation.
      $question->question_deadline_timestamp = 3600 * $question->question_deadline + $created;
    }
    return parent::save($question, $transaction);
  }


  public function validateData($question) {
    $errors = array();
    // For the moment just check that client_id/channel is valid if given. Later
    // we might require them.
    if ($question->client_id && !vopros_question_client_load($question->client_id)) {
      $errors[] = array(
        'client_id',
        t('Unknown @name @id', array('@name' => t('Client id'), '@id' => $question->client_id)),
      );
    }

    if ($question->channel && !vopros_question_channel($question->channel)) {
      $errors[] = array(
        'channel',
        t('Unknown @name @id', array('@name' => t('Channel'), '@id' => $question->channel)),
      );
    }

    if (!isset($question->question_content) || empty($question->question_content)) {
      $errors[] = array('question_content', t('@name is required', array('@name' => t('Question content'))));
    }
    if ($question->question_deadline && !is_numeric($question->question_deadline)) {
      $errors[] = array('question_deadline', t('@name must be numeric', array('@name' => t('Question deadline'))));
    }
    // For now rely on the service for validation.
    /*if (isset($question->question_usage) && $question->question_usage && !in_array($question->question_usage, array_keys(_vopros_question_usage()))) {
      $errors[] = array('question_usage', t('Selected option: %value not valid for @field',
        array('%value' => $question->question_usage, '@field' => t('Question usage'))
      ));
    }*/
    if (
      (!isset($question->user_email) || empty($question->user_email)) &&
      (!isset($question->user_mobile_phone) || empty($question->user_mobile_phone))
    ) {
      $errors[] = array('user', t('@name is required', array('@name' => t('User email or mobile phone'))));
    }
    if (!empty($errors)) {
      return array('status' => 'error', 'errors' => $errors);
    }
    return array('status' => 'valid');
  }
}
