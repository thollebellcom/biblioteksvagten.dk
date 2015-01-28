<?php

/**
 * @file
 * Views filter class.
 */

class vopros_question_user_answer_preference_views_handler_filter extends views_handler_filter_in_operator {
  /**
   * {@inheritdoc}
   */
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }
    $this->value_options = _vopros_question_user_answer_preference();
  }
}
