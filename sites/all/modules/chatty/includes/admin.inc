<?php

module_load_include('inc', 'chatty', 'includes/helpers');

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
  $form['chatty_hours'] = array(
    '#title' => t('Opening hours'),
    '#theme' => 'chatty_admin_hours',
    '#theme_wrappers' => array('form_element'),
    '#description' => t('Opening and closing hours for each day of the week, in the format HH:MM. If both opening and closing hours is unset for a given day, the chat is closed on that day.'),
    '#tree' => TRUE,
  );

  $days = array(
    t('Monday'),
    t('Tuesday'),
    t('Wednesday'),
    t('Thursday'),
    t('Friday'),
    t('Saturday'),
    t('Sunday'),
  );

  $form['chatty_hours']['open'] = array(
    '#theme_wrappers' => array('form_element'),
    '#title' => t('Opens'),
  );

  $form['chatty_hours']['close'] = array(
    '#theme_wrappers' => array('form_element'),
    '#title' => t('Closes'),
  );

  // Saved as JSON in the variable, so that the JS server can parse it.
  // Note that monday = 1.
  $hours = json_decode(variable_get('chatty_hours', ''), TRUE);

  foreach ($days as $day_num => $name) {
    $day_num += 1;

    foreach (array('open', 'close') as $state) {
      $default_value = isset($hours[$day_num][$state]) ?
        floor($hours[$day_num][$state] / 60) . ':' .
        sprintf("%02d", $hours[$day_num][$state] % 60) :
        '';

      $form['chatty_hours'][$state][$day_num] = array(
        '#type' => 'textfield',
        '#title' => $name,
        '#default_value' => $default_value,
        '#size' => 5,
        '#maxlength' => 5,
      );
    }
  }

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

/**
 * Validation for the settings form.
 */
function chatty_setting_form_validate($form, &$form_state) {
  $hours = array();

  // Re-order the chatty_hours variable to a format easier to work with.
  for ($day = 1; $day < 8; $day++) {
    foreach (array('open', 'close') as $state) {
      $value = $form_state['values']['chatty_hours'][$state][$day];
      if (empty($value)) {
        $value = NULL;
      }
      elseif (preg_match('/^(\d{1,2}):(\d{2})$/', $value, $rx)) {
        // Save time as minutes past midnight.
        $value = ($rx[1] * 60) + $rx[2];
      }
      else {
        form_error($form['chatty_hours'][$state][$day], t('Invalid time.'));
      }
      $hours[$day][$state] = $value;
    }
  }

  form_set_value($form['chatty_hours'], json_encode($hours), $form_state);
}

/**
 * Renders the opening hours into a table.
 */
function theme_chatty_admin_hours($variables) {
  $rows = array();

  foreach (element_children($variables['elements']) as $state) {
    $row = array();
    $header = array('');

    foreach (element_children($variables['elements'][$state]) as $key) {
      // Copy the label to the header. This avoids having to duplicate the
      // days.
      $header[] = $variables['elements'][$state][$key]['#title'];
      $variables['elements'][$state][$key]['#title_display'] = 'invisible';
      $row[] = drupal_render($variables['elements'][$state][$key]);
    }

    // Prepend the row header, now that the #children of the element has been
    // printed.
    array_unshift($row, drupal_render($variables['elements'][$state]));
    $rows[] = $row;
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}
