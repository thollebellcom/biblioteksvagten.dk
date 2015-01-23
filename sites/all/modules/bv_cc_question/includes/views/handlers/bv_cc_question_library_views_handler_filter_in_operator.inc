<?php

class bv_cc_question_library_views_handler_filter_in_operator extends views_handler_filter_in_operator {
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }
    $this->value_options = db_query("SELECT DISTINCT(library) FROM {bv_cc_question};")->fetchAllKeyed(0,0);
  }
}
