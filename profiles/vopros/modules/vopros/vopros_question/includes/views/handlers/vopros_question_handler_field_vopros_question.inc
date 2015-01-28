<?php

/**
 * @file
 * Views field handler for questions.
 *
 * Handles rendering of fields that one out of a set.
 */

class vopros_question_handler_field_vopros_question extends views_handler_field {
  /**
   * Render a field.
   */
  public function render($values) {
    $value = $this->get_value($values);
    $san = $this->sanitize_value($value);
    switch ($this->field) {
      case 'question_status':
        $statuses = _vopros_question_status();
        return isset($statuses[$san]) ? $statuses[$san] : $san;

      case 'question_usage':
        $statuses = _vopros_question_usage();
        return isset($statuses[$san]) ? $statuses[$san] : $san;

      case 'user_age':
        $mapping = _vopros_question_user_age();
        return isset($mapping[$san]) ? $mapping[$san] : $mapping['no inform'];

      case 'qanda_service_name':
        $mapping = _vopros_question_qanda_serice_options();
        return isset($mapping[$san]) ? $mapping[$san] : $san;

      case 'user_answer_preference':
        $mapping = _vopros_question_user_answer_preference();
        return isset($mapping[$san]) ? $mapping[$san] : $san;

    }
    return $san;
  }
}
