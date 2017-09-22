<?php

//page call for shopping online help video
function wechat_mobile_shopping_help_page() {

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
    $page['title'] = '商城视频帮助';
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  $state = $_GET['state'];
  switch ($state) {
    case '100':
      // normally access from shopping home page and user id can be getted
      break;
    
    default:
      $page['title'] = '商城视频帮助';
      $page['error_info'] = '页面state: ' . $state . '错误';
      return $page;
      break;
  }
  //get Openid by code
  $page['xyz'] = base64_encode($json->openid);    //openid should be encoded by base64
  /*$page['xyz'] = 'oOTG9t2L0J3Pw-z5e3E4dpvVnpMc';    //openid should be encoded by base64*/

  //watchdog('mobile shopping order', 'openid = <pre>@data</pre>', array('@data' => print_r($json->openid, TRUE)));
  
  $page['title'] = '商城视频帮助';

  $scheme = variable_get('file_default_scheme', 'public') . '://';

  $page['video'] = array (
    "梦乡网后台管理-注册登录" => array (
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_注册登录_01.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_注册登录_02.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_注册登录_03.mp4"),
    ),

    "梦乡网后台管理-商品分类" => array (
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品分类01.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品分类02.mp4"),
    ),

    "梦乡网后台管理-商品录入" => array (
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品录入14.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品录入15.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品录入16.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品录入17.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品录入18.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品录入19.mp4"),
    ),

    "梦乡网后台管理-积分规则分类" => array (
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_积分规则分类.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_商品积分录入12.mp4"),
    ),

    "梦乡网后台管理-促销规则分类" => array (
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_促销规则分类.mp4"),
    ),

    "梦乡网后台管理-广告信息管理" => array (
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_广告信息管理13.mp4"),
    ),

    "梦乡网后台管理-邮费快递分类" => array (
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_邮费快递分类.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_邮费快递录入01.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_邮费快递录入11.mp4"),
    ),

    "梦乡网后台管理-城镇文化" => array (
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_城镇文化01.mp4"),
        file_create_url($scheme . "/mxw_training_video/梦乡网后台管理_城镇文化02.mp4"),
    ),

  );

  return $page;
}

function deliver_shopping_help_html_page($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/themes/jquery.mobile.icons.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/themes/mobile_shopping_theme_c.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/video-js.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile_shopping_help.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/video.min.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_help_page',
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
 * End of wechat_mobile_shopping_my_doc_page.inc file name
 */


