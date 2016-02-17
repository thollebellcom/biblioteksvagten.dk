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
  // @todo implement configuration of forms on the clients.
  $agency_id = isset($_GET['agency_id']) ? check_plain($_GET['agency_id']) : '';

  $client = vopros_question_client_load_by_agency($agency_id);
  // We can't work without an agency.
  if (empty($client)) {
    if (empty($agency_id)) {
      $form['error'] = array(
        '#markup' => t('Whoops, widget not configured properly. Please contact the site and tell them about this.'),
      );
    }
    else {
      $form['error'] = array(
        '#markup' => t('@site_name has yet to approve questions from this site. Please contact @site_mail with the agency code "@agency_id".', array(
                     '@site_name' => variable_get('site_name', 'Vopros'),
                     '@site_mail' => variable_get('site_mail', '<unknown>'),
                     '@agency_id' => $agency_id,
                   )),
      );
    }
    return $form;
  }

  // Custom theme function to lay out the form.
  $form['#theme'] = array('vopros_embed_question_form');

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

  $options = _vopros_embed_answer_preferences();

  $answer_preference = 'mail';
  if (isset($_GET['answer_preference']) &&
    isset($options[$_GET['answer_preference']])) {
    $answer_preference = $_GET['answer_preference'];
  }

  $form['user_answer_preference'] = array(
    '#type' => 'radios',
    '#title' => t('How to receive answer'),
    '#options' => $options,
    '#default_value' => $answer_preference,
    '#weight' => -70,
    '#attributes' => array(
      'class' => array('options-' . count($options)),
    ),
  );

  $form['question_content'] = array(
    '#type' => 'textarea',
    '#title' => t("What's your question?"),
    '#required' => TRUE,
    '#default_value' => '',
    '#weight' => -60,
    '#attached' => array(
      'js' => array(
        $focus_script => array('type' => 'inline'),
      ),
    ),
  );

  $form['user_name'] = array(
    '#type' => 'textfield',
    '#title' => t("What's your name?"),
    '#required' => TRUE,
    '#default_value' => isset($_GET['name']) ? check_plain($_GET['name']) : '',
    '#weight' => -50,
  );

  $form['user_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your e-mail address'),
    '#default_value' => isset($_GET['mail']) ? check_plain($_GET['mail']) : '',
    '#states' => array(
      'visible' => array(
        'input[name=user_answer_preference]' => array(
          array('value' => 'mail'),
          array('value' => 'chat'),
        ),
      ),
      'required' => array(
        'input[name=user_answer_preference]' => array(
          array('value' => 'mail'),
          array('value' => 'chat'),
        ),
      ),
    ),
    '#weight' => -40,
  );

  $form['user_mobile_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter your cell number'),
    '#default_value' => isset($_GET['phone']) ? check_plain($_GET['phone']) : '',
    '#states' => array(
      'visible' => array(
        'input[name=user_answer_preference]' => array('value' => 'sms'),
      ),
      'required' => array(
        'input[name=user_answer_preference]' => array('value' => 'sms'),
      ),
    ),
    '#weight' => -30,
  );

  $form['user_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t("What's your zip code?"),
    '#default_value' => isset($_GET['zip']) ? check_plain($_GET['zip']) : '',
    '#states' => array(
      'visible' => array(
        'input[name=user_answer_preference]' => array(
          array('value' => 'mail'),
          array('value' => 'sms'),
        ),
      ),
    ),
    '#weight' => -20,
  );

  $show_deadline = array_filter(variable_get('vopros_embed_show_deadline', array('mail', 'sms')));
  if ($show_deadline) {
    $values = array();
    foreach ($show_deadline as $option) {
      $values[] = array('value' => $option);
    }
    $deadline_options = _vopros_question_deadline();
    $form['question_deadline'] = array(
      '#type' => 'radios',
      '#title' => t('When do you need the answer?'),
      '#required' => TRUE,
      '#options' => $deadline_options,
      '#default_value' => -1,
      '#weight' => -10,
      '#states' => array(
        'visible' => array(
          'input[name=user_answer_preference]' => $values,
        ),
      ),
    );
  }
  else {
    $form['question_deadline'] = array(
      '#type' => 'value',
      '#value' => -1,
      '#weight' => -10,
    );
  }

  $form['client_id'] = array(
    '#type' => 'value',
    '#value' => $client->client_id,
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

  $form['question_usage'] = array(
    '#type' => 'value',
    '#value' => variable_get('vopros_question_usage_default', ''),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit question'),
    '#attributes' => array('class' => array('primary-action')),
    '#states' => array(
      'invisible' => array(
        'input[name=user_answer_preference]' => array('value' => 'chat'),
      ),
    ),
  );

  // This a copy of $form['submit'] with just the label changed and only show
  // when chat is chosen as user answer preference.
  $form['submit-chat'] = array(
    '#type' => 'submit',
    '#value' => t('Start chat'),
    '#attributes' => array('class' => array('primary-action', 'chat-submit')),
    '#states' => array(
      'visible' => array(
        'input[name=user_answer_preference]' => array('value' => 'chat'),
      ),
    ),
  );

  return $form;
}

/**
 * Validate handler for vopros_embed_question().
 */
function vopros_embed_question_validate($form, &$form_state) {
  if (in_array($form_state['values']['user_answer_preference'], array('mail', 'chat'))) {
    if (empty($form_state['values']['user_email'])) {
      form_error($form['user_email'], t('E-mail required.'));
    }
    if (!valid_email_address($form_state['values']['user_email'])) {
      form_error($form['user_email'], t('E-mail invalid.'));
    }
  }

  if ($form_state['values']['user_answer_preference'] == 'sms' &&
    empty($form_state['values']['user_mobile_phone'])) {
    form_error($form['user_mobile_phone'], t('Mobile phone number required.'));
  }

  // Unset mail in case it was prepopulated.
  if ($form_state['values']['user_answer_preference'] == 'sms') {
    form_set_value($form['user_email'], '', $form_state);
  }

  // Unset sms in case it was prepopulated.
  if ($form_state['values']['user_answer_preference'] != 'sms') {
    form_set_value($form['user_mobile_phone'], '', $form_state);
  }
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

  $question->channel = $form_state['values']['user_answer_preference'] == 'chat' ? 'chat' : 'webform';
  $question->channel_data = array(
    'from_url' => $form_state['values']['from_url'],
    'site_email' => $form_state['values']['agency_mail'],
  );

  // Save question.
  $question->save();

  // If the form was not shown from a popup, add the originating URL to the
  // path, so we can add a return link.
  if (!$form_state['values']['popup']) {
    $query = array('destination' => $form_state['values']['from_url']);
  }

  if ($form_state['values']['user_answer_preference'] == 'chat' && module_exists('vopros_chat')) {
    // Redirect chats to the chat page.
    $form_state['redirect'] = array(vopros_chat_url($question), array('query' => $query));
  }
  else {
    // Else redirect to the confirmation page.
    $form_state['redirect'] = array('embed/ask-question/submitted', array('query' => $query));
  }
}

/**
 * Page callback for the question submitted page.
 */
function vopros_embed_question_submitted_page() {
  $build = array();

  $build[] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => t('Your question has been submitted.'),
  );

  $build[] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => vopros_embed_popup_close_link(check_plain(t('Close window'))),
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

  // Required styles.
  $styles = array(
    url($base . '/libraries/magnific-popup-0.9.9/magnific-popup.css', array('absolute' => TRUE)),
    url($base . '/css/vopros_embed_popup.css', array('absolute' => TRUE)),
  );

  // Allow module/themes to override tab styles.
  $tab_styles = array();
  drupal_alter('vopros_embed_tab_style', $tab_styles);
  if (empty($tab_styles)) {
    $tab_styles = array(url($base . '/css/vopros_embed_tab.css', array('absolute' => TRUE)));
  }

  $styles = array_merge($styles, $tab_styles);

  // Prepare query for link.
  $query = array_intersect_key($_GET, array_flip(array('agency_id', 'url', 'agency_mail', 'popup', 'answer_preference', 'destination')));

  $tab_title = format_string(variable_get('vopros_embed_tab_title', 'Ask @site_name'), array('@site_name' => variable_get('site_name', 'Drupal')));

  // Include the volatile script inline in the function.
  $volatile = file_get_contents($base . '/js/vopros_embed_volatile.js');

  // Render our code.
  $our_js = file_get_contents($base . '/js/vopros_embed.js');
  $settings = array(
    'styles' => $styles,
    'ask_url' => $ask_url,
    'tab' => theme('vopros_embed_tab', array('title' => $tab_title, 'url' => $ask_url)),
    'add_tab' => isset($_GET['tab']),
    'query' => $query,
    'confirm_message' => t('Are you sure you want to close?'),
  );

  $replacements = array(
    '!settings' => json_encode($settings),
    '!volatile' => $volatile,
  );

  // And add it to the collected JS.
  $js .= strtr($our_js, $replacements);
  $js .= "\n";

  print $js;
}
