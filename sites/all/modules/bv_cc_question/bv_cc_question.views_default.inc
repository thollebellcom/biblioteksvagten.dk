<?php
/**
 * @file
 * bv_cc_question.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function bv_cc_question_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'bv_call_center_question_list';
  $view->description = '';
  $view->tag = 'bv_cc_question';
  $view->base_table = 'bv_cc_question';
  $view->human_name = 'bv_call_center_question_list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'BV Call Center Questions';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access bv call center questions';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'answer_type' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'bv_cc_category_tid' => array(
      'bef_format' => 'default',
      'slider_options' => array(
        'bef_slider_min' => '0',
        'bef_slider_max' => '99999',
        'bef_slider_step' => '1',
        'bef_slider_animate' => '',
        'bef_slider_orientation' => 'horizontal',
      ),
      'more_options' => array(
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
    'library' => array(
      'bef_format' => 'default',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 0,
        'is_secondary' => 0,
        'any_label' => '',
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
        'rewrite' => array(
          'filter_rewrite_values' => '',
        ),
      ),
    ),
  );
  $handler->display->display_options['exposed_form']['options']['input_required'] = 0;
  $handler->display->display_options['exposed_form']['options']['text_input_required_format'] = 'plain_text';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'bv_cc_category' => 'bv_cc_category',
    'answer_type' => 'answer_type',
    'library' => 'library',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'bv_cc_category' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'answer_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'library' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
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
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* Relationship: BV Call Center Question: Uid */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'bv_cc_question';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['relationship'] = 'uid';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'vopros_user_librarian' => 'vopros_user_librarian',
  );
  /* Field: Profile: Efternavn */
  $handler->display->display_options['fields']['vopros_user_last_name']['id'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['table'] = 'field_data_vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['field'] = 'vopros_user_last_name';
  $handler->display->display_options['fields']['vopros_user_last_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_last_name']['exclude'] = TRUE;
  /* Field: BV Call Center Question: Label */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'bv_cc_question';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Title';
  $handler->display->display_options['fields']['title']['link_to_cc_question'] = TRUE;
  /* Field: BV Call Center Question: Kategori */
  $handler->display->display_options['fields']['bv_cc_category']['id'] = 'bv_cc_category';
  $handler->display->display_options['fields']['bv_cc_category']['table'] = 'field_data_bv_cc_category';
  $handler->display->display_options['fields']['bv_cc_category']['field'] = 'bv_cc_category';
  $handler->display->display_options['fields']['bv_cc_category']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['bv_cc_category']['delta_offset'] = '0';
  /* Field: BV Call Center Question: Answer_type */
  $handler->display->display_options['fields']['answer_type']['id'] = 'answer_type';
  $handler->display->display_options['fields']['answer_type']['table'] = 'bv_cc_question';
  $handler->display->display_options['fields']['answer_type']['field'] = 'answer_type';
  $handler->display->display_options['fields']['answer_type']['label'] = 'Answer type';
  /* Field: BV Call Center Question: Library */
  $handler->display->display_options['fields']['library']['id'] = 'library';
  $handler->display->display_options['fields']['library']['table'] = 'bv_cc_question';
  $handler->display->display_options['fields']['library']['field'] = 'library';
  /* Field: Profile: Fornavn */
  $handler->display->display_options['fields']['vopros_user_first_name']['id'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['table'] = 'field_data_vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['field'] = 'vopros_user_first_name';
  $handler->display->display_options['fields']['vopros_user_first_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['vopros_user_first_name']['label'] = 'Navn';
  $handler->display->display_options['fields']['vopros_user_first_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['vopros_user_first_name']['alter']['text'] = '[vopros_user_first_name] [vopros_user_last_name]';
  /* Field: BV Call Center Question: Created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'bv_cc_question';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Filter criterion: BV Call Center Question: Answer_type */
  $handler->display->display_options['filters']['answer_type']['id'] = 'answer_type';
  $handler->display->display_options['filters']['answer_type']['table'] = 'bv_cc_question';
  $handler->display->display_options['filters']['answer_type']['field'] = 'answer_type';
  $handler->display->display_options['filters']['answer_type']['group'] = 1;
  $handler->display->display_options['filters']['answer_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['answer_type']['expose']['operator_id'] = 'answer_type_op';
  $handler->display->display_options['filters']['answer_type']['expose']['label'] = 'Answer type';
  $handler->display->display_options['filters']['answer_type']['expose']['operator'] = 'answer_type_op';
  $handler->display->display_options['filters']['answer_type']['expose']['identifier'] = 'answer_type';
  $handler->display->display_options['filters']['answer_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: BV Call Center Question: Kategori (bv_cc_category) */
  $handler->display->display_options['filters']['bv_cc_category_tid']['id'] = 'bv_cc_category_tid';
  $handler->display->display_options['filters']['bv_cc_category_tid']['table'] = 'field_data_bv_cc_category';
  $handler->display->display_options['filters']['bv_cc_category_tid']['field'] = 'bv_cc_category_tid';
  $handler->display->display_options['filters']['bv_cc_category_tid']['group'] = 1;
  $handler->display->display_options['filters']['bv_cc_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['bv_cc_category_tid']['expose']['operator_id'] = 'bv_cc_category_tid_op';
  $handler->display->display_options['filters']['bv_cc_category_tid']['expose']['label'] = 'Kategori';
  $handler->display->display_options['filters']['bv_cc_category_tid']['expose']['operator'] = 'bv_cc_category_tid_op';
  $handler->display->display_options['filters']['bv_cc_category_tid']['expose']['identifier'] = 'bv_cc_category_tid';
  $handler->display->display_options['filters']['bv_cc_category_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: BV Call Center Question: Library */
  $handler->display->display_options['filters']['library']['id'] = 'library';
  $handler->display->display_options['filters']['library']['table'] = 'bv_cc_question';
  $handler->display->display_options['filters']['library']['field'] = 'library';
  $handler->display->display_options['filters']['library']['exposed'] = TRUE;
  $handler->display->display_options['filters']['library']['expose']['operator_id'] = 'library_op';
  $handler->display->display_options['filters']['library']['expose']['label'] = 'Library';
  $handler->display->display_options['filters']['library']['expose']['operator'] = 'library_op';
  $handler->display->display_options['filters']['library']['expose']['identifier'] = 'library';
  $handler->display->display_options['filters']['library']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/vopros/cc-question/views';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Search list';
  $handler->display->display_options['menu']['description'] = 'Display list of qustions';
  $handler->display->display_options['menu']['weight'] = '-50';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'Test';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $export['bv_call_center_question_list'] = $view;

  return $export;
}
