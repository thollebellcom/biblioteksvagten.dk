<?php
/**
 * @file
 * bv_settings_stg.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function bv_settings_stg_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "mailhandler" && $api == "mailhandler_mailbox") {
    return array("version" => "2");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index().
 */
function bv_settings_stg_default_search_api_index() {
  $items = array();
  $items['vopros_answer_question'] = entity_import('search_api_index', '{
    "name" : "Vopros Answer and Question search index",
    "machine_name" : "vopros_answer_question",
    "description" : "An automatically created search index required to be able to use the search page create by Vopros search.",
    "server" : "elstar_solr",
    "item_type" : "vopros_answer",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "3000",
      "fields" : {
        "answer_content" : { "type" : "text", "boost" : "3.0" },
        "answer_id" : { "type" : "integer" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "question:changed" : { "type" : "date" },
        "question:chat_session" : { "type" : "text" },
        "question:created" : { "type" : "date" },
        "question:question_content" : { "type" : "text" },
        "question:question_deadline_timestamp" : { "type" : "date" },
        "question:question_note" : { "type" : "text", "boost" : "0.8" },
        "question:question_status" : { "type" : "string" },
        "question:question_status_reason" : { "type" : "string" },
        "question:question_title" : { "type" : "text", "boost" : "2.0" },
        "question:question_usage" : { "type" : "string" },
        "question:subject_catagory" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "question:uid" : { "type" : "integer" },
        "question:user_age" : { "type" : "string" },
        "question:user_answer_preference" : { "type" : "string" },
        "question:user_email" : { "type" : "string" },
        "question:user_field_of_study" : { "type" : "string" },
        "question:user_gender" : { "type" : "string" },
        "question:user_library" : { "type" : "string" },
        "question:user_mobile_phone" : { "type" : "string" },
        "question:user_name" : { "type" : "string" },
        "question:user_postal_code" : { "type" : "string" },
        "question:vopros_editorial" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "question_id" : { "type" : "integer" },
        "search_api_language" : { "type" : "string" },
        "uid" : { "type" : "integer" },
        "user" : { "type" : "integer", "entity_type" : "user" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_language_control" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "lang_field" : "", "languages" : [] }
        },
        "search_api_alter_add_viewed_entity" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "mode" : "administrator" }
        },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "answer_content" : true,
              "question:question_title" : true,
              "question:question_content" : true,
              "question:question_note" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : {
              "answer_content" : true,
              "question:question_title" : true,
              "question:question_content" : true,
              "question:question_note" : true
            },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "answer_content" : true,
              "question:question_title" : true,
              "question:question_content" : true,
              "question:question_note" : true
            },
            "spaces" : "[^\\\\p{L}\\\\p{N}^\\u0027]",
            "ignorable" : "[-]"
          }
        },
        "search_api_stopwords" : {
          "status" : 1,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "answer_content" : true,
              "question:question_title" : true,
              "question:question_content" : true,
              "question:question_note" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc\\r\\nen \\r\\nden\\r\\ndet\\r\\net\\r\\n"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function bv_settings_stg_default_search_api_server() {
  $items = array();
  $items['elstar_solr'] = entity_import('search_api_server', '{
    "name" : "Solr",
    "machine_name" : "elstar_solr",
    "description" : "",
    "class" : "search_api_solr_service",
    "options" : {
      "clean_ids_form" : [],
      "clean_ids" : false,
      "site_hash_form" : [],
      "site_hash" : false,
      "scheme" : "http",
      "host" : "10.27.8.60",
      "port" : "8983",
      "path" : "\\/solr",
      "http_user" : "admin",
      "http_pass" : "",
      "excerpt" : 0,
      "retrieve_data" : 0,
      "highlight_data" : 0,
      "skip_schema_check" : 0,
      "solr_version" : "",
      "http_method" : "POST"
    },
    "enabled" : "1"
  }');
  return $items;
}
