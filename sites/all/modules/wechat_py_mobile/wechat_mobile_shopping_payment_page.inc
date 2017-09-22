<?php

//page call for display payment page

function wechat_mobile_shopping_payment_page($key = NULL, $value = NULL) {  //for debug and test
//function wechat_mobile_shopping_payment_page() {

  global $base_url;
  $page = array();
  $page['title'] = '待付款订单';

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
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  $nid;
  $cart = 0;
  $state = $_GET['state'];
  if (preg_match('/^100/', $state)) {
    $split = preg_split('/^100/', $state); //remove 100
    $temp = preg_split('/nid/', $split[1]); //remove vocid
    $nid = $temp[1];
  } else if (preg_match('/^101/', $state)) {
    $cart = 1;
  } else {
    //nothing to do for state error
    $page['error_info'] = '支付页面state: ' . $state . '错误';
    return $page;
  }

  //get Openid by code
  $page['xyz'] = base64_encode($json->openid);    //openid should be encoded by base64
  //watchdog('mobile payment', 'openid = <pre>@data</pre>', array('@data' => print_r($json->openid, TRUE)));

  //get user rest of poinsts
  $point_query = db_select('mobile_shopping_user_points_table', 't')
         ->condition('openid', $json->openid)
         ->fields('t', array(
            'total_points',
            'curr_points',
            ));
  $result = $point_query->execute();
  $count = $result->rowCount();
  if ($count == 0) {
    $page['my_curr_points'] = 0;
  } else {
    foreach ($result as $row) {
      $page['my_curr_points'] = $row->curr_points;
    }
  }
  //watchdog('mobile payment', 'points = <pre>@data</pre>', array('@data' => print_r($page['my_curr_points'], TRUE)));


  $user_address = get_user_address($json->openid);  
  if ($user_address != null) {
    $page['js_var'] = json_encode($user_address);
    //watchdog('mobile payment', '$js_var = <pre>@data</pre>', array('@data' => print_r($page['js_var'], TRUE)));
  }

/*
//for debug and test
  $page['xyz'] = base64_encode("oOTG9tzINV6zA_1vIBgWrqRRlTl0");    //openid should be encoded by base64
  $user_address = get_user_address("oOTG9tzINV6zA_1vIBgWrqRRlTl0");  
  if ($user_address != null) {
    $page['js_var'] = json_encode($user_address);
  }
//for debug and test
*/

  if ($key == "cart") {
    $cart = 1;
  }

  if ($cart == 0) {

    //user address
    $page['nid'] = $nid;    //merchandise id
    $value = get_merchandise_id("nid", $nid);
    if ($value == null) {
      $page['title'] = '待付款订单';
      $page['error_info'] = '没有该商品，请联系我们';
      return $page;
    } else if ($value == -1) {
      $page['title'] = '待付款订单';
      $page['error_info'] = '商品已下架，请返回重新选择';
      return $page;
    }
    $page['merchandise'] = $value;
    //watchdog('mobile payment', '$page[] = <pre>@data</pre>', array('@data' => print_r($page['merchandise'], TRUE)));

  } else if ($cart == 1) {
    $page['merchandise'] = get_merchandise_id("cart", $json->openid);
    //$page['merchandise'] = get_merchandise_id("cart", "oOTG9tzINV6zA_1vIBgWrqRRlTl0");

  } else {
    $page['error_info'] = 'parameter error';
    return $page;
  }

  return $page;
}


function deliver_shopping_payment_page($page) {
  global $base_url;
  //Remember change all icons from module imgs fold to default directory for save reason.

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile_shopping_payment.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_shopping_payment.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_payment_page',
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
    watchdog('mobile merchandise', 'error code: @error and errmsg: @errmsg at @line in @filename',
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

function get_user_address($openID) {

  $query = db_select('mobile_shopping_user_address_table', 't')
         ->condition('openid', $openID)
         ->orderBy('id', 'ASC')
         ->fields('t', array(
            'id',
            'user_name',
            'user_tel',
            'city_1',
            'city_1_code',
            'city_2',
            'city_2_code',
            'city_3',
            'city_3_code',
            'detail_address',
            ));
  $result = $query->execute();
  $count = $result->rowCount();
  if ($count == 0) {
    return null;
  }

  $element = array();

  foreach ($result as $row) {
    $element[] = array (
      'id' => $row->id,
      'user_name' => $row->user_name,
      'user_tel' => $row->user_tel,
      'city_1' => $row->city_1,
      'city_1_code' => $row->city_1_code,
      'city_2' => $row->city_2,
      'city_2_code' => $row->city_2_code,
      'city_3' => $row->city_3,
      'city_3_code' => $row->city_3_code,
      'detail_address' => $row->detail_address,
    );
  }

  return $element;
}


function get_merchandise_id($type, $value) {

  $openID;
  $nid;

  $area_array = array();

  if ($type == "cart") {
    $openID = $value;
    $query = db_select('mobile_shopping_user_cart_table', 't')
           ->condition('openid', $openID)
           ->fields('t', array(
              'merchandise_id',
              'purchase_volume',
              'cart_checkin',
              ));
           
    $result = $query->execute();

    foreach ($result as $row) {
      if ($row->cart_checkin == 1 ) {
        //checkin

        //watchdog('mobile payment', 'cart node = <pre>@data</pre>', array('@data' => print_r($row, TRUE)));
        $nid = $row->merchandise_id;
        $node = node_load($nid);

        if ($node == false) {
          continue;
        }
        if ($node->type != 'merchandise_input_ct') {
          continue;
          //return null;
        }
        $wnode = entity_metadata_wrapper('node', $node);
        //上架
        $on_shelf = $wnode->field_on_shelf->value();
        if ($on_shelf == 1) { //下架
          continue; //only for shopping cart
          //return -1; //only for single merchandise
        }


        //find 平遥，太谷或其他区域
        $category_tid = $wnode->field_product_category_term->value();
        $term_area = taxonomy_get_parents($category_tid->tid);
        $key = array_keys($term_area)[0];

        $area = $term_area[$key]->name;
        if (empty($area_array[$area])) {
          $area_array[$area] = array(); //for record element
        }
        $element = array();

        $element[$nid]['parea'] = $term_area[$key]->name;
        $element[$nid]['area_key'] = $key;
        $element[$nid]['pname'] = $node->title;
        $element[$nid]['volume'] = $row->purchase_volume;
        //watchdog('mobile payment', 'volume = <pre>@data</pre>', array('@data' => print_r($row->purchase_volume, TRUE)));

        $image = $wnode->field_home_page_img->value();
        $img_url = file_create_url($image['uri']);
        $element[$nid]['purl'] = $img_url;

        $element[$nid]['pshopping_price'] = $wnode->field_product_shopping_price->value();
        $element[$nid]['pweight'] = $wnode->field_product_express_weight->value();

        $express_free = $wnode->field_product_express_free->value();
        $element[$nid]['pexp_free'] = $express_free ? 1 : 0;   //0 包邮，1 不包邮
        if ($express_free == 1 ) {
          $element[$nid]['pexp_tid'] = $wnode->field_prodct_express_term->value()->tid;
        }


        //points
        if (($field = $wnode->field_product_user_point_term->value()) !== null) {

          $termid = $field->tid;
          $query = new EntityFieldQuery();
          $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'merchandise_points_rule_ct')
            ->fieldCondition('field_points_term', 'tid', $termid);

          $result = $query->execute();
          if (!empty($result)) {
            $nodes = node_load_multiple(array_keys($result['node']));

            //watchdog('mobile payment', '$nodes = <pre>@data</pre>', array('@data' => print_r($nodes, TRUE)));
            $points_array = array();
            foreach ($nodes as $node) {
              $wr_node = entity_metadata_wrapper('node', $node);
              $end_date = $wr_node->field_score_end_date->value();
              if (time() > $end_date) {
                $points_array['valid_date'] = 0;
              } else {
                //valide score points
                $points_array['valid_date'] = 1;
                $points_array['points_max'] = $wr_node->field_points_max->value();
                $points_array['p_convert'] = $wr_node->field_points_convert_money->value();
              }
            }

            $element[$nid]['score_points'] = $points_array;

          } else {
            // find another score points rules content type
            /**
             * for example 
             *  $query->entityCondition('entity_type', 'node')
             *     ->entityCondition('bundle', 'xxxxxxxxx points_rule_ct')
             *     ->fieldCondition('field_points_term', 'tid', $termid);
             **/
          }

        }
        //discount
        if (($field = $wnode->field_product_discount_term->value()) !== null) {

          $termid = $field->tid;
          $query = new EntityFieldQuery();
          $query->entityCondition('entity_type', 'node')
            ->entityCondition('bundle', 'merchandise_discount_rule_ct')
            ->fieldCondition('field_discount_term', 'tid', $termid);

          $result = $query->execute();
          if (!empty($result)) {
            $nodes = node_load_multiple(array_keys($result['node']));

            $discount_array = array();
            foreach ($nodes as $node) {
              $wr_node = entity_metadata_wrapper('node', $node);
              $end_date = $wr_node->field_discount_end_date->value();
              if (time() > $end_date) {
                $discount_array['valid_date'] = 0;
              } else {
                //valide score points
                $discount_array['valid_date'] = 1;
                $discount_array['vip_price'] = $wr_node->field_vip_price->value();
              }
            }

            $element[$nid]['vip_discount'] = $discount_array;

          } else {
            // find another discount term content type
            /**
             * for example 
             *  $query->entityCondition('entity_type', 'node')
             *     ->entityCondition('bundle', 'merchandise_discount_rule_ct_1')
             *     ->fieldCondition('field_points_term', 'tid', $termid);
             **/
          }
        }

        $area_array[$area] = $area_array[$area] + $element;

      } //cart checkin 1
    } //foreach for cart
    //watchdog('mobile payment', 'cart array = <pre>@data</pre>', array('@data' => print_r($area_array, TRUE)));
  } else if ($type == "nid") {
    $nid = $value;
    $node = node_load($nid);

    if ($node == false) {
      return null;
    }
    if ($node->type != 'merchandise_input_ct') {
      return null;
    }
    $wnode = entity_metadata_wrapper('node', $node);
    //上架
    $on_shelf = $wnode->field_on_shelf->value();
    if ($on_shelf == 1) { //下架
      return -1;
    }


    //find 平遥，太谷或其他区域
    $category_tid = $wnode->field_product_category_term->value();
    $term_area = taxonomy_get_parents($category_tid->tid);
    $key = array_keys($term_area)[0];

    $area = $term_area[$key]->name;
    //watchdog('mobile payment', 'single node area = <pre>@data</pre>', array('@data' => print_r($area, TRUE)));
    if (empty($area_array[$area])) {
      $area_array[$area] = array(); //for record element
    }
    $element = array();

    $element[$nid]['parea'] = $term_area[$key]->name;
    $element[$nid]['area_key'] = $key;
    $element[$nid]['pname'] = $node->title;
    $element[$nid]['volume'] = 1;

    $image = $wnode->field_home_page_img->value();
    $img_url = file_create_url($image['uri']);
    $element[$nid]['purl'] = $img_url;

    $element[$nid]['pshopping_price'] = $wnode->field_product_shopping_price->value();
    $element[$nid]['pweight'] = $wnode->field_product_express_weight->value();

    $express_free = $wnode->field_product_express_free->value();
    $element[$nid]['pexp_free'] = $express_free ? 1 : 0;   //0 包邮，1 不包邮
    if ($express_free == 1 ) {
      $element[$nid]['pexp_tid'] = $wnode->field_prodct_express_term->value()->tid;
    }


    //points

    if (($field = $wnode->field_product_user_point_term->value()) !== null) {

      $termid = $field->tid;
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'merchandise_points_rule_ct')
        ->fieldCondition('field_points_term', 'tid', $termid);

      $result = $query->execute();
      if (!empty($result)) {
        $nodes = node_load_multiple(array_keys($result['node']));

        //watchdog('mobile payment', '$nodes = <pre>@data</pre>', array('@data' => print_r($nodes, TRUE)));
        $points_array = array();
        foreach ($nodes as $node) {
          $wr_node = entity_metadata_wrapper('node', $node);
          $end_date = $wr_node->field_score_end_date->value();
          if (time() > $end_date) {
            $points_array['valid_date'] = 0;
      	  watchdog('mobile payment', '$end_date = <pre>@data</pre>', array('@data' => print_r($end_date, TRUE)));
          } else {
            //valide score points
            $points_array['valid_date'] = 1;
            $points_array['points_max'] = $wr_node->field_points_max->value();
            $points_array['p_convert'] = $wr_node->field_points_convert_money->value();
      	  watchdog('mobile payment', '$wr_node = <pre>@data</pre>', array('@data' => print_r($wr_node->title->value(), TRUE)));
          }
        }

        $element[$nid]['score_points'] = $points_array;

      } else {
        // find another score points rules content type
        /**
         * for example 
         *  $query->entityCondition('entity_type', 'node')
         *     ->entityCondition('bundle', 'xxxxxxxxx points_rule_ct')
         *     ->fieldCondition('field_points_term', 'tid', $termid);
         **/
      }

    }
    //discount
    if (($field = $wnode->field_product_discount_term->value()) !== null) {

      $termid = $field->tid;
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'merchandise_discount_rule_ct')
        ->fieldCondition('field_discount_term', 'tid', $termid);

      $result = $query->execute();
      if (!empty($result)) {
        $nodes = node_load_multiple(array_keys($result['node']));

        $discount_array = array();
        foreach ($nodes as $node) {
          $wr_node = entity_metadata_wrapper('node', $node);
          $end_date = $wr_node->field_discount_end_date->value();
          if (time() > $end_date) {
            $discount_array['valid_date'] = 0;
          } else {
            //valide score points
            $discount_array['valid_date'] = 1;
            $discount_array['vip_price'] = $wr_node->field_vip_price->value();
          }
        }

        $element[$nid]['vip_discount'] = $discount_array;

      } else {
        // find another discount term content type
        /**
         * for example 
         *  $query->entityCondition('entity_type', 'node')
         *     ->entityCondition('bundle', 'merchandise_discount_rule_ct_1')
         *     ->fieldCondition('field_points_term', 'tid', $termid);
         **/
      }
    }

    $area_array[$area] = $area_array[$area] + $element;
  } //single node

  return $area_array;
}


