<?php

module_load_include('inc', 'chatty', 'includes/helpers');

// Look at: https://www.drupal.org/forum/support/module-development-and-code-questions/2012-01-31/incoming-http-post

/**
 * Create question callback.
 *
 * Opens a new unassigned question.
 *
 * Params:
 * - agencyId: required
 * - agencyMail: required
 * - authorName: required
 * - authorEmail: required
 * - subject: required
 * - url: required
 */
function create_question_callback() {
  $agencyId = $_POST['agencyId'];
  $agencyMail = $_POST['agencyMail'];
  $authorName = $_POST['authorName'];
  $authorEmail = $_POST['authorEmail'];
  $subject = $_POST['subject'];
  $url = $_POST['url'];

  // Validate params.
  if (!$agencyId) {
    return 'An agency ID is required.';
  }
  if (!$authorName) {
    return 'A author name is required.';
  }
  if (!$authorEmail) {
    return 'A author email is required.';
  }
  if (!$subject) {
    return 'A subject is required.';
  }
  if (!$url) {
    return 'An url is required.';
  }

  // Create question in database.
  $questionId = db_insert('chatty_questions')
    ->fields(array(
      'agencyId' => $agencyId,
      'agencyMail' => $agencyMail,
      'authorName' => $authorName,
      'authorEmail' => $authorEmail,
      'subject' => $subject,
      'url' => $url,
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
 * - keepConsultant: optional
 * - title: optional
 */
function close_question_callback() {
  $questionId = $_POST['questionId'];
  $reason = $_POST['reason'];
  $keepConsultant = ($_POST['keepConsultant'] === 'false') ? false : true;
  $title = $_POST['title'];

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
  $updateArray = array(
    'reason' => $reason,
    'status' => 'complete',
    'updatedAt' => REQUEST_TIME,
  );

  if (!empty($keepConsultant)) {
    $updateArray['keepConsultant'] = $keepConsultant;
  }
  if (!empty($title)) {
    $updateArray['title'] = $title;
  }

  db_update('chatty_questions')
    ->fields($updateArray)
    ->condition('id', $questionId)
    ->execute();

  // Query the database, returning the updated question.
  $question = chatty_load_question($questionId);

  // Create a vopros question.
  $messages = chatty_load_messages($questionId);
  $messages_in_plain_text = _render_messages_in_plain_text($messages);

  _create_vopros_question(
    $reason,
    $question->subject,
    $question->authorName,
    $question->authorEmail,
    $messages_in_plain_text,
    $question->url,
    $question->agencyMail,
    $question->source,
    $keepConsultant,
    $title,
    $question->consultant
  );

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
