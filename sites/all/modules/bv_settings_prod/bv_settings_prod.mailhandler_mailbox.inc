<?php
/**
 * @file
 * bv_settings_prod.mailhandler_mailbox.inc
 */

/**
 * Implements hook_default_mailhandler_mailbox().
 */
function bv_settings_prod_default_mailhandler_mailbox() {
  $export = array();

  $mailbox = new stdClass();
  $mailbox->disabled = FALSE; /* Edit this to true to make a default mailbox disabled initially */
  $mailbox->api_version = 2;
  $mailbox->mail = 'biblioteksvagten_biblioteksvagten_dk';
  $mailbox->admin_title = 'biblioteksvagten@biblioteksvagten.dk';
  $mailbox->settings = array(
    'type' => 'imap',
    'folder' => 'INBOX',
    'domain' => '10.27.8.36',
    'port' => '993',
    'insecure' => 1,
    'name' => 'bv@biblioteksvagten.dk',
    'pass' => '',
    'extraimap' => '/imap/ssl/novalidate-cert',
    'limit' => '15',
    'encoding' => ' ISO-8859',
    'flag_after_read' => 1,
    'delete_after_read' => 0,
    'fromheader' => 'From',
    'security' => '0',
    'replies' => '0',
    'retrieve' => 'MailhandlerPhpImapRetrieve',
    'readonly' => 0,
  );
  $export['biblioteksvagten_biblioteksvagten_dk'] = $mailbox;

  return $export;
}
