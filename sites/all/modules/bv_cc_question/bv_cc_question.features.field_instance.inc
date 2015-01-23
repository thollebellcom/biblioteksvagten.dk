<?php
/**
 * @file
 * bv_cc_question.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function bv_cc_question_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'bv_cc_question-bv_cc_question-bv_cc_category'
  $field_instances['bv_cc_question-bv_cc_question-bv_cc_category'] = array(
    'bundle' => 'bv_cc_question',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'bv_cc_question',
    'field_name' => 'bv_cc_category',
    'label' => 'Kategori',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Kategori');

  return $field_instances;
}
