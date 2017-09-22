<?php
function menu_wechat_merchant_category_form($form, &$form_state) {

  global $base_url;

  $my_order_req_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/my-order',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100",
    )
  );

  $string_br = '
商品名称: test2(山西区域)
商品价格: ¥2.00
购买数量: 1 件
积分减扣: ¥-2.00
商品合计: ¥0.00

商品名称: test3(山西区域)
商品价格: ¥2.50
购买数量: 1 件
积分减扣: ¥-2.00
商品合计: ¥0.50

  
  ';
  dpm($my_order_req_url);
  dpm($string_br);
  dpm(nl2br($string_br));
  $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_vocabulary');
  $terms = taxonomy_get_tree($voc->vid, 0, 1);
  usort($terms, "term_cmp_termid");    //sort order to ASC by weight

  dpm($terms);

  $term = taxonomy_get_term_by_name('山东区域', 'wechat_shopping_merchant_vocabulary');
  dpm($term);
  $ttt = array_shift($term);
  dpm($ttt);



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
        dpm($node);
      }
    }
  }

//  $md5id = md5('dldAbc123!@#');
//  dpm($md5id);
//  $string = "2-74-5021";
//  $split = preg_split('/-/', $string); //remove 101
//
//  global $user;
//  dpm($user);
//  $curr_user = user_load($user->uid);
//  dpm($curr_user);
//
//  $query = db_select('test_mobile_shopping_user_order_table', 't')
//    ->condition('t.openid', 'o3plFw2bMRMzYBcBXCtx46DHNT9A')
//    ->condition('t.order_state', 1, '>=')
//    ->fields('t');
//
//  $result = $query->execute();
//
//  $total_order = array();
//  foreach ($result as $row) {
//    //dpm($row);
//    $total_order[$row->out_trade_no]['out_trade_no'] = $row->out_trade_no;
//    $total_order[$row->out_trade_no]['order_addr'] = $row->order_addr;
//    $total_order[$row->out_trade_no]['time_end'] = date('Y年m月d日 H:i',strtotime($row->time_end));
//
//    if (!empty($total_order[$row->out_trade_no]['order_detail'])) {
//      $total_order[$row->out_trade_no]['order_detail'] .= $row->order_detail;
//    } else {
//      $total_order[$row->out_trade_no]['order_detail'] = $row->order_detail;
//    }
//
//    if (!empty($total_order[$row->out_trade_no]['total_fee'])) {
//      $total_order[$row->out_trade_no]['total_fee'] += intval($row->total_fee);
//    } else {
//      $total_order[$row->out_trade_no]['total_fee'] = intval($row->total_fee);
//    }
//
//    if (!empty($total_order[$row->out_trade_no]['order_exp_fee'])) {
//      $total_order[$row->out_trade_no]['order_exp_fee'] += floatval($row->area_exp_fee);
//    } else {
//      $total_order[$row->out_trade_no]['order_exp_fee'] = floatval($row->area_exp_fee);
//    }
//  }
//
//
//  dpm($total_order);
//  $query = db_select('test_mobile_shopping_user_order_table', 't')
//    ->condition('t.out_trade_no', 'D20160608104017-StXfCpTj4RIWDLDo')
//    //->condition('t.area_id', $split, 'IN')
//    ->fields('t');
//
//  $result = $query->execute();
//
//  $total_order = array();
//  foreach ($result as $id => $data) {
//    dpm('---');
//    $temp = (array)$data;
//    $total_order[$id] = $temp;
//    dpm($data);
//    $m_query = db_select('test_mobile_shopping_user_order_detail_table', 't')
//         ->condition('t.order_index', $data->id)
//         ->condition('t.area_term_id', $data->area_id)
//         ->fields('t');
//    $d_result = $m_query->execute();
//    foreach ($d_result as $item) {
//      dpm($item);
//    }
//  }
//
//  $query = new EntityFieldQuery();
//
//  $results = $query->entityCondition('entity_type', 'user')
//    ->propertyCondition('status', 1)  //1 active user
//    ->fieldCondition('field_product_category_term', 'tid', '74', '=')
//    ->fieldCondition('field_wechat_openid', 'value', '', '<>')
//    ->execute();
//
//  dpm($results);
//  dpm(count($results['user']));
//  dpm($results['user']);
//
//
//  foreach ($results['user'] as $key => $uid) {
//    $user = user_load($key);
//    if (test_check_user_role($user, '微商城管理员') && !test_check_user_role($user, 'page_admin')) {
//      dpm($user);
//    }
//  }

  //dpm($total_order);
//  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
//  $usr_info = wechat_api_get_user_info("o3plFwxAmKJNrJFXtk93GmSpYWv0");
//
//  if($usr_info != '') {
//    $myself_headimage = $usr_info->headimgurl;
//    $myself_nickname = $usr_info->nickname;
//
//    dpm($usr_info);
//  } else {
//    dpm('nothing');
//  }


  //dpm($html->find('div'));

  //$img_info = curl_getinfo($ch, CURLINFO_CONTENT_TYPE);

//  $url = "http://mxweixin.dreamland360.com/sites/default/files/point_qrscan_image/7bf7051bcce841bfbcc5624692b7d65a.png";
//
//  if (preg_match('/point_qrscan_image/', $url)) {
//    $split = preg_split('/point_qrscan_image/', $url); //remove 101
//
//    $scheme = variable_get('file_default_scheme', 'public') . '://';
//    $file_name = $scheme . "point_qrscan_image" . $split[1]; 
//    dpm($file_name);
//  }
//
//  $path1 = parse_url($url);
//  dpm($path1);
//
//  $query = db_select('mobile_shopping_user_friends_table', 't')
//         ->condition('openid', "o3plFw11Au4WwDd61x0HLsJdxebQ")
//         ->orderBy('t.regist_time', 'DESC')
//         ->fields('t', array(
//            'f_openid_nick_name',
//            'f_openid_head_img_url',
//            'regist_time',
//            ));
//  $result = $query->execute();
//
//  foreach ($result as $id => $friend) {
//    $element[$id]['nick_name'] = base64_decode($friend->f_openid_nick_name);
//    $element[$id]['head_img'] = $friend->f_openid_head_img_url;
//    $element[$id]['regist_time'] = date('Y年m月d日 H:i', $friend->regist_time);
//    dpm($element);
//  }

//  $query = db_select('mobile_shopping_user_points_table', 't')
//         ->condition('MD5', "c3e539767c2607a75cbc27352a58520a")
//         ->fields('t', array(
//            'openid',
//            'total_points',
//            'curr_points',
//            ));
//  $result = $query->execute();
//  $count = $result->rowCount();
//
//  if ($count) {
//    foreach ($result as $row) {
//      //if you have registered to your friends table, then do nothing
//      $f_query = db_select('mobile_shopping_user_friends_table', 't')
//             ->condition('openid', $row->openid)
//             ->condition('MD5', "c3e539767c2607a75cbc27352a58520a")
//             ->condition('f_openid', "dkdkdkdkdk")
//             ->fields('t', array(
//                'f_openid',
//                ));
//
//      $f_result = $f_query->execute();
//      $f_count = $f_result->rowCount();
//      dpm($f_count);
//      if ($f_count) {
//        return;
//      }
//    }
//  }

//  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
//  $usr_info = wechat_api_get_user_info("o3plFw11Au4WwDd61x0HLsJdxebQ");
//
//  $scheme = variable_get('file_default_scheme', 'public') . '://';
//  header('Content-Type: image/jpg');
//  if($usr_info != '') {
//    $myself_headimage = $usr_info->headimgurl;
//    $myself_nickname = $usr_info->nickname;
//
//    //$myself_headimage = drupal_get_path('module', 'wechat_py_mobile') . '/imgs/mxweixin_qr_scan_head.jpg';
//    //$myself_nickname = "匿名用户";
//    $test_file_name = test_compose_qr_scan_image("o3plFw11Au4WwDd61x0HLsJdxebQ", $myself_headimage, $myself_nickname, "url");
//    dpm($test_file_name);
//    dpm(file_create_url($test_file_name));
//
//    $ch = curl_init($myself_nickname);
//    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
//    curl_setopt($ch, CURLOPT_BINARYTRANSFER,1);
//    $picture = curl_exec($ch);
//
//    # get the content type
//    $img_info = curl_getinfo($ch, CURLINFO_CONTENT_TYPE);
//    curl_close ($ch);
//    
//    $org_image = $scheme . "point_qrscan_image/211.jpg";
//    file_unmanaged_save_data($picture, $org_image, FILE_EXISTS_REPLACE);
//
//    $head_image_im;
//    switch ($img_info) {
//      case "image/gif": 
//        $head_image_im = imagecreatefromgif($org_image);
//        break;
//      case "image/jpeg": 
//        $head_image_im = imagecreatefromjpeg($org_image);
//        break;
//      case "image/png": 
//        $head_image_im = imagecreatefrompng($org_image);
//        break;
//      case "image/bmp": 
//        $head_image_im = imagecreatefromwbmp($org_image);
//        break; 
//    }
//    $head_image_imw = imagesx($head_image_im);
//    $head_image_imh = imagesy($head_image_im);
//
//    $dest_imagew = 200;
//    $dest_imageh = 200;
//    $dest_image_im = imagecreatetruecolor($dest_imagew, $dest_imageh);
//    imagecopyresampled($dest_image_im, $head_image_im, 0, 0, 0, 0, $dest_imagew, 
//				$dest_imageh, $head_image_imw, $head_image_imh);
//    
//    //$image11 = imagescale($head_image_im, 200, 200, IMG_NEAREST_NEIGHBOUR);
//    $head_scale = $scheme . "point_qrscan_image/101.jpg";
//    $head_image_org = $scheme . "point_qrscan_image/111.jpg";
//    imagejpeg($dest_image_im, $head_scale, 75);
//    imagedestroy($dest_image_im);
    
//    $img_info = getimagesize($usr_info->headimgurl);
//
//    $scheme = variable_get('file_default_scheme', 'public') . '://';
//    switch ($img_info['mime']) {
//      case "image/gif": 
//        $head_img_file_name = $scheme . "point_qrscan_image/" . $md5id . "head_img.gif";
//        break;
//      case "image/jpeg": 
//        $head_img_file_name = $scheme . "point_qrscan_image/" . $md5id . "head_img.jpg";
//        break;
//      case "image/png": 
//        $head_img_file_name = $scheme . "point_qrscan_image/" . $md5id . "head_img.png";
//        break;
//      case "image/bmp": 
//        $head_img_file_name = $scheme . "point_qrscan_image/" . $md5id . "head_img.bmp";
//        break; 
//    }
//    dpm($img_info);
//  }

//  $scheme = variable_get('file_default_scheme', 'public') . '://';
//  $library = libraries_load('wxpayapi');
//
//  $md5id = md5('o3plFw11Au4WwDd61x0HLsJdxebQ');
//
//  //create qr scan my_doc req url
//  $state = "101next" . $md5id;
//  $qr_scan_my_doc_req_url = t(
//    variable_get('oauth2 redirect request'),
//    array(
//      '@APPID' => variable_get('wechat_py_AppID'),
//      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/my-doc',
//      '@SNSAPI' => "snsapi_userinfo",
//      '@STATE' => $state,
//    )
//  );
//
//  $qr_scan_file_name = $scheme . "point_qrscan_image/" . $md5id . "qr_scan.png";
//  QRcode::png($qr_scan_my_doc_req_url, $qr_scan_file_name, QR_ECLEVEL_L, 3, 2);
//
//  $fn11 = $scheme . "point_qrscan_image/002.png";
//
//  $text = "https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx9ee4070dc39cdedb&redirect_uri=http://mxweixin.dreamland360.com/wechat-py-mobile/new-tpl&response_type=code&scope=snsapi_base&state=100#wechat_redirect";
//  //$text = "The page is the primary unit of interaction in jQuery Mobile and is used to group content into logical views that can be animated in and out of view with page transitions. A HTML document may start with a single 'page' and the Ajax navigation system will load additional pages on demand into the DOM as users navigate around. Alternatively, a HTML document can be built with multiple 'pages' inside it and the framework will transition between these local views with no need to request content from the server.";
//  QRcode::png($text, $fn11, QR_ECLEVEL_L, 3, 2);
//
//  $filename = $scheme . "001.png";
//  dpm($filename);
//
//  //Output image to the browser
//  header('Content-Type: image/png');
//
//  $im = imagecreatetruecolor(430, 860);
//  $bg_white = imagecolorallocate($im, 0xFF, 0xFF, 0xFF);
//  $textColor = imagecolorallocate ($im, 0, 0,0);
//  //$black = imagecolorallocate($im, 0x00, 0x00, 0x00);
//
//   //Make the background red
//  imagefilledrectangle($im, 0, 0, 429, 859, $bg_white);
//
//  //Path to our ttf font file
//
//  $font_file = drupal_get_path('module', 'wechat_py_mobile') . '/imgs/华文细黑.ttf';
//  $qr_code = drupal_get_path('module', 'wechat_py_mobile') . '/imgs/test_php_gd_qr_code.png';
//
//  $qr_code_im = imagecreatefrompng($qr_code);
//  dpm($qr_code_im);
//  imagecopy($im, $qr_code_im, 0, 430, 0, 0, 430, 430);
//  imagefttext($im, 13, 0, 20, 20, $textColor, $font_file, '这是ta的微信号48494');
//
//
//  imagepng($im, $filename, 0);
//  imagedestroy($im);
//

//  $query = new entityfieldquery();
//  $nodes = array(0, 469);
//  $query->entitycondition('entity_type', 'node')
//    ->entitycondition('bundle', 'merchandise_input_ct')
//    ->propertycondition('status', NODE_PUBLISHED)
//    ->propertycondition('nid', $nodes, 'NOT IN')
//    ->fieldCondition('field_on_shelf', 'value', '0', '=')
//    ->fieldCondition('field_product_volume', 'value', 10000000, '<')
//    ->fieldOrderBy('field_product_volume', 'value', 'DESC');
//    //->range(0,4);
//
//  $result = $query->execute();
//  if (!empty($result)) {
//    dpm($result);
//    $nodes = node_load_multiple(array_keys($result['node']));
//    $count = count($nodes);
//    //watchdog('mobile shopping', 'count = <pre>@data</pre>', array('@data' => print_r($count, TRUE)));
//    if ($count < $numbers || $count == 0) {
//      $element['end'] = 1;
//    }
//
//
//    if ($count) {
//      foreach($nodes as $node){
//      }
//    }
//  }


//  dpm(md5('梦乡网服务号'), 'md5 梦乡网服务号');
//  $time = strtotime('20151222094108');
//
//  $newformat = date('Y年m月d日 H:i',$time);
//  dpm($newformat);
//
//
//  $userids = entity_load('user');
//  dpm($userids);
//  foreach ($userids as $each_user) {
//    $user_profile = entity_metadata_wrapper('user', $each_user->uid);
//    $term_id = $user_profile->field_product_category_term->value();
//
//    if ($term_id !== null) {
//      dpm($term_id, 'find it');
//    }
//  }
//
//  $jsparam = '{"appId":"wx9ee4070dc39cdedb","nonceStr":"52wh3hzpn21gvrhkz5s2gly0vy935k5x","package":"prepay_id=wx201512181224330cfb6771990879463851","signType":"MD5","timeStamp":1450412673,"paySign":"035CB8A32C2663DBC6A11E655E34FFF9"}';
//
//  $package = json_decode($jsparam);
//  $prepay_idstr = $package->package;
//  if (preg_match('/prepay_id=/', $prepay_idstr)) {
//
//    $split = preg_split('/prepay_id=/', $prepay_idstr); //remove 100
//    dpm($split[1]);
//  }
//  dpm(json_decode($jsparam));
//
//  $query = new entityfieldquery();
//    $query->entitycondition('entity_type', 'node')
//    ->entitycondition('bundle', 'merchandise_input_ct')
//    ->propertycondition('status', NODE_PUBLISHED)
//    ->fieldCondition('field_on_shelf', 'value', '0', '=')
//    ->fieldCondition('field_product_view_count', 'value', 166, '<')
//    ->fieldOrderBy('field_product_view_count', 'value', 'DESC')
//    ->range(0,4);
//
//  $result = $query->execute();
//  if (!empty($result)) {
//    $nodes = node_load_multiple(array_keys($result['node']));
//    dpm($nodes);
//  }
//
//  $parent = taxonomy_get_parents(100);
//  dpm($parent);
//
//
//  $state = "100nid413";
//  if (preg_match('/^100/', $state)) {
//    $split = preg_split('/^100/', $state); //remove 100
//    dpm($split);
//    $nid = preg_split('/nid/', $split[1]); //remove vocid
//    dpm($nid[1]);
//  }
//  background_process_start('background_execute', $parent, $state);
//  //watchdog('py shopping callback', 'code = <pre>@openid</pre>', array('@openid' => print_r($_GET, TRUE)));
//
//    $lll = taxonomy_term_load(1722);
//    dpm($lll->field_division_category['und'][0]['value']);
//    $exp_list = array();
//
//    $query = new EntityFieldQuery();
//    $query->entityCondition('entity_type', 'node')
//      ->entityCondition('bundle', 'express_template_ct');
//      //->fieldCondition('field_express_template_term', 'tid', 4945);
//
//    $result = $query->execute();
//    if (!empty($result)) {
//      $nodes = node_load_multiple(array_keys($result['node']));
//      foreach($nodes as $node) {
//        $wnode = entity_metadata_wrapper('node', $node);
//        $fc_explist = $wnode->field_fc_express_price_list->value();
//        $exp_tid = $wnode->field_express_template_term->value();
//
//        foreach ($fc_explist as $item) {
//          $temp_array = array();
//
//          $fc_item_wrapper = entity_metadata_wrapper('field_collection_item', $item);
//          $area = $fc_item_wrapper->field_division_term->value();
//          $w_region = $fc_item_wrapper->field_which_region->value();
//
//          if ($area === null) {
//            continue;
//          }
//
//          $temp_array['tid'] = $area->tid;
//          $temp_array['name'] = $area->name;
//          $temp_array['w_region'] = $w_region;
//
//          $init_weight = $fc_item_wrapper->field_init_weight->value();
//          $init_weight_price = $fc_item_wrapper->field_init_weight_price->value();
//          $setp_weight = $fc_item_wrapper->field_step_weight->value();
//          $setp_weight_price = $fc_item_wrapper->field_step_weight_price->value();
//          $temp_array['init_weight']       = $init_weight;
//          $temp_array['init_weight_price'] = $init_weight_price;
//          $temp_array['setp_weight']       = $setp_weight;
//          $temp_array['setp_weight_price'] = $setp_weight_price;
//
//          $weight_condition = $fc_item_wrapper->field_weight_section_condition->value();
//          if ($weight_condition == 1) {
//            $fc_temp = $fc_item_wrapper->field_fc_weight_section_unit->value();
//            foreach ($fc_temp as $owc_value) {
//              $fc_owc_wrapper = entity_metadata_wrapper('field_collection_item', $owc_value);
//              $temp_array['over_wc'][$owc_value->item_id]['owc'] = $fc_owc_wrapper->field_over_wight_section->value();
//              $temp_array['over_wc'][$owc_value->item_id]['owc_price'] = $fc_owc_wrapper->field_over_wight_section_price->value();
//
//            }
//          }
//
//          $exp_list[$exp_tid->tid][$area->tid] = $temp_array; 
//        }
//
//
//      }
//    }
//    dpm($exp_list);
//
//
//  $node = node_load(413); //load 微商城用户购物车纪录 node nid=425
//  $wnode = entity_metadata_wrapper('node', $node);
//  //$discount = $wnode->field_product_express_free->value();
//  $discount = $wnode->field_product_express_free->value();
//  dpm($discount);
//  if ($discount == 0) {
//    dpm('ok no');
//  } else {
//    dpm('null');
//  }
/*
  $string = "101vocid4termid8620";
  $split = preg_split('/^101/', $string);
  //dpm($split);
  $vocid = preg_split('/vocid/', $split[1]);
  //dpm($vocid, "vocid");
  $termid = preg_split('/termid/', $vocid[1]);
  //dpm($termid, "termid");

  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  $result = wechat_api_get_user_info("oOTG9tzINV6zA_1vIBgWrqRRlTl0");

  //dpm(md5("oOTG9tzINV6zA_1vIBgWrqRRlTl0"), "md5");
  if($result == ''){
    watchdog('get user info',
             '获取用户信息发生错误! user open id = @openid',
             array('@openid' => $result->openid),
             $severity = WATCHDOG_ERROR);
  }else{
    dpm($result, 'user info');
  }

  $query = db_select('mobile_shopping_user_address_table', 't')
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
  dpm($result);
  $count = $result->rowCount();
  dpm($count);
  foreach ($result as $row) {
    dpm($row);
  }
  $node = node_load(425); //load 微商城用户购物车纪录 node nid=425
  $wnode = entity_metadata_wrapper('node', $node);
    $wnode->field_user_open_id = array(null);
    $wnode->field_merchandise_id = array(null);
    $wnode->field_purchase_volume = array(null);
    $wnode->field_cart_checkin = array(null);
    $wnode->field_purchase_date = array(null);
  $wnode->save();

  dpm(urlencode("http://mxweixin.dreamland360.com/wechat-py-mobile/pay-test/new-tpl"));

  $voc = taxonomy_vocabulary_machine_name_load('china_administrative_divisions_taxonomy');

  $terms = taxonomy_get_tree($voc->vid, 1719, 1);
    dpm($terms);
 
  $parent = taxonomy_get_parents(100);
  dpm($parent);
*/

  //$term = taxonomy_term_load(100);
  //dpm($term);
/*
  $nodes = taxonomy_select_nodes('4');


  $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_vocabulary');
  $term_all = taxonomy_get_tree($voc->vid);
  dpm($term_all);


  $term_array = array();
  $terms = taxonomy_get_tree($voc->vid, 0, 1);
  foreach ($terms as $term) {
    $term_array[$term->tid] = array(
       'name' => $term->name,
    );
    get_term($voc->vid, $term->tid, $term_array);
  }

 $json_data = json_encode($term_array,
                           JSON_HEX_TAG |
                           JSON_HEX_APOS |
                           JSON_HEX_AMP |
                           JSON_HEX_QUOT |
                           JSON_UNESCAPED_UNICODE);
  dpm($json_data, '$term_array');
  dpm(drupal_json_decode($json_data), 'decode');


  $request = file_get_contents("php://input"); //get xml data
  dpm($request);
  dpm(request_uri());
  
  //$received = json_decode($request);
  $code = isset($_GET['code']) ? $_GET['code'] : '';
  dpm($code);
  dpm($_GET['name']);
  */
  /*
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'merchandise_points_rule_ct')
    ->fieldCondition('field_points_term', 'tid', 82);

  $result = $query->execute();
  if (empty($result)) {
    drupal_set_message('query result is empty');
    return $form;
  } else {
    $nodes = node_load_multiple(array_keys($result['node']));
    dpm($nodes);
    foreach ($nodes as $node) {
      $wr_node = entity_metadata_wrapper('node', $node);
      $start_date = $wr_node->field_score_start_date->value();
      $end_date =  $wr_node->field_score_end_date->value();

      //dpm($start_date);
      dpm(date('Y-m-d\TH:i:s', $start_date));
      
      //dpm($end_date);
      dpm(date('Y-m-d\TH:i:s', $end_date));
      dpm(date('Y-m-d H:i:s', time()));
    }
  }
  
  */
  /*
  $form['link'] = array(
    '#type' => 'link',
    '#title' => '<div></div>',
    '#href' => 'node/dkdkdkd',
  );

  $node_beef = node_load(413);
  //dpm($node_beef);
  $wnode = entity_metadata_wrapper('node', $node_beef);
  $express_free = $wnode->field_product_imgs->value();
  dpm($express_free, 'node images');
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'mobile_shopping_adv_node')
    ->propertyCondition('status', NODE_PUBLISHED);


  $result = $query->execute();
  if (!empty($result)) {
    $nodes = node_load_multiple(array_keys($result['node']));
    if(count($nodes)) {
      foreach($nodes as $node){
        //dpm($node);
        $rnode = entity_metadata_wrapper('node', $node);

        
        $fc_adv_items = $rnode->field_fc_adv_items->value();
        $fc_wrapper = entity_metadata_wrapper('field_collection_item', $fc_adv_items);
        $fc_adv_image_1 = $fc_wrapper->field_first_adv_image->value();
        $img_url = file_create_url($fc_adv_image_1['uri']);

        $merchandise_list = $fc_wrapper->field_first_adv_node_by_title->value();
        $term = $fc_wrapper->field_third_adv_term_express->value();
        $list12 = taxonomy_select_nodes($term->tid, false);
        //dpm($term);
        //dpm($merchandise_list);
        //dpm($list12);

        $img1 = array(
          '#theme' => 'image',
          '#path' => $img_url,
          '#attributes' => array('id' => array('product-img'),
                                'width' => array('100%'),
                                'style' => array('margin: 0 auto;display: block;')),
        );
        $form['img1'] = array(
          '#markup' => drupal_render($img1),
          '#prefix' => '<a href="http://news.sina.com.cn">',
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
        $form['img2'] = array(
          '#markup' => drupal_render($img2),
          '#prefix' => '<a href="http://aol.com">',
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
        $form['img3'] = array(
          '#markup' => drupal_render($img3),
          '#prefix' => '<a href="http://www.sohu.com">',
          '#suffix' => '</a>',
        );
      }
    }
  }
  
  /*
  $items[$id]['img'] = array(
   '#theme' => 'image',
   '#path' => $img_url,
   '#attributes' => array('id' => array('product-img'),
                          'width' => array('100%'),
                          'style' => array('margin: 0 auto;display: block;')),
  );
  */
  return $form;
}

function test_check_user_role($user, $role) {

  if ($user != null) {
    if (in_array($role, $user->roles, true)) {
      return true;
    }
  }

  return false;
}

function test_compose_qr_scan_image($openid, $head_image_url, $nick_name, $flag) {

  global $base_url;

  $md5id = md5($openid);
  $scheme = variable_get('file_default_scheme', 'public') . '://';

  //finally generate qr_scan_image_url
  $file_name = $scheme . "point_qrscan_image/" . $md5id . ".png";

  //create background png
  header('Content-Type: image/png');
  $qr_scan_width = 200;
  $qr_scan_height = 500;

  $im = imagecreatetruecolor($qr_scan_width, $qr_scan_height);
  $bg_white = imagecolorallocate($im, 0xFF, 0xFF, 0xFF);
  imagefilledrectangle($im, 0, 0, 199, 499, $bg_white);
  $textColor = imagecolorallocate ($im, 0, 0,0);

  //create qr scan my_doc req url
  $state = "101next" . $md5id;
  $qr_scan_my_doc_req_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/my-doc',
      '@SNSAPI' => "snsapi_userinfo",
      '@STATE' => $state,
    )
  );

  $library = libraries_load('wxpayapi');
  $qr_scan_file_name = $scheme . "point_qrscan_image/" . $md5id . "qr_scan.png";
  QRcode::png($qr_scan_my_doc_req_url, $qr_scan_file_name, QR_ECLEVEL_L, 3, 2);
  $scan_image_im = imagecreatefrompng($qr_scan_file_name);
  $scan_image_imw = imagesx($scan_image_im);
  $scan_image_imh = imagesy($scan_image_im);

  //head_image
  $head_image_im;
  $dest_imagew = 200;
  $dest_imageh = 200;

  if ($flag == "url") {
    $ch = curl_init($head_image_url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_BINARYTRANSFER,1);
    $picture = curl_exec($ch);
    # get the content type
    $img_info = curl_getinfo($ch, CURLINFO_CONTENT_TYPE);
    curl_close($ch);

    switch ($img_info) {
      case "image/gif": 
        $temp_head_image_file = $scheme . "point_qrscan_image/temp_head_image.gif";
        $orig_head_image = file_unmanaged_save_data($picture, $temp_head_image_file);
        $head_image_im = imagecreatefromgif($orig_head_image);
        break;
      case "image/jpeg": 
        $temp_head_image_file = $scheme . "point_qrscan_image/temp_head_image.jpeg";
        $orig_head_image = file_unmanaged_save_data($picture, $temp_head_image_file);
        $head_image_im = imagecreatefromjpeg($orig_head_image);
        break;
      case "image/png": 
        $temp_head_image_file = $scheme . "point_qrscan_image/temp_head_image.png";
        $orig_head_image = file_unmanaged_save_data($picture, $temp_head_image_file);
        $head_image_im = imagecreatefrompng($orig_head_image);
        break;
      case "image/bmp": 
        $temp_head_image_file = $scheme . "point_qrscan_image/temp_head_image.bmp";
        $orig_head_image = file_unmanaged_save_data($picture, $temp_head_image_file);
        $head_image_im = imagecreatefromwbmp($orig_head_image);
        break; 
    }

    //copy head image to background png
    $head_image_imw = imagesx($head_image_im);
    $head_image_imh = imagesy($head_image_im);
    $dest_image_im = imagecreatetruecolor($dest_imagew, $dest_imageh);
    imagecopyresampled($dest_image_im, $head_image_im, 0, 0, 0, 0, $dest_imagew, 
        $dest_imageh, $head_image_imw, $head_image_imh);
    imagecopy($im, $dest_image_im, 0, 0, 0, 0, $dest_imagew, $dest_imageh);

  } else {
    $head_image_im = imagecreatefromjpeg($head_image_url);

    $head_image_imw = imagesx($head_image_im);
    $head_image_imh = imagesy($head_image_im);

    imagecopy($im, $head_image_im, 0, 0, 0, 0, $head_image_imw, $head_image_imh);
  }

  //write text to background png
  $font_file = drupal_get_path('module', 'wechat_py_mobile') . '/imgs/华文细黑.ttf';
  //$font_file = $scheme . "point_qrscan_image/华文细黑.ttf";
  //dpm($font_file);

  //Make the background white
  $text1 = $nick_name;
  $text2 = "攒积分，靠人品!!!";
  $text3 = "长按图片，扫描二维码";
  $text4 = "获好友积分！";
  imagefttext($im, 13, 0, 15, $dest_imageh + 20, $textColor, $font_file, $text1);
  imagefttext($im, 13, 0, 15, $dest_imageh + 40, $textColor, $font_file, $text2);
  imagefttext($im, 13, 0, 15, $dest_imageh + 60, $textColor, $font_file, $text3);
  imagefttext($im, 13, 0, 15, $dest_imageh + 80, $textColor, $font_file, $text4);

  imagecopy($im, $scan_image_im, 8, 300, 0, 0, $scan_image_imw, $scan_image_imh);

  imagepng($im, $file_name, 0);
  imagedestroy($im);

  return $file_name;
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

function old_1_menu_wechat_merchant_category_form($form, &$form_state) {
  
  //$redirectUrl = 'http://mxweixin.dreamland360.com/wechat-py-shopping/wechat-merchant-express/form-test';
  //$redirectUrl = 'wechat-merchant-express/form-test';
  //$redirectUrl = 'wechat-py-admin';
  $testurl = $_SERVER['REQUEST_URI'];
 //dpm($testurl);
  //$testurl = urlencode($redirectUrl);
  //dpm($testurl);
  //header("Location: $testurl"); //Redirect browser to url
  //exit();


  $options = array(
    '0' => '无',
    '1' => '测试1',
    '2' => 'ceshi2',
    '3' => '大哭大哭大哭',
  );

  $form['hahaselect'] = array(
    '#type' => 'select',
    '#title' => '名称',
    '#options' => $options,
    '#default_value' => '3',
  );

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('所有子分类信息'), 
  );

  $css = drupal_get_css();
  $js = drupal_get_js();
  //dpm($js);

  //$value = get_merchant_category_all();
  //dpm($value);

  $form['radios_test'] = array(
    '#type' => 'radios',
    '#title' => '测试',
    '#default_value' => 0,
    '#options' => array(0 => t('选择0'), 1 => t('选择1')),
    '#attributes' => array('name' => array('my-test')),
  );

  //dpm($form['radios_test'], '$form["radios_test"]');

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/js/merchant_input_form.js',
  );

 //dpm(time());
 //dpm(date("YmdHis", 1442112636));
 //dpm(variable_get('wechat_py_mchid'));
 //dpm(variable_get('wechat_py_mchkey'));
  
  $ttt = 'dkdk';
  $ret = ($ttt == null) ?dpm('1') :dpm('2');
 //dpm(getcwd());

  $arr = array(
    '1' => 'hello',
    '2' => 'world',
  );

  $jsdata = json_encode($arr);
 //dpm($jsdata);
  $form['testvalue'] = array(
                
    '#markup' => '<div id="divCheckbox" style="display: none;">' . 'hello' . '</div>',
  );
 
  //dpm(md5(drupal_random_bytes(16)));
  //$data = drupal_base64_encode(drupal_random_bytes(10));
  $data = drupal_random_key(10);
  //dpm($data);

  //$library = libraries_load('wxpayapi');
  //dpm($library);

  
	$src = array(
		array(0x2600),		# BLACK SUN WITH RAYS
		array(0x1F494),		# BROKEN HEART (was U+1F493)
		array(0x1F197),		# OK SIGN (was U+1F502)
		array(0x32, 0x20E3),	# KEYCAP 2
	);
 //dpm($src);

  module_load_include("php", "wechat_py_shopping", "emoji");

  $txt1 = "\xf0\x9f\x98\x84";
  $txt2 = "\xF0\x9F\x91\xA3";
  $txt3 = "\xf0\x9f\x92\x8b\xe6";
  $txt4 = "\xF0\x9F\x91\xBF\xE4\xB8";
  //$txt4 = "\xF0\x9F\x91\xBF";

  
  //1: use google convert string to unified
	$clean_text1 = emoji_google_to_unified($txt1);
  $clean_text2 = emoji_google_to_unified($txt2);

  $clean_text3 = emoji_google_to_unified($txt3);
  $clean_text4 = emoji_google_to_unified($txt4);

  //emoji_docomo_to_unified(	
  //emoji_kddi_to_unified(		
  //emoji_softbank_to_unified
  //emoji_google_to_unified(	
  //var_dump($clean_text4);

	# now we want to show it in a desktop browser

  //2: convert unified to html and insert into database. Some of html chara is special character, can't be showed.
	$html1 = emoji_unified_to_html($clean_text1);
	$html2 = emoji_unified_to_html($clean_text2);
	$html3 = emoji_unified_to_html($clean_text3);
	$html4 = emoji_unified_to_html($clean_text4);
  //dpm(bin2hex($html4));
  //if(isset($html4)){
  // //dpm('null');
  //}

  //3. Before displayed to browser, conver html to unified character
  $uni1 = emoji_html_to_unified($html1);
  $uni2 = emoji_html_to_unified($html2);
  $uni3 = emoji_html_to_unified($html3);
  $uni4 = emoji_html_to_unified($html4);

  $form['show1'] = array(
    '#markup' => '<div>' . $uni1 . '</div>',
  );
  $form['show2'] = array(
    '#markup' => '<div>' . $uni2 . '</div>',
  );
  $form['show3'] = array(
    '#markup' => '<div>' . $uni3 . '</div>',
  );
  $form['show4'] = array(
    '#markup' => '<div>' . $uni4 . '</div>',
  );


  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  //call and get user info
  $result = wechat_api_get_user_info('oOTG9t0nnlqWQUmmpieHOmtFwfU8');
  $hex1 = base64_encode('Thomas Luo');
 //dpm($hex1, 'hex1');
  if(is_base64_encoded('123458abc')) {
  //$hex2 = base64_decode('有权_(๑• . •๑)不在乎');
  //if(strlen($hex2) == 0) {
    //$hex2 = base64_decode('ZW1vamk6VGlmZmFueSAg8J+MuyDnlYXlqbc=');
    $hex2 = base64_decode('5qGC5qKF');
    $emoji = preg_split('/emoji:/', $hex2);
   //dpm($emoji);
   //dpm($hex2);
  }else{
   //dpm('can not find');
  }

  $scheme = variable_get('file_default_scheme', 'public') . '://';
  $path = $scheme . "/wechat_py_admin/123_0.jpg";
  $form['image'] = array(
    '#theme' => 'image',
    '#path' => $path,
    '#title' => 'Image Title',
    '#attributes' => array('class' => 'some-img', 'id' => 'my-img'),
  );

  //dpm($form['image'], '$form["image"]');

  $protocol = (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] !== 'off' || $_SERVER['SERVER_PORT'] == 443) ? "https://" : "http://";
  $url = "$protocol$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
 //dpm($url);
 //dpm($_SERVER['REQUEST_URI']);

  $baseUrl = urlencode('http://'.$_SERVER['HTTP_HOST'].$_SERVER['PHP_SELF'].$_SERVER['QUERY_STRING']);
 //dpm($baseUrl);
 //dpm($_SERVER['HTTP_HOST']);
 //dpm($_SERVER['PHP_SELF']);
 //dpm($_SERVER['QUERY_STRING']); //nothing

  $interval = variable_get('cron_get_user_interval', 0);
 //dpm(date("YmdHis", $interval));
  

  $squery = db_select('wechat_py_subscribe_user_table', 't')
    ->condition('t.openid', '112233')
    ->fields('t', array('openid'))
    ->execute();

  $nums = $squery->rowCount();

 //dpm($nums);
  //$result = $query->execute()->fetchAssoc();

  $key = 'mywechatcareer7777';
 //dpm(md5($key));


  $form['express_tmplate'] = array(
    '#type' => 'submit',
    '#value' => t('解析行政区域代码'),
    '#prefix' => '<div class="insert-code">',
    '#suffix' => '</div',
    '#attributes' => array('style' => array('clear: both;')),
    '#submit' => array('distriction_insert'),
  );
/*
  $url1 = "https://api.mch.weixin.qq.com/pay/unifiedorder";
  curl_test($url1);
*/


/*
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'mobile_shopping_product_input')
    ->propertyCondition('status', NODE_PUBLISHED);

  $result = $query->execute();
  $nodes = node_load_multiple(array_keys($result['node']));
 //dpm($nodes);
  if(count($nodes)) {
    foreach($nodes as $id => $node){
     //dpm($id);
      $rnode = entity_metadata_wrapper('node', $node);
     //dpm($node);
      
      //dpm($rnode->field_product_sku_list->value(), 'product node');
      $temp = $rnode->field_product_sku_list->value();
     //dpm($temp);
      $fc_wrapper = entity_metadata_wrapper('field_collection_item', $temp[0]);
      $tkd = $fc_wrapper->field_product_sku_price->value();
     //dpm($tkd);
    }
  }
*/

/*
  $transaction = db_transaction();

  try {
   //dpm('trans');
    $query = db_update('wechat_py_subscribe_user_table')
      ->fields(array(
        'nickname' => 'test4',
        'headimgurl' => 'http://',))
      ->condition('openid', 'oOTG9t--1pTUPKN34B7iiiqdnj4E');
    $rows = $query->execute();
   //dpm($rows);
  }
  catch(Exception $e) {
    $transaction->rollback();
    $errorinfo = $e->errorInfo;
    watchdog('test update',
             'update user openid: @openid info failed = <pre>@error</pre>',
             array('@openid' => '1234', 
                   '@error' => print_r($errorinfo, TRUE)));
  }
  */
  /*
	foreach ($src as $unified){

		$bytes = '';
		$hex = array();

		foreach ($unified as $cp){
			$bytes .= utf8_bytes($cp);
			$hex[] = sprintf('U+%04X', $cp);

		}

		$str = "Hello $bytes World";

		echo "<tr>\n";
		echo "<td>".implode(' ', $hex)."</td>\n";
		echo "<td>".HtmlSpecialChars(emoji_get_name($bytes))."</td>\n";
		echo "<td>$str</td>\n";
		echo "<td>".emoji_unified_to_html($str)."</td>\n";
		echo "<td>".emoji_html_to_unified(emoji_unified_to_html($str))."</td>\n";
		echo "</tr>\n";
	}
  */

/*
  $form['item'] = array(
    '#markup' => 
  );
  */

  //create new jsapipay
  /*
  $tools = new JsApiPay();

  $input = new WxPayUnifiedOrder();
  $input->SetBody("test");
  $input->SetAttach("test");
  $input->SetOut_trade_no(WxPayConfig::MCHID.date("YmdHis"));
  $input->SetTotal_fee("1");
  $input->SetTime_start(date("YmdHis"));
  $input->SetTime_expire(date("YmdHis", time() + 600));
  $input->SetGoods_tag("test");
  $input->SetNotify_url("http://paysdk.weixin.qq.com/example/notify.php");
  $input->SetTrade_type("JSAPI");
  $input->SetOpenid("sabadeierrl");
  //$order = WxPayApi::unifiedOrder($input);
 //dpm($input->GetOpenid());
 //dpm($input->GetNotify_url());
  //dpm($input);
 //dpm(WxPayConfig::CURL_PROXY_HOST);
  //dpm(md5('oOTG9t-1993DOYJC23P7w_Jj6BNQ'));
  */

  return $form;
}

function distriction_insert($form, &$form_state) {
  insert_code();
  drupal_set_message('行政区划插入结束');
}

function insert_code() {
  //$tax_voc = taxonomy_vocabulary_machine_name_load('china_administrative_divisions_taxonomy');
  //$filename = drupal_get_path('module', 'wechat_py_shopping') . '/行政区划代码';
  //$data = file_get_contents($filename);
  //$data_array = preg_split('/\s+/', $data);

  //insert_province_term($tax_voc, $data_array);
  //insert_city_to_term($tax_voc, $data_array);
  //insert_zhixiashi_county_to_term($tax_voc, $data_array);

  //drupal_set_time_limit(7200);
  //insert_county_to_term($tax_voc, $data_array);
  //drupal_set_time_limit(300);
}


function insert_province_term($tax_voc, $data_array) {

  $plevel_weight = 0;
  foreach ($data_array as $id => $code) {
    if(preg_match('/^[0-9]+$/', $code)) { //find 0-9 number it's area code
      if(preg_match('/0000$/', $code)) {
        $plevel1_code = $code;
        $plevel1_name = $data_array[$id + 1];

        $term = new stdClass();
        $term->name = $plevel1_name;
        $term->vid = $tax_voc->vid;
        $term->parent = 0;
        $term->weight = $plevel_weight;
        $plevel_weight++;
        $ret_code = taxonomy_term_save($term);

        if ($ret_code == SAVED_NEW) {

          $plevel1_tid = $term->tid;
          $pleve1_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
          $pleve1_wrapper->field_division_code->set($plevel1_code);

          if(preg_match('/^北京市$/', $plevel1_name) || 
             preg_match('/^天津市$/', $plevel1_name) || 
             preg_match('/^上海市$/', $plevel1_name) ||
             preg_match('/^重庆市$/', $plevel1_name)) {
            $pleve1_wrapper->field_division_category->set('0'); //直辖市
          } else {
            $pleve1_wrapper->field_division_category->set('1'); //省
          }

          $pleve1_wrapper->save();
        }
      }
    }
  }
}

function insert_city_to_term($tax_voc, $code_array) {
  //$terms = taxonomy_get_tree($tax_voc->vid, 0);

  $loop_count = 0;
  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', 'taxonomy_term')
        //->entityCondition('bundle', 'china_administrative_divisions_taxonomy')
        ->propertyCondition('vid', $tax_voc->vid)
        ->propertyOrderBy('weight');

  $result = $query->execute();
  foreach ($result['taxonomy_term'] as $tid) {
    $wrapper = entity_metadata_wrapper('taxonomy_term', $tid->tid);
    $pcode = $wrapper->field_division_code->value();
    $pid = $tid->tid;

    $h_code = substr($pcode, 0, 2);
    foreach ($code_array as $id => $code) {
      if(preg_match('/^[0-9]+$/', $code)) { //find 0-9 number it's area code
        $row_code = $code;
        $row_name = $code_array[$id + 1];

        if (preg_match('/^' . $h_code . '..00$/', $row_code)) {
          if (!preg_match('/0000$/', $row_code)) {
            if (preg_match('/^市辖区$/', $row_name) ||
                preg_match('/^县$/', $row_name)) {
              continue;
            } else {
              $term = new stdClass();
              $term->name = $row_name;
              $term->vid = $tax_voc->vid;
              $term->parent = $pid;
              $term->weight = $loop_count;
              $loop_count ++;
              $ret_code = taxonomy_term_save($term);
              if ($ret_code == SAVED_NEW) {
                $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
                $term_wrapper->field_division_code->set($row_code);
                if (preg_match('/0100$/', $row_code)) {
                  $term_wrapper->field_division_category->set('2'); //省会
                } else {
                  $term_wrapper->field_division_category->set('3'); //地级市
                }

                $term_wrapper->save();
              }
              unset($term);
              //dpm($row_code . ':' . $row_name);
            }

          }
        }
      }
    }


  }

 //dpm($loop_count);

}

function insert_zhixiashi_county_to_term($tax_voc, $code_array) {
  $loop_count = 0;
  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', 'taxonomy_term')
        //->entityCondition('bundle', 'china_administrative_divisions_taxonomy')
        ->propertyCondition('vid', $tax_voc->vid)
        ->propertyOrderBy('weight');
  $result = $query->execute();
  foreach ($result['taxonomy_term'] as $tid) {
    $wrapper = entity_metadata_wrapper('taxonomy_term', $tid->tid);
    //dpm($wrapper->getPropertyInfo());
    //dpm($wrapper->parent->value());
    $count = count($wrapper->parent->value());
    if ($count == 0) {
      $name = $wrapper->name->value();
      if (($name == '北京市') ||
          ($name == '天津市') ||
          ($name == '上海市') ||
          ($name == '重庆市')) {
        $pcode = $wrapper->field_division_code->value();
        $pid = $tid->tid;
        $h_code = substr($pcode, 0, 2);

        foreach ($code_array as $id => $code) {
          if(preg_match('/^[0-9]+$/', $code)) { //find 0-9 number it's area code
            $row_code = $code;
            $row_name = $code_array[$id + 1];
            if (preg_match('/^' . $h_code . '....$/', $row_code)) {
              if (preg_match('/0000$/', $row_code) ||
                  preg_match('/0100$/', $row_code) ||
                  preg_match('/0200$/', $row_code)) {
                continue;
              } else {
                $term = new stdClass();
                $term->name = $row_name;
                $term->vid = $tax_voc->vid;
                $term->parent = $pid;
                $term->weight = $loop_count;
                $loop_count ++;
                $ret_code = taxonomy_term_save($term);
                if ($ret_code == SAVED_NEW) {
                  $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
                  $term_wrapper->field_division_code->set($row_code);
                  if (preg_match('/区$/', $row_name)) {
                    $term_wrapper->field_division_category->set('4'); //市区
                  } else {
                    $term_wrapper->field_division_category->set('3'); //地级市
                  }

                  $term_wrapper->save();
                }
                unset($term);
                //dpm($row_code . ':' . $row_name);
              }
            }
          }
        }

      }
    }
  }

 //dpm($loop_count);
}


function insert_county_to_term($tax_voc, $code_array) {
  $loop_count = 0;

  $terms = taxonomy_get_tree($tax_voc->vid, 0);
  foreach ($terms as $term) {
    if ($term->parents[0] == 0) {
      if (($term->name == '北京市') ||
          ($term->name == '天津市') ||
          ($term->name == '上海市') ||
          ($term->name == '重庆市')) {
        continue;
      } else {
        $child = taxonomy_get_children($term->tid, $tax_voc->vid);
        foreach ($child as $ch_term) {
          $wrapper = entity_metadata_wrapper('taxonomy_term', $ch_term->tid);
          $pcode = $wrapper->field_division_code->value();
          $pid = $ch_term->tid;

          $h_code = substr($pcode, 0, 4);

          foreach ($code_array as $id => $code) {
            if (preg_match('/^[0-9]+$/', $code)) { //find 0-9 number it's area code
              $row_code = $code;
              $row_name = $code_array[$id + 1];
              if (preg_match('/^' . $h_code . '..$/', $row_code)) {
                if (preg_match('/^' . $h_code . '00$/', $row_code)) {
                  continue;
                }

                if (preg_match('/^市辖区$/', $row_name)) {
                  continue;
                }

                $term = new stdClass();
                $term->name = $row_name;
                $term->vid = $tax_voc->vid;
                $term->parent = $pid;
                $term->weight = $loop_count;
                $loop_count ++;
                $ret_code = taxonomy_term_save($term);
                if ($ret_code == SAVED_NEW) {
                  $term_wrapper = entity_metadata_wrapper('taxonomy_term', $term);
                  $term_wrapper->field_division_code->set($row_code);
                  if (preg_match('/区$/', $row_name)) {
                    $term_wrapper->field_division_category->set('4'); //市区
                  } elseif (preg_match('/市$/', $row_name)) {
                    $term_wrapper->field_division_category->set('5'); //县级市
                  } else {
                    $term_wrapper->field_division_category->set('6'); //县
                  }
                  $term_wrapper->save();
                }
                unset($term);
                //dpm($row_code . ':' . $row_name);
              }
            }
          }
        }
      }
    }
  }

 //dpm($loop_count);
}

function curl_test($url){
  $xml = '<xml><appid><![CDATA[wx9ee4070dc39cdedb]]></appid><attach><![CDATA[test]]></attach><body><![CDATA[test]]></body><goods_tag><![CDATA[test]]></goods_tag><mch_id>1297611801</mch_id><nonce_str><![CDATA[qhck9ce4q1gu6rympi33wsjeb6bye0ne]]></nonce_str><notify_url><![CDATA[http://paysdk.weixin.qq.com/example/notify.php]]></notify_url><openid><![CDATA[oOTG9t2L0J3Pw-z5e3E4dpvVnpMc]]></openid><out_trade_no>123370240220150913231225</out_trade_no><spbill_create_ip><![CDATA[114.246.91.251]]></spbill_create_ip><time_expire>20150913232225</time_expire><time_start>20150913231225</time_start><total_fee>1</total_fee><trade_type><![CDATA[JSAPI]]></trade_type><sign><![CDATA[6FC98E22FBAF680D8612C7AEBD11E580]]></sign></xml>';

	$ch = curl_init();
  //设置超时
  curl_setopt($ch, CURLOPT_TIMEOUT, 30);
		
  curl_setopt($ch,CURLOPT_URL, $url);
  curl_setopt($ch,CURLOPT_SSL_VERIFYPEER,TRUE);
  curl_setopt($ch,CURLOPT_SSL_VERIFYHOST,2);//严格校验
  //curl_setopt($ch, CURLOPT_CAINFO,  '/usr/share/ca-certificates/mozilla/ca-bundle.crt'); 
    
  //设置header
  curl_setopt($ch, CURLOPT_HEADER, FALSE);
  //要求结果为字符串且输出到屏幕上
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
	
		//post提交方式
  curl_setopt($ch, CURLOPT_POST, TRUE);
  curl_setopt($ch, CURLOPT_POSTFIELDS, $xml);
  //运行curl
  $data = curl_exec($ch);
 //dpm($data);
  //返回结果
  if($data){
    curl_close($ch);
    return $data;
    watchdog('jsapi lib', 'data info <pre>@data</pre>', array('@data' => print_r($data, TRUE)));
  } else { 
    $error = curl_errno($ch);
    $info = curl_getinfo($ch);
    watchdog('jsapi lib', 'curl error info <pre>@data</pre>', array('@data' => print_r($info, TRUE)));
    
    curl_close($ch);
    throw new WxPayException("curl出错，错误码:$error");
  }

}

function is_base64_encoded($data) {
  if (preg_match('%^[a-zA-Z0-9/+]*={0,2}$%', $data)) {
      return TRUE;
  } else {
      return FALSE;
  }
}


function utf8_bytes($cp){

  if ($cp > 0x10000){
    # 4 bytes
    return	chr(0xF0 | (($cp & 0x1C0000) >> 18)).
      chr(0x80 | (($cp & 0x3F000) >> 12)).
      chr(0x80 | (($cp & 0xFC0) >> 6)).
      chr(0x80 | ($cp & 0x3F));
  }else if ($cp > 0x800){
    # 3 bytes
    return	chr(0xE0 | (($cp & 0xF000) >> 12)).
      chr(0x80 | (($cp & 0xFC0) >> 6)).
      chr(0x80 | ($cp & 0x3F));
  }else if ($cp > 0x80){
    # 2 bytes
    return	chr(0xC0 | (($cp & 0x7C0) >> 6)).
      chr(0x80 | ($cp & 0x3F));
  }else{
    # 1 byte
    return chr($cp);
  }
}


function get_merchant_category_all() {
  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $req_url = t(
    //variable_get('所有分类-商品分类-微信小店'),
    variable_get('所有状态-商品-微信小店'),
    array('@ACCESS_TOKEN' => variable_get('access_token'))
  );

  $post = array(
    'status' => 0,
  );

  $json = json_encode($post,
    JSON_HEX_TAG |
    JSON_HEX_APOS |
    JSON_HEX_AMP |
    JSON_HEX_QUOT |
    JSON_UNESCAPED_UNICODE);

  $result = wechat_php_curl_https_post($req_url, $json);
  if (!$result) {
    watchdog('get all wechat category',
      'error in @line line:@filename',
      array(
        '@line' => __LINE__,
        '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return;
  }

  $json_value = json_decode($result);

  if($json_value->errcode != 0) {
    watchdog('get all wechat category',
      'errmsg <pre>@print_r</pre> in @line line @filename', 
      array(
        '@print_r' => print_r($json_value->errmsg, TRUE),
        '@line' => __LINE__,
        '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
  }

  return $json_value;
}

function term_cmp_termid($a, $b) {
    if ($a->weight == $b->weight) {
        return 0;
    }
    return ($a->weight < $b->weight) ? -1 : 1;
    //return intval($a->weight) - intval($b->weight);
}

/**
 * End of wechat_merchant_category_form.inc file name
 */
