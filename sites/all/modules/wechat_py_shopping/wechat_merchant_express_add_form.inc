<?php
/*
 * Implement menu_wechat_merchant_express_add_form for add express
 */
function menu_wechat_merchant_express_add_form($form, &$form_state){
  $form['container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['container']['express_name'] = array(
    '#type' => 'textfield',
    '#title' => t('邮费模版名称'),
    '#size' => 30, 
    '#maxlength' => 30, 
    '#required' => TRUE,
    '#description' => t('小于128个字'),
  );

  $form['container']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('保存'),
    '#submit' => array('submit_callback_save_express_name'),
  );

  return $form;
}
  /*
   * submit callback for save merchant express
   */
function submit_callback_save_express_name($form, &$form_state){
  //dpm($form_state);
  $result = $form_state['values']['express_name'];
  db_insert('wechat_py_shopping_merchant_express_template_table')
    ->fields(array(
      'template_name' => $result))
    ->execute();
  $form_state['redirect'] = 'wechat-py-shopping/wechat-merchant-express/list';
}

function xxx_yyyy(){
  $form['container_break_line1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

  //province and city select table
  $query = db_select('wechat_py_nation_city_code_table', 't')
    ->condition('t.plevel', 0)
    ->fields('t', array('area_code', 'area_name'))
    ->orderBy('t.area_code', 'ASC');

  $result = $query->execute();

  $options;
  foreach ($result as $id => $row) {
    $options[$row->area_code] = $row->area_name;
  }

/*
  $form['province_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );
  */

  $form['select_province'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#multiple' => FALSE,
    '#title' => t('请选择省份'),
    /*
    '#ajax' => array(
      'wrapper' => 'province-selection-wrapper',
      'callback' => 'ajax_province_select_callback',
      'method' => 'replaceWith',
    ),
    */
  );

  $form['select_level'] = array(
    '#type' => 'select',
    '#options' => array(
      0 => t('缺省'),
      1 => t('省会'),
      2 => t('地级市'),
      3 => t('县'),
    ),
    '#multiple' => FALSE,
    '#title' => t('行政区域划分'),
    /*
    '#ajax' => array(
      'wrapper' => 'province-selection-wrapper',
      'callback' => 'ajax_province_select_callback',
      'method' => 'replaceWith',
    ),
    */
  );


  //css and js
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_express_form.css',
    drupal_get_path('module', 'wechat_py_shopping') . '/css/multi-select.css',
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/js/jquery.multi-select.js',
    drupal_get_path('module', 'wechat_py_shopping') . '/js/py_shopping_add_form.js',
  );
  return $form;
}

/*
 * Two forms for add nation area and weight form
 */
function _form_add_wiards() {
  return array(
    1 => array(
      'form' => 'menu_wechat_merchant_express_add_name_form',
    ),
    2 => array(
      'form' => 'menu_wechat_merchant_express_add_area_form',
    ),
    3 => array(
      'form' => 'menu_wechat_merchant_express_add_weight_fee_form',
    ),
  );
}

/*
 * Implement old_menu_wechat_merchant_express_add_form for add express
 */
function old_menu_wechat_merchant_express_add_form($form, &$form_state){

  //Initial form for add nation area form
  if (empty($form_state['step'])) {
    $form_state['step'] = 1;

    // This array contains the function to be called at each step to get the
    // relevant form elements. It will also store state information for each
    // step.
    $form_state['step_information'] = _form_add_wiards();

    // for checkbox city search
    $form_state['province_selected'] = FALSE;
  }
  $step = &$form_state['step'];

  // Call the function named in $form_state['step_information'] to get the
  // form elements to display for this step.
  $form = $form_state['step_information'][$step]['form']($form, $form_state);

  if ($step > 1) {
    $form['prev'] = array(
      '#type' => 'submit',
      '#value' => t('返回'),
      '#name' => 'prev',
      '#submit' => array('form_example_wizard_previous_submit'),
      '#limit_validation_errors' => array(),
    );
  }

  // Show the Next button only if there are more steps defined.
  if ($step < count($form_state['step_information'])) {
    // The Next button should be included on every step.
    $form['next'] = array(
      '#type' => 'submit',
      '#value' => t('Next'),
      '#name' => 'next',
      '#submit' => array('form_example_wizard_next_submit'),
    );
  }
  else {
    // Just in case there are no more steps, we use the default submit handler
    // of the form wizard. Call this button Finish, Submit, or whatever you
    // want to show. When this button is clicked, the
    // form_example_wizard_submit handler will be called.
    $form['finish'] = array(
      '#type' => 'submit',
      '#value' => t('Finish'),
    );
  }
/*
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

*/

  return $form;
}

/**
 * Submit handler for the "previous" button.
 *
 * This function:
 * - Stores away $form_state['values']
 * - Decrements the step counter
 * - Replaces $form_state['values'] with the values from the previous state.
 * - Forces form rebuild.
 *
 * You are not required to change this function.
 *
 * @ingroup form_example
 */
function form_example_wizard_previous_submit($form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];
  if ($current_step > 1) {
    $current_step--;
    $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
  }
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the 'next' button.
 *
 * This function:
 * - Saves away $form_state['values']
 * - Increments the step count.
 * - Replace $form_state['values'] from the last time we were at this page
 *   or with array() if we haven't been here before.
 * - Force form rebuild.
 *
 * You are not required to change this function.
 *
 * @ingroup form_example
 */
function form_example_wizard_next_submit($form, &$form_state) {
  $current_step = &$form_state['step'];
  $form_state['step_information'][$current_step]['stored_values'] = $form_state['values'];

  if ($current_step < count($form_state['step_information'])) {
    $current_step++;
    if (!empty($form_state['step_information'][$current_step]['stored_values'])) {
      $form_state['values'] = $form_state['step_information'][$current_step]['stored_values'];
    }
    else {
      $form_state['values'] = array();
    }
    // Force rebuild with next step.
    $form_state['rebuild'] = TRUE;
    return;
  }
}

/*
 * First form to add express name
 */
function menu_wechat_merchant_express_add_name_form($form, &$form_state){
  $form = array();
  $form['express_name'] = array(
    '#type' => 'textfield',
    '#title' => t('邮费模版名称'),
    '#size' => 30, 
    '#maxlength' => 30, 
    '#required' => TRUE,
    '#description' => t('小于30个字'),
    '#attributes' => array('class' => array('template-name', 'clearfix')),
    '#default_value' => !empty($form_state['values']['express_name']) ? $form_state['values']['express_name'] : '',
    '#prefix' => '<div class="container-inline">',
    '#suffix' => '</div>',
  );
  return $form;
}

/*
 * Second form to add nation area
 */
function menu_wechat_merchant_express_add_area_form($form, &$form_state){

  //search province
  $query = db_select('wechat_py_nation_city_code_table', 't')
    ->condition('t.plevel', 0)
    ->fields('t', array('area_code', 'area_name'))
    ->orderBy('t.area_code', 'ASC');

  $result = $query->execute();

  $options;
  foreach ($result as $id => $row) {
    $options[$row->area_code] = $row->area_name;
  }

  $form['province_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['province_container']['select_province'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#multiple' => FALSE,
    '#title' => t('请选择省份'),
    '#ajax' => array(
      'wrapper' => 'province-selection-wrapper',
      'callback' => 'ajax_province_select_callback',
      'method' => 'replaceWith',
    ),
  );


/*
  $form['text_test'] = array(
    '#type' => 'checkbox',
    '#title' => t('测试'), 
    '#default_value' => 0, 
    '#prefix' => '<div id="province-selection-wrapper">',
    '#suffix' => '</div>',
  );
  */

  $form['province_container']['check_city'] = array(
    '#type' => 'checkbox',
    '#title' => t('是否选择城市'),
    '#default_value' => 0, 
    '#attributes' => array('style' => array('margin-left: 4em;')),
    '#ajax' => array(
      'wrapper' => 'city-selection-wrapper',
      'callback' => 'ajax_city_select_callback',
    ),
    '#prefix' => '<div id="province-selection-wrapper">',
    '#suffix' => '</div>',
  );

  $form['container_break_line1'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-break-line')),
  );

  $form['city_container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="city-selection-wrapper">',
    '#suffix' => '</div>',
    /*
    '#states' => array(
      // Action to take.
      'visible' => array(
        ':input[name="check_city"]' => array('checked' => TRUE),
      ),
    ),
    */
  );

  $check_city = !empty($form_state['values']['check_city']) ? $form_state['values']['check_city'] : 0;
  if($check_city) {
    $form['city_container']['select_area'] = array(
      '#type' => 'select',
      '#options' => $options,
      '#id' => 'multi-select-code',
      '#multiple' => TRUE,
      '#attributes' => array('class' => array('city-container-select')),
    );
  }

  //send id multi-select-code to js
  //drupal_add_js(array('jsWeights' => $weights), array('type' => 'setting'));
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_express_form.css',
    drupal_get_path('module', 'wechat_py_shopping') . '/css/multi-select.css',
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/js/jquery.multi-select.js',
    drupal_get_path('module', 'wechat_py_shopping') . '/js/py_shopping_add_form.js',
  );
  //dpm();
  // code...
  return $form;
}

/**
 * Ajax Callback for province-selection-wrapper.
 *
 */
function ajax_province_select_callback($form, $form_state) {
  //$form_state['province_selected'] = TRUE;
  //return $form['province_container']['check_city'];
  
  if($form['province_container']['check_city']['#checked']){
    $form['province_container']['check_city']['#checked'] = FALSE;
    $form_state['values']['check_city'] = 0;
  }
  return $form['province_container']['check_city'];
  //dpm($form);
  //dpm($form_state);
  //return $form['text_test'];
}

/**
 * Ajax Callback for city_container.
 *
 */
function ajax_city_select_callback($form, $form_state) {
  return $form['city_container'];
}

/**
 * End of wechat_merchant_express_add_form.inc file name
 */

