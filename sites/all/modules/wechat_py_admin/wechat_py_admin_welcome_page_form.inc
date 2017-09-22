<?php
/**
 * wechat py admin welcome page form
 */
function menu_wechat_py_admin_welcome_page_form($form, &$form_state){

/*
  $node = node_load(286);
  $enode = entity_metadata_wrapper('node', $node);
  $title = $enode->title->value();

  $fc_item = $enode->field_info_prod_group->value();
  foreach ($fc_item as $field) {
    dpm($field);
    //$eintro = $eload->field_product_intro->value();
    // code...
  }
  */

  $query = db_select('wechat_py_welcome_page_table', 't')->fields('t', array('welcome_text'));
  $result = $query->execute();
  $row = $result->fetchAssoc();

  $form['welcome_page'] = array(
    '#type' => 'fieldset', 
    '#title' => t('微信欢迎页面'), 
    '#weight' => 0, 
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );

  $form['welcome_page']['content'] = array(
    '#title' => t('页面内容'), 
    '#type' => 'textarea',
    '#default_value' => $row['welcome_text'], 
    '#attributes' => array('class' => array('content-input')), //Do not use id when ajax
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('保存'),
    '#weight' => 100,
/*  //no effect if default_value has value in textarea field
    '#states' => array(
      'visible' => array(
        ':input[name="content"]' => array('filled' => TRUE),
      ),
    ),
*/
  );

  return $form;
}

function menu_wechat_py_admin_welcome_page_form_submit($form, &$form_state) {
  $value = $form_state['values']['content'];
  db_update('wechat_py_welcome_page_table')
  ->fields(array(
      'welcome_text' => $value,
    ))
  ->execute();
}

/**
 * End of wechat py admin welcom page
 */
