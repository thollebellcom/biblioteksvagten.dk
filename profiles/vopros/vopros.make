api = 2
core = 7.x

; Contrib modules.
projects[better_exposed_filters][subdir] = contrib
projects[better_exposed_filters][version] = 3.4

projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = 2.0-alpha5

projects[ctools][subdir] = contrib
projects[ctools][version] = 1.12

projects[date][subdir] = contrib
projects[date][version] = 2.9

projects[diff][subdir] = contrib
projects[diff][version] = 3.3

projects[entity][subdir] = contrib
projects[entity][version] = 1.8

projects[features][subdir] = contrib
projects[features][version] = 2.10

projects[feeds][subdir] = contrib
projects[feeds][version] = 2.0-beta3

projects[file_entity][subdir] = contrib
projects[file_entity][version] = 2.1

projects[fivestar][subdir] = contrib
projects[fivestar][version] = 2.2
; Better views filter.
; https://www.drupal.org/node/1255160#comment-10392031
projects[fivestar][patch][] = https://www.drupal.org/files/issues/add_better_views-1255160-40.patch

projects[job_scheduler][subdir] = contrib
projects[job_scheduler][version] = 2.0-alpha3

projects[l10n_update][subdir] = contrib
projects[l10n_update][version] = 2.0

projects[libraries][subdir] = contrib
projects[libraries][version] = 2.3

projects[link][subdir] = contrib
projects[link][version] = 1.4

projects[mailhandler][subdir] = contrib
projects[mailhandler][version] = 2.11

projects[media][subdir] = contrib
projects[media][version] = 2.6

projects[nanosoap][subdir] = contrib
projects[nanosoap][version] = 1.0

projects[profile2][subdir] = contrib
projects[profile2][version] = 1.3

projects[rules][subdir] = contrib
projects[rules][version] = 2.9

projects[search_api][subdir] = contrib
projects[search_api][version] = 1.20

projects[search_api_solr][subdir] = contrib
projects[search_api_solr][version] = 1.11

projects[search_api_db][subdir] = contrib
projects[search_api_db][version] = 1.5

projects[services][subdir] = contrib
projects[services][version] = 3.20

projects[services_views][subdir] = contrib
projects[services_views][version] = 1.2

projects[transliteration][subdir] = contrib
projects[transliteration][version] = 3.2

projects[token][subdir] = contrib
projects[token][version] = 1.6

projects[uuid][subdir] = contrib
projects[uuid][version] = 1.0-beta2

projects[views][subdir] = contrib
projects[views][version] = 3.17
; Views menu titles and description isn't exported.
; https://www.drupal.org/node/1054746
projects[views][patch][1054746] = https://www.drupal.org/files/issues/code_export_doesn_t-1054746-5.patch

projects[votingapi][subdir] = contrib
projects[votingapi][version] = 2.12

projects[wysiwyg][subdir] = contrib
projects[wysiwyg][version] = 2.3

; Libraries
libraries[search_api_solr_php_client][download][type] = get
libraries[search_api_solr_php_client][download][url] = https://github.com/PTCInc/solr-php-client/archive/v1.0.0.zip
libraries[search_api_solr_php_client][directory_name] = SolrPhpClient
libraries[search_api_solr_php_client][destination] = libraries

libraries[ckeditor][download][type] = get
libraries[ckeditor][download][url] = http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.6.2/ckeditor_3.6.6.2.zip
libraries[ckeditor][directory_name] = ckeditor
libraries[ckeditor][destination] = libraries

libraries[spyc][directory_name] = spyc
libraries[spyc][download][type] = file
libraries[spyc][download][url] = https://raw.github.com/mustangostang/spyc/0.5.1/Spyc.php
libraries[spyc][type] = library
