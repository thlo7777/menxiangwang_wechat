<?php


/**
 * Implemented shopping adv management page
 *
 **/
function menu_wechat_py_shopping_adv_page_form($form, &$form_state){
  //get adv imgs from table
  $query = db_select('wechat_py_shopping_adv_table', 't')
    ->fields('t')
    ->orderBy('t.id', 'ASC');
  
  $result = $query->execute();
  $rows = 0;
  foreach ($result as $record) {
    $title = '第' . ($rows + 1) . '张广告图片';
    $form['image_fieldset' . $rows] = array(
      '#type' => 'fieldset',
      '#title' => $title,
      '#attributes' => array('class' => array('image-list-' . $rows, 'container-inline', 'clearfix')),
      '#weight' => $rows, 
    );


    $form['image_fieldset' . $rows]['image'] = array(
      '#theme' => 'image_style',
      '#path' => $record->image,
      '#style_name' => 'py_shopping_image_style', //540x500pix
      '#attributes' => array('style' => array('float:left;', 'margin-right:1em;')),
    );

    $form['image_fieldset' . $rows]['delete'] = array(
      '#name' => 'submit-' . $record->id, //id of record in table
      '#type' => 'submit',
      '#value' => t('删除'),
      '#validate' => array(),
      '#submit' => array('delete_adv_image_submit'),
    );

    $rows++;
  }

  $left = 3 - $rows;
  if($left > 0){
    $form['adv_image_plupload'] = array(
      '#type' => 'fieldset',
      '#title' => '上传广告图片',
      '#collapsible' => false,
      '#collapsed' => false,
      '#weight' => 20,
      '#attributes' => array('class' => array('adv-image-upload-file')),
      '#prefix' => '<div id="adv-image-plupload clearfix">',
      '#suffix' => '</div>',
    );

    $form['adv_image_plupload']['plupload'] = array(
      '#type' => 'plupload',
      '#title' => '可以选择' . $left . '张图片上传',
      '#submit_element' => '#id-adv-image-submit-element',
      '#upload_validators' => array(
        'file_validate_size' => array(512*1024),
        'file_validate_extensions' => array('jpg jpeg gif png'),
        'file_validate_image_resolution' => array('320x160', '320x160'),
      ),

      '#plupload_settings' => array(
        'cardinality' => $left,
        'multi_selection' => FALSE,
        'multiple_queues' => FALSE,
        'max_file_size' => 512*1024,
        'chunk_size' => '1mb',
        'runtimes' => 'html5,flash,silverlight,html4',
      ),

      // We need our own value callback as we need access to $form_state.
      '#value_callback' => 'adv_image_plupload_element_value',
      '#process' => array('adv_image_plupload_element_process'),
    );

    $form['adv_image_plupload']['submit'] = array(
      '#type' => 'submit',
      '#id' => 'id-adv-image-submit-element',
      '#value' => t('提交'),
      '#validate' => array(),
      '#submit' => array('upload_shopping_adv_image_submit'),
    );
  }

  $view = views_get_view('shopping_merchant_select_list');
  $view->set_display('test');
  $view->pre_execute();
  $html = $view->render('test');
  $form['view'] = array(
    '#markup' => $html,
  );

  return $form;
}

function delete_adv_image_submit($form, &$form_state){
  $id = $form_state['triggering_element']['#name'];

  $reg = preg_split('/-/', $id);
  $id = $reg[1];
  db_delete('wechat_py_shopping_adv_table')
  ->condition('id', $id)
  ->execute();
}

function upload_shopping_adv_image_submit($form, &$form_state){

  $upload_file_dir = 'public://py_shopping_image_upload/';
  //create public://py_shopping_image_upload/ if not exist
  file_prepare_directory($upload_file_dir, FILE_CREATE_DIRECTORY);
  $pud_files = $form_state['values']['plupload'];
  $rows = count($pud_files);

  $cardinality = $form_state['complete form']['adv_image_plupload']['plupload']['#plupload_settings']['cardinality'];
  if(count($pud_files) > $cardinality){
    $rows = $cardinality;
  }

  for ($i = 0; $i < $rows; $i++) {
    if($pud_files[$i]['status'] == 'done') {
      $source = $pud_files[$i]['tmppath'];
      $destination = file_stream_wrapper_uri_normalize(
        $upload_file_dir . $pud_files[$i]['name']);
      // Rename it to its original name, and put it in its final home.
      // Note - not using file_move here because if we call file_get_mime
      // (in file_uri_to_object) while it has a .tmp extension, it horks.
      $destination = file_unmanaged_move($source, $destination, FILE_EXISTS_RENAME);
      $file = plupload_file_uri_to_object($destination);
      file_save($file);
      file_validate_image_resolution($file, '320x160');
      db_insert('wechat_py_shopping_adv_table')
        ->fields(array(
          'image' => $file->uri,
          'created' => $file->timestamp,
          'link' => ''))
        ->execute();
    }
  }

  //$form_state['rebuild'] = TRUE;
}

function adv_image_plupload_element_value($element, $input = FALSE, &$form_state = NULL){

  if (isset($input) && $input === FALSE) {
    return array();
  }

  // We rely on Plupload Integration module to handle the actual field values.
  $pud_value = plupload_element_value($element, $input, $form_state);
  if (empty($pud_value)) {
    return array();
  }
  //pass selected and uploaded file names to sbumit button
  $form_state['values']['plupload'] = $pud_value;
}

function adv_image_plupload_element_process($element) {
  $module_path = drupal_get_path('module', 'wechat_py_shopping');
  $element['#attached']['js'] = array($module_path . '/js/py_shopping_plupload.js');

  return $element;
}
/**
 * End of wechat py shopping advertisement home page form
 */
