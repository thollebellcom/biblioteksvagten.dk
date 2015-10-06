<?php

require_once __DIR__ . '/reference.php';

/**
 * Tests and outputs the reference implementation.
 */
class ReferenceTest extends \PHPUnit_Framework_TestCase {
  /**
   * Test the reference implementation.
   */
  public function testReference() {
    $objects = array(
      (object) array(
        'uuid' => 'uuid-123',
        'title' => 'first question',
        'subject' => array(
          'first',
          'question',
        ),
        'description' => 'Det store spørgsmål...',
        'created' => 1427114034,
        'changed' => 1427115034,
        'question_content' => "At være eller ikke at være",
        'answer_content' => 'Det er spørgsmålet',
      ),
    );

    $namespaces = array(
      'xsi' => 'http://www.w3.org/2001/XMLSchema-instance',
      'dc' => 'http://purl.org/dc/elements/1.1/',
      'dkabm' => 'http://biblstandard.dk/abm/namespace/dkabm/',
#      'dcmitype' => 'http://purl.org/dc/dcmitype/',
      'dcterms' => 'http://purl.org/dc/terms/',
      'ac' => 'http://biblstandard.dk/ac/namespace/',
      'dkdcplus' => 'http://biblstandard.dk/abm/namespace/dkdcplus/',
      'docbook' => 'http://docbook.org/ns/docbook',
    );

    $doc = new DOMDocument('1.0', 'UTF-8');
    $collection = $doc->createElementNS('http://biblstandard.dk/abm/namespace/dkabm/', 'collection');

    $sim = new SimpleXMLElement('<?xml version="1.0" encoding="UTF-8"?>
<collection/>');
    $sim['xmlns'] = 'http://biblstandard.dk/abm/namespace/dkabm/';
    foreach ($namespaces as $short => $namespace) {
      $collection->setAttributeNS('http://www.w3.org/2000/xmlns/', 'xmlns:' . $short, $namespace);
      $sim['xmlns:' . $short] = $namespace;
    }
    $doc->appendChild($collection);


    foreach ($objects as $record) {
      osa_addi_create_object_request_xml($record, $doc, $collection, $record->uuid, 'Bibvagten', '123456', 'create');

      object_xml($record, $sim, $record->uuid, 'Bibvagten', '123456', 'create');
    }

    $doc->formatOutput = TRUE;
    $ref_xml = $doc->saveXml();
    $new_xml = $sim->asXML();
    print_r($new_xml);

    // Passing through DOMDocument to get it pretty printed.
    $dom = new DOMDocument("1.0");
    $dom->formatOutput = TRUE;
    $dom->loadXML($new_xml);
    $new_xml = $dom->saveXml();

    $this->assertEquals($ref_xml, $new_xml);
  }
}

function object_xml($object, $collection, $uuid, $source, $agency, $action) {
  $container = $collection->addChild('record');
  $dkabm_record = $container->addChild('dkabm:record');
  $dkabm_record->{'ac:identifier'} = $uuid . '|' . $agency;
}
