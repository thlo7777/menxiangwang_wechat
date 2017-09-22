<?php

//page call for shopping cart

function wechat_mobile_shopping_cart_page() {

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
    $page['title'] = '购物车';
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  $state = $_GET['state'];
  switch ($state) {
    case '100':
      // normally access from shopping home page and user id can be getted
      break;
    
    default:
      $page['title'] = '购物车';
      $page['error_info'] = '页面state: ' . $state . '错误';
      return $page;
      break;
  }


  $page['xyz'] = base64_encode($json->openid);    //openid should be encoded by base64

  $shopping_payment_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      //'@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/pay-test/payment',
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/pay/payment',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "101",     //100 is single,  101 is cart for req payment page
    )
  );
  $page['shopping_payment_url'] = $shopping_payment_url;

  $page['records'] = array();
  //watchdog('cart', 'openid = <pre>@openid</pre>', array('@openid' => print_r($json->openid, TRUE)));
  $query = db_select('mobile_shopping_user_cart_table', 't')
         ->condition('openid', $json->openid)
         ->orderBy('purchase_date', 'ASC')
         ->fields('t', array(
            'id',
            'merchandise_id',
            'purchase_volume',
            'cart_checkin',
            'purchase_date',
            ));

  $result = $query->execute();
  $count = $result->rowCount();
  if ($count > 0) {

    $items = array();
    $row_id = 0;
    foreach ($result as $key => $row) {

      $mnode = node_load($row->merchandise_id);
      if ($mnode == false ) {
        continue;
      }
      $wrapper = entity_metadata_wrapper('node', $mnode);

      $items[$row_id]['index'] = $row->id;
      $items[$row_id]['title'] = $mnode->title;
      $img_field = $wrapper->field_home_page_img->value();
      $img_url = file_create_url($img_field['uri']);
      $items[$row_id]['img_url'] = $img_url;

      $items[$row_id]['pshopping_price'] = $wrapper->field_product_shopping_price->value();
      $items[$row_id]['volume'] = $row->purchase_volume;
      $items[$row_id]['checkin'] = $row->cart_checkin;
      $row_id++;
    }

    //watchdog('cart', 'items = <pre>@openid</pre>', array('@openid' => print_r($items, TRUE)));
    $page['records'] = $items;
    //pass records to js 
    $js_var = json_encode($items);
    if ($js_var != FALSE) {
      $page['js_var'] = json_encode($items);
    }
  }

/*
  $node = node_load(425); //load 微商城用户购物车纪录 node nid=425
  $wnode = entity_metadata_wrapper('node', $node);
  $db_userid = $wnode->field_user_open_id->value();
  $db_nid = $wnode->field_merchandise_id->value();
  $db_volume = $wnode->field_purchase_volume->value();
  $db_checkin = $wnode->field_cart_checkin->value();

  $items = array();
  if (count($db_userid)) {
    foreach($db_userid as $key => $value){
      if ($openID == $value) {
        $mnode = node_load($db_nid[$key]);
        $wrapper = entity_metadata_wrapper('node', $mnode);

        $items[$key]['index'] = $key;
        $items[$key]['title'] = $mnode->title;
        $img_field = $wrapper->field_home_page_img->value();
        $img_url = file_create_url($img_field['uri']);
        $items[$key]['img_url'] = $img_url;

        $items[$key]['pshopping_price'] = $wrapper->field_product_shopping_price->value();
        $items[$key]['volume'] = $db_volume[$key];
        $items[$key]['checkin'] = $db_checkin[$key];
        //watchdog('cart', 'check = <pre>@openid</pre>', array('@openid' => print_r($db_checkin[$key], TRUE)));
      }
    }

    $page['records'] = $items;
    //pass records to js 
    $js_var = json_encode($items);
    if ($js_var != FALSE) {
      $page['js_var'] = json_encode($items);
    }

  }
*/

  $page['title'] = '购物车';
  return $page;
}


function deliver_shopping_cart_html_page($page) {
  global $base_url;
  //Remember change all icons from module imgs fold to default directory for save reason.

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile_shopping_cart.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_shopping_cart.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_cart_page',
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

