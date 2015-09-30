<?php

class fivestar_views_handler_filter_in_operator extends views_handler_filter_in_operator {

  /**
   * Initialize handler.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
    // We handle empty/not empty ourselves.
    $this->definition['allow empty'] = FALSE;
  }

  /**
   * Get the possible options (the number of stars).
   */
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    // Get field info to figure out the number of stars configured for it.
    $field_name = $this->definition['field_name'];
    $field_info = field_info_field($field_name);
    $bundles = reset($field_info['bundles']);
    $entity_type = key($field_info['bundles']);
    $bundle_name = $bundles[0];
    $field_instance = field_info_instance($entity_type, $field_name, $bundle_name);

    $max_stars = !empty($field_instance['settings']['stars']) ? $field_instance['settings']['stars'] : 5;
    $options = array(0 => t('No stars'));
    for ($i = 1; $i <= $max_stars; $i++) {
      $percentage = ceil($i * 100 / $max_stars);
      $options[$percentage] = format_plural($i, '1 star', '@count stars');
    }
    $this->value_options = $options;
  }

  /**
   * Operator callback.
   */
  function op_simple() {
    if (empty($this->value)) {
      return;
    }
    $this->ensure_my_table();

    // Zero needs special handling.
    $has_nul = in_array(0, $this->value);

    $or_statement = db_or();
    // Add regular condition if we have any values other than zero.
    if (count($this->value) > ($has_nul ? 1 : 0)) {
      $or_statement->condition("$this->table_alias.$this->real_field", array_values($this->value), $this->operator);
    }

    // Add zero condition if zero is in the values, or if it's not and the
    // operator is 'not in' (to also show 0 stars when "not in (1, 2)").
    if ($has_nul || $this->operator == 'not in') {
      $nul_operator = (($this->operator == 'in') xor $has_nul) ? 'IS NOT NULL' : 'IS NULL';
      $or_statement->condition("$this->table_alias.$this->real_field", NULL, $nul_operator);
    }

    $this->query->add_where($this->options['group'], $or_statement);
  }
}
