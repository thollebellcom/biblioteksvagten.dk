<?php

module_load_include('inc', 'chatty', 'includes/helpers');

// Look at: https://www.drupal.org/forum/support/module-development-and-code-questions/2012-01-31/incoming-http-post

/**
 * Create question callback.
 *
 * Opens a new unassigned question.
 *
 * Params:
 * - authorName: required
 * - authorEmail: required
 * - subject: required
 */
function create_question_callback() {
  $authorName = $_POST['authorName'];
  $authorEmail = $_POST['authorEmail'];
  $subject = $_POST['subject'];

  // Validate params.
  if (!$authorName) {
    return 'A author name is required.';
  }
  if (!$authorEmail) {
    return 'A author email is required.';
  }
  if (!$subject) {
    return 'A subject is required.';
  }

  // Create question in database.
  $questionId = db_insert('chatty_questions')
    ->fields(array(
      'authorName' => $authorName,
      'authorEmail' => $authorEmail,
      'subject' => $subject,
      'createdAt' => REQUEST_TIME,
      'updatedAt' => REQUEST_TIME,
      'lastHeartbeatAt' => REQUEST_TIME,
    ))
    ->execute();

  // Query the database, returning the created question.
  $question = chatty_load_question($questionId);

  return $question;
}

/**
 * Create message callback.
 *
 * Creates a message for a given question.
 *
 * Params:
 * - questionId: required
 * - text: required
 * - sentFrom: required
 */
function create_message_callback() {
  $questionId = $_POST['questionId'];
  $text = $_POST['text'];
  $sentFrom = $_POST['sentFrom'];

  // Validate params.
  if (!$questionId) {
    return 'A question ID is required.';
  }
  if (!$text) {
    return 'A text is required.';
  }
  if (!$sentFrom) {
    return 'A sent from is required.';
  }

  // Create message in database.
  $messageId = db_insert('chatty_messages')
    ->fields(array(
      'question' => $questionId,
      'text' => $text,
      'sentFrom' => $sentFrom,
      'createdAt' => REQUEST_TIME,
    ))
    ->execute();

  // Query the database, returning the created message.
  $message = chatty_load_message($messageId);

  return $message;
}

/**
 * Assign question callback.
 *
 * Assigns a question to a consultant and sets the question status to
 * "assigned".
 *
 * Params:
 * - questionId: required
 * - consultantId: required
 */
function assign_question_callback() {
  $questionId = $_POST['questionId'];
  $consultantId = $_POST['consultantId'];

  // Validate params.
  if (!$questionId) {
    return 'A question ID is required.';
  }
  if (!$consultantId) {
    return 'A consultant ID is required.';
  }

  // Update the database.
  db_update('chatty_questions')
    ->fields(array(
      'status' => 'assigned',
      'consultant' => $consultantId,
      'updatedAt' => REQUEST_TIME,
    ))
    ->condition('id', $questionId)
    ->execute();

  // Query the database, returning the updated question.
  $question = chatty_load_question($questionId);

  return $question;
}

/**
 * Close question callback.
 *
 * Sets the questions status to complete.
 *
 * Params:
 * - questionId: required
 * - reason: required
 */
function close_question_callback() {
  $questionId = $_POST['questionId'];
  $reason = $_POST['reason'];

  // Validate params.
  if (!$questionId) {
    return 'A question ID is required.';
  }
  if (!$reason) {
    return 'A reason is required.';
  }

  $allowed_reasons = array('spam', 'answered', 'later');
  if (!in_array($reason, $allowed_reasons)) {
    return 'An invalid reason was given.';
  }

  // Update the database.
  db_update('chatty_questions')
    ->fields(array(
      'reason' => $reason,
      'status' => 'complete',
      'updatedAt' => REQUEST_TIME,
    ))
    ->condition('id', $questionId)
    ->execute();

  // Query the database, returning the updated question.
  $question = chatty_load_question($questionId);

  // Create a vopros question.
  $messages = chatty_load_messages($questionId);
  $messages_in_plain_text = _render_messages_in_plain_text($messages);

  _create_vopros_question($reason, $question->subject, $question->authorName, $question->authorEmail, $messages_in_plain_text);

  return $question;
}

/**
 * Reopen question callback.
 *
 * Resets the questions status, and make it possible for other admins
 * to take over.
 *
 * Params:
 * - questionId: required
 */
function reopen_question_callback() {
  $questionId = $_POST['questionId'];

  // Validate params.
  if (!$questionId) {
    return 'A question ID is required.';
  }

  // Update the database.
  db_update('chatty_questions')
    ->fields(array(
      'status' => 'pending',
      'consultant' => NULL,
      'updatedAt' => REQUEST_TIME,
    ))
    ->condition('id', $questionId)
    ->execute();

  // Query the database, returning the updated question.
  $question = chatty_load_question($questionId);

  return $question;
}

/**
 * Question heartbeat callback.
 *
 * Sets a timestamp on the question for when the question
 * had a heartbeat by the client.
 *
 * Params:
 * - questionId: required
 */
function question_client_heartbeat_callback() {
  $questionId = $_POST['questionId'];

  // Validate params.
  if (!$questionId) {
    return 'A question ID is required.';
  }

  // Update the database.
  db_update('chatty_questions')
    ->fields(array(
      'lastHeartbeatAt' => REQUEST_TIME,
    ))
    ->condition('id', $questionId)
    ->execute();

  // Query the database, returning the updated question.
  $question = chatty_load_question($questionId);

  return $question;
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
 */
function _create_vopros_question($reason, $subject, $name, $email, $messages) {
  $default_values = array(
    'user_answer_preference' => 'chat',
    'channel' => 'chat',
    'client_id' => 52,
    'question_content' => t('Chat log:') . "\n" . $subject . "\n" . $messages,
    'user_name' => $name,
    'user_email' => $email,
  );

  // Spam.
  if ($reason === 'spam') {
    $default_values['question_status'] = 'closed';
    $default_values['question_status_reason'] = 'spam';
  }

  // Answered.
  if ($reason === 'answered') {
    $default_values['question_title'] = t('Answered chat question');
    $default_values['question_status'] = 'answered';
  }

  // Answer later.
  if ($reason === 'later') {
    $default_values['question_status'] = 'active';

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
