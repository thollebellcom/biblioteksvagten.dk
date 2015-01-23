<?php

/**
 * Admin forms and callbacks for ps_product module.
 */

/**
 * UI controller class for the admin interface.
 */
class BVCallCenterQuestionUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Display a list of Prosave Products or import the product catalog for a vendor.';
    return $items;
  }
}

/**
 * Generates the BV Call Center Question editing form.
 */
function bv_cc_question_form($form, &$form_state, $cc_question, $op = 'edit') {
  if ($op == 'clone') {
    $cc_question->question .= ' (cloned)';
  }

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Question'),
    '#default_value' => $cc_question->title,
    '#required' => TRUE,
  );

  $form['library'] = array(
    '#type' => 'textfield',
    '#title' => t('Library'),
    '#default_value' => $cc_question->library,
    '#required' => TRUE,
  );

  $form['answer_type'] = array(
    '#type' => 'select',
    '#title' => t('Answer type'),
    '#default_value' => $cc_question->answer_type,
    '#options' => bv_cc_question_answer_types(),
    '#required' => TRUE,
  );

  $form['note'] = array(
    '#type' => 'textarea',
    '#title' => t('Note'),
    '#default_value' => $cc_question->note,
    '#rows' => 3,
  );

  field_attach_form('bv_cc_question', $cc_question, $form, $form_state);

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save question'),
    '#weight' => 40,
  );

  if ($op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete question'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('bv_cc_question_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Submit handler for vopros_service_form().
 */
function bv_cc_question_form_submit($form, &$form_state) {
  $cc_question = $form_state['bv_cc_question'];
  field_attach_submit('bv_cc_question', $cc_question, $form, $form_state);
  $v = $form_state['values'];

  $cc_question->title = $v['title'];
  $cc_question->library = $v['library'];
  $cc_question->answer_type = $v['answer_type'];
  $cc_question->note = $v['note'];
  $cc_question->save();

  $form_state['redirect'] = 'admin/vopros/cc-question/new';
}

/**
 * Form API submit callback for the delete button.
 */
function bv_cc_question_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/vopros/cc-question/manage/' . $form_state['bv_cc_question']->cc_question_id . '/delete';
}

