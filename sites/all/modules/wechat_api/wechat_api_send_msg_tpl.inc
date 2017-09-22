<?php

/**
 * send news to all user 
 *
 * http请求方式: POST
 * https://api.weixin.qq.com/cgi-bin/message/mass/sendall?access_token=ACCESS_TOKEN
 *
 * POST数据示例如下：
 *
 * 图文消息（其中media_id与根据分组群发中的media_id相同）：
 * 
 * {
 *    "filter":{
 *             "is_to_all":false
 *             "group_id":"2"
 *             },
 *    "mpnews":{              
 *             "media_id":"123dsdajkasd231jhksad"               
 *              },
 *    "msgtype":"mpnews" 
 * }
 * 文本：
 * 
 * {     
 *    "filter":{
 *             "is_to_all":false
 *             "group_id":"2"
 *             },
 *     "text":{           
 *            "content":"CONTENT"            
 *            },     
 *     "msgtype":"text"
 * }
 * 语音（其中media_id与根据分组群发中的media_id相同）：
 *
 * {
 *    "filter":{
 *             "is_to_all":false
 *             "group_id":"2"
 *             },
 *     "voice":{              
 *             "media_id":"123dsdajkasd231jhksad"
 *             },
 *     "msgtype":"voice" 
 * }
 * 图片（其中media_id与根据分组群发中的media_id相同）：
 * 
 * {
 *    "filter":{
 *             "is_to_all":false
 *             "group_id":"2"
 *             },
 *     "image":{      
 *             "media_id":"123dsdajkasd231jhksad"
 *             },
 *     "msgtype":"image" 
 * }
 *
 * 请注意，此处视频的media_id需通过POST请求到下述接口特别地得到： 
 * https://file.api.weixin.qq.com/cgi-bin/media/uploadvideo?access_token=ACCESS_TOKEN POST数据如下
 *（此处media_id需通过基础支持中的上传下载多媒体文件来得到）：
 * 
 * {
 *   "media_id": "rF4UdIMfYK3efUfyoddYRMU50zMiRmmt_l0kszupYh_SzrcW5Gaheq05p_lHuOTQ",
 *   "title": "TITLE",
 *   "description": "Description"
 * }
 * 返回将为
 * 
 * {
 *   "type":"video",
 *   "media_id":"IhdaAQXuvJtGzwwc0abfXnzeezfO0NgPK6AQYShD8RQYMTtfzbLdBIQkQziv2XJc",
 *   "created_at":1398848981
 * }
 * 然后，POST下述数据（将media_id改为上一步中得到的media_id），即可进行发送
 * 
 * {
 *    "filter":{
 *             "is_to_all":false
 *             "group_id":"2"
 *             },
 *     "mpvideo":{  
 *             "media_id":"IhdaAQXuvJtGzwwc0abfXnzeezfO0NgPK6AQYShD8RQYMTtfzbLdBIQkQziv2XJc",   
 *                },
 *     "msgtype":"mpvideo" 
 * }
 *
 * return correct value:
 * {
 *    "errcode":0,
 *    "errmsg":"send job submission success",
 *    "msg_id":34182
 * }
 *
 */

function wechat_api_send_news_to_all($media_id, $msgtype, $is_to_all, $group){

  $token_url = t(
    variable_get('send news to all'),
    array('@ACCESS_TOKEN' => variable_get('access_token'))
  );

  if($is_to_all){
    $post_data['filter'] = array('is_to_all' => $is_to_all); 
  }else{
    $post_data['filter'] = array('is_to_all' => $is_to_all, 'group_id' => $group); 
  }
  $post_data['send_ignore_reprint'] = 1;
  switch($msgtype){
    case "mpnews":
      $post_data[$msgtype] = array('media_id' => $media_id);
      $post_data['msgtype'] = $msgtype;
      break;
    case "text":
      $post_data[$msgtype] = array('content' => $media_id); //$media_id is content text
      $post_data['msgtype'] = $msgtype;
      break;
    case "voice":
      $post_data[$msgtype] = array('media_id' => $media_id);
      $post_data['msgtype'] = $msgtype;
      break;
    case "image":
      $post_data[$msgtype] = array('media_id' => $media_id);
      $post_data['msgtype'] = $msgtype;
      break;
    case "mpvideo":
      $post_data[$msgtype] = array('media_id' => $media_id);
      $post_data['msgtype'] = $msgtype;
      break;
    default:
      watchdog('wechat send to all', 'message type wrong: @msgtype',
        array('@msgtype' => $msgtype), $severity = WATCHDOG_ERROR);
      return '';
  }

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  //check http://loosky.net/3069.html how to protect mess code
  $json_data = json_encode($post_data,
                           JSON_HEX_TAG |
                           JSON_HEX_APOS |
                           JSON_HEX_AMP |
                           JSON_HEX_QUOT |
                           JSON_UNESCAPED_UNICODE);

  $result = wechat_php_curl_https_post($token_url, $json_data);
  if (!$result)
  {
    watchdog('wechat send to all', 'return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);
  if($json_value->errcode){
    watchdog('wechat send to all', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  return $json_value->errmsg;
}

/**
 * send news to previews user 
 *
 * http请求方式: POST
 * https://api.weixin.qq.com/cgi-bin/message/mass/preview?access_token=ACCESS_TOKEN
 *
 * or send news to openid lists
 * http请求方式: POST
 * https://api.weixin.qq.com/cgi-bin/message/mass/send?access_token=ACCESS_TOKEN
 *
 * POST数据示例如下：
 *
 * 图文消息（其中media_id与根据分组群发中的media_id相同）：
 * 
 * {
 *    "touser":"OPENID", 
 *    or
 *    "touser":[
 *    "OPENID1",
 *    "OPENID2"
 *    ],
 *    "mpnews":{              
 *             "media_id":"123dsdajkasd231jhksad"               
 *              },
 *    "msgtype":"mpnews" 
 * }
 * 文本：
 * 
 * {     
 *     "touser":"OPENID",
 *    or
 *    "touser":[
 *    "OPENID1",
 *    "OPENID2"
 *    ],
 *     "text":{           
 *            "content":"CONTENT"            
 *            },     
 *     "msgtype":"text"
 * }
 * 语音（其中media_id与根据分组群发中的media_id相同）：
 *
 * {
 *     "touser":"OPENID",
 *    or
 *    "touser":[
 *    "OPENID1",
 *    "OPENID2"
 *    ],
 *     "voice":{              
 *             "media_id":"123dsdajkasd231jhksad"
 *             },
 *     "msgtype":"voice" 
 * }
 * 图片（其中media_id与根据分组群发中的media_id相同）：
 * 
 * {
 *     "touser":"OPENID",
 *    or
 *    "touser":[
 *    "OPENID1",
 *    "OPENID2"
 *    ],
 *     "image":{      
 *             "media_id":"123dsdajkasd231jhksad"
 *             },
 *     "msgtype":"image" 
 * }
 *
 * only for openid list
 * 请注意，此处视频的media_id需通过POST请求到下述接口特别地得到： 
 * https://file.api.weixin.qq.com/cgi-bin/media/uploadvideo?access_token=ACCESS_TOKEN POST数据如下
 *（此处media_id需通过基础支持中的上传下载多媒体文件来得到）：
 * 
 * {
 *   "media_id": "rF4UdIMfYK3efUfyoddYRMU50zMiRmmt_l0kszupYh_SzrcW5Gaheq05p_lHuOTQ",
 *   "title": "TITLE",
 *   "description": "Description"
 * }
 * 返回将为
 * 
 * {
 *   "type":"video",
 *   "media_id":"IhdaAQXuvJtGzwwc0abfXnzeezfO0NgPK6AQYShD8RQYMTtfzbLdBIQkQziv2XJc",
 *   "created_at":1398848981
 * }
 * 然后，POST下述数据（将media_id改为上一步中得到的media_id），即可进行发送
 *
 * {
 *    "touser":[
 *    "OPENID1",
 *    "OPENID2"
 *    ],
 *    "video":{
 *         "media_id":"123dsdajkasd231jhksad",
 *         "title":"TITLE",
 *        "description":"DESCRIPTION"
 *        },
 *    "msgtype":"video"
 * }
 *
 * 
 * only for preview 视频（其中media_id与根据分组群发中的media_id相同）：
 * {
 *     "touser":"OPENID",
 *     "mpvideo":{  
 *             "media_id":"IhdaAQXuvJtGzwwc0abfXnzeezfO0NgPK6AQYShD8RQYMTtfzbLdBIQkQziv2XJc",   
 *                },
 *     "msgtype":"mpvideo" 
 * }
 *
 * return correct value:
 * {
 *    "errcode":0,
 *    "errmsg":"send job submission success",
 *    "msg_id":34182
 * }
 *
 */
function wechat_api_send_preview_to_openid($media_id, $msgtype, $openid){


  if(is_array($openid)){
    //openids array
    $token_url = t(
      variable_get('send openid list media'),
      array('@ACCESS_TOKEN' => variable_get('access_token'))
    );
  }else{
    //only one openid
    $token_url = t(
      variable_get('send preview media'),
      array('@ACCESS_TOKEN' => variable_get('access_token'))
    );
  }

  $post_data['touser'] = $openid; 
  switch($msgtype){
    case "mpnews":
      $post_data[$msgtype] = array('media_id' => $media_id);
      $post_data['msgtype'] = $msgtype;
      break;
    case "text":
      $post_data[$msgtype] = array('content' => $media_id); //$media_id is content text
      $post_data['msgtype'] = $msgtype;
      break;
    case "voice":
      $post_data[$msgtype] = array('media_id' => $media_id);
      $post_data['msgtype'] = $msgtype;
      break;
    case "image":
      $post_data[$msgtype] = array('media_id' => $media_id);
      $post_data['msgtype'] = $msgtype;
      break;
    case "mpvideo":
      $post_data[$msgtype] = array('media_id' => $media_id);
      $post_data['msgtype'] = $msgtype;
      break;
    default:
      watchdog('wechat send preview', 'message type wrong: @msgtype',
        array('@msgtype' => $msgtype), $severity = WATCHDOG_ERROR);
      return '';
  }

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  //check http://loosky.net/3069.html how to protect mess code
  $json_data = json_encode($post_data,
                           JSON_HEX_TAG |
                           JSON_HEX_APOS |
                           JSON_HEX_AMP |
                           JSON_HEX_QUOT |
                           JSON_UNESCAPED_UNICODE);

  $result = wechat_php_curl_https_post($token_url, $json_data);

  if (!$result)
  {
    watchdog('wechat send preview', 'return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);
  if($json_value->errcode){
    watchdog('wechat send preview', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  return $json_value->errmsg;
}

/**
 * Upload news to server 
 *
 * http请求方式: POST
 * https://api.weixin.qq.com/cgi-bin/media/uploadnews?access_token=ACCESS_TOKEN
 *
 * return correct value:
 * {
 *  "type":"news",
 *  "media_id":"CsEf3ldqkAYJAU6EJeIkStVDSvffUJ54vqbThMgplD-VJXXof6ctX5fI6-aYyUiQ",
 *  "created_at":1391857799
 * }
 *
 * return error value:
 * {"errcode":40004,"errmsg":"invalid media type"}
 */
function wechat_api_upload_news_media($post_data){

  $token_url = t(
    variable_get('upload news'),
    array('@ACCESS_TOKEN' => variable_get('access_token'))
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_post($token_url, $post_data);
  if (!$result)
  {
    watchdog('wechat upload media', 'upload news error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('wechat upload media', 'upload news error code: @error and errmsg: @errmsg at @line in @filename',
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

/**
 * Upload temporary media file to server 
 *
 * http请求方式: POST/FORM,需使用https
 * https://api.weixin.qq.com/cgi-bin/media/upload?access_token=ACCESS_TOKEN&type=TYPE
 * 调用示例（使用curl命令，用FORM表单方式上传一个多媒体文件）：
 * curl -F media=@test.jpg "https://api.weixin.qq.com/cgi-bin/media/upload?access_token=ACCESS_TOKEN&type=TYPE"
 *
 * TYPE 媒体文件类型，分别有图片（image）、语音（voice）、视频（video）和缩略图（thumb 要用于视频与音乐格式的缩略图）
 * return correct value:
 * {"type":"TYPE","media_id":"MEDIA_ID","created_at":123456789}
 *
 * return error value:
 * {"errcode":40004,"errmsg":"invalid media type"}
 */
function wechat_api_upload_temp_media_file($file, $type){

  $token_url = t(
    variable_get('upload temp media file'),
    array('@ACCESS_TOKEN' => variable_get('access_token'),
          '@TYPE' => $type)
  );

  //Need system path instead of file url
  $file = drupal_realpath($file);
  //find file format
  $file_ext = preg_split('/\./', $file);

  //关键是判断curlfile,官网推荐php5.5或更高的版本使用curlfile来实例文件  
  if(class_exists ( '\CURLFile' )){
    $post_data = array('media' => new \CURLFile($file, 'image/' . $file_ext[1])); 
  }else{
    $post_data = array('media' => '@' . $file);
  }  
  
  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_post($token_url, $post_data);
  if (!$result)
  {
    watchdog('wechat upload media', 'upload temp media file error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('wechat upload media',
      'upload temp media file error code: @error and errmsg: @errmsg at @line in @filename',
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

/**
 * Upload image to server, and get URL for wechat news
 *
 * http请求方式: POST
 * https://api.weixin.qq.com/cgi-bin/media/uploadimg?access_token=ACCESS_TOKEN
 * 调用示例（使用curl命令，用FORM表单方式上传一个图片）：
 * curl -F media=@test.jpg "https://api.weixin.qq.com/cgi-bin/media/uploadimg?access_token=ACCESS_TOKEN"
 * only support jpg/png file, size <= 1M byte
 * return correct value:
 * {
 *   "url":  "http://mmbiz.qpic.cn/mmbiz/gLO17UPS6FS2xsypf378iaNhWacZ1G1UplZYWEYfwvuU6Ont96b1roYs CNFwaRrSaKTPCUdBK9DgEHicsKwWCBRQ/0"
 * }
 *
 * return error value:
 * {"errcode":40004,"errmsg":"invalid media type"}
 */
function wechat_api_upload_image_file($file, $type = ''){

  $token_url = t(
    variable_get('upload image url to news'),
    array('@ACCESS_TOKEN' => variable_get('access_token'))
  );

  //Need system path instead of file url
  //$file = drupal_realpath($file);
  //watchdog('wechat upload image', 'file <pre>@data</pre>', array('@data' => print_r($file, TRUE)));
  //find file format
  $file_ext = preg_split('/\./', $file);
  //dpm($file_ext[1]);
  //watchdog('wechat upload image', 'file ext <pre>@data</pre>', array('@data' => print_r($file_ext, TRUE)));

  //关键是判断curlfile,官网推荐php5.5或更高的版本使用curlfile来实例文件  
  if(class_exists ( '\CURLFile' )){
    $post_data = array('media' => new \CURLFile($file, 'image/' . $file_ext[1])); 
  }else{
    $post_data = array('media' => '@' . $file);
  }  
    
  module_load_include('inc', 'wechat_api', 'wechat_api_php5');

  $result = '';
  if ($file_ext[1] == 'gif') {
    $token_url_temp = t(
      variable_get('upload temp media file'),
      array('@ACCESS_TOKEN' => variable_get('access_token'),
            '@TYPE' => 'image')
    );

    $result = wechat_php_curl_https_post($token_url_temp, $post_data);
    if (!$result)
    {
      watchdog('wechat upload image', 'upload image file error: return null in @line line:@filename',
        array(
        '@line' => __LINE__,
        '@filename' => __FILE__,
        ),
        $severity = WATCHDOG_ERROR);
      return '';
    }
  } else {
    $result = wechat_php_curl_https_post($token_url, $post_data);
    if (!$result)
    {
      watchdog('wechat upload image', 'upload image file error: return null in @line line:@filename',
        array(
        '@line' => __LINE__,
        '@filename' => __FILE__,
        ),
        $severity = WATCHDOG_ERROR);
      return '';
    }
  }

  if (!$result)
  {
    watchdog('wechat upload image', 'upload image file error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('wechat upload media',
      'upload image file error code: @error and errmsg: @errmsg at @line in @filename',
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
/**
 * Create a temporary bar code from wechat server
 * POST数据格式：json
 * POST数据例子：{"expire_seconds": 1800, "action_name": "QR_SCENE", "action_info": {"scene": {"scene_id": 123}}}
 *
 * return correct value:
 * {"ticket":"gQH47joAAAAAAAAAASxodHRwOi8vd2VpeGluLnFxLmNvbS9xL2taZ2Z3TVRtNzJXV1Brb3ZhYmJJAAIEZ23sUwMEmm3sUw==",
 *  "expire_seconds":60,"url":"http:\/\/weixin.qq.com\/q\/kZgfwMTm72WWPkovabbI"}
 *
 * return error value:
 * {"errcode":40013,"errmsg":"invalid appid"}
 */
function wechat_api_creat_qrscene($limit, $scene_id, $seconds = 0){

  $token_url = t(
    variable_get('create QR_LIMIT_SCENE'),
    array('@ACCESS_TOKEN' => variable_get('access_token'))
  );

  if($limit){
    //for permanent bar code image
    $post = array(
      'action_name' => 'QR_LIMIT_SCENE',
      'action_info' => array('scene' => array('scene_id' => (int)$scene_id)),
    );
  }else{
    //for temporary bar code image
    $post = array(
      'expire_seconds' => $seconds,
      'action_name' => 'QR_SCENE',
      'action_info' => array('scene' => array('scene_id' => (int)$scene_id)),
    );
  }
  
  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $json = json_encode($post);
  $result = wechat_php_curl_https_post($token_url, $json, 'json');
  if (!$result)
  {
    watchdog('wechat creat qrscene', 'error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('wechat creat qrscene', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  return $json_value->ticket;
}

/**
 * get bar code by ticket from wechat server
 *
 * return correct value:
 * ticket正确情况下，http 返回码是200，是一张图片，可以直接展示或者下载。
 *
 * return error value:
 * 错误情况下（如ticket非法）返回HTTP错误码404。
 */
function wechat_api_get_qrscene_image($scene_name, $ticket){

  $token_url = t(
    variable_get('get bar code'),
    array('@TICKET' => urlencode($ticket))
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_get($token_url, true);
  if (!$result)
  {
    watchdog('wechat get bar code', 'error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }
  list($header, $body) = explode("\r\n\r\n", $result, 2);

  //find content type for image file jpg or others
  preg_match('@(Content-type)((?(1).*))@i', $header, $matches);
  $file_ext = preg_split('@\/@', $matches[2]);

  //Have to use trim to strip off odd characters for preg_match
  $destination = 'public://wechat_py_admin/' . $scene_name  . '.' . trim($file_ext[1]);
  $filename = file_unmanaged_save_data($body, $destination, FILE_EXISTS_RENAME);
  if (!$filename) {
    watchdog('wechat get bar code', 'save file error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  return $filename;
}

/**
 * get user list from wechat server 
 *
 * http请求方式: GET（请使用https协议）
 * next_openid	第一个拉取的OPENID，不填默认从头开始拉取
 * https://api.weixin.qq.com/cgi-bin/user/get?access_token=ACCESS_TOKEN

 * return correct value:
 * {"total":2,"count":2,"data":{"openid":["","OPENID1","OPENID2"]},"next_openid":"NEXT_OPENID1"}
 * total	关注该公众账号的总用户数
 * count	拉取的OPENID个数，最大值为10000
 * data	列表数据，OPENID的列表
 * next_openid	拉取列表的后一个用户的OPENID
 * https://api.weixin.qq.com/cgi-bin/user/get?access_token=ACCESS_TOKEN&next_openid=NEXT_OPENID1
 *
 * return error
 * {"errcode":40013,"errmsg":"invalid appid"}
 *
 */
function wechat_api_get_user_list(){

  $token_url = t(
    variable_get('get user list'),
    array('@ACCESS_TOKEN' => variable_get('access_token'))
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_get($token_url);
  if (!$result)
  {
    watchdog('wechat get user list', 'error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  //get user list, it will return maxmum 10000 open id each time.
  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('wechat get user list', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  //return user list json format
  return $json_value;
}

/**
 * get user list from wechat server 
 *
 * http请求方式: GET（请使用https协议）
 * https://api.weixin.qq.com/cgi-bin/user/get?access_token=ACCESS_TOKEN&next_openid=NEXT_OPENID

 * return correct value:
 * {"total":2,"count":2,"data":{"openid":["","OPENID1","OPENID2"]},"next_openid":"NEXT_OPENID1"}
 * total	关注该公众账号的总用户数
 * count	拉取的OPENID个数，最大值为10000
 * data	列表数据，OPENID的列表
 * next_openid	拉取列表的后一个用户的OPENID
 * https://api.weixin.qq.com/cgi-bin/user/get?access_token=ACCESS_TOKEN&next_openid=NEXT_OPENID1
 *
 * return error
 * {"errcode":40013,"errmsg":"invalid appid"}
 *
 */
function wechat_api_get_user_list_next($openid){

  $token_url = t(
    variable_get('get user list next'),
    array('@ACCESS_TOKEN' => variable_get('access_token'),
          '@NEXT_OPENID' => $openid)
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_get($token_url);
  if (!$result)
  {
    watchdog('wechat get user list next', 'error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  //get user list, it return maxmum 10000 open id each time.
  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('wechat get user list next', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  //return user list json format
  return $json_value;
}

/**
 * get user information from wechat server 
 *
 * http请求方式: GET（请使用https协议）
 * https://api.weixin.qq.com/cgi-bin/user/info?access_token=ACCESS_TOKEN&openid=OPENID&lang=zh_CN

 * return correct value:
 * subscribe	用户是否订阅该公众号标识，值为0时，代表此用户没有关注该公众号，拉取不到其余信息。
 * openid	用户的标识，对当前公众号唯一
 * nickname	用户的昵称
 * sex	用户的性别，值为1时是男性，值为2时是女性，值为0时是未知
 * city	用户所在城市
 * country	用户所在国家
 * province	用户所在省份
 * language	用户的语言，简体中文为zh_CN
 * headimgurl	用户头像，最后一个数值代表正方形头像大小（有0、46、64、96、132数值可选，0代表640*640正方形头像），
 *            用户没有头像时该项为空。若用户更换头像，原有头像URL将失效。
 * subscribe_time	用户关注时间，为时间戳。如果用户曾多次关注，则取最后关注时间
 * unionid	只有在用户将公众号绑定到微信开放平台帐号后，才会出现该字段。详见：获取用户个人信息（UnionID机制）
 *
 * return error
 * {"errcode":40013,"errmsg":"invalid appid"}
 *
 */
function wechat_api_get_user_info($openid){

  $token_url = t(
    variable_get('get user info'),
    array('@ACCESS_TOKEN' => variable_get('access_token'),
          '@OPENID' => $openid)
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_get($token_url);
  if (!$result)
  {
    watchdog('wechat get user info', 'error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('wechat get user info', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  //return user list json format
  return $json_value;
}

/**
 *  get user info by oauth2 access token. it can get user info if scope = snsapi_userinfo 
 *  if scope = snsapi_base  return error code: 48001 and errmsg: api unauthorized, 
 **/
function wechat_api_oauth2_get_user_info($openid, $oauth2_access_token){

  $token_url = t(
    variable_get('get oauth2 user info'),
    array('@ACCESS_TOKEN' => $oauth2_access_token,
          '@OPENID' => $openid)
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_get($token_url);
  if (!$result)
  {
    watchdog('wechat get user info', 'error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);
  if(isset($json_value->errcode)){
    watchdog('wechat get user info', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  //return user list json format
  return $json_value;
}

//reget access token to validate user subscribe for mobile shopping 
function wechat_api_validate_user_info($openid){

  $token_url = t(
    variable_get('get user info'),
    array('@ACCESS_TOKEN' => variable_get('access_token'),
          '@OPENID' => $openid)
  );

  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $result = wechat_php_curl_https_get($token_url);
  if (!$result)
  {
    watchdog('wechat get user info', 'error: return null in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  $json_value = json_decode($result);

  if(isset($json_value->errcode)){
    watchdog('wechat get user info', 'error code: @error and errmsg: @errmsg at @line in @filename',
      array(
      '@error' => $json_value->errcode,
      '@errmsg' => $json_value->errmsg,
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return '';
  }

  //return user list json format
  return $json_value;
}
/**
 * End of wechat api send message to wechat template interface
 */
