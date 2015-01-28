<?php
/**
 * @file
 * vopros_mailhandler.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function vopros_mailhandler_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}
