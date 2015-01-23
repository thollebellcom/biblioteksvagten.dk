<?php
/**
 * @file
 * bv_vopros_services.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function bv_vopros_services_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'bv_vopros_services_public_help';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'vopros_question';
  $view->human_name = 'BV Vopros Services Public Help';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Anvend';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Nulstil';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorter efter';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Poster pr side';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Felt: Spørgsmål: Question_title */
  $handler->display->display_options['fields']['question_title']['id'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_title']['field'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['label'] = 'title';
  /* Felt: Spørgsmål: Question_content */
  $handler->display->display_options['fields']['question_content']['id'] = 'question_content';
  $handler->display->display_options['fields']['question_content']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_content']['field'] = 'question_content';
  $handler->display->display_options['fields']['question_content']['label'] = 'indhold';
  /* Sorteringskriterie: Spørgsmål: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'vopros_question';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filterkriterie: Spørgsmål: Question_status */
  $handler->display->display_options['filters']['question_status']['id'] = 'question_status';
  $handler->display->display_options['filters']['question_status']['table'] = 'vopros_question';
  $handler->display->display_options['filters']['question_status']['field'] = 'question_status';
  $handler->display->display_options['filters']['question_status']['value'] = array(
    'closed' => 'closed',
  );
  /* Filterkriterie: Spørgsmål: Question_status_reason */
  $handler->display->display_options['filters']['question_status_reason']['id'] = 'question_status_reason';
  $handler->display->display_options['filters']['question_status_reason']['table'] = 'vopros_question';
  $handler->display->display_options['filters']['question_status_reason']['field'] = 'question_status_reason';
  $handler->display->display_options['filters']['question_status_reason']['value'] = 'asked for help';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Spørgsmål: Question_title */
  $handler->display->display_options['fields']['question_title']['id'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_title']['field'] = 'question_title';
  $handler->display->display_options['fields']['question_title']['label'] = 'title';
  /* Felt: Spørgsmål: Question_content */
  $handler->display->display_options['fields']['question_content']['id'] = 'question_content';
  $handler->display->display_options['fields']['question_content']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_content']['field'] = 'question_content';
  $handler->display->display_options['fields']['question_content']['label'] = 'indhold';
  /* Felt: Spørgsmål: Spørgsmål ID */
  $handler->display->display_options['fields']['question_id']['id'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['question_id']['field'] = 'question_id';
  $handler->display->display_options['fields']['question_id']['label'] = 'ID';
  $handler->display->display_options['fields']['question_id']['separator'] = '';
  /* Felt: Spørgsmål: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'vopros_question';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Oprettet';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['path'] = 'public_help';
  $translatables['bv_vopros_services_public_help'] = array(
    t('Master'),
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
    t('title'),
    t('indhold'),
    t('Services'),
    t('ID'),
    t('.'),
    t('Oprettet'),
  );
  $export['bv_vopros_services_public_help'] = $view;

  $view = new view();
  $view->name = 'bv_vopros_services_users';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'BV Vopros Services Users';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'mere';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Anvend';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Nulstil';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorter efter';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Poster pr side';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Alle -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Forskydning';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'næste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'sidste »';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Forbindelse: Bruger: Profil */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'vopros_user_librarian' => 'vopros_user_librarian',
  );
  /* Forbindelse: Profil: Image (field_vopros_user_image:fid) */
  $handler->display->display_options['relationships']['field_vopros_user_image_fid']['id'] = 'field_vopros_user_image_fid';
  $handler->display->display_options['relationships']['field_vopros_user_image_fid']['table'] = 'field_data_field_vopros_user_image';
  $handler->display->display_options['relationships']['field_vopros_user_image_fid']['field'] = 'field_vopros_user_image_fid';
  $handler->display->display_options['relationships']['field_vopros_user_image_fid']['relationship'] = 'profile';
  /* Felt: Bruger: Navn */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Felt: Profil: Fornavn */
  $handler->display->display_options['fields']['vopros_user_first_name']['id'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['field'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_first_name']['label'] = 'first_name';
  /* Felt: Profil: Efternavn */
  $handler->display->display_options['fields']['vopros_user_last_name']['id'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['table'] = 'field_data_vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['field'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_last_name']['label'] = 'last_name';
  /* Felt: Profil: Fagområder */
  $handler->display->display_options['fields']['field_vopros_user_expertise']['id'] = 'field_vopros_user_expertise';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['table'] = 'field_data_field_vopros_user_expertise';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['field'] = 'field_vopros_user_expertise';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['label'] = 'expertise';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_vopros_user_expertise']['delta_offset'] = '0';
  /* Felt: Profil: Beskrivelse */
  $handler->display->display_options['fields']['field_vopros_user_description']['id'] = 'field_vopros_user_description';
  $handler->display->display_options['fields']['field_vopros_user_description']['table'] = 'field_data_field_vopros_user_description';
  $handler->display->display_options['fields']['field_vopros_user_description']['field'] = 'field_vopros_user_description';
  $handler->display->display_options['fields']['field_vopros_user_description']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_vopros_user_description']['label'] = 'description';
  $handler->display->display_options['fields']['field_vopros_user_description']['type'] = 'text_plain';
  $handler->display->display_options['fields']['field_vopros_user_description']['settings'] = array(
    'skip_safe' => 0,
    'skip_empty_values' => 0,
  );
  /* Felt: Fil: Sti */
  $handler->display->display_options['fields']['uri']['id'] = 'uri';
  $handler->display->display_options['fields']['uri']['table'] = 'file_managed';
  $handler->display->display_options['fields']['uri']['field'] = 'uri';
  $handler->display->display_options['fields']['uri']['relationship'] = 'field_vopros_user_image_fid';
  $handler->display->display_options['fields']['uri']['label'] = 'path';
  /* Felt: Profil: Bibliotek */
  $handler->display->display_options['fields']['vopros_user_library']['id'] = 'vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['table'] = 'field_data_vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['field'] = 'vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_library']['label'] = 'library';
  /* Felt: Profil: Image */
  $handler->display->display_options['fields']['field_vopros_user_image']['id'] = 'field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['table'] = 'field_data_field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['field'] = 'field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_vopros_user_image']['label'] = 'billede';
  $handler->display->display_options['fields']['field_vopros_user_image']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_vopros_user_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_vopros_user_image']['settings'] = array(
    'image_style' => 'square_thumbnail',
    'image_link' => '',
  );
  /* Sorteringskriterie: Bruger: Seneste login */
  $handler->display->display_options['sorts']['login']['id'] = 'login';
  $handler->display->display_options['sorts']['login']['table'] = 'users';
  $handler->display->display_options['sorts']['login']['field'] = 'login';
  $handler->display->display_options['sorts']['login']['order'] = 'DESC';
  /* Filterkriterie: Bruger: Aktivt */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filterkriterie: Bruger: Roller */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['operator'] = 'not';
  $handler->display->display_options['filters']['rid']['value'] = array(
    3 => '3',
    5 => '5',
  );
  /* Filterkriterie: Profil: Fornavn (vopros_user_first_name) */
  $handler->display->display_options['filters']['vopros_user_first_name_value']['id'] = 'vopros_user_first_name_value';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['field'] = 'vopros_user_first_name_value';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['operator'] = '!=';
  $handler->display->display_options['filters']['vopros_user_first_name_value']['value'] = 'Aalborg';
  /* Filterkriterie: Profil: Fornavn (vopros_user_first_name) */
  $handler->display->display_options['filters']['vopros_user_first_name_value_1']['id'] = 'vopros_user_first_name_value_1';
  $handler->display->display_options['filters']['vopros_user_first_name_value_1']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['filters']['vopros_user_first_name_value_1']['field'] = 'vopros_user_first_name_value';
  $handler->display->display_options['filters']['vopros_user_first_name_value_1']['relationship'] = 'profile';
  $handler->display->display_options['filters']['vopros_user_first_name_value_1']['operator'] = '!=';
  $handler->display->display_options['filters']['vopros_user_first_name_value_1']['value'] = 'Statsbiblioteket';
  /* Filterkriterie: Session: Last access (from session) */
  $handler->display->display_options['filters']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['table'] = 'sessions';
  $handler->display->display_options['filters']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['operator'] = '>=';
  $handler->display->display_options['filters']['timestamp']['value']['value'] = '-900 seconds';
  $handler->display->display_options['filters']['timestamp']['value']['type'] = 'offset';

  /* Display: Services */
  $handler = $view->new_display('services', 'Services', 'services_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Felt: Bruger: Navn */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Felt: Profil: Fornavn */
  $handler->display->display_options['fields']['vopros_user_first_name']['id'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['field'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_first_name']['label'] = 'first_name';
  /* Felt: Profil: Efternavn */
  $handler->display->display_options['fields']['vopros_user_last_name']['id'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['table'] = 'field_data_vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['field'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_last_name']['label'] = 'last_name';
  /* Felt: Fil: Sti */
  $handler->display->display_options['fields']['uri']['id'] = 'uri';
  $handler->display->display_options['fields']['uri']['table'] = 'file_managed';
  $handler->display->display_options['fields']['uri']['field'] = 'uri';
  $handler->display->display_options['fields']['uri']['relationship'] = 'field_vopros_user_image_fid';
  $handler->display->display_options['fields']['uri']['label'] = 'path';
  /* Felt: Profil: Bibliotek */
  $handler->display->display_options['fields']['vopros_user_library']['id'] = 'vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['table'] = 'field_data_vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['field'] = 'vopros_user_library';
  $handler->display->display_options['fields']['vopros_user_library']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_library']['label'] = 'library';
  /* Felt: Profil: Image */
  $handler->display->display_options['fields']['field_vopros_user_image']['id'] = 'field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['table'] = 'field_data_field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['field'] = 'field_vopros_user_image';
  $handler->display->display_options['fields']['field_vopros_user_image']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_vopros_user_image']['label'] = 'billede';
  $handler->display->display_options['fields']['field_vopros_user_image']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_vopros_user_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_vopros_user_image']['settings'] = array(
    'image_style' => 'square_thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['path'] = 'users';
  $translatables['bv_vopros_services_users'] = array(
    t('Master'),
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
    t('Profil'),
    t('billede fra field_vopros_user_image'),
    t('first_name'),
    t('last_name'),
    t('expertise'),
    t('description'),
    t('path'),
    t('library'),
    t('billede'),
    t('Services'),
  );
  $export['bv_vopros_services_users'] = $view;

  return $export;
}
