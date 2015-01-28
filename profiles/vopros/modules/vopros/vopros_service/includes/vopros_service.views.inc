<?php

/**
 * @file
 * Views integration for Vopros Service forward table.
 *
 * @see http://drupal.org/project/views
 */

/**
 * Implements hook_views_data().
 */
function vopros_service_views_data() {

  $data['vopros_service_question']['table'] = array(
    'name' => 'vopros_service_question',
    'group' => 'Vopros Service forwarded questions.',
    // Relation to question table.
    'join' => array(
      'vopros_question' => array(
        'left_field' => 'uuid',
        'field' => 'uuid',
        // 'type' => 'INNER',
      ),
      'vopros_service' => array(
        'left_field' => 'client_id',
        'field' => 'client_id',
        // 'type' => 'INNER',
      ),
    ),
  );

  $data['vopros_service']['client_id'] = array(
    'title' => t('Client ID'),
    'help' => t('Client ID of this service.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'relationship' => array(
      'base' => 'vopros_question_client',
      'base field' => 'client_id',
      'field' => 'client_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Service client'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['vopros_service_question']['client_id'] = array(
    'title' => t('Client forwarded to'),
    'help' => t('Client of the service this question has been forwarded from/to.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'relationship' => array(
      'base' => 'vopros_question_client',
      'base field' => 'client_id',
      'field' => 'client_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Client forwarded to'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['vopros_service_question']['service_id'] = array(
    'title' => t('Service forwarded to'),
    'help' => t('Service this question has been forwarded from/to.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'relationship' => array(
      'base' => 'vopros_service',
      'base field' => 'client_id',
      'field' => 'client_id',
      'handler' => 'views_handler_relationship',
      'label' => t('Service forwarded to'),
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['vopros_service_question']['direction'] = array(
    'title' => t('Direction of forward'),
    'help' => t('Whether this forward is incoming or outgoing.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'vopros_service_direction_views_handler_filter_in_operator',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['vopros_service_question']['type'] = array(
    'title' => t('Type of forward'),
    'help' => t('Whether this forward is help or turn_over.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'vopros_service_type_views_handler_filter_in_operator',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}
