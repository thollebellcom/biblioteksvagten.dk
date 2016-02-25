<?php

/**
 * @file
 *
 * Vopros install profile. Uses Profiler.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function vopros_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#default_value'] = 'Vopros';
}

/**
 * Implements hook_install_tasks_alter().
 *
 * Replace locale selection with our own.
 */
function vopros_install_tasks_alter(&$tasks, $install_state) {
  $tasks['install_select_locale']['function'] = '_vopros_locale_selection';
}

/**
 * Set language to danish.
 */
function _vopros_locale_selection(&$install_state) {
  $install_state['parameters']['locale'] = 'da';
}
/**
 * Implements hook_install_tasks().
 *
 * Collects install tasks from all modules implementing
 * hook_vopros_install_tasks.
 *
 * As this function is called early and often, we have to maintain a cache or
 * else the task specifying a form may not be available on form submit.
 */
function vopros_install_tasks($install_state) {
  $tasks = module_invoke_all('vopros_install_tasks') + variable_get('vopros_install_tasks', array());
  if ($tasks && !$install_state['installation_finished']) {
    variable_set('vopros_install_tasks', $tasks);
  }

  // Allow task callbacks to be located in an include file.
  foreach ($tasks as $task) {
    if (isset($task['file'])) {
      require_once DRUPAL_ROOT . '/' . $task['file'];
    }
  }

  // Clean up if were finished.
  if ($install_state['installation_finished']) {
    variable_del('vopros_install_tasks');
  }

  $ret = array(
    // Select modules.
    'vopros_module_selection_form' => array(
      'display_name' => st('Additional options'),
      'display' => TRUE,
      'type' => 'form',
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
    ),

    // Enable modules.
    'vopros_module_enable' => array(
      'display_name' => st('Enable options'),
      'display' => TRUE,
      'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
      'type' => 'batch',
    ),

  ) + $tasks;
  return $ret;
}

/**
 * Installation task that handle selection of additional modules.
 */
function vopros_module_selection_form($form, &$form_state) {
  $modules = array(
    'vopros_database_search' => st('Questions and answer search'),
  );

  $form['modules'] = array(
    '#title' => st('Additional options'),
    '#type' => 'fieldset',
    '#description' => st("Vopros comes bundled with additional options that provide extra functionality, but that is not required for basic functions. These can be enabled later if they're not selected now. We've pre-selected recommended options."),
  );

  $form['modules']['modules_selection'] = array(
    // Title left empty to create more space in the ui.
    '#title' => '',
    '#type' => 'checkboxes',
    '#options' => $modules,
    '#default_value' => array(
      'vopros_database_search',
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => st('Enable options'),
  );

  // Validate and submit logo, iOS logo and favicon.
  $form['#submit'][] = 'vopros_module_selection_form_submit';

  return $form;
}

/**
 * Submit handler that enables the modules.
 */
function vopros_module_selection_form_submit($form, &$form_state) {
  // We depend on core system module.
  require_once DRUPAL_ROOT . '/modules/system/system.admin.inc';

  $values = $form_state['values'];
  $module_list = array();

  // Get list of selected modules.
  if (!empty($values['modules_selection'])) {
    $module_list += array_filter($values['modules_selection']);
  }

  // Store selection to batch them in the next task.
  variable_set('vopros_module_selected', $module_list);
}

/**
 * Builds an batch module enable operations list based on module list.
 *
 * @param array $module_list
 *   List of module names to change to operations.
 *
 * @return array
 *   Batch operation list.
 */
function vopros_module_list_as_operations($module_list) {
  // Resolve the dependencies now, so that module_enable() doesn't need
  // to do it later for each individual module (which kills performance).
  $files = system_rebuild_module_data();
  $modules_sorted = array();
  foreach ($module_list as $module) {
    if ($files[$module]->requires) {
      // Create a list of dependencies that haven't been installed yet.
      $dependencies = array_keys($files[$module]->requires);
      $dependencies = array_filter($dependencies, 'vopros_filter_dependencies');
      // Add them to the module list.
      $module_list = array_merge($module_list, $dependencies);
    }
  }
  $module_list = array_unique($module_list);
  foreach ($module_list as $module) {
    $modules_sorted[$module] = $files[$module]->sort;
  }
  arsort($modules_sorted);

  $operations = array();
  foreach ($modules_sorted as $module => $weight) {
    $operations[] = array(
      '_vopros_enable_module',
      array(
        $module,
        $files[$module]->info['name'],
      ),
    );
  }

  return $operations;
}

/**
 * Enables an module.
 *
 * @param string $module
 *   The modules machine name.
 * @param string $module_name
 *   The modules human name.
 * @param array $context
 *   The context of the batch job.
 */
function _vopros_enable_module($module, $module_name, &$context) {
  module_enable(array($module), FALSE);
  $context['message'] = st('Installed %module module.', array('%module' => $module_name));
}


/**
 * Helper function to filter out already enabled modules.
 *
 * @param string $dependency
 *   Name of the module that we want to check.
 *
 * @return bool
 *   If module exists and is enabled FALSE else TRUE.
 */
function vopros_filter_dependencies($dependency) {
  return !module_exists($dependency);
}

/**
 * Enable selected vopros modules as a batch process.
 */
function vopros_module_enable(&$install_state) {
  $modules = variable_get('vopros_module_selected', array());

  $operations = vopros_module_list_as_operations($modules);

  $batch = array(
    'title' => st('Enabling additional options'),
    'operations' => $operations,
  );

  variable_del('vopros_module_selected');

  return $batch;
}
