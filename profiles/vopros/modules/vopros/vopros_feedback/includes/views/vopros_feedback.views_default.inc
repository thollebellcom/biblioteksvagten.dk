<?php

/**
 * Implements hook_views_default_views().
 */
function vopros_feedback_views_default_views() {
  $views = array();

  // Feedback page, display the feedback given to a user.
  $view = new view();
  $view->name = 'vopros_feedback_user_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'vopros_feedback';
  $view->human_name = 'vopros_feedback_user_list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'All Feedback';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access feedback';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Nulstil';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorter efter';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Poster pr side';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'feedback_id' => 'feedback_id',
    'email_id' => 'email_id',
    'question_id' => 'question_id',
    'question_title' => 'question_title',
    'nothing' => 'nothing',
    'vopros_feedback_rating' => 'vopros_feedback_rating',
    'feedback_content' => 'feedback_content',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'feedback_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'email_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'question_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'question_title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
    ),
    'vopros_feedback_rating' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'feedback_content' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  /* Relationship: Feedback: Email_id */
  $handler->display->display_options['relationships']['email_id']['id'] = 'email_id';
  $handler->display->display_options['relationships']['email_id']['table'] = 'vopros_feedback';
  $handler->display->display_options['relationships']['email_id']['field'] = 'email_id';
  /* Relationship: Email: Question_id */
  $handler->display->display_options['relationships']['question_id']['id'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['question_id']['field'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['question_id']['label'] = 'spørgsmål';
  /* Field: Feedback: Feedback ID */
  $handler->display->display_options['fields']['feedback_id']['id'] = 'feedback_id';
  $handler->display->display_options['fields']['feedback_id']['table'] = 'vopros_feedback';
  $handler->display->display_options['fields']['feedback_id']['field'] = 'feedback_id';
  $handler->display->display_options['fields']['feedback_id']['label'] = '';
  $handler->display->display_options['fields']['feedback_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['feedback_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['feedback_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['feedback_id']['separator'] = '';
  /* Field: Email: Email ID */
  $handler->display->display_options['fields']['email_id']['id'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['email_id']['field'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['label'] = '';
  $handler->display->display_options['fields']['email_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['email_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['email_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['email_id']['separator'] = '';
  /* Field: Email: Question_id */
  $handler->display->display_options['fields']['question_id']['id'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['question_id']['field'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['question_id']['label'] = '';
  $handler->display->display_options['fields']['question_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['question_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['question_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['question_id']['separator'] = '';
  /* Field: Question: Question_title */
  $handler->display->display_options['fields']['question_title']['id'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_title']['field'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['question_title']['label'] = 'Question';
  $handler->display->display_options['fields']['question_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['question_title']['alter']['path'] = 'admin/vopros/questions/[question_id]';
  $handler->display->display_options['fields']['question_title']['hide_alter_empty'] = FALSE;
  /* Field: Answer link (link to email) */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Answer link (link to email)';
  $handler->display->display_options['fields']['nothing']['label'] = 'Answer';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'See answer sent to user';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/vopros/emails/[email_id]';
  /* Field: feedback: Vurdering */
  $handler->display->display_options['fields']['vopros_feedback_rating']['id'] = 'vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['table'] = 'field_data_vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['field'] = 'vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['vopros_feedback_rating']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['settings'] = array(
    'expose' => 0,
    'feedback_enable' => 0,
    'style' => 'average',
    'text' => 'average',
  );
  /* Field: Feedback: Feedback_content */
  $handler->display->display_options['fields']['feedback_content']['id'] = 'feedback_content';
  $handler->display->display_options['fields']['feedback_content']['table'] = 'vopros_feedback';
  $handler->display->display_options['fields']['feedback_content']['field'] = 'feedback_content';
  $handler->display->display_options['fields']['feedback_content']['label'] = 'Feedback';
  $handler->display->display_options['fields']['feedback_content']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['feedback_content']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['feedback_content']['hide_alter_empty'] = FALSE;
  /* Sort criterion: Email: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'vopros_email';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'email_id';
  /* Filter criterion: feedback: Vurdering (vopros_feedback_rating:rating) */
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['id'] = 'vopros_feedback_rating_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['table'] = 'field_data_vopros_feedback_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['field'] = 'vopros_feedback_rating_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['operator_id'] = 'vopros_feedback_rating_rating_op';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['label'] = 'User rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['operator'] = 'vopros_feedback_rating_rating_op';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['identifier'] = 'vopros_feedback_rating_rating';

  /* Display: User feedback */
  $handler = $view->new_display('page', 'User feedback', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Feedback';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Feedback: Email_id */
  $handler->display->display_options['relationships']['email_id']['id'] = 'email_id';
  $handler->display->display_options['relationships']['email_id']['table'] = 'vopros_feedback';
  $handler->display->display_options['relationships']['email_id']['field'] = 'email_id';
  /* Relationship: Email: Question_id */
  $handler->display->display_options['relationships']['question_id']['id'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['question_id']['field'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['question_id']['label'] = 'spørgsmål';
  /* Relationship: Email: Answer_id */
  $handler->display->display_options['relationships']['answer_id']['id'] = 'answer_id';
  $handler->display->display_options['relationships']['answer_id']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['answer_id']['field'] = 'answer_id';
  $handler->display->display_options['relationships']['answer_id']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['answer_id']['required'] = TRUE;
  /* Relationship: Email: Uid */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['relationship'] = 'uid';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'vopros_user_librarian' => 'vopros_user_librarian',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Feedback: Feedback ID */
  $handler->display->display_options['fields']['feedback_id']['id'] = 'feedback_id';
  $handler->display->display_options['fields']['feedback_id']['table'] = 'vopros_feedback';
  $handler->display->display_options['fields']['feedback_id']['field'] = 'feedback_id';
  $handler->display->display_options['fields']['feedback_id']['label'] = '';
  $handler->display->display_options['fields']['feedback_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['feedback_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['feedback_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['feedback_id']['separator'] = '';
  /* Field: Email: Email ID */
  $handler->display->display_options['fields']['email_id']['id'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['email_id']['field'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['label'] = '';
  $handler->display->display_options['fields']['email_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['email_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['email_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['email_id']['separator'] = '';
  /* Field: Email: Question_id */
  $handler->display->display_options['fields']['question_id']['id'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['question_id']['field'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['question_id']['label'] = '';
  $handler->display->display_options['fields']['question_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['question_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['question_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['question_id']['separator'] = '';
  /* Field: Question: Question_title */
  $handler->display->display_options['fields']['question_title']['id'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_title']['field'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['question_title']['label'] = 'Question';
  $handler->display->display_options['fields']['question_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['question_title']['alter']['path'] = 'admin/vopros/questions/[question_id]';
  $handler->display->display_options['fields']['question_title']['hide_alter_empty'] = FALSE;
  /* Field: Answer link (link to email) */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Answer link (link to email)';
  $handler->display->display_options['fields']['nothing']['label'] = 'Answer';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'See answer sent to user';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/vopros/emails/[email_id]';
  /* Field: feedback: Vurdering */
  $handler->display->display_options['fields']['vopros_feedback_rating']['id'] = 'vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['table'] = 'field_data_vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['field'] = 'vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['vopros_feedback_rating']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['settings'] = array(
    'expose' => 0,
    'feedback_enable' => 0,
    'style' => 'average',
    'text' => 'average',
  );
  /* Field: Feedback: Feedback_content */
  $handler->display->display_options['fields']['feedback_content']['id'] = 'feedback_content';
  $handler->display->display_options['fields']['feedback_content']['table'] = 'vopros_feedback';
  $handler->display->display_options['fields']['feedback_content']['field'] = 'feedback_content';
  $handler->display->display_options['fields']['feedback_content']['label'] = 'Feedback';
  $handler->display->display_options['fields']['feedback_content']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['feedback_content']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['feedback_content']['hide_alter_empty'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Field: Email: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Email: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'vopros_email';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'email_id';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['granularity'] = 'minute';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: feedback: Vurdering (vopros_feedback_rating:rating) */
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['id'] = 'vopros_feedback_rating_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['table'] = 'field_data_vopros_feedback_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['field'] = 'vopros_feedback_rating_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['operator_id'] = 'vopros_feedback_rating_rating_op';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['label'] = 'User rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['operator'] = 'vopros_feedback_rating_rating_op';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['identifier'] = 'vopros_feedback_rating_rating';
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  $handler->display->display_options['path'] = 'admin/vopros/feedback/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'User feedback';
  $handler->display->display_options['menu']['description'] = 'Display the feedback received by users';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Feedback';
  $handler->display->display_options['tab_options']['description'] = 'Display feedback given by users.';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  /* Display: Agency feedback */
  $handler = $view->new_display('page', 'Agency feedback', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Agency feedback';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer feedback';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Feedback: Email_id */
  $handler->display->display_options['relationships']['email_id']['id'] = 'email_id';
  $handler->display->display_options['relationships']['email_id']['table'] = 'vopros_feedback';
  $handler->display->display_options['relationships']['email_id']['field'] = 'email_id';
  /* Relationship: Email: Question_id */
  $handler->display->display_options['relationships']['question_id']['id'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['question_id']['field'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['question_id']['label'] = 'spørgsmål';
  /* Relationship: Email: Answer_id */
  $handler->display->display_options['relationships']['answer_id']['id'] = 'answer_id';
  $handler->display->display_options['relationships']['answer_id']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['answer_id']['field'] = 'answer_id';
  $handler->display->display_options['relationships']['answer_id']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['answer_id']['required'] = TRUE;
  /* Relationship: Email: Uid */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'bruger';
  $handler->display->display_options['relationships']['uid_1']['required'] = TRUE;
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['relationship'] = 'uid_1';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'vopros_user_librarian' => 'vopros_user_librarian',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Feedback: Feedback ID */
  $handler->display->display_options['fields']['feedback_id']['id'] = 'feedback_id';
  $handler->display->display_options['fields']['feedback_id']['table'] = 'vopros_feedback';
  $handler->display->display_options['fields']['feedback_id']['field'] = 'feedback_id';
  $handler->display->display_options['fields']['feedback_id']['label'] = '';
  $handler->display->display_options['fields']['feedback_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['feedback_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['feedback_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['feedback_id']['separator'] = '';
  /* Field: Email: Email ID */
  $handler->display->display_options['fields']['email_id']['id'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['email_id']['field'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['label'] = '';
  $handler->display->display_options['fields']['email_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['email_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['email_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['email_id']['separator'] = '';
  /* Field: Email: Question_id */
  $handler->display->display_options['fields']['question_id']['id'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['question_id']['field'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['question_id']['label'] = '';
  $handler->display->display_options['fields']['question_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['question_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['question_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['question_id']['separator'] = '';
  /* Field: Question: Question_title */
  $handler->display->display_options['fields']['question_title']['id'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_title']['field'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['question_title']['label'] = 'Question';
  $handler->display->display_options['fields']['question_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['question_title']['alter']['path'] = 'admin/vopros/questions/[question_id]';
  $handler->display->display_options['fields']['question_title']['hide_alter_empty'] = FALSE;
  /* Field: Answer link (link to email) */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Answer link (link to email)';
  $handler->display->display_options['fields']['nothing']['label'] = 'Answer';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'See answer sent to user';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/vopros/emails/[email_id]';
  /* Field: feedback: Vurdering */
  $handler->display->display_options['fields']['vopros_feedback_rating']['id'] = 'vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['table'] = 'field_data_vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['field'] = 'vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['vopros_feedback_rating']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['settings'] = array(
    'expose' => 0,
    'feedback_enable' => 0,
    'style' => 'average',
    'text' => 'average',
  );
  /* Field: Feedback: Feedback_content */
  $handler->display->display_options['fields']['feedback_content']['id'] = 'feedback_content';
  $handler->display->display_options['fields']['feedback_content']['table'] = 'vopros_feedback';
  $handler->display->display_options['fields']['feedback_content']['field'] = 'feedback_content';
  $handler->display->display_options['fields']['feedback_content']['label'] = 'Feedback';
  $handler->display->display_options['fields']['feedback_content']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['feedback_content']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['feedback_content']['hide_alter_empty'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid_1';
  /* Field: Email: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Email: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'vopros_email';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'email_id';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['granularity'] = 'minute';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: feedback: Vurdering (vopros_feedback_rating:rating) */
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['id'] = 'vopros_feedback_rating_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['table'] = 'field_data_vopros_feedback_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['field'] = 'vopros_feedback_rating_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['operator_id'] = 'vopros_feedback_rating_rating_op';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['label'] = 'User rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['operator'] = 'vopros_feedback_rating_rating_op';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['identifier'] = 'vopros_feedback_rating_rating';
  /* Filter criterion: Profile: Same library as current user */
  $handler->display->display_options['filters']['vopros_user_same_agency']['id'] = 'vopros_user_same_agency';
  $handler->display->display_options['filters']['vopros_user_same_agency']['table'] = 'field_data_vopros_user_library';
  $handler->display->display_options['filters']['vopros_user_same_agency']['field'] = 'vopros_user_same_agency';
  $handler->display->display_options['filters']['vopros_user_same_agency']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_same_agency']['value'] = '1';
  $handler->display->display_options['path'] = 'admin/vopros/feedback/agency';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Agency feedback';
  $handler->display->display_options['menu']['description'] = 'Display the feedback received by users in your agency';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Feedback';
  $handler->display->display_options['tab_options']['description'] = 'Display feedback given by users.';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  /* Display: All feedbacks */
  $handler = $view->new_display('page', 'All feedbacks', 'page_2');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer feedback';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Feedback: Email_id */
  $handler->display->display_options['relationships']['email_id']['id'] = 'email_id';
  $handler->display->display_options['relationships']['email_id']['table'] = 'vopros_feedback';
  $handler->display->display_options['relationships']['email_id']['field'] = 'email_id';
  /* Relationship: Email: Question_id */
  $handler->display->display_options['relationships']['question_id']['id'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['question_id']['field'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['question_id']['label'] = 'spørgsmål';
  /* Relationship: Email: Answer_id */
  $handler->display->display_options['relationships']['answer_id']['id'] = 'answer_id';
  $handler->display->display_options['relationships']['answer_id']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['answer_id']['field'] = 'answer_id';
  $handler->display->display_options['relationships']['answer_id']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['answer_id']['required'] = TRUE;
  /* Relationship: Email: Uid */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'vopros_email';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'email_id';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['relationship'] = 'uid';
  $handler->display->display_options['relationships']['profile']['label'] = 'Profil';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'vopros_user_librarian' => 'vopros_user_librarian',
  );
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile_1']['id'] = 'profile_1';
  $handler->display->display_options['relationships']['profile_1']['table'] = 'users';
  $handler->display->display_options['relationships']['profile_1']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile_1']['relationship'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Feedback: Feedback ID */
  $handler->display->display_options['fields']['feedback_id']['id'] = 'feedback_id';
  $handler->display->display_options['fields']['feedback_id']['table'] = 'vopros_feedback';
  $handler->display->display_options['fields']['feedback_id']['field'] = 'feedback_id';
  $handler->display->display_options['fields']['feedback_id']['label'] = '';
  $handler->display->display_options['fields']['feedback_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['feedback_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['feedback_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['feedback_id']['separator'] = '';
  /* Field: Email: Email ID */
  $handler->display->display_options['fields']['email_id']['id'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['email_id']['field'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['email_id']['label'] = '';
  $handler->display->display_options['fields']['email_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['email_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['email_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['email_id']['separator'] = '';
  /* Field: Email: Question_id */
  $handler->display->display_options['fields']['question_id']['id'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['question_id']['field'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['question_id']['label'] = '';
  $handler->display->display_options['fields']['question_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['question_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['question_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['question_id']['separator'] = '';
  /* Field: Question: Question_title */
  $handler->display->display_options['fields']['question_title']['id'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_title']['field'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['question_title']['label'] = 'Question';
  $handler->display->display_options['fields']['question_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['question_title']['alter']['path'] = 'admin/vopros/questions/[question_id]';
  $handler->display->display_options['fields']['question_title']['hide_alter_empty'] = FALSE;
  /* Field: Answer link (link to email) */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Answer link (link to email)';
  $handler->display->display_options['fields']['nothing']['label'] = 'Answer';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'See answer sent to user';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/vopros/emails/[email_id]';
  /* Field: feedback: Vurdering */
  $handler->display->display_options['fields']['vopros_feedback_rating']['id'] = 'vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['table'] = 'field_data_vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['field'] = 'vopros_feedback_rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['vopros_feedback_rating']['click_sort_column'] = 'rating';
  $handler->display->display_options['fields']['vopros_feedback_rating']['settings'] = array(
    'expose' => 0,
    'feedback_enable' => 0,
    'style' => 'average',
    'text' => 'average',
  );
  /* Field: Feedback: Feedback_content */
  $handler->display->display_options['fields']['feedback_content']['id'] = 'feedback_content';
  $handler->display->display_options['fields']['feedback_content']['table'] = 'vopros_feedback';
  $handler->display->display_options['fields']['feedback_content']['field'] = 'feedback_content';
  $handler->display->display_options['fields']['feedback_content']['label'] = 'Feedback';
  $handler->display->display_options['fields']['feedback_content']['alter']['max_length'] = '300';
  $handler->display->display_options['fields']['feedback_content']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['feedback_content']['hide_alter_empty'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Navn';
  /* Field: Email: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'vopros_email';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'email_id';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Feedback: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'vopros_feedback';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: feedback: Vurdering (vopros_feedback_rating:rating) */
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['id'] = 'vopros_feedback_rating_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['table'] = 'field_data_vopros_feedback_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['field'] = 'vopros_feedback_rating_rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['operator_id'] = 'vopros_feedback_rating_rating_op';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['label'] = 'User rating';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['operator'] = 'vopros_feedback_rating_rating_op';
  $handler->display->display_options['filters']['vopros_feedback_rating_rating']['expose']['identifier'] = 'vopros_feedback_rating_rating';
  /* Filter criterion: Profile: Bibliotek (vopros_user_library) */
  $handler->display->display_options['filters']['vopros_user_library_value']['id'] = 'vopros_user_library_value';
  $handler->display->display_options['filters']['vopros_user_library_value']['table'] = 'field_data_vopros_user_library';
  $handler->display->display_options['filters']['vopros_user_library_value']['field'] = 'vopros_user_library_value';
  $handler->display->display_options['filters']['vopros_user_library_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_library_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['operator_id'] = 'vopros_user_library_value_op';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['label'] = 'Bibliotek ';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['operator'] = 'vopros_user_library_value_op';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['identifier'] = 'vopros_user_library_value';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['path'] = 'admin/vopros/feedback/list2';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Alle feedback';
  $handler->display->display_options['menu']['description'] = 'Display the feedback received by users';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Feedback';
  $handler->display->display_options['tab_options']['description'] = 'Display feedback given by users.';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['vopros_feedback_user_list'] = array(
    t('Master'),
    t('All Feedback'),
    t('mere'),
    t('Apply'),
    t('Nulstil'),
    t('Sorter efter'),
    t('Asc'),
    t('Desc'),
    t('Poster pr side'),
    t('- Alle -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('email'),
    t('spørgsmål'),
    t('.'),
    t('Question'),
    t('Answer'),
    t('See answer sent to user'),
    t('Vurdering'),
    t('Feedback'),
    t('User rating'),
    t('User feedback'),
    t('more'),
    t('answer'),
    t('user'),
    t('Profile'),
    t('Name'),
    t('Uid'),
    t('Agency feedback'),
    t('bruger'),
    t('All feedbacks'),
    t('Profil'),
    t('Navn'),
    t(','),
    t('Bibliotek '),
  );

  $views[$view->name] = $view;

  return $views;
}
