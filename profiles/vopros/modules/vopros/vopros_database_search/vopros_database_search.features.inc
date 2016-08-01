<?php
/**
 * @file
 * vopros_database_search.features.inc
 */

/**
 * Implements hook_views_api().
 */
function vopros_database_search_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_search_api_index().
 */
function vopros_database_search_default_search_api_index() {
  $items = array();
  $items['answer_question_index'] = entity_import('search_api_index', '{
    "name" : "Question and Answer index",
    "machine_name" : "answer_question_index",
    "description" : "Questions and answer search index.",
    "server" : "local_database",
    "item_type" : "vopros_answer",
    "options" : {
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "answer_content" : { "type" : "text", "boost" : "3.0" },
        "changed" : { "type" : "date" },
        "created" : { "type" : "date" },
        "question:changed" : { "type" : "date" },
        "question:created" : { "type" : "date" },
        "question:question_content" : { "type" : "text" },
        "question:question_note" : { "type" : "text" },
        "question:question_status" : { "type" : "string" },
        "question:question_status_reason" : { "type" : "string" },
        "question:question_title" : { "type" : "text", "boost" : "2.0" },
        "question:question_usage" : { "type" : "text" },
        "question:subject_catagory" : { "type" : "list\\u003Cinteger\\u003E", "entity_type" : "taxonomy_term" },
        "question:user_age" : { "type" : "string" },
        "question:user_answer_preference" : { "type" : "string" },
        "question:user_email" : { "type" : "string" },
        "question:user_field_of_study" : { "type" : "string" },
        "question:user_gender" : { "type" : "string" },
        "question:user_library" : { "type" : "string" },
        "question:user_mobile_phone" : { "type" : "string" },
        "question:user_name" : { "type" : "string" },
        "question:user_postal_code" : { "type" : "string" },
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
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
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
              "question:question_usage" : true,
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
              "question:question_usage" : true,
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
              "question:question_usage" : true,
              "question:question_note" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
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
              "question:question_usage" : true,
              "question:question_note" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc\\r\\nen \\r\\nden\\r\\ndet\\r\\net\\r\\n"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
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
function vopros_database_search_default_search_api_server() {
  $items = array();
  $items['local_database'] = entity_import('search_api_server', '{
    "name" : "Local database",
    "machine_name" : "local_database",
    "description" : "",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "2",
      "partial_matches" : 1,
      "indexes" : { "answer_question_index" : {
          "uid" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "uid",
            "type" : "integer",
            "boost" : "1.0"
          },
          "answer_content" : {
            "table" : "search_api_db_answer_question_index_text",
            "type" : "text",
            "boost" : "3.0"
          },
          "user" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "user",
            "type" : "integer",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:question_title" : {
            "table" : "search_api_db_answer_question_index_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "question:question_content" : {
            "table" : "search_api_db_answer_question_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "question:question_status" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_question_status",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:question_status_reason" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_question_status_reason",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:question_usage" : {
            "table" : "search_api_db_answer_question_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "question:question_note" : {
            "table" : "search_api_db_answer_question_index_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "question:user_name" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_name",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:user_email" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_email",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:user_postal_code" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_postal_code",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:user_mobile_phone" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_mobile_phone",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:user_age" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_age",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:user_gender" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_gender",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:user_field_of_study" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_field_of_study",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:user_library" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_library",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:user_answer_preference" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_user_answer_preference",
            "type" : "string",
            "boost" : "1.0"
          },
          "question:subject_catagory" : {
            "table" : "search_api_db_answer_question_index_question_subject_catagory",
            "column" : "value",
            "type" : "list\\u003Cinteger\\u003E",
            "boost" : "1.0"
          },
          "question:created" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_created",
            "type" : "date",
            "boost" : "1.0"
          },
          "question:changed" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "question_changed",
            "type" : "date",
            "boost" : "1.0"
          },
          "created" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "created",
            "type" : "date",
            "boost" : "1.0"
          },
          "changed" : {
            "table" : "search_api_db_answer_question_index",
            "column" : "changed",
            "type" : "date",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1"
  }');
  return $items;
}
