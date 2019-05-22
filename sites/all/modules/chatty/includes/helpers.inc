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
