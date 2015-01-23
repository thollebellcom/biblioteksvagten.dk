<?php
/**
 * @file
 * Administrative page for vopros_chat.
 */

/**
 * Form callback.
 *
 * Settings form.
 */
function vopros_embed_setting_form($form, &$form_state) {
  $form['appearance'] = array(
    '#type' => 'fieldset',
    '#title' => t('Appearance'),
  );

  $form['appearance']['vopros_embed_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => variable_get('vopros_embed_title', 'Ask @site_name'),
    '#description' => t('Main title of the page. Use <em>@site_name</em> to insert the site title.'),
  );

  $form['appearance']['vopros_embed_tab_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Tab title'),
    '#default_value' => variable_get('vopros_embed_tab_title', 'Ask @site_name'),
    '#description' => t('Title of the tab used on client sites.. Use <em>@site_name</em> to insert the site title.'),
  );

  $form['embed'] = array(
    '#type' => 'fieldset',
    '#title' => t('Embed code'),
  );

  $form['embed']['agency_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Agency id'),
    '#input' => FALSE,
    '#description' => t('The agency id of the site, DK-<num> for libraries, custom string for others.'),
  );

  $form['embed']['agency_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('Local email'),
    '#input' => FALSE,
    '#description' => t('The email address to direct local inquiries to.'),
  );

  $form['embed']['answer_preference'] = array(
    '#type' => 'radios',
    '#title' => t('Default answer method'),
    '#options' => _vopros_embed_answer_preferences(),
    '#input' => FALSE,
    '#description' => t('Which answer method should be initially selected?'),
  );

  $form['embed']['tab'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create tab'),
    '#input' => FALSE,
    '#description' => t('Automatically create tab.'),
  );

  // The Drupal.formatString JS function doesn't support replacing each
  // placeholder more than once, so use different placeholders.
  // Using async and defer is the currently recommend practice,
  // @see https://www.igvita.com/2014/05/20/script-injected-async-scripts-considered-harmful/
  $code = '<script src="!script_base/question_modal.js" async defer></script>
<a href="!form_base/ask-question?!params">Ask a question</a>
';
  $tab_code = '<script src="!script_base/question_modal.js?tab=true&!params" async defer></script>
';

  $form['embed']['code'] = array(
    '#type' => 'textarea',
    '#title' => t('Code'),
    '#input' => FALSE,
    '#attached' => array(
      'js' => array(
        drupal_get_path('module', 'vopros_embed') . '/js/vopros_embed.admin.js',
        array(
          'type' => 'setting',
          'data' => array(
            'voprosEmbed' => array(
              'template' => $code,
              'tab_template' => $tab_code,
              'base' => url('embed', array('absolute' => TRUE)),
            ),
          ),
        ),
      ),
    ),
    '#description' => t('Copy this code to the site. The script element can be moved to the HEAD section of the page.'),
  );

  return system_settings_form($form);
}
