<?php

/**
 * @file
 * Entity classes defined by bv_cc_question module.
 */


/**
 * Entity class for BV Call Center Question entities.
 */
class BVCallCenterQuestion extends VoprosEntity {
  /**
   * Defined the default uri for products
   */
  public function defaultUri() {
    return array('path' => 'admin/vopros/cc-questions/' . $this->identifier());
  }
}
