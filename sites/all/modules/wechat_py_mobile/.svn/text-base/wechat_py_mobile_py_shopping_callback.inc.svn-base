<?php

//page call for ui test page
function wechat_py_mobile_py_shopping_callback(){

  $response;
  //watchdog('wechat recv message', 'got a text message from user @user: @text',
            //array('@user' => $FromUserName, '@text' =>$text));
  //watchdog('py shopping callback', 'code = @code', array('@code' => $_POST['code']));
  //watchdog('py shopping callback', 'arg <pre>@openid</pre>', array('@openid' => print_r($_POST, TRUE)));
  //watchdog('wechat_api from enable', 'token is %var', array('%var' => $record->Token), WATCHDOG_DEBUG);
  //watchdog('py shopping callback', 'code = <pre>@openid</pre>', array('@openid' => print_r($_GET, TRUE)));

  $code = isset($_GET['code']) ? $_GET['code'] : '';

  watchdog('py shopping callback', 'code = <pre>@openid</pre>', array('@openid' => print_r($_GET, TRUE)));
  switch ($code) {
    case 'url': //for jsapi signpackage
      $url = isset($_GET['name']) ? $_GET['name'] : '';
      $response = jsapi_getSignPackage($url);      
      drupal_json_output($response);
      return;
      break;

    case 'test_node_list':
      $type = $_GET['type'];
      $lastid = $_GET['lastid'];
      $sort = $_GET['sort'];
      $numbers = $_GET['numbers'];
      $send_data = get_nodes_by_all($type, $lastid, $sort, $numbers);

      $json_data = json_encode($send_data,
                               JSON_HEX_TAG |
                               JSON_HEX_APOS |
                               JSON_HEX_AMP |
                               JSON_HEX_QUOT |
                               JSON_UNESCAPED_UNICODE);

      drupal_add_http_header('Content-Type', 'application/json');
      echo $json_data;
      break;

/**
 * remove this json callback
 **/
 
 /*
    case 'wxaddr': //for test
      $url = isset($_GET['name']) ? $_GET['name'] : '';
      $response = jspai_getAddress($url);      
      drupal_json_output($response);
      return;
      break;
  */
    
    default:
      watchdog('wechat py mobile', 'ajax send unknow code @code', array('@code' => $code) , WATCHDOG_ERROR);
      break;
  }

}

function get_nodes_by_all($type, $lastid, $sort, $numbers) {
  $query = new entityfieldquery();
  if ($type == 'volume') {

    $query->entitycondition('entity_type', 'node')
    ->entitycondition('bundle', 'merchandise_input_ct')
    ->propertycondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_on_shelf', 'value', '0', '=')
    ->fieldCondition('field_product_volume', 'value', $lastid, '<')
    ->fieldOrderBy('field_product_volume', 'value', $sort)
    ->range(0,$numbers);

  } else if ($type == 'views') {

    watchdog('mobile shopping', '$lastid = <pre>@data</pre>', array('@data' => print_r($lastid, TRUE)));
    watchdog('mobile shopping', '$sort = <pre>@data</pre>', array('@data' => print_r($sort, TRUE)));
    watchdog('mobile shopping', '$numbers = <pre>@data</pre>', array('@data' => print_r($numbers, TRUE)));
    $query->entitycondition('entity_type', 'node')
    ->entitycondition('bundle', 'merchandise_input_ct')
    ->propertycondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_on_shelf', 'value', '0', '=')
    ->fieldCondition('field_product_view_count', 'value', $lastid, '<')
    ->fieldOrderBy('field_product_view_count', 'value', $sort)
    ->range(0,$numbers);

  }

  $element = array();
  global $base_url;

  //$element['total'] = total_numbers();
  $element['term_filter'] = "全部商品";
  $element['lastid'] = 0;
  $element['end'] = 0;

  $result = $query->execute();
  if (!empty($result)) {
    $nodes = node_load_multiple(array_keys($result['node']));
    $count = count($nodes);
    //watchdog('mobile shopping', 'count = <pre>@data</pre>', array('@data' => print_r($count, TRUE)));
    if ($count < $numbers || $count == 0) {
      $element['end'] = 1;
    }


    if ($count) {
      foreach($nodes as $node){
        $wnode = entity_metadata_wrapper('node', $node);

        if ($type == 'volume') {
          $order_id = $wnode->field_product_volume->value();
        } elseif ($type == 'views') {
          $order_id = $wnode->field_product_view_count->value();
        }
        $element['lastid'] = $order_id;
        //watchdog('mobile shopping', 'order_id = <pre>@data</pre>', array('@data' => print_r($order_id, TRUE)));
        //title
        //$element['data'][$order_id]['nid'] = $node->nid;
        $element['data'][$node->nid]['nid'] = $node->nid;
        $element['data'][$node->nid]['order_id'] = $order_id;

        $node_req_url = t(
          variable_get('oauth2 redirect request'),
          array(
            '@APPID' => variable_get('wechat_py_AppID'),
            '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/merchandise/' . $node->nid . "/show",
            '@SNSAPI' => "snsapi_base",
            //'@SNSAPI' => "snsapi_userinfo",
            '@STATE' => "100",
          )
        );
        $element['data'][$node->nid]['purl'] = $node_req_url;

        $element['data'][$node->nid]['pname'] = trim($node->title);
        //home page
        $img_field = $wnode->field_home_page_img->value();
        $img_url = file_create_url($img_field['uri']);
        $element['data'][$node->nid]['pimage'] = $img_url;
        $element['data'][$node->nid]['cart_plus'] = $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/imgs/cart_plus.png';
        //express free
        $express_free = $wnode->field_product_express_free->value();
        $element['data'][$node->nid]['pexp_free'] = $express_free ? null : '【包邮】';
        $element['data'][$node->nid]['pcost_price'] = $wnode->field_product_cost_price->value();
        $element['data'][$node->nid]['pshopping_price'] = $wnode->field_product_shopping_price->value();

        //points
        $score_points = $wnode->field_product_user_point_term->value();
        $element['data'][$node->nid]['pscore_points'] = $score_points ? '【积分】' : null;
        //discount
        $discount = $wnode->field_product_discount_term->value();
        $element['data'][$node->nid]['pdiscount'] = $discount ? '【促销】' : null;

      }
    }
  } else {
    $element['end'] = 1;
    $element['data'] = null;
    $element['lastid'] = $lastid;
  }

  return $element;
}
//share wechat address book
function jspai_getAddress($url) {
  if($url == '') {
    return array(); 
  }

  $library = libraries_load('wxpayapi');
  $appid = variable_get('wechat_py_AppID');
  $secret = variable_get('wechat_py_AppSecret');

  $tools = new JsApiPay($appid, $secret);
  $editAddress = $tools->GetEditAddressParameters($url);
  return $editAddress;
}

//jspai sign package
function jsapi_getSignPackage($url) {
  
  if($url == '') {
    return array(); 
  }

  $appId = variable_get('wechat_py_AppID');
  $jsapiTicket = variable_get('jsapi_ticket');
  $timestamp = time();
  $nonceStr = createNonceStr();

  // 这里参数的顺序要按照 key 值 ASCII 码升序排序
  $string = "jsapi_ticket=$jsapiTicket&noncestr=$nonceStr&timestamp=$timestamp&url=$url";

  $signature = sha1($string);

  $signPackage = array(
    "appId"     => $appId,
    "nonceStr"  => $nonceStr,
    "timestamp" => $timestamp,
    "signature" => $signature,
  );
  return $signPackage; 
}

function createNonceStr($length = 16) {
  $chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  $str = "";
  for ($i = 0; $i < $length; $i++) {
    $str .= substr($chars, mt_rand(0, strlen($chars) - 1), 1);
  }
  return $str;
}

/**
 * Convert xml object to array
 */
function shopping_xml2array($xml)
{
        $arr = array();

        foreach ($xml->children() as $r)
        {
                $t = array();
                if(count($r->children()) == 0)
                {
                        $arr[$r->getName()] = strval($r);
                }
                else
                {
                        $arr[$r->getName()][] = xml2array($r);
                }
        }
        return $arr;
}
/**
 * End of wechat_py_mobile_py_shopping_callback.inc file name
 */
