<?php

/**
 * @file
 * Reference implementation of XML generator, lifted from osa_addi.module.
 *
 * Modified to account for changes between osa and the FTP method.
 */

function osa_addi_create_object_request_xml($object, $doc, $collection, $uuid, $source, $agency, $action = 'create') {
  $actions = array(
    'create' => 'created',
    'update' => 'modified',
    'delete' => 'delete-out-of-scope',
  );

  if (!isset($actions[$action])) {
    return;
  }

  $container = $doc->createElementNS('http://biblstandard.dk/abm/namespace/dkabm/', 'record');

  // Create the record.
  $dkabm_record = $doc->createElement('dkabm:record');
  // Add values to the record.
  $dkabm_record->appendChild($doc->createElement('ac:identifier', $uuid . '|' . $agency));
  $dkabm_record->appendChild($doc->createElement('dc:date', date('Y', $object->created)));

  $activity = $doc->createElement('ac:activity');
  $action = $doc->createElement('ac:action', $actions[$action]);
  $action->setAttribute('xsi:type', "ac:TypeOfActivity");
  $activity->appendChild($action);
  $dkabm_record->appendChild($activity);

  // The rest is not needed for delete requests.
  if ($action != 'delete') {
    $dkabm_record->appendChild($doc->createElement('ac:source', $source));
    $dkabm_record->appendChild($doc->createElement('dc:title', str_replace('&', '&amp;', $object->title)));
    foreach ($object->subject as $subject) {
      $dkabm_record->appendChild($doc->createElement('dc:subject', str_replace('&', '&amp;', $subject)));
    }
    $dkabm_record->appendChild($doc->createElement('dc:description', str_replace('&', '&amp;', $object->description)));
    $dc_type = $doc->createElement('dc:type', 'Spørgsmål og svar');
    $dc_type->setAttribute('xsi:type', 'dkdcplus:BibDK-Type');
    $dkabm_record->appendChild($dc_type);
    $dkabm_record->appendChild($doc->createElement('dc:language', 'Dansk'));

    $dkabm_record->appendChild($doc->createElement('dcterms:created', date('c', $object->created)));
    $dkabm_record->appendChild($doc->createElement('dcterms:modified', date('c', $object->changed)));

    // Add record to the container.
    $container->appendChild($dkabm_record);

    // Create the docbook:article
    $docbook_article = $doc->createElement('docbook:article');
    $docbook_article->appendChild($doc->createElement('docbook:title', str_replace('&', '&amp;', $object->title)));
    $docbook_info = $doc->createElement('docbook:info');
    $docbook_publisher = $doc->createElement('docbook:publisher');
    $docbook_publisher->appendChild($doc->createElement('docbook:publishername', $source));
    $docbook_info->appendChild($docbook_publisher);
    $docbook_article->appendChild($docbook_info);

    // Create the section which holds the question and answer set.
    $docbook_section = $doc->createElement('docbook:section');
    $docbook_qandaset = $doc->createElement('docbook:qandaset');
    $docbook_qandadiv = $doc->createElement('docbook:qandadiv');
    $docbook_qandaentry = $doc->createElement('docbook:qandaentry');
    $docbook_question = $doc->createElement('docbook:question');
    $docbook_question->appendChild($doc->createElement('docbook:para', str_replace('&', '&amp;', $object->question_content)));
    $docbook_qandaentry->appendChild($docbook_question);
    $docbook_answer = $doc->createElement('docbook:answer');
    $docbook_answer->appendChild($doc->createElement('docbook:para', str_replace('&', '&amp;', $object->answer_content)));
    $docbook_qandaentry->appendChild($docbook_answer);
    $docbook_qandadiv->appendChild($docbook_qandaentry);
    $docbook_qandaset->appendChild($docbook_qandadiv);
    $docbook_section->appendChild($docbook_qandaset);
    $docbook_article->appendChild($docbook_section);

    // Add docbook:article to the container.
    $container->appendChild($docbook_article);
  }
  // Add the record container to the collection.
  $collection->appendChild($container);
}
