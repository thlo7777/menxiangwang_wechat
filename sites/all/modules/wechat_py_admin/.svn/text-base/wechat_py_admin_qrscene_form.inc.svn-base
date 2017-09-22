<?php

function menu_wechat_py_admin_qrscene_form($form, &$form_state){
  
  $form['qrscene_add_submit'] = array(
    '#type' => 'submit',
    '#value' => t('添加'),
    '#submit' => array('qrscene_add_submit'),
    // No need to validate when submitting this.
    '#limit_validation_errors' => array(),
    '#validate' => array(),
    '#weight' => 0,
  );

  if (!empty($form_state['values']['qrscene_add'])) {
    $form['qrscene_add_fieldset'] = array(
      '#type' => 'fieldset',
      '#prefix' => '<div id="qrscene-list-add">',
      '#suffix' => '</div>',
      '#weight' => 1,
    );

    $form['qrscene_add_fieldset']['action_name'] = array(
      '#type' => 'radios',
      '#title' => t('创建永久或者临时二维码'),
      '#default_value' => 0,
      '#options' => array('0' => '永久二维码', '1' => '临时二维码'),
      '#description' => t('1、临时二维码，是有过期时间的，最长可以设置为在二维码生成后的7天后过期，
                              但能够生成较多数量。临时二维码主要用于帐号绑定等不要求二维码永久保存的业务场景
                           2、永久二维码，是无过期时间的，但数量较少（目前为最多10万个）。永久二维码主要用于
                              适用于帐号绑定、用户来源统计等场景。'),
    );

    $form['qrscene_add_fieldset']['scene_name'] = array(
      '#type' => 'textfield',
      '#size' => 60, 
      '#maxlength' => 255, 
      '#required' => TRUE,
      '#title' => t('分配二维码场景名称'),
      '#description' => t('例如：平遥酒店用二维码，平遥餐馆用二维码等'),

    );

    $form['qrscene_add_fieldset']['scene_id'] = array(
      '#type' => 'textfield',
      '#size' => 10, 
      '#required' => TRUE,
      '#title' => t('分配二维码场景编号'),
      '#description' => t('例如：1,2,3...。数字编号范围1-100000。注意不要和已有场景编号重复'),
    );

    $form['qrscene_add_fieldset']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('保存'),
      '#submit' => array('qrscene_save_submit'),
      '#validate' => array('qrscene_save_validate'),
    );
  }
  //$header = array(t('酒店名称'), t('列表排名'), t('酒店地理位置：经度'), t('酒店地理位置：纬度'));
  //call theme_theming_qrscene_list_table_element
/*
  $form['qrscene_list_fieldset']['theme_table'] = array(
    'content' => array(
      '#markup' => t('你好'),
    ),
    'copy' => array(
      '#type' => 'checkbox', 
      '#title' => t('Send me a copy.'),
      '#title_display' => 'after',
    ),

    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => array(),
    ),
    '#theme' => 'theming_qrscene_list_table_element',
  );
*/

  $form['qrscene_list_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('分场景二维码列表'),
    '#prefix' => '<div id="qrscene-list-table">',
    '#suffix' => '</div>',
    '#weight' => 2,
  );
  //fetch data from wechat_py_qrscene_table
  $query = db_select('wechat_py_qrscene_table', 't')
    ->fields('t', array(
      'id',
      'action_name',
      'scene',
      'scene_id',
      'ticket',
      'qrscene_image_file',
      'qrscene_image_width',
      'qrscene_image_height'))
    ->orderBy('t.id', 'ASC');

  $result = $query->execute();
  $options = array();
  foreach($result as $item){
    $img_url = file_create_url($item->qrscene_image_file);
    $image_form = array(
      '#theme' => 'image_style',
      //'#path' => $img_url,
      '#path' => $item->qrscene_image_file,
      '#style_name' => 'thumbnail',
    );

    if($item->action_name == 'QR_SCENE'){
      $action_name = '临时二维码';
    }
    if($item->action_name == 'QR_LIMIT_SCENE'){
      $action_name = '永久二维码';
    }

    $options[$item->id] = array(
      'scene' => $item->scene,
      'scene_id' => $item->scene_id,
      'action_name' => $action_name,
      //'ticket' => $item->ticket,
      //'ticket' => array('data' => $item->ticket, 'width' => array('100px')),
      //'qrscene_image_file' => $item->qrscene_image_file,
      'qrscene_image_file' => array(
        'data' => array(
          '#markup' => '<a href="' . $img_url . '" target="_blank class="example-img">' . 
            drupal_render($image_form) . '</a>',
        ),
      ),
    );
  }

  $header = array(
    'scene' => t('场景名称'),
    'scene_id' =>  t('场景编号'),
    'action_name' => t('永久/临时二维码'),
    //'ticket' => t('ticket'),
    'qrscene_image_file' => t('二维码图片'));


  //theme table for variables theme_theming_qrscene_list_table_variables
  $form['qrscene_list_fieldset']['theme_table_select'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('当前没有记录'),
  );
  $form['qrscene_list_fieldset']['delete_row_submit'] = array(
    '#type' => 'submit', 
    '#value' => t('删除'),
    '#submit' => array('qrscene_del_row_submit'),
  );

  return $form;
}


//Validate during submit new records into database
function qrscene_save_validate($form, &$form_state){
  $value = $form_state['values']['scene_id'];
  if($value < 1 || $value > 100000){
    form_set_error('scene_id', t('编号值必须是1-100000之间'));
  }

  $result = db_select('wechat_py_qrscene_table', 't')
      ->fields('t')
      ->condition('scene_id', $value,'=')
      ->execute();
  $num_of_results = $result->rowCount();
  if($num_of_results > 0){
    form_set_error('scene_id', t('编号值已存在，请选择其他编号'));
  }
}

//Submit new records into database
function qrscene_save_submit($form, &$form_state){

  if($form_state['values']['action_name'] == 0){
    //permanent bar code
    $action_name = 'QR_LIMIT_SCENE';
  }
  if($form_state['values']['action_name'] == 1){
    //temporary bar code
    $action_name = 'QR_SCENE';
  }

  db_insert('wechat_py_qrscene_table')
  ->fields(array(
        'scene' => $form_state['values']['scene_name'],
        'scene_id' => $form_state['values']['scene_id'],
        'action_name' => $action_name,
        'ticket' => '',
    ))
  ->execute(); 

  //send creat bar code by scene_id
  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  if($action_name == 'QR_LIMIT_SCENE'){
    //permanent bar code
    $ticket = wechat_api_creat_qrscene(TRUE, $form_state['values']['scene_id']);
  }
  if($action_name == 'QR_SCENE'){
    //temporary bar code
    $ticket = wechat_api_creat_qrscene(FALSE, $form_state['values']['scene_id'], 1800);
  }
  if(!empty($ticket)){
    db_update('wechat_py_qrscene_table')
    ->fields(array(
        'ticket' => $ticket,
      ))
    ->condition('scene_id', $form_state['values']['scene_id'])
    ->execute();
  }

  //get bar code by ticket
  $filename = wechat_api_get_qrscene_image($form_state['values']['scene_name'], $ticket);
  if(!empty($filename)){
    db_update('wechat_py_qrscene_table')
    ->fields(array(
        'qrscene_image_file' => $filename,
      ))
    ->condition('scene_id', $form_state['values']['scene_id'])
    ->execute();
  }

}

/*
//theme table for theming_qrscene_list_table_variables
function theme_theming_qrscene_list_table_variables($variables){
  $output = '';
  $values = $variables['records'];

  //$del_cell = drupal_render($delete_submit);
  $rows = array();
  foreach($values as $id => $item){
    $rows[] = array(
      'data' => array(
        $item['scene'],
        $item['scene_id'],
        $item['ticket'],
        $item['qrscene_image_file'],
        drupal_render($item['delete_submit']),
      ),
    );
  }

  $header = array(t('场景名称'), t('场景编号'), t('ticket'), t('二维码图片'), t('操作'));
  $render_array = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  
  $output .= drupal_render($render_array);

  return $output;
}
*/

/*
//theme table for qrscene list table
function theme_theming_qrscene_list_table_element($variables) {
  $output = '';
  $element = $variables['element']['content'];
  dpm($variables);

  foreach (element_children($variables['element']['content']) as $item) {
    $output .= $variables['element']['content'][$item];
  }
  $output .= drupal_render($element);
  $output .= drupal_render($variables['element']['copy']);


  $output .= drupal_render($variables['element']['table']);

  $render_array['another'] = array(
    '#type' => 'checkbox', 
    '#title' => t('another checkbox.'),
  );

  $output .= drupal_render($render_array);
  return $output;
}
*/

function qrscene_del_row_submit($form, &$form_state){
  $values = $form_state['values']['theme_table_select'];
  foreach($values as $id => $item){
    if($item != 0){
      $query = db_select('wechat_py_qrscene_table', 't')
        ->fields('t', array('qrscene_image_file'))
        ->condition('id', $item);
      $row = $query->execute()->fetchAssoc();

      file_unmanaged_delete($row['qrscene_image_file']);
      db_delete('wechat_py_qrscene_table')
        ->condition('id', $item)
        ->execute();
    }
  }
}

//Only for add new qrscene name and number form elements
function qrscene_add_submit($form, &$form_state){
  $form_state['values']['qrscene_add'] = t('add');
  $form_state['rebuild'] = TRUE;
}


/**
 * End of wechat py admin qrscene form
 */
