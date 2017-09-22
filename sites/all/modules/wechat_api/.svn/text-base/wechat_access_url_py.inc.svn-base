<?php

/**
 * Check signature for legal user
 * signature、timestamp、nonce、echostr
 * 1. 将token、timestamp、nonce三个参数进行字典序排序
 * 2. 将三个参数字符串拼接成一个字符串进行sha1加密
 * 3. 开发者获得加密后的字符串可与signature对比，标识该请求来源于微信
 */
function checkSignature()
{
  $signature = filter_input(INPUT_GET, 'signature', FILTER_SANITIZE_SPECIAL_CHARS);
  $timestamp = filter_input(INPUT_GET, 'timestamp', FILTER_SANITIZE_SPECIAL_CHARS);
  $nonce = filter_input(INPUT_GET, 'nonce', FILTER_SANITIZE_SPECIAL_CHARS);
  //$signature = $_GET["signature"];
  //$timestamp = $_GET["timestamp"];
  //$nonce = $_GET["nonce"];  

  $token = variable_get('wechat_py_Token');
  $tmpArr = array($token, $timestamp, $nonce);
  sort($tmpArr, SORT_STRING);
  $tmpStr = implode( $tmpArr );
  $tmpStr = sha1( $tmpStr );

  if( $tmpStr == $signature ){
    return true;
  }else{
    return false;
  }
}

/**
 * Convert xml object to array
 */
function xml2array($xml)
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
 * hook_menu page callback for wechat access url entrance
 */
function menu_wechat_access_py_url(){

  $echostr = filter_input(INPUT_GET, 'echostr', FILTER_SANITIZE_SPECIAL_CHARS);

  //Retrun echostr for wechat server certification
  if(isset($echostr) || !is_null($echostr) || !empty($echostr)){
    echo $echostr;
    exit;
  }

  //check signatrue, and parse wechat message
  if(checkSignature()){
    $xmldata = file_get_contents("php://input"); //get xml data
    $result = wechat_api_py_dispatch_message($xmldata);  // handle received message 
    echo $result;
  }else{
    watchdog('wechat signature', 'check signature error in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    echo '';
  }
  return;
}

function wechat_api_py_dispatch_message($xmldata){
  $result = '';

  //libxml_disable_entity_loader is to prevent XML eXternal Entity Injection,
  //the best way is to check the validity of xml by yourself. 
  //use libxml_disable_entity_loader is ok now.
  libxml_disable_entity_loader(true);
  $xmldata = simplexml_load_string($xmldata, 'SimpleXMLElement', LIBXML_NOCDATA);
  //watchdog('wechat recv message', 'postobj <pre>@print_r</pre>', array('@print_r' => print_r($xmldata, TRUE)));
  $postArray = xml2array($xmldata);
  //watchdog('wechat recv message', 'postArray <pre>@print_r</pre>', array('@print_r' => print_r($postArray, TRUE)));

  //$MsgType = (string)$xmldata->MsgType;
  $MsgType = $postArray['MsgType'];

  $recv_msg = variable_get('wechat_recv_msg');


  if($MsgType == 'event'){
    //$event = (string)$xmldata->Event;
    $event = $postArray['Event'];
    watchdog('wechat recv message',
             'msg type @msgtype and event type @event',
             array('@msgtype' => $MsgType, '@event' => $event));
    $callback_func = $recv_msg[$MsgType][$event];
    if(!isset($callback_func)){
      watchdog('wechat recv message', 'can not find msg type @msgtype and event @event in recv msg callback array',
                array('@msgtype' => $MsgType, '@event' => $event));

      return $result;
    }
  }else{
    $callback_func = $recv_msg[$MsgType];
    watchdog('wechat recv message', 'msg type @msgtype ', array('@msgtype' => $MsgType));
    if(!isset($callback_func)){
      watchdog('wechat recv message', 'can not find msg type @msgtype in recv msg callback array',
                array('@msgtype' => $MsgType));

      return $result;
    }
  }
  $cb = (string)$callback_func;
  //watchdog('wechat recv message', 'callback function @msgtype ', array('@msgtype' => $cb));
  //callback function invoked by message type and event
  $result = $callback_func($postArray);

  return $result;

}

/**
 * Callback function when receive subscribe event message from wechat end user. Refer to wechat_api.install
 */
function wechat_recv_event_subscribe_msg_callback($postArray){

    $query = db_select('wechat_py_welcome_page_table', 't')->fields('t', array('welcome_text'));
    $result = $query->execute();
    $row = $result->fetchAssoc();

    $content = $row['welcome_text'];
    if (is_null($content))
    {
      $content = t('你好，欢迎关注梦乡平遥游！');
    }

  //watchdog('wechat recv message', 'postArray <pre>@print_r</pre>', array('@print_r' => print_r($postArray, TRUE)));
  collect_event_statistic($postArray);
/**
 * User subscrib by scan bar code, eventkey is qrscene_ plus scene number
Array
(
    [ToUserName] => gh_849bfca55031
    [FromUserName] => oOTG9t2L0J3Pw-z5e3E4dpvVnpMc
    [CreateTime] => 1428580638
    [MsgType] => event
    [Event] => subscribe
    [EventKey] => qrscene_2
    [Ticket] => gQHO7zoAAAAAAAAAASxodHRwOi8vd2VpeGluLnFxLmNvbS9xL1FreUpsTTNsSXpwYXR2T3NrMkw5AAIElWcmVQMECAcAAA==
)
 */
  
  //send media-text message to user
  //save user info into user table
  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  $result = wechat_api_get_user_info($postArray['FromUserName']);

  if($result == ''){
    watchdog('get user info',
             '获取用户信息发生错误! user open id = @openid',
             array('@openid' => $result->openid),
             $severity = WATCHDOG_ERROR);

  }else{

    //insert user info, first check if openid exist in the table
    $squery = db_select('wechat_py_subscribe_user_table', 't')
      ->condition('t.openid', $result->openid)
      ->fields('t', array('openid'))
      ->execute();

    $nums = $squery->rowCount();
    if($nums == 0) {
      //transaction for db insert
      $transaction = db_transaction();
      try {
        //convert emoji to base64 code 
        $emoji = base64_encode($result->nickname);
        db_insert('wechat_py_subscribe_user_table')
          ->fields(array(
            'openid' => $result->openid,
            'subscribe' => $result->subscribe,
            'nickname' => $emoji,
            'sex' => $result->sex,
            'language' => $result->language,
            'city' => $result->city,
            'province' => $result->province,
            'country' => $result->country,
            'headimgurl' => $result->headimgurl,
            'subscribe_time' => $result->subscribe_time,
            'unionid' => '')) //Read wechat api unionid doc
          ->execute();
      }
      catch(Exception $e) {
        $transaction->rollback();
        $errorinfo = $e->errorInfo;
        watchdog('get user info',
                 'insert user openid: @openid info failed = <pre>@error</pre>',
                 array('@openid' => $result->openid, 
                       '@error' => print_r($errorinfo, TRUE)));
      }
    } else {
      watchdog('get user info', 'user @openid has exists in table', array('@openid' => $result->openid));
    }

    /**
     * check user points 
     **/
    $query = db_select('mobile_shopping_user_points_table', 't')
        ->condition('t.openid', $result->openid)
        ->fields('t', array('openid'))
        ->execute();
    $count = $query->rowCount();

    $point_desc = "
    亲爱的朋友，欢迎加入梦乡网积分系统，请转发上面的图片给好友，当他／她收到图片后，长按图片中的二维码，进入梦乡网服务号。同时您就可以得到50个积分。积分可以在微商城中抵扣部分商品价格。参加梦乡积分游戏，给所有你认识的朋友转发吧！";
    //add 50 points for new register user
    if ($count == 0) {
        db_insert('mobile_shopping_user_points_table')
        ->fields(array(
          'openid' => $result->openid,
          'MD5' => md5($result->openid),
          'total_points' => 50,
          'curr_points' => 50,
          'points_desc' => $point_desc,
          'qr_scan_image_url' => "",
          'orig_head_img_url' => "unknown",
          'orig_nick_name' => "unknown",
        ))->execute();

        $content .= $content . ' 您已有50个积分，可用于在线商城消费。';

        module_load_include('inc', 'wechat_api', 'wechat_api_resp_msg_tpl');
        $resultStr = wechat_api_resp_text_message($postArray, $content);

        return $resultStr;
    }
  }


  module_load_include('inc', 'wechat_api', 'wechat_api_resp_msg_tpl');
  $resultStr = wechat_api_resp_text_message($postArray, $content);

  return $resultStr;
}

/**
 * Callback function when receive unsubscribe event message from wechat end user. Refer to wechat_api.install
 *
 * <xml>
 * <ToUserName><![CDATA[toUser]]></ToUserName>
 * <FromUserName><![CDATA[FromUser]]></FromUserName>
 * <CreateTime>123456789</CreateTime>
 * <MsgType><![CDATA[event]]></MsgType>
 * <Event><![CDATA[subscribe]]></Event>
 * </xml>
 */
function wechat_recv_event_unsubscribe_msg_callback($postArray){

  $resultStr = '';
  $user_openid = $postArray['FromUserName'];
  $time = $postArray['CreateTime'];
  db_delete('wechat_py_subscribe_user_table')
  ->condition('openid', $user_openid)
  ->execute();
  /*
  db_update('wechat_py_subscribe_user_table')
  ->fields(array(
      'subscribe' => 0,
    ))
  ->condition('openid', $user_openid)
  ->execute();
  */

  collect_event_statistic($postArray);

  //watchdog('wechat unsubscribe event',
  //         'user openid @openid time @time unsubscribe',
  //         array('@openid' => $user_openid, '@time' => date('Y年m月d日G点i分s秒', $time)));

  return $resultStr;
}

/**
 * Callback function when receive subscribe event message from wechat end user. Refer to wechat_api.install
 * message of received template:
 * <xml>
 *  <ToUserName><![CDATA[toUser]]></ToUserName>
 *  <FromUserName><![CDATA[fromUser]]></FromUserName> 
 *  <CreateTime>1348831860</CreateTime>
 *  <MsgType><![CDATA[text]]></MsgType>
 *  <Content><![CDATA[this is a test]]></Content>
 *  <MsgId>1234567890123456</MsgId>
 * </xml>
 */
function wechat_recv_text_msg_callback($postArray){
  $resultStr = '';
  $FromUserName = $postArray['FromUserName'];
  $text = $postArray['Content'];
  watchdog('wechat recv message', 'got a text message from user @user: @text',
            array('@user' => $FromUserName, '@text' =>$text));
  return $resultStr;
}

/**
 * Callback function when scan bar code event message from registered user
 * [ToUserName] => gh_849bfca55031
 *   [FromUserName] => oOTG9t2L0J3Pw-z5e3E4dpvVnpMc
 *   [CreateTime] => 1428577830
 *   [MsgType] => event
 *   [Event] => SCAN
 *   [EventKey] => 1
 *   [Ticket] => gQHt7zoAAAAAAAAAASxodHRwOi8vd2VpeGluLnFxLmNvbS9xL1UwelZNdDNsY0RvSkVlSUZ6Mkw5AAIEOl0mVQMECAcAAA==
 */
function wechat_recv_event_scan_msg_callback($postArray){
  $resultStr = '';
  collect_event_statistic($postArray);
  //watchdog('wechat recv message', 'postArray <pre>@print_r</pre>', array('@print_r' => print_r($postArray, TRUE)));
  /**
   * Registered user scan bar code, event key only has scene number
    Array
    (
        [ToUserName] => gh_849bfca55031
        [FromUserName] => oOTG9t2L0J3Pw-z5e3E4dpvVnpMc
        [CreateTime] => 1428581190
        [MsgType] => event
        [Event] => SCAN
        [EventKey] => 2
        [Ticket] => gQHO7zoAAAAAAAAAASxodHRwOi8vd2VpeGluLnFxLmNvbS9xL1FreUpsTTNsSXpwYXR2T3NrMkw5AAIElWcmVQMECAcAAA==
    )
   */

  $msgtype = $postArray['MsgType'];

  switch ($msgtype) {
      case 'event':
        $event = $postArray['Event'];
        switch ($event) {
          case 'subscribe': //加关注
            if(empty($postArray['EventKey'])){  //服务号加关注
              $eventkey = '';
            }else{  //扫码加关注
              $eventkey = $postArray['EventKey'];
              if ($eventkey != 'qrscene_3' &&  $eventkey != 'qrscene_2') {
                //mobile shopping admin user scan
                get_user_info_to_user_admin_table($eventkey, $postArray);
              }
            }
          case 'SCAN':  //已关注后扫码事件
            $eventkey = $postArray['EventKey'];
            if ($eventkey != '3' && $eventkey != '2') {
              //mobile shopping admin user scan
              get_user_info_to_user_admin_table($eventkey, $postArray);
            }
            break;
          
          default:
            // code...
            break;
        }
        break;
      
      default:
        // code...
        break;
  }

  return $resultStr;
}

/**
 * Callback function when user click 热门活动 menu 
 * Array
 * (
 *   [ToUserName] => gh_849bfca55031
 *   [FromUserName] => oOTG9t2L0J3Pw-z5e3E4dpvVnpMc
 *   [CreateTime] => 1428935037
 *   [MsgType] => event
 *   [Event] => CLICK
 *   [EventKey] => menu14
 * )
 */
function wechat_recv_event_click_msg_callback($postArray){
  $resultStr = '';
  collect_event_statistic($postArray);
  //watchdog('wechat recv message', 'postArray <pre>@print_r</pre>', array('@print_r' => print_r($postArray, TRUE)));
  //menu14 is 热门活动, please check wechat menu definition
  if($postArray['EventKey'] == 'menu14'){
    module_load_include('inc', 'wechat_api', 'wechat_api_resp_msg_tpl');
    $resultStr = wechat_api_resp_img_text_message($postArray);
  }
  return $resultStr;
}

//record all even view message
function wechat_recv_event_view_msg_callback($postArray) {
  $resultStr = '';
  collect_event_statistic($postArray);
  //watchdog('wechat recv message', 'postArray <pre>@print_r</pre>', array('@print_r' => print_r($postArray, TRUE)));
  return $resultStr;
}

/**
 * received template message response 
 *
 * <xml>
 *  <ToUserName><![CDATA[gh_7f083739789a]]></ToUserName>
 *  <FromUserName><![CDATA[oia2TjuEGTNoeX76QEjQNrcURxG8]]></FromUserName>
 *  <CreateTime>1395658920</CreateTime>
 *  <MsgType><![CDATA[event]]></MsgType>
 *  <Event><![CDATA[TEMPLATESENDJOBFINISH]]></Event>
 *  <MsgID>200163836</MsgID>
 *  <Status><![CDATA[success]]></Status>
 *  ////////
 *  <Event><![CDATA[TEMPLATESENDJOBFINISH]]></Event>
 *    <MsgID>200163840</MsgID>
 *    <Status><![CDATA[failed:user block]]></Status>
 *  ////////
 *  <Event><![CDATA[TEMPLATESENDJOBFINISH]]></Event>
 *    <MsgID>200163840</MsgID>
 *    <Status><![CDATA[failed: system failed]]></Status>
 *  ////////
 * </xml>
 **/
function wechat_recv_event_template_send_job_callback($postArray) {
  $resultStr = '';

  $FromUserName = $postArray['FromUserName'];
  $msgid = $postArray['MsgID'];
  $status = $postArray['Status'];
  if ($status != 'success') {
    watchdog('mobile shopping', 'template msg response: <pre>@data</pre>', array('@data' => print_r($status, TRUE)));
  }

  return $resultStr;

}


function collect_event_statistic($postArray)
{
  $msgtype = $postArray['MsgType'];

  switch ($msgtype) {
      case 'event':
        $event = $postArray['Event'];
        switch ($event) {
          case 'unsubscribe': //推出关注
            $eventkey = '';
            break;
          case 'subscribe': //加关注
            if(empty($postArray['EventKey'])){  //服务号加关注
              $eventkey = '';
            }else{  //扫码加关注
              $eventkey = $postArray['EventKey'];
            }
          case 'SCAN':  //已关注后扫码事件
            $eventkey = $postArray['EventKey'];
            break;
          case 'LOCATION':  //上报地理位置
            $eventkey = '';
            break;
          case 'CLICK':  //自定义菜单click事件
            $eventkey = $postArray['EventKey'];
            break;
          case 'VIEW':  //自定义菜单url跳转事件
            $eventkey = $postArray['EventKey'];
            break;
          
          default:
            // code...
            break;
        }
        break;
      
      default:
        // code...
        break;
  }

  db_insert('wechat_event_statistic_table')
    ->fields(array(
      'openid' => $postArray['FromUserName'],
      'msgtype' => $postArray['MsgType'],
      'event' => $postArray['Event'],
      'eventkey' => $eventkey,
      'createtime' => $postArray['CreateTime'],))
    ->execute();
}

//get user wechat openid and save to admin user account
function get_user_info_to_user_admin_table($eventkey, $postArray) {

  watchdog('mobile shopping scan', 'eventkey <pre>@data</pre>', array('@data' => print_r($eventkey, TRUE)));

  $uid = '';
  if (preg_match('/^qrscene_/', $eventkey)) {

    $split = preg_split('/^qrscene_/', $prepay_idstr); //remove 100
    $uid = $split[1];
  } else {
    $uid = $eventkey;
  }

  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  $result = wechat_api_get_user_info($postArray['FromUserName']);

  if($result == ''){
    watchdog('mobile shopping',
             'user admin scan error, can not get user basic information from  user open id = @openid',
             array('@openid' => $result->openid),
             $severity = WATCHDOG_ERROR);
  }else{
    global $user;
    $user_profile = entity_metadata_wrapper('user', $uid);

    watchdog('mobile shopping scan', 'user_profile <pre>@data</pre>', array('@data' => print_r($user_profile, TRUE)));

    $user_profile->field_wechat_subscribe->set($result->subscribe);
    $user_profile->field_wechat_openid->set($result->openid);
    $emoji = base64_encode($result->nickname);
    $user_profile->field_wechat_nickname->set($emoji);
    $user_profile->field_wechat_sex->set($result->sex);
    $user_profile->field_wechat_city->set($result->city);
    $user_profile->field_wechat_country->set($result->province);
    $user_profile->field_wechat_province->set($result->country);
    $user_profile->field_wechat_language->set($result->language);
    $user_profile->field_wechat_headimgurl->set($result->headimgurl);
    $user_profile->field_wechat_subscribe_time->set($result->subscribe_time);
    $user_profile->save();  //save new user into database

  }

}

/**
 * End of wechat access url entrance
 */
