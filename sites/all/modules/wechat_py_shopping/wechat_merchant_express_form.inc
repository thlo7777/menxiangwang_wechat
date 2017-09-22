<?php

/*
 * Implement menu_wechat_merchant_express_root_form for merchat express home page
 */
function menu_wechat_merchant_express_root_form($form, &$form_state){
  //$val = menu_load_links(MENU_WECHAT_PY_SHOPPING . '/wechat-merchant-express/');
  $menu = menu_load_links(MENU_WECHAT_PY_SHOPPING);

  $items = array();

  foreach ($menu as $row) {
    if(preg_match('/wechat-merchant-express\//', $row['link_path'])) {

      $data_array = array(
        '#type' => 'link',
        '#title' => $row['link_title'],
        '#href' => $row['link_path'],
        '#suffix' => ' ' . theme('mark', array('type' => 'MARK_NEW')),
      );
      $items[] = drupal_render($data_array);
    }
  }

  $form['menu_list']= array(
    '#theme' => 'item_list',
    '#items' => $items,
    '#type' => 'ul',
    '#attributes' => array('class' => 'express-list'),
  );
  // code...
  return $form;
}

/*
 *Implement menu_wechat_merchant_express_list_form for merchat express home page
 */

function menu_wechat_merchant_express_list_form($form, &$form_state){
  $form['container_break_line1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

  $query = db_select('wechat_py_shopping_merchant_express_template_table', 't')
    ->fields('t', array('id', 'template_name'))
    ->orderBy('t.id', 'ASC');

  $result = $query->execute();

  foreach ($result as $id => $row) {

    $form[$id]['inline'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('container-inline')),
    );

    $form[$id]['inline']['label'] = array(
      '#type' => 'item',
      '#title' => $row->template_name,
      '#prefix' => '<div class="merchant-express-label">',
      '#suffix' => '</div>',
    );

    $form[$id]['inline']['edit'] = array(
      '#type' => 'submit',
      '#value' => t('编辑模版'),
      '#name' => $row->id,
      '#attributes' => array('class' => array('edit-submit')),
      '#submit' => array('submit_callback_edit_weight_express'),
    );

    $form[$id]['inline']['remove'] = array(
      '#type' => 'submit',
      '#value' => t('删除模版'),
      '#name' => $row->id,
      '#attributes' => array('class' => array('remove-submit')),
      '#submit' => array('submit_callback_remove_weight_express'),
    );

    $form[$id]['container_break_line1']= array(
      '#type' => 'container',
      '#attributes' => array('class' => array('container-break-line')),
    );
  }

  $form['add_express'] = array(
    '#type' => 'submit',
    '#value' => t('增加邮费模版'),
    '#weight' => 100,
    '#submit' => array('submit_callback_add_merchant_express'),
    '#attributes' => array('style' => array('float: right;')),
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_express_form.css',
  );

  return $form;
}

/*
 * submit call for edit express template
 */
function submit_callback_edit_weight_express($form, &$form_state){
  $button = $form_state['triggering_element'];
  $row = $button['#name'];
  $form_state['redirect'] = 'wechat-py-shopping/wechat-merchant-express/' . $row . '/edit';
}
/*
 * submit call for remove express
 */
function submit_callback_remove_weight_express($form, &$form_state){
  $button = $form_state['triggering_element'];
  $row = $button['#name'];
  db_delete('wechat_py_shopping_merchant_express_template_table')
  ->condition('id', $row)
  ->execute();
}

/*
 * submit callback for add express
 */
function submit_callback_add_merchant_express($form, &$form_state){
  $form_state['redirect'] = 'wechat-py-shopping/wechat-merchant-express/add';
}

function old_menu_wechat_merchant_express_list_form($form, &$form_state){

  $form['container_name'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-name', 'clearfix')),
  );

  $form['container_name']['name'] = array (
    '#type' => 'textfield',
    '#title' => t('模版名称'), 
    '#size' => 60, 
    '#maxlength' => 128, 
    '#required' => TRUE,
    '#description' => t('小于20个字'),
    '#attributes' => array('class' => array('template-name', 'clearfix')),
  );

  //break line for form element
  $form['container_break_line1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

  $form['container_delivery'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline', 'container-delivery', 'clearfix')),
  );
  $form['container_delivery']['delivery'] = array (
    '#type' => 'item',
    '#title' => t('配送方式'), 
    '#markup' => '<div>快递</div>',
  );

  //break line for form element
  $form['container_break_line2'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

  $form['container_fee'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['container_fee']['area_label'] = array(
    '#type' => 'item',
    '#title' => t('配送区域'),
    '#prefix' => '<div class="merchant-express-head-font">',
    '#suffix' => '</div>',
  );

  $form['container_fee']['startprice_label'] = array(
    '#type' => 'item',
    '#title' => t('指定公斤起价(元)'),
    '#prefix' => '<div class="merchant-express-head-font">',
    '#suffix' => '</div>',
  );

  $form['container_fee']['unit_weight'] = array(
    '#type' => 'item',
    '#title' => t('续重量计价单位(公斤)'),
    '#prefix' => '<div class="merchant-express-head-font">',
    '#suffix' => '</div>',
  );

  $form['container_fee']['unit_price'] = array(
    '#type' => 'item',
    '#title' => t('续重量运费计价(元)'),
    '#prefix' => '<div class="merchant-express-head-font">',
    '#suffix' => '</div>',
  );

  $form['container_break_line3'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

  $form['fieldset'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => '快递邮费设置',
    '#prefix' => '<div id="ajax-weight-fee-wrapper">',
    '#suffix' => '</div>',
  );

  if (empty($form_state['weight_fee_nums'])) {
    $form_state['weight_fee_nums'] = 0;
  }

  for ($i = 0; $i < $form_state['weight_fee_nums']; $i++) {
    $form['fieldset']['name'][$i] = array(
      '#type' => 'merchant_express_form_weight_fee',
    );
  }

  $form['area_submit'] = array(
    '#type' => 'submit',
    '#value' => t('增加指定区域'),
    '#weight' => 100,
    '#submit' => array('submit_ajax_weight_fee'),
    '#ajax' => array(
      'callback' => 'ajax_weight_fee_callback',
      'wrapper' => 'ajax-weight-fee-wrapper',
    ),
  );


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('保存模版'),
    '#weight' => 110,
  );

  $form['#submit'][] = 'merchant_express_all_submit';

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_express_form.css',
  );
  return $form;
}

//for delete setup weight rows
function ctools_ajax_merchant_express_weight_section_delete($row) {
  ctools_include('ajax');

  $commands = array();
  $commands[] = ajax_command_remove(".form-item-container-row-$row");
  print ajax_render($commands);
  exit;
}

function ctools_ajax_merchant_express_delete($row) {
  ctools_include('ajax');

  $commands = array();
  $commands[] = ajax_command_remove(".form-item-fieldset-name-$row");
  print ajax_render($commands);
  exit;
}

function submit_ajax_weight_fee($form, &$form_state) {
  $form_state['weight_fee_nums']++;
  $form_state['rebuild'] = TRUE;
}

function ajax_weight_fee_callback($form, $form_state) {
  return $form['fieldset'];
}

function merchant_express_all_submit($form, &$form_state){

  $op = $form_state['values']['op'];
  switch ($op) {
    case '保存模版':
      dpm($form_state);
      drupal_set_message('保存模版');
      break;

    default:
      break;
  }
}


function preg_match_chinese_test() {
  //$result = preg_match('/^市辖区ddkd$/', '市辖区ddkd');
  //dpm($result);

  $filename = drupal_get_path('module', 'wechat_py_shopping') . '/行政区划代码';
  $data = file_get_contents($filename);
  $data_array = preg_split('/\s+/', $data);

  $a_code;
  $a_name;
  $count = 0;

  foreach ($data_array as $id => $code) {

    $a_code = $code;
    if(!empty($data_array[$id + 1])) {
      $a_name = $data_array[$id + 1];
    }else{
      continue;
    }

    /*
    if(preg_match('/00$/', $code)) {
      if(preg_match('/^县$/', $a_name) || 
         preg_match('/^省直辖县级行政区划$/', $a_name) || 
         preg_match('/^自治区直辖县级行政区划$/', $a_name)) {
        $count++;
        dpm($code . " : " . $a_name);
      }
    }
    */
    /*
    if(preg_match('/00$/', $code) &&
       !preg_match('/0000$/', $code) &&
       !preg_match('/0100$/', $code)) {
      $count++;
      dpm($code . " : " . $a_name);
    }
    */
    if(preg_match('/01$/', $code) &&
       !preg_match('/^市辖区$/', $a_name)) {
      $count++;
      dpm($code . " : " . $a_name);
    }
  }
  dpm("totally: " . $count);

}

function insert_nation_area_code_table() {
  $filename = drupal_get_path('module', 'wechat_py_shopping') . '/行政区划代码';
  $data = file_get_contents($filename);
  $data_array = preg_split('/\s+/', $data);
  
  $plevel1_code;
  $plevel1_name;
  $plevel2_code;
  $plevel2_name;
  $plevel3_code;
  $plevel3_name;
  //dpm($data_array);
  foreach ($data_array as $id => $code) {
    if(preg_match('/^[0-9]+$/', $code)) { //find 0-9 number it's area code

      if(preg_match('/0000$/', $code)) { //find a province code
        $plevel1_code = $code;
        $plevel1_name = $data_array[$id + 1];

        if(preg_match('/^北京市$/', $plevel1_name) || 
           preg_match('/^天津市$/', $plevel1_name) || 
           preg_match('/^上海市$/', $plevel1_name) ||
           preg_match('/^重庆市$/', $plevel1_name)) {

          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => 0,//province parent level is 0
              'area_code' => $plevel1_code,
              'area_name' => $plevel1_name,
              'city_level' => 1 //zhi xia shi
            ))
          ->execute();
          continue ;
        } else {
          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => 0,//province parent level is 0
              'area_code' => $plevel1_code,
              'area_name' => $plevel1_name,
              'city_level' => 2 //province
            ))
          ->execute();
          continue ;
        }
      }

      if(preg_match('/0100$/', $code)) {
        $plevel2_code = $code;
        $plevel2_name = $data_array[$id + 1];
        if(preg_match('/^市辖区$/', $plevel2_name)) {
          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => $plevel1_code,//province is parent
              'area_code' => $plevel2_code,
              'area_name' => $plevel2_name,
              'city_level' => 99 //other
            ))
          ->execute();

          continue ;
        } else {
          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => $plevel1_code,//province is parent
              'area_code' => $plevel2_code,
              'area_name' => $plevel2_name,
              'city_level' => 3 //capital of province
            ))
          ->execute();

          continue ;
        }
      }


      if(preg_match('/00$/', $code)) {
        $plevel2_code = $code;
        $plevel2_name = $data_array[$id + 1];

        if(preg_match('/^县$/', $plevel2_name) ||
           preg_match('/^省直辖县级行政区划$/', $plevel2_name) ||
           preg_match('/^自治区直辖县级行政区划$/', $plevel2_name)) {

          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => $plevel1_code,//province is parent
              'area_code' => $plevel2_code,
              'area_name' => $plevel2_name,
              'city_level' => 99 //other
            ))
          ->execute();
          continue ;
        } else { 

          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => $plevel1_code,//province is parent
              'area_code' => $plevel2_code,
              'area_name' => $plevel2_name,
              'city_level' => 4 //city
            ))
          ->execute();
          continue ;
        }
      }

      if(preg_match('/01$/', $code)) {
        $plevel3_code = $code;
        $plevel3_name = $data_array[$id + 1];

        if(preg_match('/^市辖区$/', $plevel3_name)) {
          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => $plevel2_code,//province is parent
              'area_code' => $plevel3_code,
              'area_name' => $plevel3_name,
              'city_level' => 99 //other
            ))
          ->execute();

          continue ;
        } else {
          if(preg_match('/^北京市$/', $plevel1_name) || 
             preg_match('/^天津市$/', $plevel1_name) || 
             preg_match('/^上海市$/', $plevel1_name) ||
             preg_match('/^重庆市$/', $plevel1_name)) {
            db_insert('wechat_py_nation_city_code_table')
            ->fields(array(
                'plevel' => $plevel1_code,//province is parent
                'area_code' => $plevel3_code,
                'area_name' => $plevel3_name,
                'city_level' => 5 //region of city
              ))
            ->execute();

            continue ;
          } else {
           if(preg_match('/^钟山区$/', $plevel3_name)) {
              db_insert('wechat_py_nation_city_code_table')
              ->fields(array(
                  'plevel' => $plevel2_code,//province is parent
                  'area_code' => $plevel3_code,
                  'area_name' => $plevel3_name,
                  'city_level' => 5 //region of city
                ))
              ->execute();

              continue ;
            } else {
              db_insert('wechat_py_nation_city_code_table')
              ->fields(array(
                  'plevel' => $plevel1_code,//province is parent
                  'area_code' => $plevel3_code,
                  'area_name' => $plevel3_name,
                  'city_level' => 6 //county of city
                ))
              ->execute();

              continue ;
            } 
          }
        }
      }
      
      $plevel3_code = $code;
      $plevel3_name = $data_array[$id + 1];
      //zhi xia shi city area
      if(preg_match('/^北京市$/', $plevel1_name) || 
         preg_match('/^天津市$/', $plevel1_name) || 
         preg_match('/^上海市$/', $plevel1_name) ||
         preg_match('/^重庆市$/', $plevel1_name)) {

        if(preg_match('/2[2-7][0-9]$/', $plevel3_code)) {
          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => $plevel1_code,//province is parent
              'area_code' => $plevel3_code,
              'area_name' => $plevel3_name,
              'city_level' => 4 //same level with city because zhi xia shi
            ))
          ->execute();

          continue ;
        } else {
          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => $plevel1_code,//province is parent
              'area_code' => $plevel3_code,
              'area_name' => $plevel3_name,
              'city_level' => 5 //region of city
            ))
          ->execute();

          continue ;
        }
      } else {
        if(preg_match('/[2-9][0-9]$/', $plevel3_code)) {
          db_insert('wechat_py_nation_city_code_table')
          ->fields(array(
              'plevel' => $plevel1_code,//province is parent
              'area_code' => $plevel3_code,
              'area_name' => $plevel3_name,
              'city_level' => 6 //county of city
            ))
          ->execute();

          continue ;
        } else {
          if(preg_match('/市$/', $plevel3_name)) {
            db_insert('wechat_py_nation_city_code_table')
            ->fields(array(
                'plevel' => $plevel1_code,//province is parent
                'area_code' => $plevel3_code,
                'area_name' => $plevel3_name,
                'city_level' => 6 //county of city
              ))
            ->execute();

            continue ;
          } else {
            db_insert('wechat_py_nation_city_code_table')
            ->fields(array(
                'plevel' => $plevel2_code,//province is parent
                'area_code' => $plevel3_code,
                'area_name' => $plevel3_name,
                'city_level' => 5 //region of city
              ))
            ->execute();

            continue ;
          }
        }
      }

    }
  }
}

function old_menu_weight_section_form(/*$form, &$form_state*/){
  

  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'merchant_express_setup_weight')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->range(0,1);

  $result = $query->execute();

  $node;
  if (!empty($result['node'])) {
    $keys = array_keys($result['node']);
    $node = node_load(array_shift($keys));
  }else{
    drupal_set_message('can\'t find node type merchant_express_setup_weight', 'error');
    return $form;
  }

  module_load_include('inc', 'node', 'node.pages');
  $form = drupal_get_form('merchant_express_setup_weight_node_form', $node);
  //$form = node_add('merchant_express_setup_weight');
  //$form['#attached']['js'] = array(
  //  drupal_get_path('module', 'node') . '/node.js',
  //);

  unset($form['title']);
  $form['actions']['delete']['#access'] = false;
  //dpm($form);
  return drupal_render($form);
}

/*
 * menu page callback form for weight section
 */
function menu_weight_section_form($form, &$form_state){

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => '设置快递重量区间',
    '#attributes' => array('class' => array('container-weight', 'clearfix')),
    '#prefix' => '<div id="ajax-section-weight-wrapper">',
    '#suffix' => '</div>',
  );

  $form['fieldset']['label'] = array(
    '#markup' => '<div class="weight-label-1">首重</div>
                  <div class="weight-label-2">首重价格</div>
                  <div class="weight-label-3">续重</div>
                  <div class="weight-label-4">续重价格</div>',
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
    '#weight' => -2,
  );

  $form['fieldset']['container_break_line1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
    '#weight' => -1,
  );

  //Initial setup this form
  if($form_state['rebuild'] == FALSE) {
    
    $query = db_select('wechat_py_shopping_weight_section_table', 't')
      ->fields('t', array('id', 'start_weight', 'start_price', 'unit_weight', 'unit_price'))
      ->orderBy('t.id', 'ASC');

    $result = $query->execute();
    $num = $result->rowCount();
    
    //Nothing find in table
    if($num == 0){
      $form_state['rows_num'] = 1;
      for ($delta = 0; $delta < $form_state['rows_num']; $delta++) {

        $form['fieldset'][$delta] = array(
          '#type' => 'container',
          '#weight' => $delta,
          '#attributes' => array('class' => array('my-container-inline')),
        );
        $form['fieldset'][$delta]['weight_' . $delta] = array(
          '#type' => 'merchant_express_setup_weight_el',
          '#delta' => $delta,
          '#table_id' => -1, //for new element
          '#startw' => 0,
          '#startp' => 0,
          '#unitw' => 0,
          '#unitp' => 0,
        );
        $form['fieldset'][$delta]['remove'] = array(
          '#type' => 'submit',
          '#name' => $delta,
          '#value' => t('删除'), 
          '#attributes' => array('class' => array('remove-submit')),
          '#validate' => array(),
          '#limit_validation_errors' => array(),
          '#submit' => array('submit_callback_remove_section_weight'),
        );
      }

      $form['fieldset']['max_delta'] = array(
        '#type' => 'value',
        '#value' => $form_state['rows_num'],
      );
    }else{

      $delta = 0;
      foreach ($result as $id => $row) {
        // code...
        $form['fieldset'][$delta] = array(
          '#type' => 'container',
          '#weight' => $delta,
          '#attributes' => array('class' => array('my-container-inline')),
        );
        $form['fieldset'][$delta]['weight_' . $delta] = array(
          '#type' => 'merchant_express_setup_weight_el',
          '#delta' => $delta,
          '#table_id' => $row->id,
          '#startw' => $row->start_weight,
          '#startp' => $row->start_price,
          '#unitw' => $row->unit_weight,
          '#unitp' => $row->unit_price,
        );
        $form['fieldset'][$delta]['remove'] = array(
          '#type' => 'submit',
          '#name' => $delta,
          '#value' => t('删除'), 
          '#attributes' => array('class' => array('remove-submit')),
          '#validate' => array(),
          '#limit_validation_errors' => array(),
          '#submit' => array('submit_callback_remove_section_weight'),
        );
        $delta++;
      }

      $form_state['rows_num'] = $delta;
      $form['fieldset']['max_delta'] = array(
        '#type' => 'value',
        '#value' => $delta,
      );
    }

  }else{  //add new data or remove data

    //dpm($form_state);
    $form['fieldset'] = $form_state['fieldset'];
    $delta = $form_state['rows_num']; 
    if($delta > $form['fieldset']['max_delta']['#value']) {

      $form['fieldset'][$delta] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('my-container-inline')),
        '#weight' => $delta,
      );

      $form['fieldset'][$delta]['weight_' . $delta] = array(
        '#type' => 'merchant_express_setup_weight_el',
        '#delta' => $delta,
        '#table_id' => -1, //for new element
        '#startw' => 0,
        '#startp' => 0,
        '#unitw' => 0,
        '#unitp' => 0,
      );

      $form['fieldset'][$delta]['remove'] = array(
        '#type' => 'submit',
        '#name' => $delta,
        '#value' => t('删除'), 
        '#attributes' => array('class' => array('remove-submit')),
        '#validate' => array(),
        '#limit_validation_errors' => array(),
        '#submit' => array('submit_callback_remove_section_weight'),
        /*
        '#ajax' => array(
          'path' => 'wechat-py-shopping/wechat-merchant-express/form-test/ajax-remove',
          'effect' => 'fade',
        ),
        */
      );
    }
    $form['fieldset']['max_delta']['#value'] = $delta;
    //dpm($form);
  }

  $form['fieldset']['add_weight'] = array(
    '#type' => 'submit',
    '#value' => t('增加区间'),
    '#weight' => 100,
    '#submit' => array('submit_ajax_section_weight'),
    '#validate' => array(),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => 'ajax_section_weight_callback',
      'wrapper' => 'ajax-section-weight-wrapper',
    ),
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_express_form.css',
  );

  $form['save_all'] = array(
    '#type' => 'submit',
    '#value' => t('保存所有记录'),
    '#weight' => 200,
  );

  $form['#submit'][] = 'menu_weight_section_form_all_submit';

  return $form;
}

function ajax_section_weight_callback($form, $form_state) {
  return $form['fieldset'];
}

function submit_ajax_section_weight($form, &$form_state){
  $form_state['fieldset'] = $form['fieldset'];
  $form_state['rows_num']++;
  $form_state['rebuild'] = TRUE;
}

function menu_weight_section_form_all_submit($form, &$form_state){
  $op = $form_state['values']['op'];
  switch ($op) {
    case '保存所有记录':
      $inputs = $form_state['input'];
      foreach ($inputs as $key => $data) {

        //find weight_x key from form_state['input']['weight_x']['cr']['start_text']
        //and set value to parent_element[x]['weight_x']['cr']['start_text'][#value]
        if(preg_match('/^weight_/', $key)){
          $data_array = preg_split('/_/', $key);
          $x = $data_array[1];

          $form_state['values']['weight_' . $x]['cr']['start_weight'] =
            $form_state['input']['weight_' . $x]['cr']['start_weight'];
          $form_state['values']['weight_' . $x]['cr']['start_price'] =
            $form_state['input']['weight_' . $x]['cr']['start_price'];
          $form_state['values']['weight_' . $x]['cr']['unit_weight'] =
            $form_state['input']['weight_' . $x]['cr']['unit_weight'];
          $form_state['values']['weight_' . $x]['cr']['unit_price'] =
            $form_state['input']['weight_' . $x]['cr']['unit_price'];
        }

      }

      $values = $form_state['values'];
      foreach ($values as $key => $data) {
        //find weight_x key from form_state['values']['weight_x']['cr']['start_text']
        //and set value to parent_element[x]['weight_x']['cr']['start_text'][#value]
        if(preg_match('/^weight_/', $key)){
          $data_array = preg_split('/_/', $key);
          $x = $data_array[1];

          $start_w = $form_state['values']['weight_' . $x]['cr']['start_weight'];
          $start_p = $form_state['values']['weight_' . $x]['cr']['start_price'];
          $unit_w = $form_state['values']['weight_' . $x]['cr']['unit_weight'];
          $unit_p = $form_state['values']['weight_' . $x]['cr']['unit_price'];
          $table_id = $form_state['values']['weight_' . $x]['cr']['table_id'];

          if($table_id == -1) {
            db_insert('wechat_py_shopping_weight_section_table')
              ->fields(array(
                'start_weight' => $start_w,
                'start_price' => $start_p,
                'unit_weight' => $unit_w,
                'unit_price' => $unit_p,))
              ->execute();
            //new data to be insert into table
          }else{
            db_update('wechat_py_shopping_weight_section_table')
              ->fields(array(
                'start_weight' => $start_w,
                'start_price' => $start_p,
                'unit_weight' => $unit_w,
                'unit_price' => $unit_p,))
              ->condition('id', $table_id)
              ->execute();
            //data to be updated into table
          }
        }

      }
      break;

    default:
      drupal_set_message('缺少提交按钮！');
      break;
  }
}

/*
 * form test for everything
 */
function menu_weight_form_test_form($form, &$form_state){
  //insert_nation_area_code_table();
  //preg_match_chinese_test();

  $protocol = (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off' || $_SERVER['SERVER_PORT'] == 443) ? "https://" : "http://";
  $purl = "$protocol$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
  dpm($purl);
  
  if(empty($form_state['rows_num'])){
    $form_state['rows_num'] = 0;
    $form['container'] = array(
      '#type' => 'container',
      '#attributes' => array('id' => array('ajax-wrapper-for-test')),
      '#tree' => TRUE,
    );

    for ($i = 0; $i < $form_state['rows_num']; $i++) {
      $form['container'][$i] = array(
        '#prefix' => '<div class="my-container-inline cr-' . $i .'">',
        '#suffix' => '</div>',
      );
      $form['container'][$i]['text_' . $i] = array(
        '#type' => 'merchant_express_setup_weight_el',
        '#delta' => $i,
        '#table_id' => 7,
        '#startw' => 0,
        '#startp' => 0,
        '#unitw' => 0,
        '#unitp' => 0,
      );

      $form['container'][$i]['del'] = array(
        '#type' => 'submit',
        '#name' => $i,
        '#value' => t('删除'), 
        '#validate' => array(),
        '#limit_validation_errors' => array(),
        //'#attributes' => array('class' => array('after-my-container-inline')),

        '#submit' => array('submit_container_del'),
        '#ajax' => array(
          'path' => 'wechat-py-shopping/wechat-merchant-express/form-test/ajax-remove',
          'effect' => 'fade',
        ),
      );
    }
  }else{
    $form['container'] = $form_state['container'];
  }


  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('测试'),
    '#submit' => array('submit_test_button'),

/*
    '#ajax' => array(
      'callback' => 'ajax_test_buttion_callback',
      'wrapper' => 'ajax-wrapper-for-test',
    ),
    */
  );

  //display table for express template

  $form['container_break_line1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );
  $form['container_break_line2'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

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

  $form['area_container'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="ajax-wrapper-area">',
    '#suffix' => '</div>',
  );

  $condition; //for city level   98: city self  4:city of province(include zhixiashi county, exclude capital city) 6: county of province
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
      '#id' => 'form-test-multi-select-code',
      '#multiple' => TRUE,
    );
    $form_state['condition'] = 98;

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
        $condition = 98; //province and zhi xia shi
        break;

      case '1':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', 3)
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $condition = 98; //capital city
        break;

      case '2':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', array(1, 3, 4), 'IN')
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $condition = 98; //capital city
        break;

      case '3':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', array(1, 2), 'IN')
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $condition = 4; //city
        break;

      case '4':
        $query = db_select('wechat_py_nation_city_code_table', 't')
          ->condition('t.city_level', array(1, 2), 'IN')
          ->fields('t', array('area_code', 'area_name'))
          ->orderBy('t.area_code', 'ASC');
        $condition = 6; //county
        break;
      
      default:
        // code...
        break;
    }
    $form_state['template_id'] = 1;
    $form_state['condition'] = $condition;

    $result = $query->execute();

    $city_options;
    foreach ($result as $id => $row) {
      $city_options[$row->area_code] = $row->area_name;
    }

    $form['area_container']['city_select'] = array(
      '#type' => 'select',
      '#options' => $city_options,
      '#id' => 'form-test-multi-select-code',
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


  $form['weight_container']['select'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#id' => 'weight-multi-select-code',
    '#multiple' => TRUE,
  );

  $form['save_test_submit'] = array(
    '#type' => 'submit',
    '#value' => t('保存数据'),
    '#id' => 'save-city-submit',
    '#validate' => array(),
    '#limit_validation_errors' => array(),
    '#submit' => array('submit_save_city'),
    /*
    '#ajax' => array(                                 
      'callback' => 'ajax_submit_save_city',        
    ),
    */
  );

  /*
  $form['save_test_submit'] = array(
    '#markup' => '<div id="save-city-submit">保存城市</div>',
  );
  */

  global $base_url;
  $ajax_express_url = array(
    'basePath' => $base_url . '/wechat-py-shopping/wechat-merchant-express/form-test/ajax-json',
  );
  drupal_add_js(array('wechat_py_shopping' => $ajax_express_url), 'setting');

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/multi-select.css',
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_express_form.css',
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/js/jquery.multi-select.js',
    drupal_get_path('module', 'wechat_py_shopping') . '/js/jquery.quicksearch.js',
    drupal_get_path('module', 'wechat_py_shopping') . '/js/form-test.js',
  );

  return $form;
}

//ajax call for select city area
function ajax_select_area_callback($form, $form_state) {
  return $form['area_container'];
}

function submit_container_del($form, &$form_state){

  //dpm($form, 'del');
  //dpm($form_state, 'del');
  $button = $form_state['triggering_element'];
  $row = $button['#name'];

  // Where in the form we'll find the parent element.
  $address = array_slice($button['#array_parents'], 0, -2);
  $parent_element = drupal_array_get_nested_value($form, $address);
  // Go one level up in the form, to the widgets container.
  //dpm($parent_element);
  //remove input by del submit
  unset($form_state['input']['container'][$row]);
  unset($parent_element[$row]);

  $inputs = $form_state['input']['container'];
  foreach ($inputs as $key => $data) {
    $parent_element[$key]['text_' . $key]['#value'] = $data['text_' . $key];
  }

  if($form_state['rows_num'] > 0){
    $form_state['rows_num']--;
  }

  //dpm($parent_element, 'parent_element');

  //$form['container'] = $parent_element;
  $form_state['container'] = $parent_element; 


  $form_state['rebuild'] = TRUE;
}

function ajax_submit_save_city($form, &$form_state){
  //$form_state['rebuild'] = TRUE;
  $commands = array();
  $commands[] = ajax_command_invoke(NULL, 'save_submit', array($form_state['template_id'], $form_state['condition']));
  return array('#type' => 'ajax', '#commands' => $commands);
  //ajax_deliver(array('#type' => 'ajax', '#commands' => $commands));
}

function submit_save_city ($form, &$form_state){
  dpm($form_state);
  //$form_state['rebuild'] = TRUE;
}

function submit_test_button($form, &$form_state){
  dpm($form_state);
  //dpm($form);
  // code...
}

function form_test_ajax_json_data() {
  $received_json = file_get_contents("php://input");
  $json = drupal_json_decode($received_json);

  $template_id = $json['template_id'];
  $city = $json['city'];
  $weight = $json['weight'];
  watchdog('recev city', 'postArray <pre>@print_r</pre>', array('@print_r' => print_r($json, TRUE)));
/*
  foreach ($json as $id => $data) {
    $text = $id . ':' . $data;
    //$return = file_put_contents($file, $text, FILE_APPEND | LOCK_EX);
    dpm($text);
    // code...
  }
  */
  //dpm($json);
}

/*
 * return function for hook_theme
 */
function _wechat_py_shopping_theme($existing, $type, $theme, $path) {

  return array(
    'merchant_express_form_weight_fee_theme_wrappers' => array(
      'render element' => 'element',
    ),

    'merchant_express_setup_weight_theme_wrappers' => array(
      'render element' => 'element',
    ),

    'my_link_button' => array(
      'render element' => 'element',
    ),
  );
}

/**
 * theme_wrapper for merchant_express_form_weight_fee_theme_wrappers
 */
function theme_merchant_express_form_weight_fee_theme_wrappers($variables) {
  $element = $variables['element'];
  //dpm($element);

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'],
      array(
        ' ' => '-',
        '_' => '-',
        '[' => '-',
        ']' => '',
      )
    );
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . '<div class="container-inline">' . $prefix . $element['#children'] . $suffix . "</div>\n";
      break;

    case 'invisible':
    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= ' <div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";


  return $output;
}

/**
 * theme_wrapper for merchant_express_setup_weight_theme_wrappers
 */
function theme_merchant_express_setup_weight_theme_wrappers($variables) {
  $element = $variables['element'];

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'],
      array(
        ' ' => '-',
        '_' => '-',
        '[' => '-',
        ']' => '',
      )
    );
  }

  // add own element class for save and remove
  $delta = $element['#delta'];
  $attributes['class'][] = 'form-item-container-row-' . $delta;
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . '<div class="container-inline">' . $prefix . $element['#children'] . $suffix . "</div>\n";
      break;

    case 'invisible':
    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= ' <div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";


  return $output;
}

/*
 * return function for hook_element_info
 */
function _wechat_py_shopping_element_info() {
  $types['merchant_express_form_weight_fee'] = array(
    // #input == TRUE means that the form value here will be used to determine
    // what #value will be.
    '#input' => TRUE,

    // #process is an array of callback functions executed when this element is
    // processed. Here it provides the child form elements which define
    // areacode, prefix, and extension.
    '#process' => array('merchant_express_form_weight_fee_process'),

    // Validation handlers for this element. These are in addition to any
    // validation handlers that might.
    '#element_validate' => array('merchant_express_form_weight_fee_validate'),
    '#autocomplete_path' => FALSE,
    '#theme_wrappers' => array('merchant_express_form_weight_fee_theme_wrappers'),
  );

  $types['merchant_express_setup_weight_el'] = array(
    // #input == TRUE means that the form value here will be used to determine
    // what #value will be.
    '#input' => TRUE,

    // #process is an array of callback functions executed when this element is
    // processed. Here it provides the child form elements which define
    // areacode, prefix, and extension.
    '#process' => array('merchant_express_setup_weight_process'),

    // Validation handlers for this element. These are in addition to any
    // validation handlers that might.
    '#element_validate' => array('merchant_express_setup_weight_validate'),
    '#autocomplete_path' => FALSE,
    '#theme_wrappers' => array('merchant_express_setup_weight_theme_wrappers'),
  );

  return $types;
}

/*
 * theme wrappers for my link button
 */
function theme_my_link_button($variables) {
  $element = $variables['element'];
  dpm($element);
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  //$element['#attributes']['class'][] = 'form-' . $element['#button_type'];
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Process callback for the 1kg_15kg_process.
 */
function merchant_express_form_weight_fee_process($element, &$form_state, $complete_form) {
  // #tree = TRUE means that the values in $form_state['values'] will be stored
  // hierarchically. In this case, the parts of the element will appear in
  // $form_state['values'] as
  // $form_state['values']['<element_name>']['areacode'],
  // $form_state['values']['<element_name>']['prefix'],
  // etc. This technique is preferred when an element has member form
  // elements.
  //dpm($element);
  // Include the CTools tools that we need.
  ctools_include('ajax');

  $element['#tree'] = TRUE;

  $element['container_select'] = array (
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline', 'container-select', 'clearfix')),
  );

  $element['container_select']['label'] = array(
    '#type' => 'item',
    '#title' => t('选择计价重量区间值'), 
  );

  $element['container_select']['weight_select'] = array (
    '#type' => 'select',
    '#options' => array(
      0 => t('从1公斤－15公斤'),
      1 => t('从15.1公斤－50公斤'),
    ),
    '#default_value' => 0,
  );

  $element['container_express'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline', 'container-express', 'clearfix')),
  );

  $element['container_express']['label'] = array(
    '#type' => 'item',
    '#title' => t('指定区域'), 
  );

  $element['container_express']['edit'] = array(
    '#markup' => '<div><a class="js_edit_area" href="javascript:;">编辑</a></div>',
  );

  //dpm($element['#id']);
  $nums = preg_split('/name-/', $element['#id']);
  $id = $nums[1];
  $element['container_express']['delete'] = array(
    //'#markup' => '<div><a class="js_delete_area" href="javascript:;">删除</a></div>',
    '#markup' => '<div class="js_delete_area">' . 
                 ctools_ajax_text_button("删除", 
                 "wechat-py-shopping/wechat-merchant-express/$id/delete", t('删除本行')) .
                 '</div>',
  );

  $element['container_express']['start_level'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#attributes' => array('class' => array('start-level')),
  );


  $element['container_express']['weight_unit'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#attributes' => array('class' => array('weight-unit')),
  );

  $element['container_express']['weight_price'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#attributes' => array('class' => array('weight-price')),
  );
  return $element;
}

/**
 * Validation handler for the merchant weight fee.
 *
 * Any problems are shown on the form element using form_error().
 */
function merchant_express_form_weight_fee_validate($element, &$form_state) {

  dpm($form_state);
  if($element['#value']['container_express']['start_level'] <= 0) {
    form_error($element['container_express']['start_level'], t('指定公斤起价: 不能为0，最大为999元'));
  }

  if(0 == preg_match('/^[0-9.]+$/', $element['#value']['container_express']['start_level'])) {
    form_error($element['container_express']['start_level'], t('指定公斤起价: 必须输入数字，最大为999元'));
  }

  if($element['#value']['container_express']['weight_unit'] <= 0) {
    form_error($element['container_express']['weight_unit'], t('续重量计价单位: 不能为0，最大为999元'));
  }

  if(0 == preg_match('/^[0-9.]+$/', $element['#value']['container_express']['weight_unit'])) {
    form_error($element['container_express']['weight_unit'], t('续重量计价单位: 必须输入数字，最大为999元'));
  }

  if($element['#value']['container_express']['weight_price'] <= 0) {
    form_error($element['container_express']['weight_price'], t('续重量运费计价: 不能为0，最大为999元'));
  }

  if(0 == preg_match('/^[0-9.]+$/', $element['#value']['container_express']['weight_price'])) {
    form_error($element['container_express']['weight_price'], t('续重量运费计价: 必须输入数字，最大为999元'));
  }

  return $element;
}

function merchant_express_setup_weight_process($element, &$form_state, $complete_form) {
  // #tree = TRUE means that the values in $form_state['values'] will be stored
  // hierarchically. In this case, the parts of the element will appear in
  // $form_state['values'] as
  // $form_state['values']['<element_name>']['areacode'],
  // $form_state['values']['<element_name>']['prefix'],
  // etc. This technique is preferred when an element has member form
  // elements.

  //ctools_include('ajax');

  $element['#tree'] = TRUE;

  //for rows num
  $delta = $element['#delta'];
  //if it's a new, then table_id is 0
  $table_id = $element['#table_id'];
  $value1 = $element['#startw'];
  $value2 = $element['#startp'];
  $value3 = $element['#unitw'];
  $value4 = $element['#unitp'];

  $element['cr'] = array (
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline', 'container-row-' . $delta, 'clearfix')),
  );

  $element['cr']['table_id'] = array(
    '#type' => 'value',
    '#value' => $table_id,
  );

  $element['cr']['start_weight'] = array(
    '#type' => 'textfield',
    '#size' => 6,
    '#maxlength' => 6,
    '#required' => TRUE,
    '#field_suffix' => t('公斤'),
    '#default_value' => $value1,
    '#prefix' => '<div class="start-weight-text">',
    '#suffix' => '</div>',
  );

  $element['cr']['start_price'] = array(
    '#type' => 'textfield',
    '#size' => 7,
    '#maxlength' => 7,
    '#required' => TRUE,
    '#field_suffix' => t('元'),
    '#default_value' => $value2,
    '#prefix' => '<div class="start-price-text">',
    '#suffix' => '</div>',
  );

  $element['cr']['unit_weight'] = array(
    '#type' => 'textfield',
    '#size' => 6,
    '#maxlength' => 6,
    '#required' => TRUE,
    '#field_suffix' => t('公斤'),
    '#default_value' => $value3,
    '#prefix' => '<div class="unit-weight-text">',
    '#suffix' => '</div>',
  );

  $element['cr']['unit_price'] = array(
    '#type' => 'textfield',
    '#size' => 7,
    '#maxlength' => 7,
    '#required' => TRUE,
    '#field_suffix' => t('元'),
    '#default_value' => $value4,
    '#prefix' => '<div class="unit-price-text">',
    '#suffix' => '</div>',
  );


  return $element;
}

/*
 * remove section weight submit callback
 */
function submit_callback_remove_section_weight($form, &$form_state){
  //dpm($form_state);
  $button = $form_state['triggering_element'];
  $row = $button['#name'];

  // Where in the form we'll find the parent element.
  $address = array_slice($button['#array_parents'], 0, -2);
  $parent_element = drupal_array_get_nested_value($form, $address);
  //dpm($parent_element);

  //remove data from table if table_id is not -1
  $table_id = $parent_element[$row]['weight_' . $row]['#table_id'];
  if($table_id != -1) {
    db_delete('wechat_py_shopping_weight_section_table')
    ->condition('id', $table_id)
    ->execute();
  }

  //dpm($table_id);
  unset($form_state['input']['weight_' . $row]);
  unset($parent_element[$row]);

  $inputs = $form_state['input'];
  foreach ($inputs as $key => $data) {

    //find weight_x key from form_state['input']['weight_x']['cr']['start_text']
    //and set value to parent_element[x]['weight_x']['cr']['start_text'][#value]
    if(preg_match('/^weight_/', $key)){
      $data_array = preg_split('/_/', $key);
      $x = $data_array[1];
      if(isset($parent_element[$key])) {
        $parent_element[$x]['weight_' . $x]['cr']['start_weight']['#value'] =
          $form_state['input']['weight_' . $x]['cr']['start_weight'];

        $parent_element[$x]['weight_' . $x]['cr']['start_price']['#value'] =
          $form_state['input']['weight_' . $x]['cr']['start_price'];

        $parent_element[$x]['weight_' . $x]['cr']['unit_weight']['#value'] =
          $form_state['input']['weight_' . $x]['cr']['unit_weight'];

        $parent_element[$x]['weight_' . $x]['cr']['unit_price']['#value'] =
          $form_state['input']['weight_' . $x]['cr']['unit_price'];
      }
    }

  }

  $form_state['fieldset'] = $parent_element; 

  //dpm($parent_element);
  //dpm($form_state);
  $form_state['rebuild'] = TRUE;
}

/*
 * ajax callback for remove section weight
 */
 /*
function ajax_callback_remove_section_weight($form, &$form_state){
  // code...
  return $form['fieldset'];
}
*/

/*
 * for element type "merchant_express_setup_weight" validation function
 */
function merchant_express_setup_weight_validate($element, &$form_state) {

  //dpm($element);
  //dpm($form_state);
  //首重检验
  if($element['#value']['cr']['start_weight'] <= 0) {
    form_error($element['cr']['start_weight'], t('指定公斤: 不能为0，最大为999.99公斤或999999公斤'));
  }

  if(0 == preg_match('/^[0-9.]+$/', $element['#value']['cr']['start_weight'])) {
    form_error($element['container_express']['start_level'], t('指定公斤: 必须输入数字可带小数点'));
  }

  //首重价格检验
  if($element['#value']['cr']['start_price'] <= 0) {
    form_error($element['cr']['start_price'], t('价格: 不能为0，最大为999.99元或者999999元'));
  }

  if(0 == preg_match('/^[0-9.]+$/', $element['#value']['cr']['start_price'])) {
    form_error($element['container_express']['start_level'], t('价格: 必须输入数字可带小数点'));
  }

  //续重检验
  if($element['#value']['cr']['unit_weight'] <= 0) {
    form_error($element['cr']['unit_weight'], t('指定公斤: 不能为0，最大为999.99公斤或999999公斤'));
  }

  if(0 == preg_match('/^[0-9.]+$/', $element['#value']['cr']['unit_weight'])) {
    form_error($element['cr']['end_text'], t('指定公斤: 必须输入数字可带小数点'));
  }

  //续重价格检验
  if($element['#value']['cr']['unit_price'] <= 0) {
    form_error($element['cr']['unit_price'], t('价格: 不能为0，最大为999.99元或者999999元'));
  }

  if(0 == preg_match('/^[0-9.]+$/', $element['#value']['cr']['unit_price'])) {
    form_error($element['container_express']['start_level'], t('价格: 必须输入数字可带小数点'));
  }

  return $element;
}
/**
 * End of wechat_merchant_express_form.inc file name
 */
