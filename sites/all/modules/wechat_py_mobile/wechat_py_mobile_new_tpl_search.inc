<?php

//page call for ui test page
function wechat_py_mobile_new_tpl_search(){

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

  //get user OPENID
  $code = isset($_GET['code']) ? $_GET['code'] : '';
  //watchdog('merchandise', 'GET = <pre>@openid</pre>', array('@openid' => print_r($_GET, TRUE)));
  $json = oauth2_get_accss_token($code);
  
  if ($json == null) {
    $page['title'] = '梦乡网微商城';
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  //watchdog('merchandise', 'user id = <pre>@openid</pre>', array('@openid' => print_r($json, TRUE)));
  $state = $_GET['state'];
  // normally open home page
  if (preg_match('/^100$/', $state)) {
    //$page['term_filter'] = "全部商品";
    $page['voc_id'] = "1";
    $page['term_id'] = "1";
    $page['last_id'] = "10000000";
  } else if (preg_match('/^101/', $state)) {
    //access from term filter dialog
    $split = preg_split('/^101/', $state); //remove 101
    $vocid = preg_split('/vocid/', $split[1]); //remove vocid
    $termid = preg_split('/termid/', $vocid[1]); //remove termid, [0] = vocid [1] = termid

    $page['voc_id'] = $termid[0];
    $page['term_id'] = $termid[1];
    $page['last_id'] = "10000000";
  } else {
    //nothing to do for state error
    $page['title'] = '梦乡网微商城';
    $page['error_info'] = '主页state: ' . $state . '错误';
    return $page;
  }

  //get Openid by code
  $page['xyz'] = base64_encode($json->openid);    //openid should be encoded by base64

/*
  $term_filter = isset($_GET['search']) ? $_GET['search'] : '';
  if ($term_filter == '') {
    $page['term_filter'] = "全部商品";
    $page['voc_id'] = "1";
    $page['term_id'] = "1";
    $page['last_id'] = "10000000";
  } else {
    $term_name = '';
    foreach ($term_filter as $term) {
      if ($term == "全部商品") {
        $term_name = $term;
        break;
      } else {
        $term_name .= $term . "》";
      }
    }
    $page['term_filter'] = $term_name;
    $page['voc_id'] = $_GET['vocid'];
    $page['term_id'] = $_GET['termid'];
    $page['last_id'] = "10000000";
  }
*/


  //广告位栏目表图片查询
  //显示分类，依照人气或者销量显示两张商品图片
  //页面底部信息
  //固定底部搜索按钮，我的订单按钮，购物车按钮，我的地址按钮
  //返回首页按钮

  //广告位栏目表图片查询
  $page['adv_container'] = home_page_adv_images();
  //watchdog('py mobile', 'adv nodes <pre>@data</pre>', array('@data' => print_r($page, TRUE)));

  //商品类目按钮，我的订单按钮，购物车按钮，我的地址按钮
  $icon_path = $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/imgs/';
  $page['button_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('button-container', 'container-inline', 'clearfix')),
  );
  $page['button_container']['search_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'term_search.png',
    '#attributes' => array('id' => array('term-search-icon'),
                           'width' => array('80%'),
                           'style' => array('margin: 0 auto;display: block;')),
  );
  $page['button_container']['category_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_mer_cat.png',
    '#attributes' => array('id' => array('category-icon'),
                           'width' => array('80%'),
                           'style' => array('margin: 0 auto;display: block;')),
  );
  $page['button_container']['order_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_my_ord.png',
    '#attributes' => array('id' => array('order-icon'),
                           'width' => array('80%'),
                           'style' => array('margin: 0 auto;display: block;')),
  );


  $page['button_container']['cart_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_sho_car.png',
    '#attributes' => array('id' => array('cart-icon'),
                           'width' => array('80%'),
                           'style' => array('margin: 0 auto;display: block;')),
  );
  $page['button_container']['cart_icon_add'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_sho_car_add.png',
    '#attributes' => array('id' => array('cart-icon-add'),
                           'width' => array('80%'),
                           'style' => array('margin: 0 auto;display: none;')),
  );

  $page['button_container']['address_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_per_cen.png',
    '#attributes' => array('id' => array('address-icon'),
                           'width' => array('80%'),
                           'style' => array('margin: 0 auto;display: block;')),
  );

  $page['commodity_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('commodity-container')),
  );

  $page['footer'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('footer-container')),
  );


  $search_req_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/search-dialog',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100",
    )
  );

  $shopping_cart_req_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/shopping-cart',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100",
    )
  );

  $my_doc_req_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/my-doc',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100",
    )
  );

  $my_order_req_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/my-order',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100",
    )
  );
  /*$my_order_req_url = $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/my-order';*/

  $page['product_cat'] = get_all_product_category();
  $page['search_url'] = $search_req_url;
  $page['cart_url'] = $shopping_cart_req_url;
  $page['my_order_url'] = $my_order_req_url;
  $page['my_doc_url'] = $my_doc_req_url;
  $page['title'] = '梦乡网微商城';

  return $page;
}

function deliver_new_tpl_search_html_page($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/swiper.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile_new_tpl.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/swiper.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/py_shopping_adv_image.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_shopping_home_page.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_py_mobile_new_tpl_search',
    '#page' => $page,
    '#styles' => $css,
    '#scripts' => $js,
  );

  print drupal_render($render);
}

//fetch adv image
function home_page_adv_images() {
  global $base_url;
  $element;
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'mobile_shopping_adv_node')
    ->fieldCondition('field_default_adv_node', 'value', '1', '=')
    ->propertyCondition('status', NODE_PUBLISHED);

  $result = $query->execute();
  if (!empty($result)) {
    $nodes = node_load_multiple(array_keys($result['node']));
    if(count($nodes)) {
      foreach($nodes as $node){
        $rnode = entity_metadata_wrapper('node', $node);
        $fc_adv_items = $rnode->field_fc_adv_items->value();
        $fc_wrapper = entity_metadata_wrapper('field_collection_item', $fc_adv_items);
        $fc_adv_image_1 = $fc_wrapper->field_first_adv_image->value();
        $img_url = file_create_url($fc_adv_image_1['uri']);

        $img1 = array(
          '#theme' => 'image',
          '#path' => $img_url,
          '#attributes' => array('id' => array('product-img'),
                                'width' => array('100%'),
                                'style' => array('margin: 0 auto;display: block;')),
        );
        $element['img1'] = array(
          '#markup' => drupal_render($img1),
          '#prefix' => '<a href="' . $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/adv-page/1" data-ajax="false">',
          '#suffix' => '</a>',
        );

        $fc_adv_image_2 = $fc_wrapper->field_second_adv_image->value();
        $img_url = file_create_url($fc_adv_image_2['uri']);
        $img2 = array(
          '#theme' => 'image',
          '#path' => $img_url,
          '#attributes' => array('id' => array('product-img'),
                                'width' => array('100%'),
                                'style' => array('margin: 0 auto;display: block;')),
        );
        $element['img2'] = array(
          '#markup' => drupal_render($img2),
          '#prefix' => '<a href="' . $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/adv-page/2" data-ajax="false">',
          '#suffix' => '</a>',
        );
        $fc_adv_image_3 = $fc_wrapper->field_third_adv_image->value();
        $img_url = file_create_url($fc_adv_image_3['uri']);
        $img3 = array(
          '#theme' => 'image',
          '#path' => $img_url,
          '#attributes' => array('id' => array('product-img'),
                                'width' => array('100%'),
                                'style' => array('margin: 0 auto;display: block;')),
        );
        $element['img3'] = array(
          '#markup' => drupal_render($img3),
          '#prefix' => '<a href="' . $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/adv-page/3" data-ajax="false">',
          '#suffix' => '</a>',
        );
      }
    }
  }

  return $element;
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

    //if 40029 happend, because browser history store last oauth2 redirect url, and contains old code. so
    //resend oauth2 redirect ulr to this page, then ok. don't forget drupal_exit :)
    if ($json_value->errcode == "40029" && preg_match('/invalid code/', $json_value->errmsg)) {
      global $base_url;
      watchdog('mobile shopping', 'redirect 40029 error in new tpl');

      $redirect_40029_req_url = t(
        variable_get('oauth2 redirect request'),
        array(
          '@APPID' => variable_get('wechat_py_AppID'),
          //'@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/pay-test/new-tpl',
          '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/new-tpl-search',
          '@SNSAPI' => "snsapi_base",
          '@STATE' => "100",
        )
      );

      drupal_goto($redirect_40029_req_url);
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

function get_all_product_category() {
    $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_vocabulary');
    
    if (!$voc) {
        return NULL;
    }

    $element = array();
    $terms = taxonomy_get_tree($voc->vid, 0, 1);
    usort($terms, "term_cmp_termid");    //sort order to ASC by termid
    foreach($terms as $delta => $term) {
        $cterms = taxonomy_get_tree($voc->vid, $term->tid, 1);
        $element[$delta] = array(
            'tid' => $term->tid,
            'name' => $term->name
        );

        if (empty($cterms)) {
            $element[$delta]['child'] = array();
        } else {
            usort($cterms, "term_cmp_termid");
            foreach ($cterms as $id => $cterm) {
                $element[$delta]['child'][$id] = array(
                    'tid' => $cterm->tid,
                    'name' => $cterm->name
                );
            }
        }
    }
    return $element;
}

function term_cmp_termid($a, $b) {
    return intval($a->tid) - intval($b->tid);
}

/**
 * End of wechat_py_mobile_new_tpl_search.inc file name
 */

