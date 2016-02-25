<?php
/**
 * @file
 * vopros_user.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function vopros_user_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'vopros_user_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Vopros user list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Vopros user list';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer vopros';
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
    'name' => 'name',
    'vopros_user_library' => 'vopros_user_library',
    'vopros_user_first_name' => 'vopros_user_first_name',
    'vopros_user_last_name' => 'vopros_user_last_name',
    'mail' => 'mail',
    'vopros_user_phone_number' => 'vopros_user_phone_number',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'vopros_user_library' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'vopros_user_first_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'vopros_user_last_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'mail' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
    'vopros_user_phone_number' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
    ),
  );
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'vopros_user_librarian' => 'vopros_user_librarian',
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = 'User name';
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = FALSE;
  /* Field: Profile: Bibliotek */
  $handler->display->display_options['fields']['vopros_user_library']['id'] = 'vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['table'] = 'field_data_vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['field'] = 'vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_library']['hide_alter_empty'] = FALSE;
  /* Field: Profile: Fornavn */
  $handler->display->display_options['fields']['vopros_user_first_name']['id'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['field'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['relationship'] = 'profile';
  /* Field: Profile: Efternavn */
  $handler->display->display_options['fields']['vopros_user_last_name']['id'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['table'] = 'field_data_vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['field'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_last_name']['hide_alter_empty'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['mail']['link_to_user'] = 0;
  /* Field: Profile: Telefonnummer */
  $handler->display->display_options['fields']['vopros_user_phone_number']['id'] = 'vopros_user_phone_number';
  $handler->display->display_options['fields']['vopros_user_phone_number']['table'] = 'field_data_vopros_user_phone_number';
  $handler->display->display_options['fields']['vopros_user_phone_number']['field'] = 'vopros_user_phone_number';
  $handler->display->display_options['fields']['vopros_user_phone_number']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_phone_number']['hide_alter_empty'] = FALSE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
  );
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['filters']['uid_1']['table'] = 'users';
  $handler->display->display_options['filters']['uid_1']['field'] = 'uid';
  $handler->display->display_options['filters']['uid_1']['value'] = '';
  $handler->display->display_options['filters']['uid_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid_1']['expose']['operator_id'] = 'uid_1_op';
  $handler->display->display_options['filters']['uid_1']['expose']['label'] = 'User name';
  $handler->display->display_options['filters']['uid_1']['expose']['operator'] = 'uid_1_op';
  $handler->display->display_options['filters']['uid_1']['expose']['identifier'] = 'uid_1';
  /* Filter criterion: Profile: Fornavn (vopros_user_first_name) */
  $handler->display->display_options['filters']['vopros_user_first_name_value']['id'] = 'vopros_user_first_name_value';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['field'] = 'vopros_user_first_name_value';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['operator'] = 'starts';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_user_first_name_value']['expose']['operator_id'] = 'vopros_user_first_name_value_op';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['expose']['label'] = 'First name';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['expose']['operator'] = 'vopros_user_first_name_value_op';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['expose']['identifier'] = 'vopros_user_first_name_value';
  /* Filter criterion: Profile: Efternavn (vopros_user_last_name) */
  $handler->display->display_options['filters']['vopros_user_last_name_value']['id'] = 'vopros_user_last_name_value';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['table'] = 'field_data_vopros_user_last_name';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['field'] = 'vopros_user_last_name_value';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['operator'] = 'starts';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_user_last_name_value']['expose']['operator_id'] = 'vopros_user_last_name_value_op';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['expose']['label'] = 'Last name';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['expose']['operator'] = 'vopros_user_last_name_value_op';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['expose']['identifier'] = 'vopros_user_last_name_value';
  /* Filter criterion: Profile: Bibliotek (vopros_user_library) */
  $handler->display->display_options['filters']['vopros_user_library_value']['id'] = 'vopros_user_library_value';
  $handler->display->display_options['filters']['vopros_user_library_value']['table'] = 'field_data_vopros_user_library';
  $handler->display->display_options['filters']['vopros_user_library_value']['field'] = 'vopros_user_library_value';
  $handler->display->display_options['filters']['vopros_user_library_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_library_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['operator_id'] = 'vopros_user_library_value_op';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['label'] = 'Library';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['operator'] = 'vopros_user_library_value_op';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['identifier'] = 'vopros_user_library_value';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
  );
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['filters']['uid_1']['table'] = 'users';
  $handler->display->display_options['filters']['uid_1']['field'] = 'uid';
  $handler->display->display_options['filters']['uid_1']['value'] = '';
  $handler->display->display_options['filters']['uid_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid_1']['expose']['operator_id'] = 'uid_1_op';
  $handler->display->display_options['filters']['uid_1']['expose']['label'] = 'User name';
  $handler->display->display_options['filters']['uid_1']['expose']['operator'] = 'uid_1_op';
  $handler->display->display_options['filters']['uid_1']['expose']['identifier'] = 'uid_1';
  /* Filter criterion: Profile: Fornavn (vopros_user_first_name) */
  $handler->display->display_options['filters']['vopros_user_first_name_value']['id'] = 'vopros_user_first_name_value';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['field'] = 'vopros_user_first_name_value';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['operator'] = 'starts';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_user_first_name_value']['expose']['operator_id'] = 'vopros_user_first_name_value_op';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['expose']['label'] = 'First name';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['expose']['operator'] = 'vopros_user_first_name_value_op';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['expose']['identifier'] = 'vopros_user_first_name_value';
  /* Filter criterion: Profile: Efternavn (vopros_user_last_name) */
  $handler->display->display_options['filters']['vopros_user_last_name_value']['id'] = 'vopros_user_last_name_value';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['table'] = 'field_data_vopros_user_last_name';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['field'] = 'vopros_user_last_name_value';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['operator'] = 'starts';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_user_last_name_value']['expose']['operator_id'] = 'vopros_user_last_name_value_op';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['expose']['label'] = 'Last name';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['expose']['operator'] = 'vopros_user_last_name_value_op';
  $handler->display->display_options['filters']['vopros_user_last_name_value']['expose']['identifier'] = 'vopros_user_last_name_value';
  /* Filter criterion: Profile: Bibliotek (vopros_user_library) */
  $handler->display->display_options['filters']['vopros_user_library_value']['id'] = 'vopros_user_library_value';
  $handler->display->display_options['filters']['vopros_user_library_value']['table'] = 'field_data_vopros_user_library';
  $handler->display->display_options['filters']['vopros_user_library_value']['field'] = 'vopros_user_library_value';
  $handler->display->display_options['filters']['vopros_user_library_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_library_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['operator_id'] = 'vopros_user_library_value_op';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['label'] = 'Library';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['operator'] = 'vopros_user_library_value_op';
  $handler->display->display_options['filters']['vopros_user_library_value']['expose']['identifier'] = 'vopros_user_library_value';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    4 => '4',
    6 => '6',
    3 => '3',
  );
  $handler->display->display_options['filters']['rid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['rid']['expose']['operator_id'] = 'rid_op';
  $handler->display->display_options['filters']['rid']['expose']['label'] = 'Rolle';
  $handler->display->display_options['filters']['rid']['expose']['operator'] = 'rid_op';
  $handler->display->display_options['filters']['rid']['expose']['identifier'] = 'rid';
  $handler->display->display_options['filters']['rid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    4 => 0,
    6 => 0,
    3 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['rid']['expose']['reduce'] = TRUE;
  $handler->display->display_options['filters']['rid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['path'] = 'admin/vopros/users';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Users';
  $handler->display->display_options['menu']['description'] = 'View the list of users.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $translatables['vopros_user_list'] = array(
    t('Master'),
    t('Vopros user list'),
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
    t('Profile'),
    t('User name'),
    t('Bibliotek'),
    t('Fornavn'),
    t('Efternavn'),
    t('E-mail'),
    t('Telefonnummer'),
    t('Name'),
    t('First name'),
    t('Last name'),
    t('Library'),
    t('Page'),
    t('more'),
    t('Rolle'),
  );
  $export['vopros_user_list'] = $view;

  $view = new view();
  $view->name = 'vopros_user_profile_service';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'profile';
  $view->human_name = 'Vopros user profile service';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '2';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Profile: User uid */
  $handler->display->display_options['relationships']['user']['id'] = 'user';
  $handler->display->display_options['relationships']['user']['table'] = 'profile';
  $handler->display->display_options['relationships']['user']['field'] = 'user';
  /* Field: Profile: Profile ID */
  $handler->display->display_options['fields']['pid']['id'] = 'pid';
  $handler->display->display_options['fields']['pid']['table'] = 'profile';
  $handler->display->display_options['fields']['pid']['field'] = 'pid';
  /* Field: Profile: Bibliotek */
  $handler->display->display_options['fields']['vopros_user_library']['id'] = 'vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['table'] = 'field_data_vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['field'] = 'vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['label'] = 'agency';
  $handler->display->display_options['fields']['vopros_user_library']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 1,
  );
  /* Field: Profile: Efternavn */
  $handler->display->display_options['fields']['vopros_user_last_name']['id'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['table'] = 'field_data_vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['field'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['label'] = 'last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['type'] = 'text_plain';
  $handler->display->display_options['fields']['vopros_user_last_name']['settings'] = array(
    'skip_safe' => 1,
    'skip_empty_values' => 0,
  );
  /* Field: Profile: Fornavn */
  $handler->display->display_options['fields']['vopros_user_first_name']['id'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['field'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['label'] = 'first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['type'] = 'text_plain';
  $handler->display->display_options['fields']['vopros_user_first_name']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 1,
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'user';
  $handler->display->display_options['fields']['name']['label'] = 'user_name';
  /* Field: Profile: User uid */
  $handler->display->display_options['fields']['user']['id'] = 'user';
  $handler->display->display_options['fields']['user']['table'] = 'profile';
  $handler->display->display_options['fields']['user']['field'] = 'user';
  $handler->display->display_options['fields']['user']['label'] = 'uid';
  $handler->display->display_options['fields']['user']['separator'] = '';
  /* Field: Profile: Beskrivelse */
  $handler->display->display_options['fields']['field_vopros_user_description']['id'] = 'field_vopros_user_description';
  $handler->display->display_options['fields']['field_vopros_user_description']['table'] = 'field_data_field_vopros_user_description';
  $handler->display->display_options['fields']['field_vopros_user_description']['field'] = 'field_vopros_user_description';
  $handler->display->display_options['fields']['field_vopros_user_description']['label'] = 'description';
  $handler->display->display_options['fields']['field_vopros_user_description']['type'] = 'text_plain';
  /* Field: Profile: Image */
  $handler->display->display_options['fields']['field_vopros_user_image']['id'] = 'field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['table'] = 'field_data_field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['field'] = 'field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['label'] = 'image';
  $handler->display->display_options['fields']['field_vopros_user_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_vopros_user_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Profile: Fagområder */
  $handler->display->display_options['fields']['field_vopros_user_expertise']['id'] = 'field_vopros_user_expertise';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['table'] = 'field_data_field_vopros_user_expertise';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['field'] = 'field_vopros_user_expertise';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['label'] = 'expertise';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['delta_offset'] = '0';
  /* Filter criterion: Profile: User uid */
  $handler->display->display_options['filters']['user']['id'] = 'user';
  $handler->display->display_options['filters']['user']['table'] = 'profile';
  $handler->display->display_options['filters']['user']['field'] = 'user';
  $handler->display->display_options['filters']['user']['exposed'] = TRUE;
  $handler->display->display_options['filters']['user']['expose']['operator_id'] = 'user_op';
  $handler->display->display_options['filters']['user']['expose']['label'] = 'User uid';
  $handler->display->display_options['filters']['user']['expose']['operator'] = 'user_op';
  $handler->display->display_options['filters']['user']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['user']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  /* Filter criterion: User: Name (raw) */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'users';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'user';
  $handler->display->display_options['filters']['name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Name (raw)';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'user_name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $translatables['vopros_user_profile_service'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('User'),
    t('Profile ID'),
    t('.'),
    t(','),
    t('agency'),
    t('last_name'),
    t('first_name'),
    t('user_name'),
    t('uid'),
    t('description'),
    t('image'),
    t('expertise'),
    t('User uid'),
    t('Name (raw)'),
    t('Services'),
  );
  $export['vopros_user_profile_service'] = $view;

  return $export;
}
