<?php

//page call for delivery json data with mobile client
function wechat_mobile_shopping_data_api() {

  $raw_data = file_get_contents("php://input"); //get xml data
  $data = drupal_json_decode($raw_data);
  //watchdog('mobile shopping', 'raw code = <pre>@data</pre>', array('@data' => print_r($_GET, TRUE)));
  //watchdog('mobile shopping', 'json data = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));

  $send_data = null;


  if ($data['ajax'] == 'mobile_set_article_views_obj') {
    $send_data= set_article_views($data);
  }

  if ($data['ajax'] == 'mobile_get_article_info_obj') {
    $send_data= get_article_info($data);
  }

  if ($data['ajax'] == 'shopping_get_self_qr_scan_image_obj') {
    $send_data= get_self_qr_scan_image($data);
  }
  
  if ($data['ajax'] == 'shopping_save_user_comment') {
    $send_data= save_user_comment($data);
  }

  if ($data['ajax'] == 'shopping_validate_comment_access') {
    $send_data= validation_comment_access($data);
  }

  if ($data['ajax'] == 'shopping_unfiedorder_data_obj') {
    $send_data= pay_unified_order($data);
  }

  if ($data['ajax'] == 'shopping_get_express_obj') {
    $send_data= get_express_template($data);
  }

  if ($data['ajax'] == 'shopping_merchandise_view_obj') {
    $send_data= add_views_merchandise($data);
  }

  if ($data['ajax'] == 'shopping_remove_address_obj') {
    $send_data= remove_user_addr($data);
  }

  if ($data['ajax'] == 'shopping_save_addr_obj') {
    $send_data= save_user_addr($data);
  }

  if ($data['ajax'] == 'shopping_user_address_obj') {
    $send_data= get_user_addr($data);
  }

  if ($data['ajax'] == 'shopping_address_city_obj') {
    $send_data= get_city($data);
  }

  if ($data['ajax'] == 'shopping_get_cart_count_obj') {
    $send_data= get_cart_count($data);
  }

  if ($data['ajax'] == 'shopping_add_cart_obj') {
    $send_data = add_cart_to_purchase_record_table($data);
  }

  if ($data['ajax'] == 'shopping_update_cart_obj') {
    $send_data= update_cart_record_table($data);
  }

  if ($data['ajax'] == 'shopping_smc_obj') {
    $send_data = node_list($data);
  }

  if ($data['ajax'] == 'shopping_term_obj') {

    $send_data = get_term_list($data);
  }

  if ($data['ajax'] == 'shopping_service_area') {

    $send_data = get_all_service_area($data);
  }

  drupal_add_http_header('Content-Type', 'application/json');

  $json_data;
  if (!empty($send_data['uo_return'])) {
    $json_data = $send_data['uo_return'];
  } else {
    $json_data = json_encode($send_data,
                             JSON_HEX_TAG |
                             JSON_HEX_APOS |
                             JSON_HEX_AMP |
                             JSON_HEX_QUOT |
                             JSON_UNESCAPED_UNICODE);
  }

  echo $json_data;

}

/**
 * set article node views + 1
 **/
function set_article_views($data) {
  watchdog('mobile shopping', 'set_article_views = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  $nid = $data['info'];

  $node = node_load($nid);
  if ($node) {
    $wnode = entity_metadata_wrapper('node', $node);
    $views = $wnode->field_product_view_count->value();
    if ($views == null) {
      $views = 0;
    }
    $wnode->field_product_view_count->set($views + 1);
    $wnode->save();
  }

  return null;
}

/**
 * get all city culture articles information
 **/
function get_article_info($data) {
  //watchdog('mobile shopping', 'get_article_info = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  $element = array();

  $info = $data['info'];

  $query = new EntityFieldQuery();
  //search nodes by term
  if ($info['type'] == 'term') {

    $field_term = 'field_area_term_' . $info['area'];
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', $info['ct'])
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('changed', $info['time'], '<')
      ->propertyOrderBy('changed', 'DESC')
      ->fieldCondition($field_term, 'tid', $info['para'])
      ->range(0, $info['range']);
  } //search nodes by term

  //search all nodes
  if ($info['type'] == 'all') {
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', $info['ct'])
      ->propertyCondition('status', NODE_PUBLISHED)
      ->propertyCondition('changed', $info['time'], '<')
      ->propertyOrderBy('changed', 'DESC')
      ->range(0, $info['range']);
  } // type is all search

  $result = $query->execute();
  if (!empty($result)) {
    $nodes = node_load_multiple(array_keys($result['node']));
    if(count($nodes)) {
      foreach($nodes as $node){
        $wnode = entity_metadata_wrapper('node', $node);
        $element[$node->nid]['info_head'] = $wnode->title->value();
        $element[$node->nid]['info_time'] = $node->changed;

        $views = $wnode->field_product_view_count->value();
        if ($views == null) {
          $element[$node->nid]['info_views'] = 0;
        } else {
          $element[$node->nid]['info_views'] = $views;
        }

        $link_or_content = $wnode->field_nei_rong_huo_lian_jie->value();
        $element[$node->nid]['link_or_article'] = $link_or_content;

        $article_image = $wnode->field_article_image->value();
        if ($article_image != null) {
          $element[$node->nid]['info_image'] = file_create_url($article_image['uri']);
        } else {
          if ($link_or_content == '0') {
            $article = $wnode->field_article_content->value();
            //$text = strip_tags($article['value']);
            // Strip HTML Tags
            $clear = strip_tags($article['value']);
            // Clean up things like &amp;
            $clear = html_entity_decode($clear);
            // Strip out any url-encoded stuff
            $clear = urldecode($clear);
            // Replace non-AlNum characters with space
            //$clear = preg_replace('/[^A-Za-z0-9]/', ' ', $clear);
            // Replace Multiple spaces with single space
            $clear = preg_replace('/ +/', ' ', $clear);
            // Trim the string of leading/trailing space
            $clear = trim_all($clear);
            //watchdog('mobile shopping', 'text = <pre>@data</pre>', array('@data' => print_r($clear, TRUE)));
            $element[$node->nid]['article'] = truncate_utf8($clear, 60, TRUE, FALSE);
          }
        }

        if ($link_or_content == '1') {
          $element[$node->nid]['link'] = $wnode->field_article_link->value();
        }
      }
    }
  } else {
    //search end
    $element['last_row'] = 1;
  }


  return $element;
}

function trim_all( $str , $what = NULL , $with = ' ' )
{
    if( $what === NULL )
    {
        //  Character      Decimal      Use
        //  "\0"            0           Null Character
        //  "\t"            9           Tab
        //  "\n"           10           New line
        //  "\x0B"         11           Vertical Tab
        //  "\r"           13           New Line in Mac
        //  " "            32           Space
       
        $what   = "\\x00-\\x20";    //all white-spaces and control chars
    }
   
    return trim( preg_replace( "/[".$what."]+/" , $with , $str ) , $what );
}

/**
 * detect if qr scan image is ready
 **/
function get_self_qr_scan_image($data) {
  //watchdog('mobile shopping', 'get_self_qr_scan_image = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  $url = $data['file_url'];

  if (preg_match('/point_qrscan_image/', $url)) {
    $split = preg_split('/point_qrscan_image/', $url); //remove domain uri

    $scheme = variable_get('file_default_scheme', 'public') . '://';
    $file_name = $scheme . "point_qrscan_image" . $split[1]; 

    if (file_exists($file_name)) {
      return 1;
    } else {
      return 0;
    }
  } else {
    return 0;
  }

}

/**
 * save user comment
 **/
function save_user_comment($data) {
  //watchdog('mobile shopping', 'save_user_comment = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  $openID = base64_decode($data['xyz']);
  $nid = $data['nid'];
  $comment_text = $data['comment'];


  $nick_name = '';
  $head_img_url = '';
  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  $result = wechat_api_get_user_info($openID);

  if($result == ''){  //can't get user head and nick name

    $nick_name = '匿名用户';
    $head_img_url = '';
  }else{
    $head_img_url = $result->headimgurl;
    $nick_name = $result->nickname;
  }

  $comment = new stdClass();
  $comment->nid = $nid; // nid of a node you want to attach a comment to
  $comment->cid = 0; // leave it as is
  $comment->pid = 0; // parent comment id, 0 if none
  $comment->uid = 0; // user's id should = 0, from wechat as anonymous user
  $comment->mail = ''; // user's email
  $comment->name = $nick_name; // If user is authenticated you can omit this field, it will be auto-populated, if the user is anonymous and you want to name him somehow, input his name here
  $comment->thread = ''; // OPTIONAL. If you need comments to be threaded you can fill this value. Otherwise omit it.
  $comment->hostname = ''; // OPTIONAL. You can log poster's ip here
  $comment->created = time(); // OPTIONAL. You can set any time you want here. Useful for backdated comments creation.
  $comment->is_anonymous = 0; // leave it as is
  $comment->homepage = ''; // you can add homepage URL here
  $comment->status = COMMENT_PUBLISHED; // We auto-publish this comment
  $comment->language = LANGUAGE_NONE; // The same as for a node
  $comment->field_comment_user_head_url['und'][0]['value'] = $head_img_url;
  $comment->subject = $comment_text;
  comment_submit($comment); // saving a comment
  comment_save($comment);

  $element['nick_name'] = $nick_name;
  $element['head_img_url'] = $head_img_url;
  $element['time'] = date('Y年m月d日 H:i', time());

  return $element;
}

/**
 * check user if has authority to add comment
 **/
function validation_comment_access($data) {
  $openID = base64_decode($data['xyz']);
  $nid = $data['nid'];

  //watchdog('mobile shopping', 'shopping_validate_comment_access = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  $element = array();

  $query = db_select('mobile_shopping_user_order_table', 't')
         ->condition('openid', $openID)
         ->fields('t', array('id'));
  $result = $query->execute();

  foreach ($result as $row) {
    $m_query = db_select('mobile_shopping_user_order_detail_table', 't')
         ->condition('order_index', $row->id)
         ->condition('merchandise_id', $nid)
         ->fields('t', array(
            'merchandise_id',
            ));
    $m_result = $m_query->execute();
    $count = $m_result->rowCount();

    if ($count > 0) {
      $element['state'] = "1";  //OK
      return $element;
    }

  }


  $element['state'] = "0";  //NO
  return $element;
}

/**
 * pay unified order create
 **/
function pay_unified_order($data) {
  //watchdog('mobile shopping', 'unfiedorder_obj = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));

  $exp_array = $data['area_exp_fee'];

  $attach_order_split = count($exp_array) . '-'; //caculate order number. Depends area number

  /**
   * list order split format: 
   * xxxx-key1-key2- ...
   * xxxx = splited orders number
   * key1 = area key1
   * key2 = area key2, ....
   **/
  foreach ($exp_array as $area_exp) {
    foreach ($area_exp as $key => $exp_fee) {
      $attach_order_split .= $key;
    }
    $attach_order_split .= '-';
  }
  $attach_order_split = rtrim($attach_order_split, "-");
  //watchdog('mobile shopping', 'attach_order_split = <pre>@data</pre>', array('@data' => print_r($attach_order_split, TRUE)));

  $openID = base64_decode($data['xyz']);

  $unpay_order = $data;
  
  $element = array();

  $library = libraries_load('wxpayapi');
  $input = new WxPayUnifiedOrder();
  $input->SetBody("梦乡网商品订单");
  //$input->SetBody("梦乡网开发测试订单");
  //$input->SetDetail($detail);
  $input->SetAttach($attach_order_split);   //split order information
  $nonceStr = createNonceStr();
  $trade_no = "D" . date("YmdHis-") . $nonceStr;
  $unpay_order['out_trade_no'] = $trade_no;
  $input->SetOut_trade_no($trade_no);
  $total_fee = intval(floatval($data['all_pay']) * 100);
  $input->SetTotal_fee($total_fee);
  //watchdog('mobile shopping', 'SetTotal_fee <pre>@data</pre>', array('@data' => print_r($data['all_pay'], TRUE)));
  //$input->SetTotal_fee("1");
  $order_ts = date("YmdHis");
  $order_tex = date("YmdHis", time() + 10*60*60);    //10 hours valid time
  $unpay_order['time_start'] = $order_ts;
  $unpay_order['time_expire'] = $order_tex;
  $input->SetTime_start($order_ts);
  $input->SetTime_expire($order_tex);
  //$input->SetGoods_tag("test");

  $input->SetTrade_type("JSAPI");
  $input->SetOpenid($openID);
  $unpay_order['openid'] = $openID;

  //test background for split order
  //background_process_start('test_background_process_order', $unpay_order);


  $order = WxPayApi::unifiedOrder($input, 30);

  //watchdog('mobile shopping', 'order <pre>@data</pre>', array('@data' => print_r($order, TRUE)));
  if ($order['return_code'] != "SUCCESS") {
    $element['return_code'] = $order['return_code'];
    $element['return_msg'] = $order['return_msg'];
    return $element;
  }

  if ($order['result_code'] != "SUCCESS") {
    $element['err_code'] = $order['err_code'];
    $element['err_code_des'] = $order['err_code_des'];
    return $element;
  }

  $tools = new JsApiPay();
  $jsApiParameters = $tools->GetJsApiParameters($order);

  //watchdog('mobile shopping', 'jsApiParameters <pre>@data</pre>', array('@data' => print_r($jsApiParameters, TRUE)));

  $unpay_order['prepay_package'] = $jsApiParameters;
  //call background_process_order from module file, pass detail and prepayid
  background_process_start('background_process_order', $unpay_order);

  //send jsApiParameters to device
  $element['uo_return'] = $jsApiParameters;
  return $element;
}

//create rand 16 length string for out trade number
function createNonceStr($length = 16) {
  $chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  $str = "";
  for ($i = 0; $i < $length; $i++) {
    $str .= substr($chars, mt_rand(0, strlen($chars) - 1), 1);
  }
  return $str;
}

function get_express_template($data) {

  $express_cache_list = &drupal_static(__FUNCTION__);
  if (!isset($express_cache_list)) {
    if ($cache = cache_get('mobile_shopping_express_template_cache')) {
      $express_cache_list = $cache->data;
    } else {
      //function create set_express_cache_list
      //return express_cache_list
      $express_cache_list = set_express_cache_list();
      // Do your expensive calculations here, and populate $my_data
      // with the correct stuff..
      //then set to cache
      //watchdog('mobile shopping', 'set express_cache_list = <pre>@data</pre>', array('@data' => print_r($express_cache_list, TRUE)));
      cache_set('mobile_shopping_express_template_cache', $express_cache_list);
    }
  }

  //watchdog('mobile shopping', 'get_express_template = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  //watchdog('mobile shopping', 'get express_cache = <pre>@data</pre>', array('@data' => print_r($express_cache_list, TRUE)));

  $term = taxonomy_term_load($data['term']['city_1_code']);
  $dc = $term->field_division_category['und'][0]['value'];
  $city_1_code = array('tid' => $term->tid, 'division' => $dc);

  $term = taxonomy_term_load($data['term']['city_2_code']);
  $dc = $term->field_division_category['und'][0]['value'];
  $city_2_code = array('tid' => $term->tid, 'division' => $dc);

  $term = taxonomy_term_load($data['term']['city_3_code']);
  $dc = $term->field_division_category['und'][0]['value'];
  $city_3_code = array('tid' => $term->tid, 'division' => $dc);

  $term = array();
  foreach ($data['term'] as $key => $value) {
    if ($key != "city_1_code" && $key != "city_2_code" && $key != "city_3_code") {
      $term[$key] = $value;
    }
  }

  $element = array();
  //find express_template
  foreach ($term as $key => $tid) {
    if (!empty($express_cache_list[$tid])) {
      $exp_item_list = $express_cache_list[$tid];
      //watchdog('mobile shopping', 'exp_item_list = <pre>@data</pre>', array('@data' => print_r($exp_item_list, TRUE)));

      foreach ($exp_item_list as $termid => $item) {
        //city 1 level
        if ($termid == $city_1_code['tid']) {
          //处理圆通或其他快递模版
          if (!empty($exp_item_list[$city_1_code['tid']][0])) {  //省或直辖市 w_region = 0
            $element[$key] = $exp_item_list[$city_1_code['tid']][0];
            break ;
          }  
          //处理宅急送快递模版
          if (!empty($exp_item_list[$city_1_code['tid']][1])) { //重要城市 w_region = 1
            
            //watchdog('mobile shopping', 'city 1 = <pre>@data</pre>', array('@data' => print_r($city_1_code['tid'], TRUE)));
            //直辖市市区处理
            if ($city_1_code['tid'] == $city_2_code['tid']) {
              if ($city_3_code['division'] == 4) {  //直辖市市区
                $element[$key] = $exp_item_list[$city_1_code['tid']][1];
                break;
              }

              if ($city_3_code['division'] == 3) {  //直辖市郊县
                $element[$key] = $exp_item_list[$city_1_code['tid']][2];
                break;
              }

            }

            //山西省其他地市，除晋中。晋中单独处理  //有可能以后坐表格，还有其他地区如晋中，太谷等做单独处理，
            //因为快递从这些地区走。
            if ($city_1_code['tid'] == "1722") {
              if ($city_2_code['tid'] != "1770") {
                $element[$key] = $exp_item_list[$city_1_code['tid']][1];
                break;
              }
            }

          } else if (!empty($exp_item_list[$city_1_code['tid']][2])) { //地级城市 w_region = 2

            //直辖市郊县
            if ($city_1_code['tid'] == $city_2_code['tid']) {
              if ($city_3_code['division'] == 3) {  //直辖市郊县
                $element[$key] = $exp_item_list[$city_1_code['tid']][2];
                break;
              }
            } 

            if ($city_2_code['division'] == 3 && $city_3_code['division'] == 4) {  //各省地级市
              $element[$key] = $exp_item_list[$city_1_code['tid']][2];
              break;
            }

            if ($city_3_code['division'] == 5 || $city_3_code['division'] == 6) {  //各省县和县级市
              $element[$key] = $exp_item_list[$city_1_code['tid']][3];
              break;
            }

          } else if (!empty($exp_item_list[$city_1_code['tid']][3])) { //县级城市 w_region = 3
            //各省县级城市
            if ($city_3_code['division'] == 5 || $city_3_code['division'] == 6) {  //各省县和县级市
              $element[$key] = $exp_item_list[$city_1_code['tid']][3];
              break;
            }
          }
        }

        //处理宅急送快递模版
        //city 2 level
        if ($termid == $city_2_code['tid']) {
          //重要城市中不处理直辖市,不处理县和县级市,只处理市区
          if ($city_1_code['tid'] != $city_2_code['tid'] && $city_3_code['division'] == 4) {
            $element[$key] = $exp_item_list[$city_2_code['tid']][1];
            break;
          }

          //山西省其他地市，除晋中。晋中单独处理  //有可能以后坐表格，还有其他地区如晋中，太谷等做单独处理，
          //因为快递从这些地区走。
          if ($city_1_code['tid'] == "1722") {
            if ($city_2_code['tid'] == "1770") {
              $element[$key] = $exp_item_list[$city_2_code['tid']][1];
              break;
            }
          }
        }


      }
    }
    // code...
  }

  //watchdog('mobile shopping', 'return data = <pre>@data</pre>', array('@data' => print_r($element, TRUE)));
  return $element;
}

//set all express template price into cache
function set_express_cache_list() {
  $exp_list = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'express_template_ct');

  $result = $query->execute();
  if (!empty($result)) {
    $nodes = node_load_multiple(array_keys($result['node']));
    foreach($nodes as $node) {
      $wnode = entity_metadata_wrapper('node', $node);
      $fc_explist = $wnode->field_fc_express_price_list->value();
      $exp_tid = $wnode->field_express_template_term->value();

      foreach ($fc_explist as $item) {
        $temp_array = array();

        $fc_item_wrapper = entity_metadata_wrapper('field_collection_item', $item);
        $area = $fc_item_wrapper->field_division_term->value();
        $w_region = $fc_item_wrapper->field_which_region->value();

        if ($area === null) {
          continue;
        }

        $temp_array['tid'] = $area->tid;
        $temp_array['name'] = $area->name;
        $temp_array['w_region'] = $w_region;

        $init_weight = $fc_item_wrapper->field_init_weight->value();
        $init_weight_price = $fc_item_wrapper->field_init_weight_price->value();
        $step_weight = $fc_item_wrapper->field_step_weight->value();
        $step_weight_price = $fc_item_wrapper->field_step_weight_price->value();
        $temp_array['init_weight']       = $init_weight;
        $temp_array['init_weight_price'] = $init_weight_price;
        $temp_array['step_weight']       = $step_weight;
        $temp_array['step_weight_price'] = $step_weight_price;

        $weight_condition = $fc_item_wrapper->field_weight_section_condition->value();
        if ($weight_condition == 1) {
          $fc_temp = $fc_item_wrapper->field_fc_weight_section_unit->value();
          foreach ($fc_temp as $owc_value) {
            $fc_owc_wrapper = entity_metadata_wrapper('field_collection_item', $owc_value);
            $temp_array['over_wc'][$owc_value->item_id]['owc'] = $fc_owc_wrapper->field_over_wight_section->value();
            $temp_array['over_wc'][$owc_value->item_id]['owc_price'] = $fc_owc_wrapper->field_over_wight_section_price->value();
            //$temp_array['over_wc'][]['owc'] = $fc_owc_wrapper->field_over_wight_section->value();
            //$temp_array['over_wc'][]['owc_price'] = $fc_owc_wrapper->field_over_wight_section_price->value();

          }
        }

        $exp_list[$exp_tid->tid][$area->tid][$w_region] = $temp_array; 
      }


    }
  }
  return $exp_list;
}

function add_views_merchandise($data) {
  $nid = $data['nid'];

  $node = node_load($nid); //load 微商城用户购物车纪录 node nid=425
  $wnode = entity_metadata_wrapper('node', $node);
  $views = $wnode->field_product_view_count->value();
  $wnode->field_product_view_count->set($views + 1);
  $wnode->save();

  return null;
}

function remove_user_addr($data) {
  //watchdog('mobile shopping', 'remove user addr = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));

  db_delete('mobile_shopping_user_address_table')
    ->condition('id', $data['addr']['id'])
    ->execute();
  return null;
}

function save_user_addr($data) {
  //watchdog('mobile shopping', 'save user addr = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));

  $openID = base64_decode($data['xyz']);
  $index = db_insert('mobile_shopping_user_address_table')
    ->fields(array(
      'openid' => $openID,
      'user_name' => $data['save_addr']['user_name'],
      'user_tel' => $data['save_addr']['user_tel'],
      'city_1' => $data['save_addr']['city_1'],
      'city_1_code' => $data['save_addr']['city_1_code'],
      'city_2' => $data['save_addr']['city_2'],
      'city_2_code' => $data['save_addr']['city_2_code'],
      'city_3' => $data['save_addr']['city_3'],
      'city_3_code' => $data['save_addr']['city_3_code'],
      'detail_address' => $data['save_addr']['detail_address'],
    ))->execute();

  $element = array('index' => $index);
  return $element;
}

function get_user_addr($data) {
  //watchdog('mobile shopping', 'save user addr = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  $openID = base64_decode($data['xyz']);

  $query = db_select('mobile_shopping_user_address_table', 't')
         ->condition('openid', $openID)
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

function get_city($data) {
  //watchdog('mobile shopping', 'get city_1 = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));

  $voc = taxonomy_vocabulary_machine_name_load('china_administrative_divisions_taxonomy');
  $term_array = array();

  $terms = taxonomy_get_tree($voc->vid, $data['term'], 1);
  foreach ($terms as $key) {
    $term = taxonomy_term_load($key->tid);
    $term_array[] = array (
      'tid' => $term->tid,
      'name' => $term->name,
    );
  }
  
  $element['xyz'] = $data['xyz'];
  $element['level'] = $data['level'];
  $element['term'] = $term_array;
  return $element;
}

function get_cart_count($data) {
  //watchdog('mobile shopping', 'cart count = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  /*
  $node = node_load(425); //load 微商城用户购物车纪录 node nid=425
  $wnode = entity_metadata_wrapper('node', $node);
  $count = count($wnode->field_user_open_id->value());
  */

  $openID = base64_decode($data['xyz']);

  $query = db_select('mobile_shopping_user_cart_table', 't')
         ->condition('openid', $openID)
         ->fields('t');
         
  $result = $query->execute();
  $count = $result->rowCount();

  return $count ? $count: 0;
}


function update_cart_record_table($data) {
  //watchdog('mobile shopping', 'cart update data = <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  $openID = base64_decode($data['xyz']);

  $cart_update = $data['data'];

  foreach ($cart_update as $row) {
    if ($row['checkin'] == 2) {

      db_delete('mobile_shopping_user_cart_table')
        ->condition('id', $row['key'])
        ->execute();

    } else {

      db_update('mobile_shopping_user_cart_table')
        ->condition('id', $row['key'])
        ->fields(array(
          'purchase_volume' => $row['volume'],
          'cart_checkin' => $row['checkin'],
          'purchase_date' => time(),
        ))
        ->execute();
    }
  }

/*
  $node = node_load(425); //load 微商城用户购物车纪录 node nid=425
  $wnode = entity_metadata_wrapper('node', $node);

  $cart_update = $data['data'];
  $db_uid = $wnode->field_user_open_id->value();

  foreach ($db_uid as $key => $value) {
    if ($value == $openID && $cart_update[$key]['key'] == $key) {
      if ($cart_update[$key]['checkin'] == 2) {
        //remove row
        $wnode->field_user_open_id[$key]->set(NULL);
        $wnode->field_merchandise_id[$key]->set(NULL);
        $wnode->field_purchase_volume[$key]->set(NULL);
        $wnode->field_cart_checkin[$key]->set(NULL);
        $wnode->field_purchase_date[$key]->set(NULL);
      } else {
        $wnode->field_purchase_volume[$key] = $cart_update[$key]['volume'];
        $wnode->field_cart_checkin[$key] = $cart_update[$key]['checkin'];
        $time = date("YmdHis", time());
        $wnode->field_purchase_date[$key] = $time;
      }

    }
  }

  $wnode->save();
*/

  return null;
}

function add_cart_to_purchase_record_table($data) {

  $element = array();

  //should use base64 decode for openid
  $openID = base64_decode($data['xyz']);
  $nid = $data['nid'];

  //find records, insert new records if can't find
  $query = db_select('mobile_shopping_user_cart_table', 't')
         ->condition('openid', $openID)
         ->condition('merchandise_id', $nid)
         ->fields('t', array(
            'id',
            'purchase_volume',
            'cart_checkin',
            'purchase_date',
            ));

  $result = $query->execute();
  $count = $result->rowCount();
  if ($count > 0) {
    foreach ($result as $row) {
      db_update('mobile_shopping_user_cart_table')
        ->condition('id', $row->id)
        ->fields(array(
          'purchase_volume' => $row->purchase_volume + 1,
          'cart_checkin' => $row->cart_checkin,
          'purchase_date' => time(),
        ))
        ->execute();

    }
    //update
  } else {
    //insert new record
    db_insert('mobile_shopping_user_cart_table')
      ->fields(array(
        'openid' => $openID,
        'merchandise_id' => $nid,
        'purchase_volume' => 1,
        'cart_checkin' => 1,
        'purchase_date' => time(),
      ))->execute();
  }

/*
  $node = node_load(425); //load 微商城用户购物车纪录 node nid=425
  $wnode = entity_metadata_wrapper('node', $node);

  $db_nid = $wnode->field_merchandise_id->value();
  $db_uid = $wnode->field_user_open_id->value();
  $index = -1;
  foreach ($db_nid as $key => $value) {
    if ($value == $nid && $openID == $db_uid[$key]) {
      $index = $key;
      break;
    }
  }

  if ($index == -1) {

    $wnode->field_user_open_id[] = $openID;
    $wnode->field_merchandise_id[] = $nid;
    $wnode->field_purchase_volume[] = 1;
    $wnode->field_cart_checkin[] = "1";
    $time = date("YmdHis", time());
    $wnode->field_purchase_date[] = $time;

  } else {

    $db_volume = $wnode->field_purchase_volume->value();
    $wnode->field_purchase_volume[$index] = $db_volume[$index] + 1;
    $wnode->field_cart_checkin[$index] = "1";
    $time = date("YmdHis", time());
    $wnode->field_purchase_date[$index] = $time;
  }

  $wnode->save();
  */

  $element['state'] = "0";  //OK
  return $element;

}


function get_term_list($data) {
  //get merchandise term vocbulary
  $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_vocabulary');
  $term_array = array();
  $terms = taxonomy_get_tree($voc->vid, 0, 1);
  foreach ($terms as $term) {
    $term_array[$term->tid] = array(
       'name' => $term->name,
    );
    get_term($voc->vid, $term->tid, $term_array);
  }

  $element['m_term'] = $term_array;

  //get merchandise points term vocbulary
  $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_points_vocabulary');
  $term_array = array();
  $terms = taxonomy_get_tree($voc->vid, 0, 1);
  foreach ($terms as $term) {
    $term_array[$term->tid] = array(
       'name' => $term->name,
    );
    get_term($voc->vid, $term->tid, $term_array);
  }
  $element['p_term'] = $term_array;

  //get merchandise discount term vocbulary
  $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchantdise_discount_vocabulary');
  $term_array = array();
  $terms = taxonomy_get_tree($voc->vid, 0, 1);
  foreach ($terms as $term) {
    $term_array[$term->tid] = array(
       'name' => $term->name,
    );
    get_term($voc->vid, $term->tid, $term_array);
  }
  $element['d_term'] = $term_array;

  return $element;
}

function get_term($vid, $ptid, &$element){

  $terms = taxonomy_get_tree($vid, $ptid, 1);

  if (count((array)$terms)) {
    foreach ($terms as $term) {
      $element[$ptid]['children'][$term->tid] = array(
         'name' => $term->name,
      );
      get_term($vid, $term->tid, $element[$ptid]['children']);
    }
  }
}

function node_list($data) {

  $type = $data['type'];
  $sort = $data['sort'];
  $lastid = $data['lastid'];
  $numbers = $data['numbers'];
  $term = $data['term'];
  $vocid = $data['vocid'];
  $termid = $data['termid'];
  $nids = $data['nids'];

  switch ($type) {
    case 'volume':
      //if ($term == "all") {
      if ($vocid == $termid && $vocid == 1) {

        $element = get_nodes_by_all($type, $lastid, $nids, $sort, $numbers);

      //} elseif ($term == "term") {
      } else {
        $element = get_nodes_by_termid($vocid, $termid, $type, $lastid, $nids, $sort, $numbers);
      }

      break;
    case 'views':
      //if ($term == "all") {
      if ($vocid == $termid && $vocid == 1) {

        $element = get_nodes_by_all($type, $lastid, $nids, $sort, $numbers);

      //} elseif ($term == "term") {
      } else {
        $element = get_nodes_by_termid($vocid, $termid, $type, $lastid, $nids, $sort, $numbers);
      }
      break;

    default:
      // code...
      break;
  }

  return $element;
}

function get_nodes_by_termid($vocid, $termid, $type, $lastid, $nids, $sort, $numbers) {
  $element = array();
  $voc;
  switch ($vocid) {
    case '2':
      $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_vocabulary');
      $element['term_filter'] = "商品分类";
      break;
    case '3':
      $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_points_vocabulary');
      $element['term_filter'] = "积分商品";
      break;
    case '4':
      $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchantdise_discount_vocabulary');
      $element['term_filter'] = "促销商品";
      break;
    
    default:
      // code...
      break;
  }

  $term_array = array();
  if ($termid == 1 || $termid == $vocid) {
    $all_terms = taxonomy_get_tree($voc->vid);
    $element['term_filter'] = $element['term_filter'] . ">全部";
    foreach ($all_terms as $term) {
      $term_array[] = $term->tid;
    }
    if (empty($all_terms)) {
      return null;
    }
  } else {
    $all_terms = taxonomy_get_children($termid, $voc->vid);

    //watchdog('mobile shopping', 'all_terms = <pre>@data</pre>', array('@data' => print_r($all_terms, TRUE)));
    if (empty($all_terms)) {
      $term_parent = taxonomy_get_parents($termid);
      $term_parent_name = '';
      if (!empty($term_parent)) {
        $key = array_keys($term_parent)[0];
        $term_parent_name = $term_parent[$key]->name;
      }

      $term_child = taxonomy_term_load($termid);
      $element['term_filter'] = $element['term_filter'] . ">" . $term_parent_name . ">" . $term_child->name;
      $term_array[] = $termid;
    } else {

      $term_child = taxonomy_term_load($termid);
      $element['term_filter'] = $element['term_filter'] . ">" . $term_child->name . ">全部";

      foreach ($all_terms as $term) {
        $term_array[] = $term->tid;
      }
    }
  }

  //watchdog('mobile shopping', 'term_array = <pre>@data</pre>', array('@data' => print_r($term_array, TRUE)));
  //watchdog('mobile shopping', 'vocid = <pre>@data</pre>', array('@data' => print_r($vocid, TRUE)));
  //watchdog('mobile shopping', 'nids = <pre>@data</pre>', array('@data' => print_r($nids, TRUE)));
  $query = new entityfieldquery();
  switch ($vocid) {
    case '2': //wechat_shopping_merchant_vocabulary
      if ($type == 'volume') {

        $query->entitycondition('entity_type', 'node')
        ->entitycondition('bundle', 'merchandise_input_ct')
        ->propertycondition('status', NODE_PUBLISHED)
        ->propertycondition('nid', $nids, 'NOT IN')  //all nodes not in set.
        ->fieldCondition('field_on_shelf', 'value', '0', '=')
        ->fieldCondition('field_product_volume', 'value', $lastid, '<')
        ->fieldOrderBy('field_product_volume', 'value', $sort)
        ->fieldCondition('field_product_category_term', 'tid', $term_array, 'IN')
        ->range(0,$numbers);

      } else if ($type == 'views') {

        $query->entitycondition('entity_type', 'node')
        ->entitycondition('bundle', 'merchandise_input_ct')
        ->propertycondition('status', NODE_PUBLISHED)
        ->propertycondition('nid', $nids, 'NOT IN')  //all nodes not in set.
        ->fieldCondition('field_on_shelf', 'value', '0', '=')
        ->fieldCondition('field_product_view_count', 'value', $lastid, '<')
        ->fieldOrderBy('field_product_view_count', 'value', $sort)
        ->fieldCondition('field_product_category_term', 'tid', $term_array, 'IN')
        ->range(0,$numbers);

      }
      break;
    case '3': //wechat_shopping_merchant_points_vocabulary
      if ($type == 'volume') {

        $query->entitycondition('entity_type', 'node')
        ->entitycondition('bundle', 'merchandise_input_ct')
        ->propertycondition('status', NODE_PUBLISHED)
        ->propertycondition('nid', $nids, 'NOT IN')  //all nodes not in set.
        ->fieldCondition('field_on_shelf', 'value', '0', '=')
        ->fieldCondition('field_product_volume', 'value', $lastid, '<')
        ->fieldOrderBy('field_product_volume', 'value', $sort)
        ->fieldCondition('field_product_user_point_term', 'tid', $term_array, 'IN')
        ->range(0,$numbers);

      } else if ($type == 'views') {

        $query->entitycondition('entity_type', 'node')
        ->entitycondition('bundle', 'merchandise_input_ct')
        ->propertycondition('status', NODE_PUBLISHED)
        ->propertycondition('nid', $nids, 'NOT IN')  //all nodes not in set.
        ->fieldCondition('field_on_shelf', 'value', '0', '=')
        ->fieldCondition('field_product_view_count', 'value', $lastid, '<')
        ->fieldOrderBy('field_product_view_count', 'value', $sort)
        ->fieldCondition('field_product_user_point_term', 'tid', $term_array, 'IN')
        ->range(0,$numbers);

      }
      break;
    case '4': //wechat_shopping_merchantdise_discount_vocabulary
      if ($type == 'volume') {

        $query->entitycondition('entity_type', 'node')
        ->entitycondition('bundle', 'merchandise_input_ct')
        ->propertycondition('status', NODE_PUBLISHED)
        ->propertycondition('nid', $nids, 'NOT IN')  //all nodes not in set.
        ->fieldCondition('field_on_shelf', 'value', '0', '=')
        ->fieldCondition('field_product_volume', 'value', $lastid, '<')
        ->fieldOrderBy('field_product_volume', 'value', $sort)
        ->fieldCondition('field_product_discount_term', 'tid', $term_array, 'IN')
        ->range(0,$numbers);

      } else if ($type == 'views') {

        $query->entitycondition('entity_type', 'node')
        ->entitycondition('bundle', 'merchandise_input_ct')
        ->propertycondition('status', NODE_PUBLISHED)
        ->propertycondition('nid', $nids, 'NOT IN')  //all nodes not in set.
        ->fieldCondition('field_on_shelf', 'value', '0', '=')
        ->fieldCondition('field_product_view_count', 'value', $lastid, '<')
        ->fieldOrderBy('field_product_view_count', 'value', $sort)
        ->fieldCondition('field_product_discount_term', 'tid', $term_array, 'IN')
        ->range(0,$numbers);

      }
      break;
    
    default:
      // code...
      break;
  }

  global $base_url;

  //$element['total'] = total_numbers();
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
        $element['data'][$node->nid]['nid'] = $node->nid;
        $element['data'][$node->nid]['order_id'] = $order_id;

        $node_req_url = t(
          variable_get('oauth2 redirect request'),
          array(
            '@APPID' => variable_get('wechat_py_AppID'),
            '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/merchandise/' . $node->nid . "/show",
            '@SNSAPI' => "snsapi_base",
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

        //points
        $score_points = $wnode->field_product_user_point_term->value();

        if ($score_points) {
          $max_points = get_point_max($score_points->tid);
          $element['data'][$node->nid]['pscore_points'] = '【' . $max_points . '个积分】';
        } else {
          $element['data'][$node->nid]['pscore_points'] = null;
        }
        //discount
        $discount = $wnode->field_product_discount_term->value();
        $element['data'][$node->nid]['pdiscount'] = $discount ? '【促销】' : null;

        $element['data'][$node->nid]['pcost_price'] = $wnode->field_product_cost_price->value();
        $element['data'][$node->nid]['pshopping_price'] = $wnode->field_product_shopping_price->value();


      }
    }
  } else {
    $element['end'] = 1;
    $element['data'] = null;
    $element['lastid'] = $lastid;
  }

  //watchdog('mobile shopping', '$element = <pre>@data</pre>', array('@data' => print_r($element, TRUE)));
  return $element;
}

function get_point_max($tid) {

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




function get_nodes_by_all($type, $lastid, $nids, $sort, $numbers) {
  $query = new entityfieldquery();
  if ($type == 'volume') {

    //watchdog('mobile shopping', 'nids = <pre>@data</pre>', array('@data' => print_r($nids, TRUE)));
    $query->entitycondition('entity_type', 'node')
    ->entitycondition('bundle', 'merchandise_input_ct')
    ->propertycondition('status', NODE_PUBLISHED)
    ->propertycondition('nid', $nids, 'NOT IN')  //all nodes not in set.
    ->fieldCondition('field_on_shelf', 'value', '0', '=')
    ->fieldCondition('field_product_volume', 'value', $lastid, '<')
    ->fieldOrderBy('field_product_volume', 'value', $sort)
    ->range(0,$numbers);

  } else if ($type == 'views') {

    $query->entitycondition('entity_type', 'node')
    ->entitycondition('bundle', 'merchandise_input_ct')
    ->propertycondition('status', NODE_PUBLISHED)
    ->propertycondition('nid', $nids, 'NOT IN')  //all nodes not in set.
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
    //watchdog('mobile shopping', 'nodes = <pre>@data</pre>', array('@data' => print_r($result['node'], TRUE)));
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
        if ($score_points) {
          $max_points = get_point_max($score_points->tid);
          $element['data'][$node->nid]['pscore_points'] = '【' . $max_points . '个积分】';
        } else {
          $element['data'][$node->nid]['pscore_points'] = null;
        }
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


function total_numbers() {
  $query = new entityfieldquery();

  $count = $query->entitycondition('entity_type', 'node')
    ->entitycondition('bundle', 'merchandise_input_ct')
    ->propertycondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_on_shelf', 'value', '0', '=')
    ->count()
    ->execute();

  return $count;
}

function get_all_service_area() {

    $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_vocabulary');
    
    if (!$voc) {
        return NULL;
    }

    $element = array();
    $terms = taxonomy_get_tree($voc->vid, 0, 1);
    usort($terms, "cmp_termid");    //sort order to ASC by termid
    foreach($terms as $delta => $term) {
        $cterms = taxonomy_get_tree($voc->vid, $term->tid, 1);
        $element[$delta] = array(
            'tid' => $term->tid,
            'name' => $term->name,
	    'weight' => $term->weight
        );

        if (empty($cterms)) {
            $element[$delta]['child'] = array();
        } else {
            usort($cterms, "cmp_termid");
            foreach ($cterms as $id => $cterm) {
                $element[$delta]['child'][$id] = array(
                    'tid' => $cterm->tid,
                    'name' => $cterm->name,
	    	    'weight' => $term->weight
                );
            }
        }
    }
    return $element;

}

function cmp_termid($a, $b) {
    return intval($a->tid) - intval($b->tid);
}

/**
 * End of wechat_mobile_shopping_data_api.inc file name
 */
