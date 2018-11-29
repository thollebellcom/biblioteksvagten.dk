<?php
/**
 * @file
 * vopros_simple_text_format.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function vopros_simple_text_format_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format simple_text'.
  $permissions['use text format simple_text'] = array(
    'name' => 'use text format simple_text',
    'roles' => array(
      'Admin' => 'Admin',
      'Biblioteksvagt' => 'Biblioteksvagt',
      'Kontaktperson' => 'Kontaktperson',
      'Super Admin' => 'Super Admin',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
