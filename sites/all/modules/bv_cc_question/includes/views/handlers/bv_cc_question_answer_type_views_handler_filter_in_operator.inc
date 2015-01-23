<?php

class bv_cc_question_answer_type_views_handler_filter_in_operator extends views_handler_filter_in_operator {
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }
    $this->value_options = bv_cc_question_answer_types();
  }
}
