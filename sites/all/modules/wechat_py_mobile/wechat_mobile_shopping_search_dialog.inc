<?php

//page call for home page search dialog
function wechat_mobile_shopping_search_dialog(){

  global $base_url;
  $page = array();
  //check if it's a mobile browser, use touch event feature to test.
  $page['scripts'] = 
  '<script>
    function isMobile() {
      try{ document.createEvent("TouchEvent"); return true; }
      catch(e){ return false; }
    }
    if (!isMobile()) {
      window.location.replace("http://mxweixin.dreamland360.com/content/默认的404错误");
    }
  </script>';

  $code = isset($_GET['code']) ? $_GET['code'] : '';
  //watchdog('shopping term filter', 'GET = <pre>@openid</pre>', array('@openid' => print_r($_GET, TRUE)));
  $json = oauth2_get_accss_token($code);
  
  if ($json == null) {  //can't find user id return 
    $page['title'] = '商品搜索';
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  $state = $_GET['state'];
  switch ($state) {
    case '100':
      // normally open term filter page
      break;

    default:
      $page['title'] = '商品搜索';
      $page['error_info'] = '页面state: ' . $state . '错误';
      return $page;
      break;
  }

  $req_url = t(
    variable_get('js oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      //'@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/pay-test/new-tpl',
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/new-tpl',
      '@SNSAPI' => "snsapi_base",
    )
  );

  $page['home_page'] = $req_url;
  //watchdog('mobile search', '$req_url = <pre>@openid</pre>', array('@openid' => print_r($req_url, TRUE)));
  $page['title'] = '商品搜索';
  return $page;
}


function deliver_search_dialog_html_page($page) {
  global $base_url;
  //Remember change all icons from module imgs fold to default directory for save reason.

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile_search_dialog.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/md5.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_shopping_search_dialog.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_search_dialog',
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
