<?php

/**
 * @file
 * Admin functions for Vopros statistics module.
 */

/**
 * Display statistics for a year.
 */
function vopros_statistics_year_view($year = NULL) {
  $csv = $_GET['csv'];

  if (empty($year)) {
    $year = date('Y', REQUEST_TIME);
  }

  // Generate all of the weeks.
  $dates = array();
  foreach (range(1, 52) as $week_num) {
    $dates[$week_num] = array(
      ':start' => strtotime($year . 'W' . sprintf("%02d", $week_num) . '1'),
      ':end' => strtotime($year . 'W' . sprintf("%02d", $week_num + 1) . '1'),
    );

    if ($dates[$week_num][':end'] > REQUEST_TIME) {
      break;
    }
  }

  $header = array(t('Week number'), t('Total questions'));
  if (module_exists('vopros_editorial')) {
    $vocab = taxonomy_vocabulary_machine_name_load('vopros_editorial');
    $terms = taxonomy_term_load_multiple(FALSE, array('vid' => $vocab->vid));
    foreach ($terms as $term) {
      $header[] = $term->name;
    }
  }
  $rows = array();

  foreach ($dates as $week => $where) {
    $question_ids = db_query("SELECT question_id FROM {vopros_question} WHERE created >= :start AND created <= :end", $where)->fetchAllKeyed(0, 0);
    $row = array(
      $week,
      count($question_ids),
    );
    $question_ids[] = 0;
    if (!empty($terms)) {
      $editorials = db_query("SELECT COUNT(*), vopros_editorial_tid FROM field_data_vopros_editorial
                              WHERE entity_id IN (:question_ids) GROUP BY vopros_editorial_tid", array(':question_ids' => $question_ids))->fetchAllKeyed(1, 0);
      foreach ($terms as $tid => $term) {
        $row[] = $editorials[$tid];
      }
    }

    $rows[] = $row;
  }

  if ($csv === 'yes') {
    _vopros_statistics_download_send_headers("statistics-year-" . date("Y-m-d") . ".csv");
    echo _vopros_statistics_array2csv($header, $rows);

    die();
  }

  $build = array(
    'csv' => array(
      '#markup' => l(t('Download as CSV'),
        $_GET['q'],
        array(
          'query' => array('csv' => 'yes'),
          'attributes' => array('target' => '_blank'),
        )),
      '#prefix' => '<div><br />',
      '#suffix' => '</div>',
    ),
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    ),
  );

  return $build;
}

/**
 * Display count of created questions devided by the time it was created.
 */
function vopros_statistics_week_view($start = NULL, $end = NULL) {
  $csv = $_GET['csv'];

  if (!$end) {
    $end = REQUEST_TIME;
  }
  if (!$start) {
    $start = REQUEST_TIME - 86400 * 7;
  }

  $result = db_query("SELECT DAYNAME(FROM_UNIXTIME(q.created)) AS day_name, COUNT(*) AS questions FROM {vopros_question} AS q
            WHERE created < :end
            AND created > :start
            GROUP BY day_name", array(':end' => $end, ':start' => $start))->fetchAllKeyed(0, 1);

  $header = array(t('Week day'), t('Total questions created'));
  $rows = array();
  // Create a unix timestamp for a random date that has the time 00:00:00.
  $weeks = array(
    'Monday' => t('Monday'),
    'Tuesday' => t('Tuesday'),
    'Wednesday' => t('Wednesday'),
    'Thursday' => t('Thursday'),
    'Friday' => t('Friday'),
    'Saturday' => t('Saturday'),
    'Sunday' => t('Sunday'),
  );

  // Create the total count.
  foreach ($weeks as $week_day => $label) {
    $rows[$week_day] = array($label, isset($result[$week_day]) ? $result[$week_day] : 0);
  }

  // Get statistics for each editorial.
  if (module_exists('vopros_editorial')) {
    $vocab = taxonomy_vocabulary_machine_name_load('vopros_editorial');
    $terms = taxonomy_term_load_multiple(FALSE, array('vid' => $vocab->vid));
    foreach ($terms as $tid => $term) {
      $header[] = $term->name;
      $result = db_query("SELECT DAYNAME(FROM_UNIXTIME(q.created)) AS day_name, COUNT(*) AS questions FROM {vopros_question} AS q
                                              INNER JOIN {field_data_vopros_editorial} AS f ON f.entity_id = q.question_id
                                              WHERE q.created < :end
                                              AND q.created > :start
                                              AND f.vopros_editorial_tid = :tid
                                              GROUP BY day_name", array(
                                                ':tid' => $tid,
                                                ':end' => $end,
                                                ':start' =>
                                                $start,
                                              ))->fetchAllKeyed(0, 1);
      foreach ($weeks as $week_day => $label) {
        $rows[$week_day][] = isset($result[$week_day]) ? $result[$week_day] : 0;
      }
    }
  }

  if ($csv === 'yes') {
    _vopros_statistics_download_send_headers("statistics-week-" . date("Y-m-d") . ".csv");
    echo _vopros_statistics_array2csv($header, $rows);

    die();
  }

  $build = array(
    'form' => drupal_get_form('vopros_statistics_week_form', $start, $end),
    'csv' => array(
      '#markup' => l(t('Download as CSV'),
        $_GET['q'],
        array(
          'query' => array('csv' => 'yes'),
          'attributes' => array('target' => '_blank'),
        )),
    ),
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    ),
  );

  return $build;
}

/**
 * Form for selecting the date range for the time statistics page.
 */
function vopros_statistics_week_form($form, &$form_state, $start, $end) {
  $form['start'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start for time range'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-10:+1',
    '#default_value' => date('Y-m-d', $start),
    '#required' => TRUE,
  );

  $form['end'] = array(
    '#type' => 'date_popup',
    '#title' => t('End for time range'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-10:+1',
    '#default_value' => date('Y-m-d', $end),
    '#required' => TRUE,
  );

  $form['get'] = array(
    '#type' => 'submit',
    '#value' => t('Get statistics'),
  );

  return $form;
}

/**
 * Submit handler for vopros_statistics_time_form()
 */
function vopros_statistics_week_form_submit($form, &$form_state) {
  $start = strtotime($form_state['values']['start']);
  $end = strtotime($form_state['values']['end']);
  $form_state['redirect'] = "admin/vopros/statistics/week/$start/$end";
}

/**
 * Display count of created questions devided by the time it was created.
 */
function vopros_statistics_time_view($start = NULL, $end = NULL) {
  $csv = $_GET['csv'];

  if (!$end) {
    $end = REQUEST_TIME;
  }
  if (!$start) {
    $start = REQUEST_TIME - 86400 * 7;
  }

  $result = db_query("SELECT HOUR(FROM_UNIXTIME(q.created)) AS created_hour, COUNT(*) AS questions FROM {vopros_question} AS q
            WHERE created < :end
            AND created > :start
            GROUP BY created_hour
            ORDER BY created_hour", array(':end' => $end, ':start' => $start))->fetchAllKeyed(0, 1);

  $header = array(t('Time'), t('Questions created'));
  $rows = array();
  // Create a unix timestamp for a random date that has the time 00:00:00.
  $start_time = strtotime('2000-12-12 00:00:00');
  foreach (range(0, 23) as $time) {
    $count = isset($result[$time]) ? $result[$time] : 0;
    $rows[$time] = array(
      date('H:i:s', $start_time + $time * 3600) . ' - ' .
      date('H:i:s', $start_time + $time * 3600 + 3599), $count,
    );
  }

  if (module_exists('vopros_editorial')) {
    $vocab = taxonomy_vocabulary_machine_name_load('vopros_editorial');
    $terms = taxonomy_term_load_multiple(FALSE, array('vid' => $vocab->vid));
    foreach ($terms as $tid => $term) {
      $header[] = $term->name;
      $result = db_query("SELECT HOUR(FROM_UNIXTIME(q.created)) AS created_hour, COUNT(*) AS questions FROM {vopros_question} AS q
                          INNER JOIN {field_data_vopros_editorial} AS f ON f.entity_id = q.question_id
                          WHERE created < :end
                          AND created > :start
                          AND f.vopros_editorial_tid = :tid
                          GROUP BY created_hour
                          ORDER BY created_hour", array(
                            ':end' => $end,
                            ':start' => $start,
                            ':tid' => $tid,
                          ))->fetchAllKeyed(0, 1);
      foreach (range(0, 23) as $time) {
        $rows[$time][] = isset($result[$time]) ? $result[$time] : 0;
      }
    }
  }

  if ($csv === 'yes') {
    _vopros_statistics_download_send_headers("statistics-time-" . date("Y-m-d") . ".csv");
    echo _vopros_statistics_array2csv($header, $rows);

    die();
  }

  $build = array(
    'form' => drupal_get_form('vopros_statistics_time_form', $start, $end),
    'csv' => array(
      '#markup' => l(t('Download as CSV'),
        $_GET['q'],
        array(
          'query' => array('csv' => 'yes'),
          'attributes' => array('target' => '_blank'),
        )),
    ),
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    ),
  );
  return $build;
}

/**
 * Form for selecting the date range for the time statistics page.
 */
function vopros_statistics_time_form($form, &$form_state, $start, $end) {
  $form['start'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start for time range'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-10:+1',
    '#default_value' => date('Y-m-d', $start),
    '#required' => TRUE,
  );

  $form['end'] = array(
    '#type' => 'date_popup',
    '#title' => t('End for time range'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-10:+1',
    '#default_value' => date('Y-m-d', $end),
    '#required' => TRUE,
  );

  $form['get'] = array(
    '#type' => 'submit',
    '#value' => t('Get statistics'),
  );

  return $form;
}

/**
 * Submit handler for vopros_statistics_time_form()
 */
function vopros_statistics_time_form_submit($form, &$form_state) {
  $start = strtotime($form_state['values']['start']);
  $end = strtotime($form_state['values']['end']);
  $form_state['redirect'] = "admin/vopros/statistics/time/$start/$end";
}

/**
 * Display statistics based on Q and A service names.
 */
function vopros_statistics_client_channels_view($start = NULL, $end = NULL) {
  $csv = $_GET['csv'];

  if (!$end) {
    $end = REQUEST_TIME;
  }
  if (!$start) {
    $start = REQUEST_TIME - 86400 * 7;
  }

  $clients = vopros_question_client_load_multiple();
  $channels = vopros_question_channels();

  // We are using the 0 tid for totals, cross editorial.
  $terms = array(0 => (object) array('name' => t('Total questions')));
  if (module_exists('vopros_editorial')) {
    $vocab = taxonomy_vocabulary_machine_name_load('vopros_editorial');
    $terms += taxonomy_term_load_multiple(FALSE, array('vid' => $vocab->vid));
  }

  // Get counts by client, channel and tid.
  $res = db_query("SELECT COUNT(*) AS count,
                      q.client_id AS client_id,
                      q.channel AS channel,
                      f.vopros_editorial_tid AS tid
                      FROM {vopros_question} AS q
                      LEFT JOIN {field_data_vopros_editorial} AS f
                      ON q.question_id = f.entity_id
                      WHERE created <= :end
                      AND created >= :start
                      GROUP BY client_id, channel, tid
                      ORDER BY client_id, channel, tid",
  array(':end' => $end, ':start' => $start));

  // Calculate totals and rearrange result for display.
  $totals = array();
  $column_totals = array();
  foreach ($res as $row) {
    // We handle the rows without a tid as tid 0. Means they're (mostly) not a
    // special case.
    $tid = $row->tid ? $row->tid : 0;
    $client_name = check_plain(isset($clients[$row->client_id]) ? $clients[$row->client_id]->label : '<unknown>');
    $channel_name = check_plain(isset($channels[$row->channel]) ? $channels[$row->channel]['name'] : '<unknown>');

    $totals[$client_name]['totals'][$tid] += $row->count;
    $totals[$client_name]['channels'][$channel_name][$tid] = $row->count;
    // Also add non-zero to the zero (the totals column) tid.
    if ($tid != 0) {
      $totals[$client_name]['totals'][0] += $row->count;
      $totals[$client_name]['channels'][$channel_name][0] += $row->count;
    }

    // Add everything to the column totals.
    $column_totals[$tid] += $row->count;
    // Again, add to the total column.
    if ($tid != 0) {
      $column_totals[0] += $row->count;
    }
  }

  $totals['<em>' . t('Total') . '</em>']['totals'] = $column_totals;

  $header = array(t('Client'));
  foreach ($terms as $tid => $term) {
    $header[] = $term->name;
  }

  $rows = array();
  foreach ($totals as $name => $data) {
    $row = array(
      $name,
    );
    foreach ($terms as $tid => $term) {
      $row[] = $data['totals'][$tid] + 0;
    }
    $rows[] = $row;
    foreach ($data['channels'] as $channel => $chan_data) {
      $row = array(
        ' - ' . $channel,
      );
      foreach ($terms as $tid => $term) {
        $row[] = $chan_data[$tid] + 0;
      }
      $rows[] = $row;

    }
  }

  if ($csv === 'yes') {
    _vopros_statistics_download_send_headers("statistics-channels-" . date("Y-m-d") . ".csv");
    echo _vopros_statistics_array2csv($header, $rows);

    die();
  }

  $build = array(
    'form' => drupal_get_form('vopros_statistics_client_channels_form', $start, $end),
    'csv' => array(
      '#markup' => l(t('Download as CSV'),
        $_GET['q'],
        array(
          'query' => array('csv' => 'yes'),
          'attributes' => array('target' => '_blank'),
        )),
    ),
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    ),
  );

  return $build;
}

/**
 * Form for selecting the date range for the time statistics page.
 */
function vopros_statistics_client_channels_form($form, &$form_state, $start, $end) {
  $form['start'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start for time range'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-10:+1',
    '#default_value' => date('Y-m-d', $start),
    '#required' => TRUE,
  );

  $form['end'] = array(
    '#type' => 'date_popup',
    '#title' => t('End for time range'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-10:+1',
    '#default_value' => date('Y-m-d', $end),
    '#required' => TRUE,
  );

  $form['get'] = array(
    '#type' => 'submit',
    '#value' => t('Get statistics'),
  );

  return $form;
}

/**
 * Submit handler for vopros_statistics_client_channels_form()
 */
function vopros_statistics_client_channels_form_submit($form, &$form_state) {
  $start = strtotime($form_state['values']['start']);
  $end = strtotime($form_state['values']['end']);
  $form_state['redirect'] = "admin/vopros/statistics/client_channels/$start/$end";
}

/**
 * Display statistics based on Q and A service names.
 */
function vopros_statistics_info_email_view($status = null) {
  $csv = $_GET['csv'];
  $build = array();
  $rows = array();

  if ($status === 0 || $status === 1) {

    // Grab all users.
    $query = new EntityFieldQuery();
    $entities = $query->entityCondition('entity_type', 'user', '=')
      ->propertyCondition('status', true)
      ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT')
      ->execute();

    $users = entity_load('user', array_keys($entities['user']));

    // Run through all users.
    foreach($users as $user) {
      $wants_to_recieve = true;

      // If no email is set (user 0), don't proceed.
      if (! $user->mail) continue;

      // If the user don't want to receive emails, don't proceed.
      if ($field = field_get_items('user', $user, 'field_no_info_mail')) {

        // The user doesn't want any emails.
        if ($field[0]['value'] === '1') {
          $wants_to_recieve = false;
        }
      }

      if ($wants_to_recieve == $status) {
        $rows[] = array($user->mail);
      }
    }

    $header = array(t('E-mail addresses (' . count($rows) . ')'));

    if ($csv === 'yes') {
      _vopros_statistics_download_send_headers("statistics-channels-" . date("Y-m-d") . ".csv");
      echo _vopros_statistics_array2csv($header, $rows);

      die();
    }

    $build = array(
      'form' => drupal_get_form('vopros_statistics_info_email_form', $status),
      'csv' => array(
        '#markup' => l(t('Download as CSV'),
          $_GET['q'],
          array(
            'query' => array('csv' => 'yes'),
            'attributes' => array('target' => '_blank'),
          )),
      ),
      'table' => array(
        '#theme' => 'table',
        '#header' => $header,
        '#rows' => $rows,
      ),
    );
  }

  return $build;
}

/**
 * Form for selecting the date range for the time statistics page.
 */
function vopros_statistics_info_email_form($form, &$form_state, $status) {
  $form['status'] = array(
    '#type' => 'radios',
    '#title' => t('Show users that have said:'),
    '#options' => array(
      0 => t('No'),
      1 => t('Yes')
    ),
    '#default_value' => $status,
  );

  $form['get'] = array(
    '#type' => 'submit',
    '#value' => t('Get statistics'),
  );

  return $form;
}

/**
 * Submit handler for vopros_statistics_client_channels_form()
 */
function vopros_statistics_info_email_form_submit($form, &$form_state) {
  $status = $form_state['values']['status'];

  $form_state['redirect'] = "admin/vopros/statistics/info-email/$status";
}




/**
 * Display statistics based on Q and A service names.
 */
function vopros_statistics_client_channels_column_view($start = NULL, $end = NULL) {
  $csv = $_GET['csv'];

  if (!$end) {
    $end = REQUEST_TIME;
  }
  if (!$start) {
    $start = REQUEST_TIME - 86400 * 7;
  }

  $clients = vopros_question_client_load_multiple();
  $channels = vopros_question_channels();

  // We are using the 0 tid for totals, cross editorial.
  $terms = array(0 => (object) array('name' => t('Total questions')));
  if (module_exists('vopros_editorial')) {
    $vocab = taxonomy_vocabulary_machine_name_load('vopros_editorial');
    $terms += taxonomy_term_load_multiple(FALSE, array('vid' => $vocab->vid));
  }

  // Get counts by client, channel and tid.
  $res = db_query("SELECT COUNT(*) AS count,
                      q.client_id AS client_id,
                      q.channel AS channel,
                      f.vopros_editorial_tid AS tid
                      FROM {vopros_question} AS q
                      LEFT JOIN {field_data_vopros_editorial} AS f
                      ON q.question_id = f.entity_id
                      WHERE created <= :end
                      AND created >= :start
                      GROUP BY client_id, channel, tid
                      ORDER BY client_id, channel, tid",
    array(':end' => $end, ':start' => $start));

  // Calculate totals and rearrange result for display.
  $totals = array();
  $column_totals = array();
  foreach ($res as $row) {
    // We handle the rows without a tid as tid 0. Means they're (mostly) not a
    // special case.
    $tid = $row->tid ? $row->tid : 0;
    $client_name = check_plain(isset($clients[$row->client_id]) ? $clients[$row->client_id]->label : '<unknown>');
    $channel_name = check_plain(isset($channels[$row->channel]) ? $channels[$row->channel]['name'] : '<unknown>');

    $totals[$client_name]['totals'][$tid] += $row->count;
    $totals[$client_name]['channels'][$channel_name][$tid] = $row->count;
    // Also add non-zero to the zero (the totals column) tid.
    if ($tid != 0) {
      $totals[$client_name]['totals'][0] += $row->count;
      $totals[$client_name]['channels'][$channel_name][0] += $row->count;
    }

    // Add everything to the column totals.
    $column_totals[$tid] += $row->count;
    // Again, add to the total column.
    if ($tid != 0) {
      $column_totals[0] += $row->count;
    }
  }

  // Default totals.
  $_totals['client'] = 'Totalt:';
  $_totals['total'] = 0;
  $_totals['chat'] = 0;
  $_totals['email'] = 0;
  $_totals['phone'] = 0;
  $_totals['sms'] = 0;
  $_totals['webform'] = 0;

  // Header.
  $header = array(
    t('Client'),
    t('Total number of questions'),
    t('Number of chat questions'),
    t('Number of email questions'),
    t('Number of phone questions'),
    t('Number of SMS questions'),
    t('Number of webform questions'),
  );

  // Rows.
  $rows = array();
  foreach ($totals as $name => $data) {
    $row = array();

    $chatCount = _collect_channel_data($data['channels']['Chat'][0]);
    $emailCount = _collect_channel_data($data['channels']['E-mail'][0]);
    $phoneCount = _collect_channel_data($data['channels']['Telefon'][0]);
    $smsCount = _collect_channel_data($data['channels']['SMS'][0]);
    $webformCount = _collect_channel_data($data['channels']['Webform'][0]);

    $totalCount = $chatCount + $emailCount + $phoneCount + $smsCount + $webformCount;

    $row['client'] = $name;
    $row['total'] = $totalCount;
    $row['chat'] = $chatCount;
    $row['email'] = $emailCount;
    $row['phone'] = $phoneCount;
    $row['sms'] = $smsCount;
    $row['webform'] = $webformCount;

    $rows[] = $row;

    // Update totals.
    $_totals['total'] = $_totals['total'] + $totalCount;
    $_totals['chat'] = $_totals['chat'] + $chatCount;
    $_totals['email'] = $_totals['email'] + $emailCount;
    $_totals['phone'] = $_totals['phone'] + $phoneCount;
    $_totals['sms'] = $_totals['sms'] + $smsCount;
    $_totals['webform'] = $_totals['webform'] + $webformCount;
  }

  // Add totals.
  $rows[] = $_totals;

  if ($csv === 'yes') {
    _vopros_statistics_download_send_headers("statistics-channels-" . date("Y-m-d") . ".csv");
    echo _vopros_statistics_array2csv($header, $rows);

    die();
  }

  $build = array(
    'form' => drupal_get_form('vopros_statistics_client_channels_column_form', $start, $end),
    'csv' => array(
      '#markup' => l(t('Download as CSV'),
        $_GET['q'],
        array(
          'query' => array('csv' => 'yes'),
          'attributes' => array('target' => '_blank'),
        )),
    ),
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
    ),
  );

  return $build;
}

function _collect_channel_data($count) {
  if ($count === null) {
    $count = 0;
  }

  return $count;
}

/**
 * Form for selecting the date range for the time statistics page.
 */
function vopros_statistics_client_channels_column_form($form, &$form_state, $start, $end) {
  $form['start'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start for time range'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-10:+1',
    '#default_value' => date('Y-m-d', $start),
    '#required' => TRUE,
  );

  $form['end'] = array(
    '#type' => 'date_popup',
    '#title' => t('End for time range'),
    '#date_format' => 'd-m-Y',
    '#date_year_range' => '-10:+1',
    '#default_value' => date('Y-m-d', $end),
    '#required' => TRUE,
  );

  $form['get'] = array(
    '#type' => 'submit',
    '#value' => t('Get statistics'),
  );

  return $form;
}

/**
 * Submit handler for vopros_statistics_client_channels_form()
 */
function vopros_statistics_client_channels_column_form_submit($form, &$form_state) {
  $start = strtotime($form_state['values']['start']);
  $end = strtotime($form_state['values']['end']);
  $form_state['redirect'] = "admin/vopros/statistics/client_channels_column/$start/$end";
}

function _vopros_statistics_array2csv(array &$header, array &$content) {
  $array = $content;

  if (count($array) == 0) {
    return NULL;
  }

  ob_start();

  $df = fopen("php://output", 'w');

  // Header.
  fputcsv($df, $header);

  // Content.
  foreach ($array as $row) {
    fputcsv($df, $row);
  }

  fclose($df);

  return ob_get_clean();
}

function _vopros_statistics_download_send_headers($filename) {

  // Disable caching.
  $now = gmdate("D, d M Y H:i:s");
  header("Expires: Tue, 03 Jul 2001 06:00:00 GMT");
  header("Cache-Control: max-age=0, no-cache, must-revalidate, proxy-revalidate");
  header("Last-Modified: {$now} GMT");

  // Force download.
  header("Content-Type: application/force-download");
  header("Content-Type: application/octet-stream");
  header("Content-Type: application/download");

  // Disposition / encoding on response body.
  header("Content-Disposition: attachment;filename={$filename}");
  header("Content-Transfer-Encoding: binary");
}
