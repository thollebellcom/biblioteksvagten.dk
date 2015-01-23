<?php

/**
 * Entity controller class for BV Call Center Question.
 */
class BVCallCenterQuestionEntityController extends EntityAPIController {
  /**
   * Creates a new instance of a bv_cc_question entity.
   */
  public function create(array $values = array()) {
    $values = $values + array(
      'cc_question_id' => 0,
      'title' => variable_get('bv_cc_question_default_question', 'Callcenterspørgsmål'),
      'library' => '',
      'answer_type' => NULL,
      'note' => '',
      'uid' => $GLOBALS['user']->uid,
      'created' => REQUEST_TIME,
    );
    return parent::create($values);
  }
}

/**
 * Extend the default metadata.
 */
class BVCallCenterQuestionMetadataController extends EntityDefaultMetadataController {
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    // Communicate that this is a unix time stamp.
    $properties['created']['type'] = 'date';
    $properties['uid']['type'] = 'user';

    return $info;
  }
}

/**
 * Extend the default views data definition.
 */
class BVCallCenterQuestionViewsController extends EntityDefaultViewsController {
  /**
   * Comes up with views information based on the given schema and property
   * info.
   */
  protected function map_from_schema_info($property_name, $schema_field_info, $property_info) {
    $property = parent::map_from_schema_info($property_name, $schema_field_info, $property_info);

    // For normal fields, use our custom version which can link to the entity edit screen.
    if ($property['field']['handler'] == 'views_handler_field') {
      $property['field']['handler'] = 'views_handler_field_bv_cc_question';
    }

    // Use in operator for answer_type filter.
    if ($property_name == 'answer_type') {
      $property['filter']['handler'] = 'bv_cc_question_answer_type_views_handler_filter_in_operator';
    }

    // Use in operator for library filter.
    if ($property_name == 'library') {
      $property['filter']['handler'] = 'bv_cc_question_library_views_handler_filter_in_operator';
    }

    return $property;
  }
}
