<?php

//page call for my account info
function wechat_mobile_shopping_my_doc_page() {

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

  $state = $_GET['state'];
  $md5openid = '';
  if (preg_match('/^101next/', $state)) {
    $split = preg_split('/^101next/', $state); //remove 101
    //watchdog('mobile shopping', 'my doc split = <pre>@data</pre>', array('@data' => print_r($split, TRUE)));
    $md5openid = $split[1];
  }
  //get user OPENID
  //get qr_scan md5id for 40029 redirect error
  $code = isset($_GET['code']) ? $_GET['code'] : '';
  $json = oauth2_get_accss_token($code, $md5openid);
  
  if ($json == null) {
    $page['title'] = '个人中心';
    $page['error_info'] = '微信加载页面缓慢，请退出页面重新进入';
    return $page;
  }

  //watchdog('mobile shopping', 'oauth2 = <pre>@data</pre>', array('@data' => print_r($json, TRUE)));
  if (preg_match('/^100$/', $state)) {
    //normally access from shopping home page and user id can be getted
  } else if (preg_match('/^101next/', $state)) {
    //access from term filter dialog
    $split = preg_split('/^101next/', $state); //remove 101
    //watchdog('mobile shopping', 'my doc split = <pre>@data</pre>', array('@data' => print_r($split, TRUE)));
    $md5openid = $split[1];
    //check md5openid and insert to friends table
    insert_myself_to_md5_friends_table($json->openid, $md5openid, $json->access_token);
  } else {
    //nothing to do for state error
    $page['title'] = '个人中心';
    $page['error_info'] = '页面state: ' . $state . '错误';
    return $page;
  }

  //get Openid by code
  $page['xyz'] = base64_encode($json->openid);    //openid should be encoded by base64


  $friends = get_friends($json->openid);
  if (count($friends)) {
    $page['friends'] = $friends;
  }

  $page['mxweixin_qr_code_image'] = file_create_url(drupal_get_path('module', 'wechat_py_mobile') . '/imgs/梦乡网服务号.png');

  $my_points = get_my_points($json->openid, $json->access_token);
  if (count($my_points)) {
    $page['my_points'] = $my_points;
  }

  $mobile_shopping_home_url = t(
    variable_get('oauth2 redirect request'),
    array(
      '@APPID' => variable_get('wechat_py_AppID'),
      '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/new-tpl',
      '@SNSAPI' => "snsapi_base",
      '@STATE' => "100",
    )
  );
  $page['mobile_shopping_home_page'] = $mobile_shopping_home_url;
  $page['title'] = '个人中心';

  return $page;
}

function deliver_shopping_my_doc_html_page($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile_shopping_my_doc.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_shopping_my_doc.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_my_doc_page',
    '#page' => $page,
    '#styles' => $css,
    '#scripts' => $js,
  );

  print drupal_render($render);
}

//get oauth2 access_token by redirect code, and finished if scope is snsapi_base
function oauth2_get_accss_token($code, $md5openid) {
  
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

      watchdog('mobile shopping', 'redirect 40029 error in my doc');

      $state = "101next" . $md5openid;
      $my_doc_40029_req_url = t(
        variable_get('oauth2 redirect request'),
        array(
          '@APPID' => variable_get('wechat_py_AppID'),
          '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/my-doc',
          '@SNSAPI' => "snsapi_userinfo",
          '@STATE' => $state,
        )
      );

      drupal_goto($my_doc_40029_req_url);
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
//  if(isset($json_value->errcode)){
//    watchdog('mobile shopping', 'error code: @error and errmsg: @errmsg at @line in @filename',
//      array(
//      '@error' => $json_value->errcode,
//      '@errmsg' => $json_value->errmsg,
//      '@line' => __LINE__,
//      '@filename' => __FILE__,
//      ),
//      $severity = WATCHDOG_ERROR);
//    return null;
//  }
  return $json_value;

}


//oauth2 to get user info, nick name and head image
function oauth2_get_user_info($openid, $access_token) {

  $req_url = t(
    variable_get('get oauth2 user info'),
    array(
      '@ACCESS_TOKEN' => $access_token,
      '@OPENID' => $openid,
    )
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_get($req_url);
  if ($result == Null)
  {
    watchdog('mobile shopping', 'error: oauth2 get user info return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  //get user info.
  $json_value = json_decode($result);
  if(isset($json_value->errcode)){

    watchdog('mobile shopping', 'request uri = <pre>@data</pre>', array('@data' => print_r($_SERVER['REQUEST_URI'], TRUE)));
    watchdog('mobile shopping', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }
  return $json_value;

}
function insert_myself_to_md5_friends_table($openid, $md5openid, $access_token) {

  global $base_url;

  if ($md5openid == md5($openid)) {
    //send to myself
    return;
  }

  $usr_info = oauth2_get_user_info($openid, $access_token);
  //module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  //$usr_info = wechat_api_get_user_info($openid);
  $myself_headimage = '';
  $myself_nickname = '';
  if($usr_info != '') {
    //watchdog('mobile shopping', 'user info = <pre>@data</pre>', array('@data' => print_r($usr_info, TRUE)));

    if (property_exists($usr_info, "headimgurl")) {
      $myself_headimage = $usr_info->headimgurl;
      if ($myself_headimage == '') {
        $myself_headimage = file_create_url(drupal_get_path('module', 'wechat_py_mobile') . '/imgs/friends_for_anonymous.png');
      }
    } else {
      $myself_headimage = file_create_url(drupal_get_path('module', 'wechat_py_mobile') . '/imgs/friends_for_anonymous.png');
    }

    if (property_exists($usr_info, "nickname")) {
      $myself_nickname = $usr_info->nickname;
      if ($myself_nickname == '') {
        $myself_nickname = "匿名用户";
      }
    } else {
      $myself_nickname = "匿名用户";
    }

  } else {
    $myself_headimage = file_create_url(drupal_get_path('module', 'wechat_py_mobile') . '/imgs/friends_for_anonymous.png');
    $myself_nickname = "匿名用户";
  }

  $query = db_select('mobile_shopping_user_points_table', 't')
         ->condition('MD5', $md5openid)
         ->fields('t', array(
            'openid',
            'total_points',
            'curr_points',
            ));
  $result = $query->execute();
  $count = $result->rowCount();

  if ($count) {
    foreach ($result as $row) {
      //if you have registered to your friends table, then do nothing
      $f_query = db_select('mobile_shopping_user_friends_table', 't')
             ->condition('openid', $row->openid)
             ->condition('MD5', $md5openid)
             ->condition('f_openid', $openid)
             ->fields('t', array(
                'f_openid',
                ));

      $f_result = $f_query->execute();
      $f_count = $f_result->rowCount();
      if ($f_count) {
        return;
      }

      //get $openid head image and nick name, then insert to friends table and add total points and curr points 1
      db_update('mobile_shopping_user_points_table')
        ->condition('openid', $row->openid)
        ->condition('MD5', $md5openid)
        ->fields(array(
          'total_points' => $row->total_points + 50,
          'curr_points' => $row->curr_points + 50,
        ))->execute();

      db_insert('mobile_shopping_user_friends_table')
        ->fields(array(
          'openid' => $row->openid,
          'MD5' => $md5openid,
          'f_openid' => $openid,
          'f_openid_nick_name' => base64_encode($myself_nickname),
          'f_openid_head_img_url' => $myself_headimage,
          'regist_time' => time(),
        ))->execute();

      //send message to qrscan md5openid user for has points
      $my_doc_req_url = t(
        variable_get('oauth2 redirect request'),
        array(
          '@APPID' => variable_get('wechat_py_AppID'),
          '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/my-doc',
          '@SNSAPI' => "snsapi_base",
          '@STATE' => "100",
        )
      );
      $element = array();
      $post_data['touser'] = $row->openid;
      $post_data['template_id'] = '8cOtlRg1jPZwlLfmzXUtQIt8ASquJcxtVLEZPCJK8lg';  //积分提醒模版
      $post_data['url'] = $my_doc_req_url;  //return to my doc
      $element['first'] = array(
        'value' => "您有新的积分啦",
        'color' => "#173177",
      );

      $element['keyword1'] = array(
        'value' => "5分",
      );

      $time_end = date('Y年m月d日 H:i',time());
      $element['keyword2'] = array(
        'value' => $time_end,
      );

      $element['remark'] = array(
        'value' => "您的朋友【" . $myself_nickname . "】相当给力!",
      );

      $post_data['data'] = $element;

      $json_data = json_encode($post_data,
                               JSON_HEX_TAG |
                               JSON_HEX_APOS |
                               JSON_HEX_AMP |
                               JSON_HEX_QUOT |
                               JSON_UNESCAPED_UNICODE);

      module_load_include('inc', 'wechat_api', 'wechat_api_php5');

      $token_url = t(
        variable_get('send template message'),
        array('@ACCESS_TOKEN' => variable_get('access_token'))
      );

      $result = wechat_php_curl_https_post($token_url, $json_data);
      if (!$result)
      {
        watchdog('send_template_msg_to_service', 'return null in @line line:@filename',
          array(
          '@line' => __LINE__,
          '@filename' => __FILE__,
          ),
          $severity = WATCHDOG_ERROR);
      }

      $json_value = json_decode($result);
      if($json_value->errcode){
        watchdog('send_template_msg_to_service', 'error code: @error and errmsg: @errmsg at @line in @filename',
          array(
          '@error' => $json_value->errcode,
          '@errmsg' => $json_value->errmsg,
          '@line' => __LINE__,
          '@filename' => __FILE__,
          ),
          $severity = WATCHDOG_ERROR);
      }
    }
  }

}

function get_my_points($openid, $access_token) {
  $element = array();
  $query = db_select('mobile_shopping_user_points_table', 't')
         ->condition('openid', $openid)
         ->fields('t', array(
            'total_points',
            'curr_points',
            'points_desc',
            'qr_scan_image_url',
            'orig_head_img_url',
            'orig_nick_name',
            ));
  $result = $query->execute();
  $count = $result->rowCount();

  if ($count) {

    foreach ($result as $point) {
      $element['total_points'] = $point->total_points;
      $element['curr_points'] = $point->curr_points;
      $element['points_desc'] = $point->points_desc;
      $element['qr_scan_image_url'] = $point->qr_scan_image_url;
      $element['orig_head_img_url'] = $point->orig_head_img_url;
      $element['orig_nick_name'] = base64_decode($point->orig_nick_name);
    }

    $myself_nickname = '';
    $myself_headimage = '';
    $usr_info = oauth2_get_user_info($openid, $access_token);
    //module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
    //$usr_info = wechat_api_get_user_info($openid);

    //check if head image and nick name changed
    if($usr_info != '') {
      $myself_headimage = $usr_info->headimgurl;
      $myself_nickname = $usr_info->nickname;

      if ($myself_headimage != $element['orig_head_img_url'] ||
          $myself_nickname != $element['orig_nick_name']) {
        $qr_scan_image_file = compose_qr_scan_image($openid, $myself_headimage, $myself_nickname, 'url');
        $element['qr_scan_image_url'] = $qr_scan_image_file;  //update qr scan image url
        

        db_update('mobile_shopping_user_points_table')
          ->condition('openid', $openid)
          ->fields(array(
            'qr_scan_image_url' => $qr_scan_image_file,
            'orig_head_img_url' => $myself_headimage,
            'orig_nick_name' => base64_encode($myself_nickname),
          ))->execute();
      }
    }

  } else {
    //creat scan image, then insert total poinsts and curr_points == 0
    $element = initial_my_points_table($openid, $access_token);
  }


  return $element;
}

function compose_qr_scan_image($openid, $head_image_url, $nick_name, $flag) {

  global $base_url;

  $md5id = md5($openid);
  $scheme = variable_get('file_default_scheme', 'public') . '://';

  //finally generate qr_scan_image_url
  $file_name = $scheme . "point_qrscan_image/" . $md5id . ".png";

  $bp_process_paramter = array(
    'openid' => $openid,
    'file_name' => $file_name,
    'head_image_url' => $head_image_url,
    'nick_name' => $nick_name,
    'flag' => $flag,
  );
  background_process_start('background_process_compose_qr_scan_image', $bp_process_paramter);

  return file_create_url($file_name);   //need absolutely url
}

function initial_my_points_table($openid, $access_token) {
  $point_desc = "
    亲爱的朋友，欢迎加入梦乡网积分系统，请转发上面的图片给好友，当他／她收到图片后，长按图片中的二维码，进入梦乡网服务号。同时您就可以得到50个积分。积分可以在微商城中抵扣部分商品价格。参加梦乡积分游戏，给所有你认识的朋友转发吧！";
  $total_points = 50;
  $curr_points = 50;

  $myself_nickname = '';
  $myself_headimage = '';

  $usr_info = oauth2_get_user_info($openid, $access_token);
  //module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  //$usr_info = wechat_api_get_user_info($openid);
  //watchdog('mobile shopping', 'my doc = <pre>@data</pre>', array('@data' => print_r($openid, TRUE)));

  if($usr_info != '') {
    $myself_headimage = $usr_info->headimgurl;
    $myself_nickname = $usr_info->nickname;
    $qr_scan_image_file = compose_qr_scan_image($openid, $myself_headimage, $myself_nickname, 'url');
  } else {
    $myself_headimage = drupal_get_path('module', 'wechat_py_mobile') . '/imgs/mxweixin_qr_scan_head.jpg';
    $myself_nickname = "匿名用户";
    $qr_scan_image_file = compose_qr_scan_image($openid, $myself_headimage, $myself_nickname, 'local');
  }

  //watchdog('mobile shopping', 'qr scan image = <pre>@data</pre>', array('@data' => print_r($qr_scan_image_file, TRUE)));
  $element['total_points'] = $total_points;
  $element['curr_points'] = $curr_points;
  $element['points_desc'] = $point_desc;
  $element['qr_scan_image_url'] = $qr_scan_image_file;
  $element['orig_head_img_url'] = $myself_headimage;
  $element['orig_nick_name'] = $myself_nickname;

  db_insert('mobile_shopping_user_points_table')
    ->fields(array(
      'openid' => $openid,
      'MD5' => md5($openid),
      'total_points' => $total_points,
      'curr_points' => $curr_points,
      'points_desc' => $point_desc,
      'qr_scan_image_url' => $qr_scan_image_file,
      'orig_head_img_url' => $myself_headimage,
      'orig_nick_name' => base64_encode($myself_nickname),
    ))->execute();

  return $element;
}

function get_friends($openid) {

  $element = array();
  $query = db_select('mobile_shopping_user_friends_table', 't')
         ->condition('openid', $openid)
         ->orderBy('t.regist_time', 'DESC')
         ->fields('t', array(
            'f_openid_nick_name',
            'f_openid_head_img_url',
            'regist_time',
            ));
  $result = $query->execute();

  foreach ($result as $id => $friend) {
    $element[$id]['nick_name'] = base64_decode($friend->f_openid_nick_name);
    $element[$id]['head_img'] = $friend->f_openid_head_img_url;
    $element[$id]['regist_time'] = date('Y年m月d日 H:i', $friend->regist_time);
  }

  return $element;
}
/**
 * End of wechat_mobile_shopping_my_doc_page.inc file name
 */

