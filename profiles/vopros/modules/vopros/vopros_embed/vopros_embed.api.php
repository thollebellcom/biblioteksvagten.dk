<?php

/**
 * @file
 * Hooks provided by the Vopros embed module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter the tab CSS.
 */
function hook_vopros_embed_tab_style_alter(&$styles) {
  // Totally override style sheet.
  $styles['processed'] = array(
    drupal_get_path('theme', 'watchmen') . '/css/ask_vopros.css',
  );
  // Add FontAwesome.
  $styles['external'][] = '//maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css';
}

/**
 * @} End of "defgroup update_api".
 */
