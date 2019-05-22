<?php

module_load_include('inc', 'chatty', 'includes/helpers');

/**
 * Get all questions callback.
 *
 * Params:
 * - statusType: required
 * - consultantId: nullable.
 *
 * Ex. /api/endpoint?statusType=pending&consultantId=123
 */
function get_questions_callback() {
  $statusType = $_GET['statusType'];
  $consultantId = (isset($_GET['consultantId']) ? $_GET['consultantId'] : NULL);

  // Validate parameters.
  if (!$statusType) {
    return 'A status type is required.';
  }
  if ($statusType != 'pending' && $statusType != 'assigned' && $statusType != 'complete') {
    return 'An invalid status type was given. Only pending, assigned and complete can be used.';
  }

  // Query the database.
  $query = db_select('chatty_questions');

  $query->addField('chatty_questions', 'id');
  $query->addField('chatty_questions', 'authorName');
  $query->addField('chatty_questions', 'authorEmail');
  $query->addField('chatty_questions', 'subject');
  $query->addField('chatty_questions', 'status');
  $query->addField('chatty_questions', 'consultant');
  $query->addField('chatty_questions', 'createdAt');
  $query->addField('chatty_questions', 'updatedAt');

  $query->condition('chatty_questions.status', $statusType, '=');

  // Filter only if a consultant ID is given. A null parameter (or no param)
  // does not filter on consultants.
  if ($consultantId) {
    $query->condition('chatty_questions.consultant', $consultantId, '=');
  }

  return $query->execute()->fetchAll();
}

/**
 * Get question callback.
 *
 * Params:
 * - questionId: required.
 *
 * Ex. /api/endpoint?questionId=123
 */
function get_question_callback() {
  $questionId = $_GET['questionId'];

  // Validate parameters.
  if (!$questionId) {
    return 'A question ID is required.';
  }

  // Query the database.
  $question = chatty_load_question($questionId);

  return $question;
}

/**
 * Get all messages callback.
 *
 * Params:
 * - questionId: required.
 *
 * Ex. /api/endpoint?questionId=123
 */
function get_messages_callback() {
  $questionId = $_GET['questionId'];

  // Validate parameters.
  if (!$questionId) {
    return 'A question ID is required.';
  }

  // Query the database.
  $messages = chatty_load_messages($questionId);

  return $messages;
}

/**
 * Get consultant name callback.
 *
 * Params:
 * - consultantId: required.
 *
 * Ex. /api/endpoint?consultantId=123
 */
function get_consultant_name_callback() {
  $consultantId = $_GET['consultantId'];

  // Validate parameters.
  if (!$consultantId) {
    return 'A consultant ID is required.';
  }

  // Load the user.
  $user = user_load($consultantId);
  if (!$user) {
    return 'Invalid data provided.';
  }

  // Get the name.
  $profile = profile2_load_by_user($user, 'vopros_user_librarian');
  if ($profile) {
    $name = vopros_user_profile_user_name($profile);
  }
  else {
    // Else fall back to username.
    $name = $user->name;
  }

  return $name;
}

/**
 * Get settings callback.
 */
function get_settings_callback() {
  $settings = array();

  // Messages.
  $settings['messages'] = array(
    'chatAssigned' => variable_get('chatty_assigned_message'),
    'chatClosedByAdmin' => variable_get('chatty_closed_by_admin_message'),
    'chatReopened' => variable_get('chatty_reopened_message'),
    'chatPending' => variable_get('chatty_pending_message'),
  );

  // Standard answers.
  $settings['standardAnswers'] = _convert_standard_messages(variable_get('chatty_standard_messages'));

  return $settings;
}

/**
 * Standard messages for editors.
 */
function _convert_standard_messages($text) {
  $messages = array();

  foreach (explode("\n", $text) as $line) {
    $parts = explode('|', trim($line));

    if (count($parts) > 2) {

      if (!empty($parts[0])) {
        $messages[$parts[0]][$parts[1]] = $parts[2];
      }
      else {
        $messages[$parts[1]] = $parts[2];
      }
    }
  }

  return $messages;
}
