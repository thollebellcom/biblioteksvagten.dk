<?php
/**
 * @file
 * vopros_services.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function vopros_service_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'vopros_service_forwarded_question_list';
  $view->description = 'Used to display forwarded questions';
  $view->tag = 'default';
  $view->base_table = 'vopros_question';
  $view->human_name = 'Forwarded question list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Forwarded questions list';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    5 => '5',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Anvend';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Nulstil';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorter efter';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Poster pr side';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'question_id' => 'question_id',
    'question_status_reason' => 'question_status_reason',
    'question_title' => 'question_title',
    'client_id' => 'client_id',
    'question_status' => 'question_status',
    'question_deadline_timestamp' => 'question_deadline_timestamp',
    'changed' => 'changed',
    'created' => 'created',
    'label' => 'label',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'question_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'question_status_reason' => array(
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
    'client_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
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
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'label' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Sidefod: Spørgsmål: Views Count */
  $handler->display->display_options['footer']['views_count']['id'] = 'views_count';
  $handler->display->display_options['footer']['views_count']['table'] = 'vopros_question';
  $handler->display->display_options['footer']['views_count']['field'] = 'views_count';
  /* Forbindelse: Spørgsmål: Kommentar */
  $handler->display->display_options['relationships']['feedback_question_id']['id'] = 'feedback_question_id';
  $handler->display->display_options['relationships']['feedback_question_id']['table'] = 'vopros_question';
  $handler->display->display_options['relationships']['feedback_question_id']['field'] = 'feedback_question_id';
  $handler->display->display_options['relationships']['feedback_question_id']['label'] = 'spørgsmål';
  /* Forbindelse: Vopros Service forwarded questions.: Client forwarded to */
  $handler->display->display_options['relationships']['client_id_1']['id'] = 'client_id_1';
  $handler->display->display_options['relationships']['client_id_1']['table'] = 'vopros_service_question';
  $handler->display->display_options['relationships']['client_id_1']['field'] = 'client_id';
  $handler->display->display_options['relationships']['client_id_1']['label'] = 'Client';
  /* Felt: Spørgsmål: Spørgsmål ID */
  $handler->display->display_options['fields']['question_id']['id'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_id']['field'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['question_id']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['question_id']['separator'] = '';
  /* Felt: Spørgsmål: Question_status_reason */
  $handler->display->display_options['fields']['question_status_reason']['id'] = 'question_status_reason';
  $handler->display->display_options['fields']['question_status_reason']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_status_reason']['field'] = 'question_status_reason';
  $handler->display->display_options['fields']['question_status_reason']['exclude'] = TRUE;
  /* Felt: Spørgsmål: Question_title */
  $handler->display->display_options['fields']['question_title']['id'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_title']['field'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['label'] = 'Title';
  $handler->display->display_options['fields']['question_title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['question_title']['alter']['path'] = 'admin/vopros/questions/[question_id]';
  $handler->display->display_options['fields']['question_title']['hide_alter_empty'] = FALSE;
  /* Felt: Spørgsmål: Question client */
  $handler->display->display_options['fields']['client_id']['id'] = 'client_id';
  $handler->display->display_options['fields']['client_id']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['client_id']['field'] = 'client_id';
  $handler->display->display_options['fields']['client_id']['label'] = 'Received from';
  $handler->display->display_options['fields']['client_id']['element_label_colon'] = FALSE;
  /* Felt: Spørgsmål: Question_status */
  $handler->display->display_options['fields']['question_status']['id'] = 'question_status';
  $handler->display->display_options['fields']['question_status']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_status']['field'] = 'question_status';
  $handler->display->display_options['fields']['question_status']['label'] = 'Status';
  $handler->display->display_options['fields']['question_status']['hide_alter_empty'] = FALSE;
  /* Felt: Spørgsmål: Question_deadline_timestamp */
  $handler->display->display_options['fields']['question_deadline_timestamp']['id'] = 'question_deadline_timestamp';
  $handler->display->display_options['fields']['question_deadline_timestamp']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_deadline_timestamp']['field'] = 'question_deadline_timestamp';
  $handler->display->display_options['fields']['question_deadline_timestamp']['label'] = 'Deadline';
  $handler->display->display_options['fields']['question_deadline_timestamp']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['question_deadline_timestamp']['date_format'] = 'vopros_question_deadline';
  /* Felt: Spørgsmål: Changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Felt: Spørgsmål: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Oprettet';
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Felt: Client: Etiket */
  $handler->display->display_options['fields']['label']['id'] = 'label';
  $handler->display->display_options['fields']['label']['table'] = 'vopros_question_client';
  $handler->display->display_options['fields']['label']['field'] = 'label';
  $handler->display->display_options['fields']['label']['relationship'] = 'client_id_1';
  $handler->display->display_options['fields']['label']['label'] = 'Forwarded to';
  /* Filterkriterie: Spørgsmål: Question_status */
  $handler->display->display_options['filters']['question_status']['id'] = 'question_status';
  $handler->display->display_options['filters']['question_status']['table'] = 'vopros_question';
  $handler->display->display_options['filters']['question_status']['field'] = 'question_status';
  $handler->display->display_options['filters']['question_status']['value'] = array(
    'new' => 'new',
    'active' => 'active',
    'assigned' => 'assigned',
    'answered' => 'answered',
    'closed' => 'closed',
  );
  $handler->display->display_options['filters']['question_status']['group'] = 1;
  $handler->display->display_options['filters']['question_status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['question_status']['expose']['operator_id'] = 'question_status_op';
  $handler->display->display_options['filters']['question_status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['question_status']['expose']['operator'] = 'question_status_op';
  $handler->display->display_options['filters']['question_status']['expose']['identifier'] = 'question_status';
  $handler->display->display_options['filters']['question_status']['expose']['remember'] = TRUE;
  /* Filterkriterie: Spørgsmål: Redaktion (vopros_editorial) */
  $handler->display->display_options['filters']['vopros_editorial_tid']['id'] = 'vopros_editorial_tid';
  $handler->display->display_options['filters']['vopros_editorial_tid']['table'] = 'field_data_vopros_editorial';
  $handler->display->display_options['filters']['vopros_editorial_tid']['field'] = 'vopros_editorial_tid';
  $handler->display->display_options['filters']['vopros_editorial_tid']['group'] = 1;
  $handler->display->display_options['filters']['vopros_editorial_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_editorial_tid']['expose']['operator_id'] = 'vopros_editorial_tid_op';
  $handler->display->display_options['filters']['vopros_editorial_tid']['expose']['label'] = 'with the editorial';
  $handler->display->display_options['filters']['vopros_editorial_tid']['expose']['operator'] = 'vopros_editorial_tid_op';
  $handler->display->display_options['filters']['vopros_editorial_tid']['expose']['identifier'] = 'vopros_editorial_tid';
  $handler->display->display_options['filters']['vopros_editorial_tid']['expose']['remember'] = TRUE;
  /* Filterkriterie: Spørgsmål: Question client */
  $handler->display->display_options['filters']['client_id']['id'] = 'client_id';
  $handler->display->display_options['filters']['client_id']['table'] = 'vopros_question';
  $handler->display->display_options['filters']['client_id']['field'] = 'client_id';
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
  /* Filterkriterie: Vopros Service forwarded questions.: Direction of forward */
  $handler->display->display_options['filters']['direction']['id'] = 'direction';
  $handler->display->display_options['filters']['direction']['table'] = 'vopros_service_question';
  $handler->display->display_options['filters']['direction']['field'] = 'direction';
  $handler->display->display_options['filters']['direction']['group'] = 1;
  $handler->display->display_options['filters']['direction']['exposed'] = TRUE;
  $handler->display->display_options['filters']['direction']['expose']['operator_id'] = 'direction_op';
  $handler->display->display_options['filters']['direction']['expose']['label'] = 'Direction of forward';
  $handler->display->display_options['filters']['direction']['expose']['operator'] = 'direction_op';
  $handler->display->display_options['filters']['direction']['expose']['identifier'] = 'direction';
  $handler->display->display_options['filters']['direction']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filterkriterie: Vopros Service forwarded questions.: Type of forward */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'vopros_service_question';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type of forward';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: List */
  $handler = $view->new_display('page', 'List', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Anvend';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Nulstil';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorter efter';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'admin/vopros/questions/forwarded';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Forwarded';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'Questions';
  $handler->display->display_options['tab_options']['description'] = 'Display a list of active questions';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['vopros_service_forwarded_question_list'] = array(
    t('Master'),
    t('Forwarded questions list'),
    t('mere'),
    t('Anvend'),
    t('Nulstil'),
    t('Sorter efter'),
    t('Asc'),
    t('Desc'),
    t('Poster pr side'),
    t('- Alle -'),
    t('Forskydning'),
    t('« første'),
    t('‹ forrige'),
    t('næste ›'),
    t('sidste »'),
    t('spørgsmål'),
    t('Client'),
    t('Spørgsmål ID'),
    t('.'),
    t('Question_status_reason'),
    t('Title'),
    t('Received from'),
    t('Status'),
    t('Deadline'),
    t('Updated'),
    t('Oprettet'),
    t('Forwarded to'),
    t('with the editorial'),
    t('Direction of forward'),
    t('Type of forward'),
    t('List'),
  );

  $export['vopros_service_forwarded_question_list'] = $view;

  return $export;
}
