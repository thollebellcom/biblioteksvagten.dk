<?php

/**
 * @file
 * Views filter for client_id.
 */

class vopros_question_client_views_handler_filter_in_operator extends views_handler_filter_in_operator {
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }
    $this->value_options = _vopros_question_client_options();
  }
}
