<?php

//page call for display merchandise

function wechat_mobile_shopping_merchandise_show($nid){

  global $base_url;
  $page = array();
  $page['title'] = '商品';

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
  //watchdog('show', 'GET = <pre>@openid</pre>', array('@openid' => print_r($_GET, TRUE)));
  $json = oauth2_get_accss_token($code, $nid);
  
  if ($json == null) {
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  $state = $_GET['state'];
  switch ($state) {
    case '100':
      // normally access from shopping home page and user id can be getted
      break;
    
    default:
      $page['error_info'] = '页面state: ' . $state . '错误';
      return $page;
      break;
  }

  //get Openid by code
  $page['xyz'] = base64_encode($json->openid);    //openid should be encoded by base64

  $shopping_cart_req_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/shopping-cart',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100",
    )
  );
  $page['shopping_cart_url'] = $shopping_cart_req_url;

  $page['nid'] = $nid;    //merchandise id
  $node = node_load($nid);
  if ($node == false) {
    $page['title'] = '商品';
    $page['error_info'] = '没有该商品，请联系我们';
    return $page;
  }

  if ($node->type != 'merchandise_input_ct') {
    $page['title'] = '商品';
    $page['error_info'] = '没有该商品，请联系我们';
    return $page;
  }

  $wnode = entity_metadata_wrapper('node', $node);

  //上架
  $on_shelf = $wnode->field_on_shelf->value();
  if ($on_shelf == 1) { //下架
    $page['error_info'] = '商品已下架，请返回重新选择';
    return $page;
  }

  $shopping_payment_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      //'@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/pay-test/payment',
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/pay/payment',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100nid" . $nid,     //$nid for payment page
    )
  );

  $page['shopping_payment_url'] = $shopping_payment_url;

  //title
  $page['title'] = $node->title;
  $all_images = $wnode->field_product_imgs->value();
  foreach ($all_images as $id => $image) {
    $img_url = file_create_url($image['uri']);
    $page['images'][$id] = array(
      '#theme' => 'image',
      '#path' => $img_url,
      '#attributes' => array('id' => array('product-img'),
                             'width' => array('100%'),
                             'style' => array('margin: 0 auto;display: block;')),
    );
  }

  $express_free = $wnode->field_product_express_free->value();
  $page['pexp_free'] = $express_free ? '' : '【包邮】';

  //user points max
  $score_points = $wnode->field_product_user_point_term->value();
  if ($score_points) {
    $max_points = node_get_point_max($score_points->tid);
    $page['max_points'] = $max_points;
  } else {
    $page['max_points'] = 0;
  }

  if (isset($wnode->field_product_cost_price)) {
    $page['pcost_price'] =  '原价: ¥' . $wnode->field_product_cost_price->value();
  } else {
    $page['pcost_price'] = '';
  }

  if (isset($wnode->field_product_shopping_price)) {
    $page['pshopping_price'] = '¥' . $wnode->field_product_shopping_price->value();
  }

  if ($page['pcost_price'] == '' || $page['pcost_price'] == $page['pshopping_price']) {
    $page['pcost_price'] = '';
  }

  if (isset($wnode->field_product_maker)) {
    $page['maker'] = "产地: " . $wnode->field_product_maker->value();
  }

  if (isset($wnode->field_product_sku_property)) {
    $page['sku'] = "规格: " . $wnode->field_product_sku_property->value();
  }

  if (isset($wnode->field_product_express_weight)) {
    $page['weight'] = "重量: " . $wnode->field_product_express_weight->value() . "克";
  }

  if (isset($wnode->field_product_volume)) {
    $page['volume'] = "销量: " . $wnode->field_product_volume->value();
  }

  if (isset($wnode->field_product_detail)) {

    $content = $wnode->field_product_detail->value();
    if($content['format'] == 'filtered_html' || $content['format'] == 'plain_text'){
      $page['content']['#markup'] = $content['value'];
    }else if($content['format'] == 'full_html'){
      $page['content']['#markup'] = $content['safe_value'];
    }

  }

  //node comments for wechat
  $cids = comment_get_thread($node, COMMENT_MODE_THREADED, 10000);
  if (count($cids)) {
    $comments = comment_load_multiple($cids);
    foreach ($comments as $id => $cm) {
      $page['comments'][$id]['pid'] = $cm->pid;
      $page['comments'][$id]['name'] = $cm->name;
      $page['comments'][$id]['subject'] = $cm->subject;
      $page['comments'][$id]['head_image_url'] = $cm->field_comment_user_head_url['und'][0]['safe_value'];
      $page['comments'][$id]['created'] = date('Y年m月d日 H:i',$cm->created);
    }
  }


  $home_page = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/new-tpl',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100"
    )
  );
  $page['home_page'] = $home_page;
  return $page;
}


function deliver_merchandise_show_html_page($page) {
  global $base_url;
  //Remember change all icons from module imgs fold to default directory for save reason.

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/swiper.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile_merchandise_show.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/swiper.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/py_shopping_adv_image.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_merchandise_show.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_merchandise_show',
    '#page' => $page,
    '#styles' => $css,
    '#scripts' => $js,
  );

  print drupal_render($render);
}

//get oauth2 access_token by redirect code, and finished if scope is snsapi_base
function oauth2_get_accss_token($code, $nid) {
  
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
    watchdog('mobile merchandise', 'error: return null in @line line:@filename',
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

    //if 40029 happend, because browser history store last oauth2 redirect url, and contains old code. so
    //resend oauth2 redirect ulr to this page, then ok. don't forget drupal_exit :)
    if ($json_value->errcode == "40029" && preg_match('/invalid code/', $json_value->errmsg)) {
      global $base_url;

      watchdog('mobile shopping', 'redirect 40029 error in merchandise show');
      $node_40029_req_url = t(
        variable_get('oauth2 redirect request'),
        array(
          '@APPID' => variable_get('wechat_py_AppID'),
          '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/merchandise/' . $nid . "/show",
          '@SNSAPI' => "snsapi_base",
          '@STATE' => "100",
        )
      );

      drupal_goto($node_40029_req_url);
      drupal_exit();
    } else {
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
  }

  return $json_value;

}

function node_get_point_max($tid) {

  $termid = $tid;
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'merchandise_points_rule_ct')
    ->fieldCondition('field_points_term', 'tid', $termid);

  $result = $query->execute();
  if (!empty($result)) {
    $nodes = node_load_multiple(array_keys($result['node']));

    //watchdog('mobile payment', '$nodes = <pre>@data</pre>', array('@data' => print_r($nodes, TRUE)));
    foreach ($nodes as $node) {
      $wr_node = entity_metadata_wrapper('node', $node);
      return $wr_node->field_points_max->value();
    }
  }

}

