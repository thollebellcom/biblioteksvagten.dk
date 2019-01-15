<?php
/**
 * @file
 * vopros_simple_text_format.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function vopros_simple_text_format_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: simple_text
  $profiles['simple_text'] = array(
    'format' => 'simple_text',
    'editor' => 'ckeditor',
    'settings' => array(
      'buttons' => array(
        'default' => array(
          'Bold' => 1,
          'Italic' => 1,
          'Underline' => 1,
          'Strike' => 1,
          'Link' => 1,
          'Unlink' => 1,
          'Paste' => 1,
          'PasteText' => 1,
          'PasteFromWord' => 1,
        ),
      ),
      'theme' => '',
      'language' => 'da',
      'toolbarLocation' => 'top',
      'resize_enabled' => 1,
      'default_toolbar_grouping' => 0,
      'simple_source_formatting' => 0,
      'css_setting' => 'theme',
      'css_theme' => '',
      'css_path' => '',
      'stylesSet' => '',
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'forcePasteAsPlainText' => 0,
      'pasteFromWordNumberedHeadingToList' => 0,
      'pasteFromWordPromptCleanup' => 0,
      'pasteFromWordRemoveFontStyles' => 1,
      'pasteFromWordRemoveStyles' => 1,
    ),
    'preferences' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 1,
      'add_to_summaries' => 1,
      'version' => '3.6.2.7275',
    ),
    'name' => 'formatsimple_text',
  );

  return $profiles;
}
