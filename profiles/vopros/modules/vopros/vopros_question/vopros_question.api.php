<?php

/**
 * @file
 * API documentation for Vopros Question module.
 */

/**
 * Implements hook_vopros_question_user_answer_preference().
 */
function hook_vopros_question_user_answer_preference() {

}

/**
 * Alter Question extras fields.
 */
function hook_vopros_question_field_extra_fields_alter(&$extra) {

}

/**
 * Alter Question status reasons.
 */
function hook_vopros_question_status_reasons_alter(&$reasons) {

}

/**
 * Return question channels.
 *
 * @return array
 *   Keys are channel identifiers, the value is an array of options:
 *   'name':
 *     Human readable name.
 *   'manual':
 *     When true, this channel can be used for manually created questions.
 *     (optional)
 */
function hook_vopros_question_channels() {

}

/**
 * Alter Question status reason options.
 */
function hook_vopros_question_status_reason_options_alter(&$type, &$options) {

}

/**
 * Alter Question view.
 */
function hook_vopros_question_view_alter(&$build, &$type) {

}
