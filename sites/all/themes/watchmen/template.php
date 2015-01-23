<?php

/**
 * @file
 * Watchmen template functions.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function watchmen_form_vopros_embed_question_alter(&$form, $form_state) {
  drupal_add_css('//maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css', array('type' => 'external'));

  // Add angle icon to answer preference items.
  if (isset($form['user_answer_preference'])) {
    // Hide the answer preference label visually.
    $form['user_answer_preference']['#title_display'] = 'invisible';

    foreach ($form['user_answer_preference']['#options'] as $key => &$val) {
      $val = '<span>' . $val . '</span><i class="fa fa-2x fa-fw fa-angle-right"></i>';
    }

    $form['user_answer_preference']['#attached']['js'][] = drupal_get_path('theme', 'watchmen') . '/js/vopros_chat_status.js';
  }
}

/**
 * Implements hook_vopros_embed_tab_style_alter().
 */
function watchmen_vopros_embed_tab_style_alter(&$path) {
  $path[] = '//maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css';
  $path[] = url(drupal_get_path('theme', 'watchmen') . '/css/ask_vopros.css', array('absolute' => TRUE));
}
