<?php

//page call for user order
function wechat_mobile_shopping_my_order_page() {

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
    $page['title'] = '我的订单';
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  $state = $_GET['state'];
  switch ($state) {
    case '100':
      // normally access from shopping home page and user id can be getted
      break;
    
    default:
      $page['title'] = '我的订单';
      $page['error_info'] = '页面state: ' . $state . '错误';
      return $page;
      break;
  }
  //get Openid by code
  $page['xyz'] = base64_encode($json->openid);    //openid should be encoded by base64
  /*$page['xyz'] = 'oOTG9t2L0J3Pw-z5e3E4dpvVnpMc';    //openid should be encoded by base64*/

  //watchdog('mobile shopping order', 'openid = <pre>@data</pre>', array('@data' => print_r($json->openid, TRUE)));
  
  $page['title'] = '我的订单';

  $query = db_select('mobile_shopping_user_order_table', 't')
    ->condition('t.openid', $json->openid)
    ->condition('t.order_state', 1, '>=')
    ->orderBy('t.time_start', 'DESC')
    ->fields('t');

  $result = $query->execute();

  $total_order = array();
  foreach ($result as $row) {
    //dpm($row);
    $total_order[$row->out_trade_no]['out_trade_no'] = $row->out_trade_no;
    $total_order[$row->out_trade_no]['order_addr'] = $row->order_addr;
    $total_order[$row->out_trade_no]['time_end'] = date('Y年m月d日 H:i',strtotime($row->time_end));

    if (!empty($total_order[$row->out_trade_no]['order_detail'])) {
      $total_order[$row->out_trade_no]['order_detail'] .= nl2br($row->order_detail);
    } else {
      $total_order[$row->out_trade_no]['order_detail'] = nl2br($row->order_detail);
    }

    if (!empty($total_order[$row->out_trade_no]['total_fee'])) {
      $total_order[$row->out_trade_no]['total_fee'] += intval($row->total_fee);
    } else {
      $total_order[$row->out_trade_no]['total_fee'] = intval($row->total_fee);
    }

    if (!empty($total_order[$row->out_trade_no]['order_exp_fee'])) {
      $total_order[$row->out_trade_no]['order_exp_fee'] += floatval($row->area_exp_fee);
    } else {
      $total_order[$row->out_trade_no]['order_exp_fee'] = floatval($row->area_exp_fee);
    }
  }
  $page['paid'] = $total_order;

//  $query = db_select('mobile_shopping_user_order_table', 't')
//         ->condition('openid', $json->openid)
//         ->fields('t', array(
//            'id',
//            'out_trade_no',
//            'order_state',
//            'time_start',
//            'time_expire',
//            'time_end',
//            'total_fee',
//            'prepay_package',
//            'order_addr',
//            ))
//         ->orderBy('id', 'DESC');
//  $result = $query->execute();
//
//  foreach ($result as $row) {
//    $element = array();
//    $element['out_trade_no'] = $row->out_trade_no;
//    $element['time_expire'] = $row->time_expire;
//    $element['prepay_package'] = $row->prepay_package;
//    $time = strtotime($row->time_end);
//    $time_end = date('Y年m月d日 H:i',$time);
//    $element['time_end'] = $time_end;
//    $element['total_fee'] = number_format(floatval($row->total_fee)/100, 2);
//    $element['order_addr'] = $row->order_addr;
//
//    $d_query = db_select('mobile_shopping_user_order_detail_table', 't')
//         ->condition('order_index', $row->id)
//         ->fields('t', array(
//            'merchandise_id',
//            'area_term_id',
//            'm_title',
//            'm_purl',
//            'm_price',
//            'm_volume',
//            'exp_fee',
//            'point_p',
//            'point',
//            'discount',
//            ));
//
//    $d_result = $d_query->execute();
//    $detail = array();
//    
//    $merchandise_price = 0.0;
//    foreach ($d_result as $item) {
//      $detail[$item->merchandise_id]['m_title'] = $item->m_title;
//      $detail[$item->merchandise_id]['m_purl'] = $item->m_purl;
//      $detail[$item->merchandise_id]['m_price'] = $item->m_price;
//      $detail[$item->merchandise_id]['m_volume'] = $item->m_volume;
//      $p1 = 0;
//      $p2 = 0;
//      $p3 = 0;
//      if (isset($item->exp_fee) || trim($item->exp_fee) !== '') {
//
//        $p1 = $item->exp_fee;
//        //$detail[$item->merchandise_id]['exp_fee'] = $item->exp_fee;
//        $detail[$item->merchandise_id]['exp_fee'] = 0; //remove item express fee   2016/06/04
//      } else {
//        $p1 = 0;
//      }
//
//      if (isset($item->point_p) || trim($item->point_p) !== '') {
//        $p2 = $item->point_p;
//        $detail[$item->merchandise_id]['point_p'] = $item->point_p;
//      } else {
//        $p2 = 0;
//      }
//
//      if (isset($item->discount) || trim($item->discount) !== '') {
//        $p3 = $item->discount;
//        $detail[$item->merchandise_id]['discount'] = $item->discount;
//      } else {
//        $p3 = 0;
//      }
//
//      //$total_p = floatval($item->m_price) * intval($item->m_volume) + floatval($p1) - floatval($p2) - floatval($p3);
//      $total_p = floatval($item->m_price) * intval($item->m_volume) - floatval($p2) - floatval($p3);
//
//      $detail[$item->merchandise_id]['total_item'] = number_format($total_p, 2);
//      $merchandise_price += $total_p;
//    }
//
//    $element['total_exp'] = number_format(floatval($element['total_fee']) - $merchandise_price, 2);
//    $element['detail'] = $detail;
//
//    if (intval($row->order_state) >= 1) {
//      $page['paid'][$row->id] = $element;
//    } else {
//      $page['unpaid'][$row->id] = $element;
//    }
//  }

  $shopping_cart_req_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/shopping-cart',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "101",
    )
  );
  $page['shopping_cart_url'] = $shopping_cart_req_url;

  if (!empty($page['paid'])) {
    //watchdog('mobile shopping', 'my order paid = <pre>@data</pre>', array('@data' => print_r($page['paid'], TRUE)));
  }

  if (!empty($page['unpaid'])) {
    //watchdog('mobile shopping', 'my order unpaid = <pre>@data</pre>', array('@data' => print_r($page['unpaid'], TRUE)));
  }
  return $page;
}

function deliver_shopping_my_order_html_page($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/themes/jquery.mobile.icons.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/themes/mobile_shopping_theme_c.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile_shopping_my_order.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_shopping_my_order.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_my_order_page',
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


