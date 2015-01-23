<?php
/**
 * @file
 * bv_vopros_services.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bv_vopros_services_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function bv_vopros_services_views_api() {
  return array("version" => "3.0");
}
