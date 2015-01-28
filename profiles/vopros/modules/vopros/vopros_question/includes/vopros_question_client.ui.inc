<?php

/**
 * @file
 * Provides a controller for building an vopros client overview form.
 */

/**
 * UI controller class for the admin interface.
 */
class VoprosClientUIController extends VoprosUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Display a list of clients.';
    return $items;
  }

  /**
   * {@inheritdoc}
   */
  protected function overviewTableHeaders($conditions, $rows, $additional_header = array()) {
    $header = $additional_header;
    array_unshift($header, t('Agency'));
    return parent::overviewTableHeaders($conditions, $rows, $header);
  }

  /**
   * {@inheritdoc}
   */
  protected function overviewTableRow($conditions, $id, $entity, $additional_cols = array()) {
    $additional_cols[] = $entity->agency;
    return parent::overviewTableRow($conditions, $id, $entity, $additional_cols);
  }
}
