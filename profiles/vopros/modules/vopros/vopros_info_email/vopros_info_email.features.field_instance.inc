<?php
/**
 * @file
 * vopros_info_email.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function vopros_info_email_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_no_info_mail'.
  $field_instances['user-user-field_no_info_mail'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_no_info_mail',
    'label' => 'Ønsker IKKE info mail',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 1,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 2,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Ønsker IKKE info mail');

  return $field_instances;
}
