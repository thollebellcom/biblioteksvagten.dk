<?php
 
class fivestar_views_handler_filter_in_operator extends views_handler_filter_in_operator {
  // Get the possible options (the number of stars)
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }
    // Get field info
    $field = field_info_field($this->definition['field_name']);
    // Create options list.
    $max_stars = !empty($field['settings']['stars']) ? $field['settings']['stars'] : 5;
    $options = array(0 => t('No stars'));
    for($i = 1; $i <= $max_stars; $i++) {
      $percentage = ceil($i * 100 / $max_stars);
      $options[$percentage] = format_plural($i, '1 star', '@count stars');
    }
    $this->value_options = $options;
  }
}
