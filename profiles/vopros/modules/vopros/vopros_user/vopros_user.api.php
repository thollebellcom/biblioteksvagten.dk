<?php

/**
 * @file
 * Hooks provided by the Vopros user module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Additional non-Vopros permissions.
 *
 * This hook allows modules to add permissions to the Vopros staff role on
 * behalf of other modules.
 *
 * @return
     An array of role name => array of permissions.
 */
function hook_vopros_extra_permissions() {
  return array(
    'staff' => array(
      'access toolbar',
      'view the administration theme',
    ),
  );
}

/**
 * @} End of "addtogroup hooks".
 */
