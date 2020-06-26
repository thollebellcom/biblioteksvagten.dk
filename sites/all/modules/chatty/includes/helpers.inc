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
  $query->addField('chatty_questions', 'url');
  $query->addField('chatty_questions', 'agencyId');
  $query->addField('chatty_questions', 'agencyMail');
  $query->addField('chatty_questions', 'lastHeartbeatAt');
  $query->addField('chatty_questions', 'createdAt');
  $query->addField('chatty_questions', 'updatedAt');

  $query->condition('chatty_questions.id', $questionId, '=');

  $result = $query->execute()->fetchObject();

  // Grab the client by the agency ID.
  $client = vopros_question_client_load_by_agency($result->agencyId);
  unset($result->agencyId);

  if ($client) {
    $result->source = $client->label;
  }
  else {
    $result->source = t('Undefined');
  }

  return $result;
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

/**
 * Create vopros question.
 *
 * Just a helper wrapper.
 *
 * Params:
 * - $reason: required
 * - $subject: required
 * - $name: required
 * - $email: required
 * - $messages: required
 * - $fromUrl: required
 * - $agencyMail: required
 * - $keepConsultant: optional
 * - $title: optional
 * - $consultantUid: optional
 */
function _create_vopros_question($reason, $subject, $name, $email, $messages, $fromUrl, $agencyMail, $keepConsultant, $title, $consultantUid) {
  $default_values = array(
    'user_answer_preference' => 'mail',
    'channel' => 'chat',
    'client_id' => 52,
    'question_content' => t('Chat log:') . "\n" . $subject . "\n" . $messages,
    'user_name' => $name,
    'user_email' => $email,
    'question_usage' => 'other',
    'channel_data' => array(
      'from_url' => $fromUrl,
      'site_email' => $agencyMail,
    ),
  );

  if (!empty($title)) {
    $default_values['question_title'] = trim($title);
  }

  // Spam.
  if ($reason === 'spam') {
    $default_values['question_status'] = 'closed';
    $default_values['question_status_reason'] = 'spam';
  }

  // Answered.
  if ($reason === 'answered') {
    $default_values['question_title'] = t('Answered chat question');
    $default_values['question_status'] = 'answered';
    $default_values['user_answer_preference'] = 'chat';
  }

  // Answer later.
  if ($reason === 'later') {
    $default_values['channel'] = 'mail';
    $default_values['question_status'] = 'active';

    if ($keepConsultant) {
      $default_values['uid'] = $consultantUid;
      $default_values['question_status'] = 'assigned';
    }
    else {
      // Release the question.
      $default_values['uid'] = 0;
    }

    // The question is still open, change the answer preference to allow editors
    // to contact the user by mail later.
    $default_values['user_answer_preference'] = 'mail';
  }

  $question = vopros_question_new($default_values);

  $question->save();
}

/**
 * Render a chat log in plain text.
 */
function _render_messages_in_plain_text($messages) {
  // Same as drupal_get_user_timezone() uses to get the system default.
  $timezone = variable_get('date_default_timezone', @date_default_timezone_get());
  $plain = array();

  foreach ($messages as $message) {
    $sentFrom = 'Unknown';

    if ($message->sentFrom == 'admin') {
      $sentFrom = t('Operator');
    }
    if ($message->sentFrom == 'user') {
      $sentFrom = t('Asker');
    }
    if ($message->sentFrom == 'system') {
      $sentFrom = t('System');
    }

    $plain[] = format_date($message->createdAt, 'custom', 'G:i', $timezone) . ' - ' . $sentFrom . ': ' . $message->text;
  }

  return implode("\n", $plain);
}
