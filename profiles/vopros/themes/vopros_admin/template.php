<?php

/**
 * Imlements template_preprocess_views_field().
 */
function vopros_admin_preprocess_views_view_field(&$vars) {
  $view = $vars['view'];

  // Need to customize the question list a bit
  if ($view->name == 'vopros_question_list') {
    // Add icon on question status list, if the question has been reactivated by mail.
    if (
      $vars['field']->field == 'question_status' &&
      !empty($vars['row']->vopros_question_question_status_reason) &&
      $vars['row']->vopros_question_question_status_reason == 'reactivated by email'
    ) {
      $path = drupal_get_path('theme', 'vopros_admin');
      $vars['output'] .= ' ' . theme('image', array('path' => $path . '/images/mail_icon.png'));
    }
  }
}
