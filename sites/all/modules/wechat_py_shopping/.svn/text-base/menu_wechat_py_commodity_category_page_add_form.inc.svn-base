<?php
//for own custome online shopping
function old_menu_wechat_py_commodity_category_page_add_form($form, &$form_state, $id, $level){

  $form_state['temporary']['parent_id'] = array(
    'id' => $id,
    'level' => $level,
  );

  $query = db_select('wechat_py_commodity_category_table', 't')
    ->condition('t.id', $id)
    ->fields('t');
  $result = $query->execute();
  $rows = null;
  foreach ($result as $key) {
    $rows = $key;
  }

  $form['edit_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => '编辑',
    '#attributes' => array('class' => array('edit-category')),
  );

  $form['edit_fieldset']['parent_level'] = array(
    '#type' => 'textfield', 
    '#required' => TRUE,
    '#default_value' => $rows->name, 
    '#size' => 60, 
    '#maxlength' => 128, 
  );

  $form['edit_fieldset']['save'] = array(
    '#type' => 'submit',
    '#value' => t('保存'),
  );
  $form['edit_fieldset']['delete'] = array(
    '#type' => 'submit',
    '#value' => t('删除'),
    '#attributes' => array('onclick' => 'if(!confirm("删除后子分类同时删除，确实要删除吗?")){return false;}'),
  );

  $form['container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['container']['child_level'] = array(
    '#type' => 'textfield', 
    '#size' => 60, 
    '#maxlength' => 128, 
  );

  $form['container']['add'] = array(
    '#type' => 'submit',
    '#attributes' => array('style' => 'float: right;'),
    '#validate' => array('child_add_category_validation'),
  );

  if($id != 0 && $level == 1){
    $form['edit_fieldset']['parent_level']['#title'] = t('商品一级分类名称');
    $form['container']['child_level']['#title'] = t('输入商品二级分类名称');
    $form['container']['add']['#value'] = t('增加二级分类商品');
  }

  if($id != 0 && $level == 2){
    $form['edit_fieldset']['parent_level']['#title'] = t('商品二级分类名称');
    $form['container']['child_level']['#title'] = t('输入商品三级分类名称');
    $form['container']['add']['#value'] = t('增加三级分类商品');
  }

  if($id != 0 && $level == 3){
    $form['edit_fieldset']['parent_level']['#title'] = t('商品三级分类名称');
    unset($form['container']['child_level']);
    unset($form['container']['add']);
  }

  //return button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('返回'),
    '#attributes' => array('style' => array('margin-top: 3em;')),
    '#weight' =>  100,
  );
  $form['#submit'][] = 'add_all_submit';
  
  return $form;
}

function child_add_category_validation($form, &$form_state){
  $text = strlen(trim($form_state['values']['child_level']));
  if($text == 0){
    form_set_error('child_level', t('分类名称不能为空'));
  }

}

//record all all submit event
function add_all_submit($form, &$form_state){
  $op = $form_state['values']['op'];
  switch ($op) {
    case '增加二级分类商品':
      $name = $form_state['values']['child_level'];
      $id = $form_state['temporary']['parent_id']['id'];
      $level = 2; //second level category
      $pid = $id;
      db_insert('wechat_py_commodity_category_table')
              ->fields(array(
                'name' => $name,
                'level' => $level,
                'pid' => $pid,
                ))->execute();
      break;
    case '增加三级分类商品':
      $name = $form_state['values']['child_level'];
      $id = $form_state['temporary']['parent_id']['id'];
      $level = 3; //third level category
      $pid = $id;
      db_insert('wechat_py_commodity_category_table')
              ->fields(array(
                'name' => $name,
                'level' => $level,
                'pid' => $pid,
                ))->execute();
      break;
    case '保存':
      $name = $form_state['values']['parent_level'];
      $id = $form_state['temporary']['parent_id']['id'];
      db_update('wechat_py_commodity_category_table')
        ->fields(array('name' => $name))
        ->condition('id', $id)
        ->execute();
    
      $form_state['redirect'] = 'wechat-py-shopping/commodity-category';
      break;

    case '删除':
      $id = $form_state['temporary']['parent_id']['id'];
      db_delete('wechat_py_commodity_category_table')
      ->condition('id', $id)
      ->execute();
    
      $form_state['redirect'] = 'wechat-py-shopping/commodity-category';
      break;

    case '返回':
      $form_state['redirect'] = 'wechat-py-shopping/commodity-category';
      break;

    default:
      break;
  }
}
/**
 * End of menu_wechat_py_commodity_category_page_add_form.inc file name
 */
