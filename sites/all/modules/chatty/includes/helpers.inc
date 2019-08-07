<?php

/**
 * Load question.
 *
 * @param int $questionId
 *   The ID of the question to load the log for.
 *
 * @return array
 *   An array of chat log object keyed by timestamp.
 */
function chatty_load_question($questionId) {
  $query = db_select('chatty_questions');

  $query->addField('chatty_questions', 'id');
  $query->addField('chatty_questions', 'authorName');
  $query->addField('chatty_questions', 'authorEmail');
  $query->addField('chatty_questions', 'subject');
  $query->addField('chatty_questions', 'status');
  $query->addField('chatty_questions', 'consultant');
  $query->addField('chatty_questions', 'lastHeartbeatAt');
  $query->addField('chatty_questions', 'createdAt');
  $query->addField('chatty_questions', 'updatedAt');

  $query->condition('chatty_questions.id', $questionId, '=');

  return $query->execute()->fetchObject();
}

/**
 * Load messages.
 *
 * @param int $questionId
 *   The ID of the question to load the log for.
 *
 * @return array
 *   An array of chat log object keyed by timestamp.
 */
function chatty_load_messages($questionId) {
  $query = db_select('chatty_messages');

  $query->addField('chatty_messages', 'id');
  $query->addField('chatty_messages', 'text');
  $query->addField('chatty_messages', 'sentFrom');
  $query->addField('chatty_messages', 'question');
  $query->addField('chatty_messages', 'createdAt');

  $query->condition('chatty_messages.question', $questionId, '=');

  return $query->execute()->fetchAll();
}

/**
 * Load message.
 *
 * @param int $messageId
 *   The ID of the question to load the log for.
 *
 * @return array
 *   An array of chat log object keyed by timestamp.
 */
function chatty_load_message($messageId) {
  $query = db_select('chatty_messages');

  $query->addField('chatty_messages', 'id');
  $query->addField('chatty_messages', 'text');
  $query->addField('chatty_messages', 'sentFrom');
  $query->addField('chatty_messages', 'question');
  $query->addField('chatty_messages', 'createdAt');

  $query->condition('chatty_messages.id', $messageId, '=');

  return $query->execute()->fetchObject();
}

/*
 * Status.
 * Returns 'open', 'closed'.
 */
function _chatty_status() {
  $status = 'closed';
  $hours = variable_get('chatty_hours');
  $readable_hours = json_decode($hours);
  $day_of_week = date('w');
  $now_in_minutes = ((date('G') * 60) + date('i'));
  $today = new stdClass();

  if ($day_of_week === 0) {
    $day_of_week = 7;
  }

  $count = 1;
  foreach ($readable_hours as $readable_hour) {
    if ($count === (int) $day_of_week) {
      $today = $readable_hour;
    }

    $count++;
  }

  if ($today->open !== NULL || $today->close !== NULL) {
    if (($today->open === NULL || $today->open <= $now_in_minutes) &&
        ($today->close === NULL || $today->close > $now_in_minutes)) {
      $status = 'open';
    }
  }

  return $status;
}
