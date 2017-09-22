<?php

function menu_wechat_merchant_group_getall_form($form, &$form_state){

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('所有分组消息'), 
  );

  $value = get_merchant_group_all();

  $data = drupal_json_decode($value);
  dpm($data);
  $form['fieldset']['group_info'] = array(
    '#type' => 'item',
    '#markup' => '<div>' . $value . '</div>',
  );
  return $form;
}

function get_merchant_group_all(){
  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $req_url = t(
    variable_get('获取所有分组-分组管理接口-微信小店'),
    array('@ACCESS_TOKEN' => variable_get('access_token'))
  );
  $result = wechat_php_curl_https_get($req_url);
  if (!$result)
  {
    watchdog('wechat get all merchant group info', 'get error in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }
  return $result;
}

/**
 * End of menu_wechat_merchant_group_getall_form.inc file name
 */
