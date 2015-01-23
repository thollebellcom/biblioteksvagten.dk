<?php
/**
 * @file
 * bv_cc_question.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function bv_cc_question_taxonomy_default_vocabularies() {
  return array(
    'bv_call_center_question' => array(
      'name' => 'Call Center Question',
      'machine_name' => 'bv_call_center_question',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
