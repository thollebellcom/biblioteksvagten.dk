<?php

/**
 * Drrush aliases for Biblioteksvagten.
 */

// Shut up phpcs.
$aliases = array();

$aliases['vopros-server'] = array(
  'remote-host' => 'vopros.biblioteksvagten.dk',
  'remote-user' => 'root',
  'path-aliases' => array(
    '%dump-dir' => '/tmp',
  ),
);

$aliases['adm'] = array(
  'parent' => '@vopros-server',
  'uri' => 'adm.biblioteksvagten.dk',
  'root' => '/var/www/adm.biblioteksvagten.dk',
  'deployotron' => array(
    'branch' => 'master',
    'dump-dir' => '/root/backup/adm',
    // Updb clears the cache.
    'no-cc-all' => TRUE,
  ),
);

$aliases['vopros'] = array(
  'parent' => '@vopros-server',
  'uri' => 'vopros.biblioteksvagten.dk',
  'root' => '/var/www/vopros.biblioteksvagten.dk',
  'deployotron' => array(
    'branch' => 'develop',
    'no-dump' => TRUE,
    // Updb clears the cache.
    'no-cc-all' => TRUE,
  ),
);

$aliases['dev'] = array(
  'parent' => '@vopros-server',
  'uri' => 'dev.biblioteksvagten.dk',
  'root' => '/var/www/dev.biblioteksvagten.dk',
  'deployotron' => array(
    'branch' => 'develop',
    'no-dump' => TRUE,
    // Updb clears the cache.
    'no-cc-all' => TRUE,
  ),
);
