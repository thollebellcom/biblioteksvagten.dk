<?php

/**
 * @file
 * Administrative pages for Vopros User.
 */

/**
 * Settings form for the vopros_user module.
 */
function vopros_user_settings_form($form, &$form_state) {
  $form['vopros_user_libraries'] = array(
    '#type' => 'textarea',
    '#title' => t('Libraries'),
    '#description' => t('Enter one library per line in the format <em>librarynumber|library name</em>.'),
    '#default_value' => variable_get('vopros_user_libraries', ''),
  );

  $states = array(
    'enabled' => array(
      'textarea[name=vopros_user_libraries]' => array('value' => ''),
    ),
  );

  $form['vopros_user_service_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Service URL'),
    '#description' => t('URL of the OpenAgency service.'),
    '#default_value' => variable_get('vopros_user_service_url', VOPROS_USER_DEFAULT_URL),
    '#states' => $states,
  );

  $form['vopros_user_service_group'] = array(
    '#type' => 'textfield',
    '#title' => t('Service group'),
    '#description' => t('Group used for authentication.'),
    '#default_value' => variable_get('vopros_user_service_group', ''),
    '#states' => $states,
  );

  $form['vopros_user_service_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Service user'),
    '#description' => t('User used for authentication.'),
    '#default_value' => variable_get('vopros_user_service_user', ''),
    '#states' => $states,
  );

  $form['vopros_user_service_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Service password'),
    '#description' => t('Password used for authentication.'),
    '#default_value' => variable_get('vopros_user_service_password', ''),
    '#states' => $states,
  );

  $form['vopros_user_included_libraries'] = array(
    '#type' => 'textarea',
    '#title' => t('Included libraries'),
    '#description' => t('Enter the library ids you want to include to the library list, seperate by space and leave empty to include all.'),
    '#default_value' => variable_get('vopros_user_included_libraries', ''),
    '#states' => $states,
  );

  $form['#submit'][] = 'vopros_user_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Submit handler for settings form.
 *
 * Clear the library cache.
 */
function vopros_user_settings_form_submit($form, &$form_state) {
  cache_set('vopros_user_libraries', array(), 'cache_field', REQUEST_TIME - 86400);
}

/**
 * Role settings form.
 */
function vopros_user_role_settings_form($form, &$form_state) {
  $roles = user_roles();
  unset($roles[DRUPAL_ANONYMOUS_RID]);
  unset($roles[DRUPAL_AUTHENTICATED_RID]);
  $roles[0] = '<' . t('disabled') . '>';

  $form['vopros_user_staff_role'] = array(
    '#type' => 'select',
    '#title' => t('Staff role'),
    '#default_value' => variable_get('vopros_user_staff_role', 0),
    '#options' => $roles,
    '#description' => t('This role will be automatically assigned new Vopros permissions whenever a module is enabled. Changing this setting will not affect existing permissions.'),
  );

  if (variable_get('vopros_user_staff_role', 0)) {
    $form['actions']['rebuild'] = array(
      '#type' => 'submit',
      '#value' => t('Rebuild permissions'),
      '#weight' => 50,
      '#submit' => array('vopros_user_role_settings_form_rebuild_submit'),
    );
  }

  return system_settings_form($form);
}

/**
 * Submit handler for the rebuild button.
 *
 * Redirects to the rebuild confirm form.
 */
function vopros_user_role_settings_form_rebuild_submit($form, &$form_state) {
  $form_state['redirect'] = 'admin/vopros/config/user/roles/rebuild';
}

/**
 * Rebuild permissions form callback.
 */
function vopros_user_role_settings_rebuild_form($form, &$form_state) {
  return confirm_form($form,
                      t('Are you sure you want to rebuild permissions?'),
                      'admin/vopros/config/user/roles',
                      t('This will reset permissions for the staff profile to the defaults recommended by Vopros and can not be undone.')
  );
}

/**
 * Rebuild permissions form submit handler.
 */
function vopros_user_role_settings_rebuild_form_submit($form, &$form_state) {
  $rid = variable_get('vopros_user_staff_role', 0);
  if ($rid) {
    // Remove all permissions for the staff role.
    db_delete('role_permission')
      ->condition('rid', $rid)
      ->execute();

    // Clear the user access cache.
    drupal_static_reset('user_access');
    drupal_static_reset('user_role_permissions');

    // Rebuild.
    vopros_user_update_permissions();

    drupal_set_message(t('Permissions rebuild.'), 'status');
  }

  $form_state['redirect'] = 'admin/vopros/config/user/roles';
}
