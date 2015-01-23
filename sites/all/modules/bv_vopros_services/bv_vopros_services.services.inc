<?php
/**
 * @file
 * bv_vopros_services.services.inc
 */

/**
 * Implements hook_default_services_endpoint().
 */
function bv_vopros_services_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'bv_vopros_services';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'bv_vopros_services';
  $endpoint->authentication = array();
  $endpoint->server_settings = array();
  $endpoint->resources = array(
    'users' => array(
      'operations' => array(
        'index' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'public_help' => array(
      'operations' => array(
        'index' => array(
          'enabled' => '1',
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['bv_vopros_services'] = $endpoint;

  return $export;
}
