<?php
/**
 * @file
 * Administrative pages for chatty.
 */

/**
 * Form callback.
 *
 * Settings form.
 */
function chatty_setting_form($form, &$form_state) {

  // Chat assigned.
  $form['chatty_assigned_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Chat assigned message'),
    '#description' => t('Text shown when an operator assigns the chat to himself.<br>You can use the following tokens: %consultant_name'),
    '#default_value' => variable_get('chatty_assigned_message', 'The chat was assigned to %consultant_name.'),
  );

  // Chat reopened.
  $form['chatty_reopened_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Chat reopened message'),
    '#description' => t('Text shown when the chat is reopened.'),
    '#default_value' => variable_get('chatty_reopened_message', 'The chat was reopened.'),
  );

  // Chat pending.
  $form['chatty_pending_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Chat pending message'),
    '#description' => t('Text shown when the chat is pending.'),
    '#default_value' => variable_get('chatty_pending_message', 'Waiting for an operator...'),
  );

  // Chat was closed by admin.
  $form['chatty_closed_by_admin_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Chat closed by admin message'),
    '#description' => t('Text shown when the chat is closed by the admin.<br>You can use the following tokens: %consultant_name'),
    '#default_value' => variable_get('chatty_closed_by_admin_message', 'The chat was closed by %consultant_name.'),
  );

  // Standard messages.
  $form['chatty_standard_messages'] = array(
    '#type' => 'textarea',
    '#title' => t('Standard messages'),
    '#description' => t('Standard messages in group|title|message format. Group can be left out.'),
    '#default_value' => variable_get('chatty_standard_messages', ''),
  );

  return system_settings_form($form);
}
