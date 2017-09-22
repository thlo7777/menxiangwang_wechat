<?php

//page call for custome service order detail
function wechat_mobile_shopping_service_order_detail_page() {

  global $base_url;
  $page = array();

  //check if it's a mobile browser, use touch event feature to test.
  $page['inline_js'] = '
    function isMobile() {
      try{ document.createEvent("TouchEvent"); return true; }
      catch(e){ return false; }
    }

    if (!isMobile()) {
      window.location.replace("http://mxweixin.dreamland360.com/content/默认的404错误");
    }
  ';

  //get user OPENID
  $code = isset($_GET['code']) ? $_GET['code'] : '';
  $json = oauth2_get_accss_token($code);
  
  if ($json == null) {
    $page['title'] = '订单详情';
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  $state = $_GET['state'];  //order table id

  //get Openid by code
  $page['xyz'] = base64_encode($json->openid);    //openid should be encoded by base64

  //watchdog('mobile shopping order', 'openid = <pre>@data</pre>', array('@data' => print_r($json->openid, TRUE)));
  
  $page['title'] = '订单详情';

  $query = db_select('mobile_shopping_user_order_table', 't')
    ->condition('t.order_state', 1, '>=')
    ->condition('t.id', $state, '=')
    ->fields('t');

  $result = $query->execute();

  $total_order = array();
  foreach ($result as $row) {
    //dpm($row);
    $total_order['out_trade_no'] = $row->out_trade_no;
    $total_order['time_start'] = date('Y年m月d日 H:i',strtotime($row->time_end));
    $total_order['total_fee'] = number_format((floatval($row->total_fee) / 100), 2);
    $total_order['order_exp_fee'] = number_format($row->area_exp_fee, 2);
    $total_order['order_addr'] = $row->order_addr;
    $total_order['order_detail'] = nl2br(rtrim($row->order_detail));
    $total_order['order_state'] = $row->order_state;

    $area_term = taxonomy_term_load($row->area_id);
    if ($area_term) {
        //find user area term
      $total_order['area_name'] = $area_term->name;
    } else {
      $total_order['area_name'] = '无';
    }
  }

  $page['order_detail'] = $total_order;

  return $page;
}

function deliver_shopping_service_order_detail_html_page($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/themes/jquery.mobile.icons.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/themes/mobile_shopping_theme_c.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_service_order_detail_page',
    '#page' => $page,
    '#styles' => $css,
    '#scripts' => $js,
  );

  print drupal_render($render);
}

//get oauth2 access_token by redirect code, and finished if scope is snsapi_base
function oauth2_get_accss_token($code) {
  
  if($code == '') {
    return null; 
  }

  $req_url = t(
    variable_get('get oauth2 access_token'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@APPSECRET' => variable_get('wechat_py_AppSecret'),
      '@CODE' => $code,
    )
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_get($req_url);
  if ($result == Null)
  {
    watchdog('mobile shopping', 'error: get user openid return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return null;
  }

  //get user list, it will return maxmum 10000 open id each time.
  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('mobile shopping', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return null;
  }
  return $json_value;

}

/**
 * End of wechat_mobile_shopping_service_order_detail_page.inc file name
 */
