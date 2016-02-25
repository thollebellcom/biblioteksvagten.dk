<?php
/**
 * @file
 * vopros_public_question.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function vopros_public_question_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'vopros_question_published_list';
  $view->description = 'Used to display questions, to find the ones that can/should be answered';
  $view->tag = 'default';
  $view->base_table = 'vopros_public_question';
  $view->human_name = 'Published Question list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Public question list';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access questions';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Anvend';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Nulstil';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorter efter';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'question_id' => 'question_id',
    'question_title' => 'question_title',
    'subject_catagory' => 'subject_catagory',
    'question_status' => 'question_status',
    'question_deadline_timestamp' => 'question_deadline_timestamp',
    'changed' => 'changed',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'question_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'question_title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'subject_catagory' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'question_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'question_deadline_timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Public question: Question_id */
  $handler->display->display_options['relationships']['question_id']['id'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['table'] = 'vopros_public_question';
  $handler->display->display_options['relationships']['question_id']['field'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['required'] = TRUE;
  /* Field: Question: Question ID */
  $handler->display->display_options['fields']['question_id']['id'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_id']['field'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['question_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['question_id']['separator'] = '';
  /* Field: Question: Question_title */
  $handler->display->display_options['fields']['question_title']['id'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_title']['field'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['question_title']['label'] = 'Title';
  $handler->display->display_options['fields']['question_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['question_title']['alter']['path'] = 'admin/vopros/questions/[question_id]';
  $handler->display->display_options['fields']['question_title']['hide_alter_empty'] = FALSE;
  /* Field: Question: Subject */
  $handler->display->display_options['fields']['subject_catagory']['id'] = 'subject_catagory';
  $handler->display->display_options['fields']['subject_catagory']['table'] = 'field_data_subject_catagory';
  $handler->display->display_options['fields']['subject_catagory']['field'] = 'subject_catagory';
  $handler->display->display_options['fields']['subject_catagory']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['subject_catagory']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['subject_catagory']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['subject_catagory']['delta_offset'] = '0';
  /* Field: Question: Question_status */
  $handler->display->display_options['fields']['question_status']['id'] = 'question_status';
  $handler->display->display_options['fields']['question_status']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_status']['field'] = 'question_status';
  $handler->display->display_options['fields']['question_status']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['question_status']['label'] = 'Status';
  $handler->display->display_options['fields']['question_status']['hide_alter_empty'] = FALSE;
  /* Field: Question: Question_deadline_timestamp */
  $handler->display->display_options['fields']['question_deadline_timestamp']['id'] = 'question_deadline_timestamp';
  $handler->display->display_options['fields']['question_deadline_timestamp']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_deadline_timestamp']['field'] = 'question_deadline_timestamp';
  $handler->display->display_options['fields']['question_deadline_timestamp']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['question_deadline_timestamp']['label'] = 'Deadline';
  $handler->display->display_options['fields']['question_deadline_timestamp']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['question_deadline_timestamp']['date_format'] = 'vopros_question_deadline';
  /* Field: Question: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Question: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['relationship'] = 'question_id';
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Filter criterion: Question: Question_status */
  $handler->display->display_options['filters']['question_status']['id'] = 'question_status';
  $handler->display->display_options['filters']['question_status']['table'] = 'vopros_question';
  $handler->display->display_options['filters']['question_status']['field'] = 'question_status';
  $handler->display->display_options['filters']['question_status']['relationship'] = 'question_id';
  $handler->display->display_options['filters']['question_status']['value'] = array(
    'all' => 'all',
    'new' => 'new',
    'active' => 'active',
    'assigned' => 'assigned',
    'answered' => 'answered',
    'closed' => 'closed',
  );
  $handler->display->display_options['filters']['question_status']['group'] = 1;
  $handler->display->display_options['filters']['question_status']['expose']['operator_id'] = 'question_status_op';
  $handler->display->display_options['filters']['question_status']['expose']['label'] = 'Show all';
  $handler->display->display_options['filters']['question_status']['expose']['operator'] = 'question_status_op';
  $handler->display->display_options['filters']['question_status']['expose']['identifier'] = 'question_status';
  $handler->display->display_options['filters']['question_status']['expose']['remember'] = TRUE;
  /* Filter criterion: Question: Question_usage */
  $handler->display->display_options['filters']['question_usage']['id'] = 'question_usage';
  $handler->display->display_options['filters']['question_usage']['table'] = 'vopros_question';
  $handler->display->display_options['filters']['question_usage']['field'] = 'question_usage';
  $handler->display->display_options['filters']['question_usage']['relationship'] = 'question_id';
  $handler->display->display_options['filters']['question_usage']['group'] = 1;
  $handler->display->display_options['filters']['question_usage']['exposed'] = TRUE;
  $handler->display->display_options['filters']['question_usage']['expose']['operator_id'] = 'question_usage_op';
  $handler->display->display_options['filters']['question_usage']['expose']['label'] = 'Usage';
  $handler->display->display_options['filters']['question_usage']['expose']['operator'] = 'question_usage_op';
  $handler->display->display_options['filters']['question_usage']['expose']['identifier'] = 'question_usage';
  $handler->display->display_options['filters']['question_usage']['expose']['remember'] = TRUE;
  /* Filter criterion: Question: Question client */
  $handler->display->display_options['filters']['client_id']['id'] = 'client_id';
  $handler->display->display_options['filters']['client_id']['table'] = 'vopros_question';
  $handler->display->display_options['filters']['client_id']['field'] = 'client_id';
  $handler->display->display_options['filters']['client_id']['relationship'] = 'question_id';
  $handler->display->display_options['filters']['client_id']['group'] = 1;
  $handler->display->display_options['filters']['client_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['client_id']['expose']['operator_id'] = 'client_id_op';
  $handler->display->display_options['filters']['client_id']['expose']['label'] = 'Received from';
  $handler->display->display_options['filters']['client_id']['expose']['operator'] = 'client_id_op';
  $handler->display->display_options['filters']['client_id']['expose']['identifier'] = 'client_id';
  $handler->display->display_options['filters']['client_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: Question: Subject (subject_catagory) */
  $handler->display->display_options['filters']['subject_catagory_tid']['id'] = 'subject_catagory_tid';
  $handler->display->display_options['filters']['subject_catagory_tid']['table'] = 'field_data_subject_catagory';
  $handler->display->display_options['filters']['subject_catagory_tid']['field'] = 'subject_catagory_tid';
  $handler->display->display_options['filters']['subject_catagory_tid']['relationship'] = 'question_id';
  $handler->display->display_options['filters']['subject_catagory_tid']['group'] = 1;
  $handler->display->display_options['filters']['subject_catagory_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['subject_catagory_tid']['expose']['operator_id'] = 'subject_catagory_tid_op';
  $handler->display->display_options['filters']['subject_catagory_tid']['expose']['label'] = 'Subject';
  $handler->display->display_options['filters']['subject_catagory_tid']['expose']['operator'] = 'subject_catagory_tid_op';
  $handler->display->display_options['filters']['subject_catagory_tid']['expose']['identifier'] = 'subject_catagory_tid';

  /* Display: Public questions */
  $handler = $view->new_display('page', 'Public questions', 'page_1');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Public question: Question_id */
  $handler->display->display_options['relationships']['question_id']['id'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['table'] = 'vopros_public_question';
  $handler->display->display_options['relationships']['question_id']['field'] = 'question_id';
  $handler->display->display_options['relationships']['question_id']['required'] = TRUE;
  $handler->display->display_options['path'] = 'admin/vopros/questions/published-list';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Published list';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['vopros_question_published_list'] = array(
    t('Master'),
    t('Public question list'),
    t('more'),
    t('Anvend'),
    t('Nulstil'),
    t('Sorter efter'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('question'),
    t('Question ID'),
    t('.'),
    t('Title'),
    t('Subject'),
    t('Status'),
    t('Deadline'),
    t('Updated'),
    t('Created'),
    t('Show all'),
    t('Usage'),
    t('Editorial'),
    t('Received from'),
    t('Public questions'),
  );
  $export['vopros_question_published_list'] = $view;

  return $export;
}
