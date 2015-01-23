api = 2
core = 7.x

; Contrib modules.
projects[better_exposed_filters][subdir] = contrib
projects[better_exposed_filters][version] = 3.0-beta4

projects[cache_actions][subdir] = contrib
projects[cache_actions][version] = 2.0-alpha5

projects[ctools][subdir] = contrib
projects[ctools][version] = 1.4

projects[date][subdir] = contrib
projects[date][version] = 2.6

projects[diff][subdir] = contrib
projects[diff][version] = 3.2

projects[entity][subdir] = contrib
projects[entity][version] = 1.4

projects[facetapi][subdir] = contrib
projects[facetapi][version] = 1.2

projects[features][subdir] = contrib
projects[features][version] = 2.0

projects[feeds][subdir] = contrib
projects[feeds][version] = 2.0-alpha7

projects[fivestar][subdir] = contrib
projects[fivestar][download][type] = git
projects[fivestar][download][url] = http://git.drupal.org/sandbox/googletorp/1255156.git
projects[fivestar][download][revision] = b38930ff1890f88c63f293bae65b3c6913b6c1e6

projects[job_scheduler][subdir] = contrib
projects[job_scheduler][version] = 2.0-alpha3

projects[libraries][subdir] = contrib
projects[libraries][version] = 2.1

projects[link][subdir] = contrib
projects[link][version] = 1.1

projects[mailhandler][subdir] = contrib
projects[mailhandler][version] = 2.9

projects[nanosoap][subdir] = contrib
projects[nanosoap][version] = 1.0

projects[profile2][subdir] = contrib
projects[profile2][version] = 1.3

projects[rules][subdir] = contrib
projects[rules][version] = 2.6

projects[search_api][subdir] = contrib
projects[search_api][version] = 1.8

projects[search_api_solr][subdir] = contrib
projects[search_api_solr][version] = 1.2

projects[services][subdir] = contrib
projects[services][version] = 3.7

; Need the latest version to have fields working
projects[services_views][subdir] = contrib
projects[services_views][download][type] = git
projects[services_views][download][url] = http://git.drupal.org/project/services_views.git
projects[services_views][download][revision] = 1d584a0f283240d0596a20e705f5572245c7b014

projects[token][subdir] = contrib
projects[token][version] = 1.4

projects[uuid][subdir] = contrib
projects[uuid][version] = 1.0-alpha5

projects[views][subdir] = contrib
projects[views][version] = 3.7

projects[votingapi][subdir] = contrib
projects[votingapi][version] = 2.10

; Ting module

projects[osa_addi][subdir] = contrib
projects[osa_addi][type] = module
projects[osa_addi][download][type] = git
projects[osa_addi][download][url] = https://github.com/DBCDK/Vopros-opensearch-admin.git

projects[ting][type] = "module"
projects[ting][download][type] = "git"
projects[ting][download][url] = "https://github.com/ding2/ting.git"
projects[ting][download][tag] = "7.x-0.11"

; Our own module collection
projects[vopros_modules][type] = module
projects[vopros_modules][download][type] = git
projects[vopros_modules][download][url] = "https://github.com/DBCDK/Vopros-base.git"
projects[vopros_modules][download][revision] = 0c97535cf1d9e7dbd657fb6c13a7753d9591f339
projects[vopros_modules][directory_name] = vopros

; Libraries
libraries[search_api_solr_php_client][download][type] = get
libraries[search_api_solr_php_client][download][url] = http://solr-php-client.googlecode.com/files/SolrPhpClient.r60.2011-05-04.tgz
libraries[search_api_solr_php_client][directory_name] = SolrPhpClient
libraries[search_api_solr_php_client][destination] = libraries
