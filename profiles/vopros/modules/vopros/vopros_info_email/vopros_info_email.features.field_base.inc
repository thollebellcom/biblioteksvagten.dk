<?php
/**
 * @file
 * vopros_info_email.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function vopros_info_email_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_no_info_mail'.
  $field_bases['field_no_info_mail'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_no_info_mail',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
