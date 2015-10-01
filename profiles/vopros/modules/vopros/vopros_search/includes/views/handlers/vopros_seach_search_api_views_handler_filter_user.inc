<?php

/**
 * @file
 * Contains the VoprosSeachSearchApiViewsHandlerFilterUser class.
 */

/**
 * Views filter handler for user in search_api.
 */
class VoprosSeachSearchApiViewsHandlerFilterUser extends SearchApiViewsHandlerFilterOptions {
  /**
   * Fills the value_options property with all possible options.
   */
  protected function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    $profiles = profile2_load_multiple(FALSE, array('type' => 'vopros_user_librarian'));
    $options = vopros_user_get_librarians();
    // Sort the options.
    asort($options);
    $this->value_options = $options;
  }
}
