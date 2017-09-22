<?php
/*
 * Implement menu_wechat_merchant_express_edit_form for add express
 */
function menu_wechat_merchant_express_edit_form($form, &$form_state, $tmp_id){

  $form_state['template_id'] = $tmp_id;
  //get express template name from table
  $query = db_select('wechat_py_shopping_merchant_express_template_table', 't')
    ->condition('t.id', $tmp_id)
    ->fields('t', array('id', 'template_name'));

  $result = $query->execute();
  $result = $query->execute()->fetchAssoc();

  drupal_set_title('编辑模版：' . $result['template_name']);

  //modify template name
  $form['name_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['name_container']['template_name'] = array(
    '#type' => 'textfield',
    '#title' => t('编辑模版名称'),
    '#default_value' => $result['template_name'], 
  );

  $form['name_container']['name_submit'] = array(
    '#type' => 'submit',
    '#value' => t('确定'),
    '#submit' => array('submit_save_template_name'),
  );

  $form['container_break_line1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

  //remove weight area item
  $form['delete_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['delete_container']['item'] = array(
    '#type' => 'textfield',
    '#title' => t('序列号'),
    '#size' => 30, 
    '#maxlength' => 30, 
  );

  $form['delete_container']['delete_item'] = array(
    '#type' => 'submit',
    '#value' => t('删除纪录'),
    '#weight' => 100,
    '#validate' => array('validate_delete_item'),
    '#submit' => array('submit_delete_item'),
  );

  //list all weight city combination

  $form['list_container'] = array(
    '#type' => 'container',
    '#prefix' => '<div class="list-container">',
    '#suffix' => '</div>',
  );

  //find all weight and area item
  $query = db_select('wechat_py_shopping_weight_area_table', 't')
    ->condition('t.template_id', $tmp_id)
    ->fields('t', array('id', 'area_name', 'city_level', 'weight_sections'))
    ->orderBy('t.id', 'ASC');

  $result = $query->execute();
  foreach ($result as $id => $item) {
    $form['list_container'][$id] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('container-inline')),
    );

    $form['list_container'][$id]['number'] = array(
      '#markup' => '<span>&nbsp;&nbsp;序列号: ' . $item->id . '&nbsp;&nbsp;</span>',
    );

    switch ($item->city_level) {
      case '98': //only self
        $form['list_container'][$id]['city_name'] = array(
          '#markup' => '<span>' . $item->area_name . '</span>',
        );
        break;
      case '4': //city include zhixia shi county
        $form['list_container'][$id]['city_name'] = array(
          '#markup' => '<span>' . $item->area_name . '辖区地级城市</span>',
        );
        break;
      case '6': //city include zhixia shi county
        $form['list_container'][$id]['city_name'] = array(
          '#markup' => '<span>' . $item->area_name . '辖区县级城市</span>',
        );
        break;
      
      default:
        // code...
        break;
    }

    //parse weight_sections
    $weight_sections = $item->weight_sections;
    $ws_item = preg_split('/[\s:]+/', $weight_sections);

    $options = '';
    foreach ($ws_item as $key) {
      $query = db_select('wechat_py_shopping_weight_section_table', 't')
        ->condition('t.id', $key)
        ->fields('t', array('id', 'start_weight', 'start_price', 'unit_weight', 'unit_price'));

      $result = $query->execute()->fetchAssoc();
      $options .= '首重:' . $result['start_weight'] .
                '公斤 首重价格:' . $result['start_price'] . 
                '元 续重:' . $result['unit_weight'] .
                '公斤 续重价格:' . $result['unit_price'] . '元<br>';
    }

    /*
    $form['list_container'][$id]['weight_area'] = array(
      '#markup' => '<span style="float: right; display:">' . $options . '</span>',
    );
    */
    $form['list_container'][$id]['weight_area'] = array(
      '#type' => 'item',
      '#markup' => '<span style="float: right;margin: 0 1em 0 0;">' . $options . '</span>',
    );

    $form['list_container']['cbl' . $id]= array(
      '#type' => 'container',
      '#attributes' => array('class' => array('container-break-line')),
    );
  }

  //add weight area form
  $form['add_item'] = array(
    '#type' => 'submit',
    '#value' => t('增加纪录'),
    '#weight' => 100,
    '#submit' => array('submit_add_item'),
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_express_form.css',
  );

  return $form;
}

//update template name
function submit_save_template_name($form, &$form_state){
  //dpm($form_state);
  $result = $form_state['values']['template_name'];
  $tmp_id = $form_state['template_id'];

  db_update('wechat_py_shopping_merchant_express_template_table')
    ->fields(array('template_name' => $result))
    ->condition('id', $tmp_id)
    ->execute();
}

//remove weight and city item
function submit_delete_item($form, &$form_state){
  //dpm($form_state);
}

//validate serial number of item
function validate_delete_item($form, &$form_state){
  $number = $form_state['values']['item'];
  if(empty($number)) {
    form_set_error('item', t('输入序列号'));
    return;
  }

  db_delete('wechat_py_shopping_weight_area_table')
  ->condition('id', $number)
  ->execute();
}

//add weight and city item
function submit_add_item($form, &$form_state){
  $tmp_id = $form_state['template_id'];
  $form_state['redirect'] = 'wechat-py-shopping/wechat-merchant-express/' . $tmp_id . '/add-item';
}

//add weight and city item form
function menu_wechat_merchant_express_add_item($form, &$form_state, $tmp_id){

  drupal_set_title('增加城市和邮递价格');
  $form_state['template_id'] = $tmp_id;

  //radio select for condition
  $form['container_select'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  $radio_active = array(0 => t('直辖市和省份'), 
                        1 => t('省会城市'), 
                        2 => t('所有地级以上城市'),
                        3 => t('省辖区地级城市'), 
                        4 => t('省辖区县级城市'));
  $form['container_select']['radio'] = array(
    '#type' => 'radios',
    '#title' => t('选择区域'),
    '#default_value' => 0,
    '#options' => $radio_active,
    '#attributes' => array('class' => array('radio-area-selection')),
    '#ajax' => array(
      'callback' => 'ajax_select_area_callback',
      'wrapper' => 'ajax-wrapper-area',
      // 'method' defaults to replaceWith, but valid values also include
      // append, prepend, before and after.
      // 'method' => 'replaceWith',
      // 'effect' defaults to none. Other valid values are 'fade' and 'slide'.
      // See ajax_example_autotextfields for an example of 'fade'.
      'effect' => 'fade',
      // 'speed' defaults to 'slow'. You can also use 'fast'
      // or a number of milliseconds for the animation to last.
      // 'speed' => 'slow',
    ),
  );

  $form['container_break_line1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

  $form['area_container'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="ajax-wrapper-area">',
    '#suffix' => '</div>',
  );

  $city_level; //for city level   98: city self  4:city of province(include zhixiashi county, exclude capital city) 6: county of province
  if (empty($form_state['values']['radio'])) {
    //search province
    $query = db_select('wechat_py_nation_city_code_table', 't')
      ->condition('t.city_level', array(1, 2), 'IN')
      ->fields('t', array('area_code', 'area_name'))
      ->orderBy('t.area_code', 'ASC');

    $result = $query->execute();

    $city_options;
    foreach ($result as $id => $row) {
      $city_options[$row->area_code] = $row->area_name;
    }

    $form['area_container']['city_select'] = array(
      '#type' => 'select',
      '#options' => $city_options,
      '#id' => 'city-multi-select-code',
      '#multiple' => TRUE,
    );
    $form_state['city_level'] = 98;

  } else {
    $level = $form_state['values']['radio'];

    switch ($level) {
      /*
        0 => t('直辖市和省份'), 
        1 => t('省会城市'), 
        2 => t('所有地级以上城市'),
        3 => t('省辖区地级城市'), 
        4 => t('省辖区县级城市'), 
       */
      case '0':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', array(1, 2), 'IN')
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $city_level = 98; //province and zhi xia shi
        break;

      case '1':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', 3)
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $city_level = 98; //capital city
        break;

      case '2':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', array(1, 3, 4), 'IN')
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $city_level = 98; //capital city
        break;

      case '3':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', array(1, 2), 'IN')
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $city_level = 4; //city
        break;

      case '4':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', array(1, 2), 'IN')
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $city_level = 6; //county
        break;
      
      default:
        // code...
        break;
    }
    $form_state['city_level'] = $city_level;

    $result = $query->execute();

    $city_options;
    foreach ($result as $id => $row) {
      $city_options[$row->area_code] = $row->area_name;
    }

    $form['area_container']['city_select'] = array(
      '#type' => 'select',
      '#options' => $city_options,
      '#id' => 'city-multi-select-code',
      '#multiple' => TRUE,
    );
  }

  //weight section select
  $form['weight_container'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="ajax-wrapper-weight">',
    '#suffix' => '</div>',
  );

  $query = db_select('wechat_py_shopping_weight_section_table', 't')
    ->fields('t', array('id', 'start_weight', 'start_price', 'unit_weight', 'unit_price'))
    ->orderBy('t.id', 'ASC');

  $result = $query->execute();
  $options;
  foreach ($result as $id => $row) {
    $options[$row->id] = '首重:' . $row->start_weight . 
                         '公斤 首重价格:' . $row->start_price . 
                         '元 续重:' . $row->unit_weight . '公斤 续重价格:' . $row->unit_price . '元';
  }


  $form['weight_container']['weight_select'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#id' => 'weight-multi-select-code',
    '#multiple' => TRUE,
  );

  $form['save_submit'] = array(
    '#type' => 'submit',
    '#value' => t('保存纪录'),
    '#id' => 'save-weight-city-submit',
    '#validate' => array('validate_weight_city_select'),
    '#submit' => array('submit_save_weight_city'),
  );
  
  //css and js
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/multi-select.css',
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_express_form.css',
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/js/jquery.multi-select.js',
    drupal_get_path('module', 'wechat_py_shopping') . '/js/jquery.quicksearch.js',
    drupal_get_path('module', 'wechat_py_shopping') . '/js/edit_express_template.js',
  );

  return $form;
}

//validate weight city select list
function validate_weight_city_select($form, &$form_state){

  if(!isset($form_state['input']['city_select'])) {
    form_set_error('city_select', t('请选择城市'));
    return;
  }

  if(!isset($form_state['input']['weight_select'])) {
    form_set_error('city_select', t('请选择首重和价格'));
    return;
  }
}

//save weight, city, tmp id and condition into table
function submit_save_weight_city($form, &$form_state){
  //dpm($form_state);
  $tmp_id = $form_state['template_id'];
  $city_level = $form_state['city_level'];
  $city = $form_state['input']['city_select'];
  $weight = $form_state['input']['weight_select'];

  //weight data format  1:2:3:....
  $weight_sections = '';
  foreach ($weight as $id => $key) {
    $weight_sections .= $key . ':';
  }
  $weight_sections = rtrim($weight_sections, ":");

  foreach ($city as $id => $key) {
    //Find city name
    $query = db_select('wechat_py_nation_city_code_table', 't')
      ->condition('t.area_code', $key)
      ->fields('t', array('area_name'));

    $result = $query->execute()->fetchAssoc();

    if(!isset($result['area_name'])) {
      form_set_error(t('没有找到城市名称，请检查数据库'));
      return;
    }
    $city_name = $result['area_name'];

    try {
    db_insert('wechat_py_shopping_weight_area_table')
      ->fields(array(
        'template_id' => $tmp_id,
        'area_code' => $key,
        'area_name' => $city_name,
        'city_level' => $city_level,
        'weight_sections' => $weight_sections))
      ->execute();
    } catch(Exception $e) {

      $errorinfo = $e->errorInfo;
      watchdog('wechat py shopping',
               'insert weight area table = <pre>@error</pre>',
               array('@error' => print_r($errorinfo, TRUE)));

      form_set_error(t('保存数据错误, 检查日志信息 '));
      return;
    }

  }

  //redirect to edit list form
  $form_state['redirect'] = 'wechat-py-shopping/wechat-merchant-express/' . $tmp_id . '/edit';
}

/**
 * End of wechat_merchant_express_edit_form.inc file name
 */

