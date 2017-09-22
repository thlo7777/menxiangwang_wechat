<?php
//require  '/var/www/wechat/wechat_config_inc.php';
/**
 * Root directory of Drupal installation.
 */

define('DRUPAL_ROOT', getcwd());
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

//check if it's not an validate user, then return

/**
 *[Thu Mar 26 01:10:42.927783 2015] [dumpio:trace7] [pid 17484] mod_dumpio.c(103): [client 140.207.54.76:50733] mod_dumpio:  dumpio_out (data-HEAP): \r\n2966969435895037597
 * Found this error when put echo after 32 line in this file. echo will output and prepend '\r\n'
 * only for wechat validation for change configure
 */
if(isset($_GET['echostr'])){
  $echoStr = $_GET['echostr'];
  echo $echoStr;
}

if ((require wechat_py_path . wechat_api_path . '/wechat_rcv_message.php') !== 1)
{
  wechat_write_log('require wechat_rcv_message.php error', __FILE__, __LINE__);
  exit;
}

if ((require wechat_py_path . wechat_api_path . '/wechat_php_tools.php') !== 1)
{
  wechat_write_log('require wechat_php_tools.php error', __FILE__, __LINE__);
  exit;
}


//  }else{
if (checkSignature()){
    $xmldata = file_get_contents("php://input"); //get xml data
    //wechat_write_log($xmldata, __FILE__, __LINE__);
    $result = wechat_rev_msg($xmldata); // handle received message
    echo $result;
  }else{
  wechat_write_log('failed', __FILE__, __LINE__);
  return;
}

/**
 * Check signature for legal user
 * signature、timestamp、nonce、echostr
 * 1. 将token、timestamp、nonce三个参数进行字典序排序
 * 2. 将三个参数字符串拼接成一个字符串进行sha1加密
 * 3. 开发者获得加密后的字符串可与signature对比，标识该请求来源于微信
 */
function checkSignature()
{
  $signature = $_GET["signature"];
  $timestamp = $_GET["timestamp"];
  $nonce = $_GET["nonce"];  

  //$token = wechat_TOKEN;
  $token = "MengXiangPingYaoYou";
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

/*
  global $handle;
  $filename = 'wxsignature.txt';
  if (!$handle = fopen($filename, 'a+')) {
       echo "Cannot open file ($filename)";
       exit;
  }
  fwrite($handle, 'tmpstr:' . $tmpStr . "\n");
  fwrite($handle, 'signature:' . $signature . "\n");
  //fwrite($handle, 'rawdata:' . $rawdata . "\n");
  if(is_null($echoStr)){
    fwrite($handle, 'echoStr: null echoStr' . "\n");
  }else{
    fwrite($handle, 'echoStr:' . $echoStr . "\n");
  }

*/
/*        
$headers = apache_request_headers();

foreach ($headers as $header => $value) {
fwrite($handle, "$header: $value \n");
}*/

//fwrite($handle, "--------------------------------------------------------\n");
//fclose($handle);

