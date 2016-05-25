<?php
/**
 * @file
 * bv_settings_prod.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function bv_settings_prod_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodejs_enable_userchannel';
  $strongarm->value = '0';
  $export['nodejs_enable_userchannel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodejs_pages';
  $strongarm->value = '*';
  $export['nodejs_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodejs_server_host';
  $strongarm->value = 'chat.biblioteksvagten.dk';
  $export['nodejs_server_host'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodejs_server_port';
  $strongarm->value = '8181';
  $export['nodejs_server_port'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodejs_server_scheme';
  $strongarm->value = 'https';
  $export['nodejs_server_scheme'] = $strongarm;

  return $export;
}
