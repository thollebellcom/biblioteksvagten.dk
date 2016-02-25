<?php
/**
 * @file
 * vopros_database_search.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function vopros_database_search_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'vopros_database_search';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'search_api_index_answer_question_index';
  $view->human_name = 'Vopros answer and question search';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Search';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access answers';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Question: Question_title (indexed) */
  $handler->display->display_options['fields']['question_question_title']['id'] = 'question_question_title';
  $handler->display->display_options['fields']['question_question_title']['table'] = 'search_api_index_answer_question_index';
  $handler->display->display_options['fields']['question_question_title']['field'] = 'question_question_title';
  $handler->display->display_options['fields']['question_question_title']['label'] = '';
  $handler->display->display_options['fields']['question_question_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['question_question_title']['link_to_entity'] = 1;
  /* Field: Question: Question_content (indexed) */
  $handler->display->display_options['fields']['question_question_content']['id'] = 'question_question_content';
  $handler->display->display_options['fields']['question_question_content']['table'] = 'search_api_index_answer_question_index';
  $handler->display->display_options['fields']['question_question_content']['field'] = 'question_question_content';
  $handler->display->display_options['fields']['question_question_content']['label'] = '';
  $handler->display->display_options['fields']['question_question_content']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['question_question_content']['link_to_entity'] = 0;
  /* Field: Question: Date asked (indexed) */
  $handler->display->display_options['fields']['question_created_1']['id'] = 'question_created_1';
  $handler->display->display_options['fields']['question_created_1']['table'] = 'search_api_index_answer_question_index';
  $handler->display->display_options['fields']['question_created_1']['field'] = 'question_created';
  $handler->display->display_options['fields']['question_created_1']['label'] = 'Date asked';
  $handler->display->display_options['fields']['question_created_1']['date_format'] = 'short';
  $handler->display->display_options['fields']['question_created_1']['second_date_format'] = 'long';
  $handler->display->display_options['fields']['question_created_1']['link_to_entity'] = 0;
  /* Field: Question: Question_status_reason (indexed) */
  $handler->display->display_options['fields']['question_question_status_reason']['id'] = 'question_question_status_reason';
  $handler->display->display_options['fields']['question_question_status_reason']['table'] = 'search_api_index_answer_question_index';
  $handler->display->display_options['fields']['question_question_status_reason']['field'] = 'question_question_status_reason';
  $handler->display->display_options['fields']['question_question_status_reason']['label'] = '';
  $handler->display->display_options['fields']['question_question_status_reason']['exclude'] = TRUE;
  $handler->display->display_options['fields']['question_question_status_reason']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['question_question_status_reason']['link_to_entity'] = 0;
  /* Field: Question: Question_status (indexed) */
  $handler->display->display_options['fields']['question_question_status']['id'] = 'question_question_status';
  $handler->display->display_options['fields']['question_question_status']['table'] = 'search_api_index_answer_question_index';
  $handler->display->display_options['fields']['question_question_status']['field'] = 'question_question_status';
  $handler->display->display_options['fields']['question_question_status']['label'] = 'Status';
  $handler->display->display_options['fields']['question_question_status']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['question_question_status']['alter']['text'] = '[question_question_status] ([question_question_status_reason])';
  $handler->display->display_options['fields']['question_question_status']['link_to_entity'] = 0;
  /* Sort criterion: Question: Date asked (indexed) */
  $handler->display->display_options['sorts']['question_created']['id'] = 'question_created';
  $handler->display->display_options['sorts']['question_created']['table'] = 'search_api_index_answer_question_index';
  $handler->display->display_options['sorts']['question_created']['field'] = 'question_created';
  $handler->display->display_options['sorts']['question_created']['order'] = 'DESC';
  /* Filter criterion: Search: Fulltext search */
  $handler->display->display_options['filters']['search_api_views_fulltext']['id'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['table'] = 'search_api_index_answer_question_index';
  $handler->display->display_options['filters']['search_api_views_fulltext']['field'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['group'] = 1;
  $handler->display->display_options['filters']['search_api_views_fulltext']['exposed'] = TRUE;
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator_id'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['operator'] = 'search_api_views_fulltext_op';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['identifier'] = 'search_api_views_fulltext';
  $handler->display->display_options['filters']['search_api_views_fulltext']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'search';
  $translatables['vopros_database_search'] = array(
    t('Master'),
    t('Search'),
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
    t('Date asked'),
    t('Status'),
    t('[question_question_status] ([question_question_status_reason])'),
    t('Page'),
  );
  $export['vopros_database_search'] = $view;

  return $export;
}
