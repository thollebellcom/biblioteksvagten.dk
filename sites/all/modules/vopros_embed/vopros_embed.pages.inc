<?php

/**
 * @file
 * Page and form callbacks.
 */

/**
 * Form builder.
 *
 * Returns a form for asking a question.
 */
function vopros_embed_question($form, &$form_state) {
  $form['#attached'] = array(
    'css' => array(drupal_get_path('module', 'vopros_embed') . '/css/vopros_embed.css'),
  );

  $agency_id = isset($_GET['agency_id']) ? check_plain($_GET['agency_id']) : '';

  // We can't work without an agency.
  if (empty($agency_id)) {
    $form['error'] = array(
      '#markup' => t('Whoops, widget not configured properly. Please contact the site and tell them about this.'),
    );

    return $form;
  }

  $question = vopros_question_new();
  $form['question'] = array(
    '#type' => 'value',
    '#value' => $question,
  );

  // Fall back to Referer header.
  $referrer = isset($_GET['url']) ? check_plain($_GET['url']) : $_SERVER['HTTP_REFERER'];

  $agency_mail = isset($_GET['agency_mail']) ? check_plain($_GET['agency_mail']) : '';

  $popup = isset($_GET['popup']);

  $focus_script = <<<EOF
jQuery(document).ready(function ($) {
  \$('.form-item-question-content textarea').focus();
});
EOF;

  $form['question_content'] = array(
    '#type' => 'textarea',
    '#title' => t('Question content'),
    '#required' => TRUE,
    '#default_value' => '',
    '#weight' => -70,
    '#attached' => array(
      'js' => array(
        $focus_script => array('type' => 'inline'),
      ),
    ),
  );

  $form['user_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
    '#default_value' => isset($_GET['name']) ? check_plain($_GET['name']) : '',
    '#weight' => -60,
  );

  $form['user_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal code'),
    '#required' => TRUE,
    '#default_value' => isset($_GET['zip']) ? check_plain($_GET['zip']) : '',
    '#weight' => -50,
  );

  // Pick out a specific subset of options.
  $options = array_intersect_key(_vopros_question_user_answer_preference(), array('mail' => TRUE, 'sms' => TRUE));
  $form['user_answer_preference'] = array(
    '#type' => 'radios',
    '#title' => t('How to recieve answer'),
    '#options' => $options,
    '#default_value' => 'mail',
    '#weight' => -40,
  );

  $form['user_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#default_value' => isset($_GET['mail']) ? check_plain($_GET['mail']) : '',
    '#states' => array(
      'visible' => array(
        'input[name=user_answer_preference]' => array('value' => 'mail'),
      ),
    ),
    '#weight' => -30,
  );

  $form['user_mobile_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile phone'),
    '#default_value' => isset($_GET['phone']) ? check_plain($_GET['phone']) : '',
    '#states' => array(
      'visible' => array(
        'input[name=user_answer_preference]' => array('value' => 'sms'),
      ),
    ),
    '#weight' => -20,
  );

  $deadline_options = _vopros_question_deadline();
  $form['question_deadline'] = array(
    '#type' => 'radios',
    '#title' => t('Deadline'),
    '#required' => TRUE,
    '#options' => $deadline_options,
    '#default_value' => -1,
    '#weight' => -10,
  );

  $form['agency_id'] = array(
    '#type' => 'value',
    '#value' => $agency_id,
  );

  $form['agency_mail'] = array(
    '#type' => 'value',
    '#value' => $agency_mail,
  );

  $form['from_url'] = array(
    '#type' => 'value',
    '#value' => $referrer,
  );

  $form['popup'] = array(
    '#type' => 'value',
    '#value' => $popup,
  );

  $form['form']['question_usage'] = array(
    '#type' => 'value',
    '#value' => variable_get('vopros_question_usage_default', ''),
  );

  if (module_exists('vopros_editorial')) {
    // We have to call field_attach_form, else it wont copy over the values to
    // the entity in field_attach_submit().
    field_attach_form('vopros_question', $question, $form, $form_state, NULL, array('field_name' => 'vopros_editorial'));

    // Hardcoded.
    $form['vopros_editorial']['und']['#type'] = 'value';
    $form['vopros_editorial']['und']['#value'] = 2;
  }

  // Remove the pre_render callback that field_attach_form added. We don't want
  // it to reorder the form elements.
  unset($form['#pre_render']);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit question'),
    '#attributes' => array('class' => array('primary-action')),
  );

  $form['help'] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => 'Biblioteksvagten er de danske bibliotekers nationale spørgetjeneste, hvor en lang række biblioteker arbejder sammen om at besvare spørgsmål fra brugere i hele landet.',
  );

  $image = array(
    'path' => drupal_get_path('module', 'vopros_embed') . '/images/bvagt_logo_mid.jpg',
    'alt' => 'Biblioteksvagten.dk',
  );
  $form['image'] = array(
    '#prefix' => '<div>',
    '#suffix' => '</div>',
    '#markup' => theme('image', $image),
  );

  return $form;
}

/**
 * Validate handler for vopros_embed_question().
 */
function vopros_embed_question_validate($form, &$form_state) {
  if ($form_state['values']['user_answer_preference'] == 'mail' &&
    empty($form_state['values']['user_email'])) {
    form_error($form['user_email'], t('E-mail required.'));
    // Unset sms in case it was prepopulated.
    form_set_value($form['user_mobile_phone'], '', $form_state);
  }

  if ($form_state['values']['user_answer_preference'] == 'sms' &&
    empty($form_state['values']['user_mobile_phone'])) {
    form_error($form['user_mobile_phone'], t('Mobile phone number required.'));
    // Unset E-mail in case it was prepopulated.
    form_set_value($form['user_email'], '', $form_state);
  }

  // Validate fields.
  field_attach_validate('vopros_question', $question, $form, $form_state);

}

/**
 * Submit handler for vopros_embed_question().
 */
function vopros_embed_question_submit($form, &$form_state) {
  $question = $form_state['values']['question'];
  $info = entity_get_property_info('vopros_question');

  foreach ($info['properties'] as $key => $property) {
    if (isset($form_state['values'][$key])) {
      $question->{$key} = $form_state['values'][$key];
    }
  }
  $log = array();

  // Ensure that there's an qanda_service_name fer this sender.
  $agency_id = $question->agency_id;
  $qanda_options = _vopros_question_qanda_serice_options();
  if (!isset($qanda_options[$agency_id])) {
    $options = variable_get('vopros_question_qanda_service_options', '');
    // @todo look up agency name.
    $new_options = trim($options) . "\n" . $agency_id . '|' . $agency_id . "\n";
    variable_set('vopros_question_qanda_service_options', $new_options);
  }
  $question->qanda_service_name = $agency_id;

  field_attach_submit('vopros_question', $question, $form, $form_state);

  // Save question.
  $question->save();

  if (module_exists('vopros_log')) {
    if ($form_state['values']['from_url']) {
      $log[] = "Sendt fra " . $form_state['values']['from_url'];
    }

    if ($form_state['values']['agency_mail']) {
      $log[] = "Videresend til " . $form_state['values']['agency_mail'] . " hvis dette er et spørgsmål der bedre kan besvares lokalt.";
    }
    // Save log entry.
    $values = array(
      'question_id' => $question->question_id,
      // 'answer_id' => NULL,
      'log_content' => implode("\n", $log),
      // 'uid' => NULL,
    );
    $log = vopros_log_new($values);
    vopros_log_save($log);
  }

  // If the form was not shown from a popup, add the originating URL to the
  // path, so we can add a return link.
  if (!$form_state['values']['popup']) {
    $query = array('destination' => $form_state['values']['from_url']);
  }

  $form_state['redirect'] = array('embed/ask-question/submitted', array('query' => $query));
}

/**
 * Page callback for the question submitted page.
 */
function vopros_embed_question_submitted_page() {
  $build[] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => t('Your question has been submitted.'),
    '#attached' => array(
      'css' => array(drupal_get_path('module', 'vopros_embed') . '/css/vopros_embed.css'),
    'js' => array(drupal_get_path('module', 'vopros_embed') . '/js/vopros_embed_popup.js'),
    ),
  );

  $opening_hours = array(
    array(
      'data' => array(
        'Mandag-torsdag:',
        array('data' => 'kl. 8.00 - 22.00', 'class' => 'hours'),
      )
    ),
    array(
      'data' => array(
        'Fredag:',
        array('data' => 'kl. 8.00 - 20.00', 'class' => 'hours'),
      ),
    ),
    array(
      'data' => array(
        'Lørdag:',
        array('data' => 'kl. 8.00 - 16.00', 'class' => 'hours'),
      ),
    ),
    array(
      'data' => array(
        'Søndag:',
        array('data' => 'kl.14.00 - 22.00', 'class' => 'hours'),
      ),
    ),
  );

  $build[] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => theme('table', array('rows' => $opening_hours, 'caption' => 'Biblioteksvagten er online:')),
  );

  // Add return button.
  if (isset($_GET['destination'])) {
    $build[] = array(
      '#prefix' => '<p>',
      '#suffix' => '</p>',
      '#markup' => l(t('Return'), $_GET['destination']),
    );
  }
  return $build;
}

/**
 * Return JavaScript for popup.
 */
function vopros_embed_question_modal_js() {
  drupal_add_http_header('Content-Type', 'application/javascript');

  $base = drupal_get_path('module', 'vopros_embed');
  $libraries = array(
    // Add our own copy of jQuery.
    $base . '/libraries/jquery-1.11.1.min.js',
    // Add jQuery migrate to reintroduce functions BBQ needs.
    $base . '/libraries/jquery-migrate-1.2.1.min.js',
    // Add BBQ for URL query string manipulation.
    $base . '/libraries/bbq-1.2.1/jquery.ba-bbq.min.js',
    // Add Magific Popup.
    $base . '/libraries/magnific-popup-0.9.9/jquery.magnific-popup.min.js',
  );

  $js = '';
  foreach ($libraries as $lib) {
    $js .= file_get_contents($lib);
    $js .= "\n";
  }

  $ask_url = url('embed/ask-question', array('absolute' => TRUE));

  // Add our own code.
  $our_js = file_get_contents($base . '/js/vopros_embed.js');
  $css = array(
    '!mag_style' => url($base . '/libraries/magnific-popup-0.9.9/magnific-popup.css', array('absolute' => TRUE)),
    '!vopros_style' => url($base . '/css/vopros_embed_popup.css', array('absolute' => TRUE)),
    '!ask_url' => $ask_url,
  );
  $js .= strtr($our_js, $css);
  $js .= "\n";

  print $js;
}
