<?php

/**
 * wechat_py_mobile_pay_notify_url
 */
function wechat_py_mobile_pay_notify_url() {

  $xml = file_get_contents("php://input");
  libxml_disable_entity_loader(true);
  $notify = json_decode(json_encode(simplexml_load_string($xml, 'SimpleXMLElement', LIBXML_NOCDATA)), true);
  //watchdog('wechat py mobile', 'notify <pre>@data</pre>', array('@data' => print_r($notify, TRUE)));
  $sign = makeSign($notify);

  if ($notify['sign'] == $sign) { //check notify sing valid, and order has been paied
    $out_trade_no = $notify['out_trade_no'];
    //$split_order = preg_split('/-/', $notify['attach']); //split order by attach area id
   
    //update mobile_shopping_user_order_table for state and insert transaction_id
    $query = db_select('mobile_shopping_user_order_table', 't')
           ->condition('out_trade_no', $out_trade_no)
           ->fields('t', array(
              'order_state',
              ));
    $result = $query->execute();
    $count = $result->rowCount();
    if (!$count) {
      watchdog('wechat py mobile', 'can not find out_trade_no: <pre>@data</pre> this order has not finished or unpay',
               array('@data' => print_r($out_trade_no, TRUE)));
      return;   //don't find order which means pay hasn't finished or unpay
    }

    foreach ($result as $row) {
      if ($row->order_state >= 1) {
        watchdog('notify', 'order state has changed <pre>@data</pre>', array('@data' => print_r($row->order_state, TRUE)));
        echo '<xml><return_code><![CDATA[SUCCESS]]></return_code><return_msg><![CDATA[OK]]></return_msg></xml>';
        return; //order has been paied and state has been changed
      }
    }

    //update order state from 0 unpay to 1 paied and checking
    try {
      $num_updated = db_update('mobile_shopping_user_order_table')
        ->fields(array(
          'time_end' => $notify['time_end'],
          'transaction_id' => $notify['transaction_id'],
          'order_state' => 1,
        ))
        ->condition('out_trade_no', $out_trade_no)
        ->execute();

      //remove paied mechandise from cart records
      remove_records_from_user_cart($out_trade_no);

      //check if update right order, then return ok else wait over tiem and wechat send again
      if ($num_updated != 0) {
        background_process_start('background_process_order_notify', $out_trade_no);
        echo '<xml><return_code><![CDATA[SUCCESS]]></return_code><return_msg><![CDATA[OK]]></return_msg></xml>';
      }
      //watchdog('order notify', 'update rows = <pre>@data</pre>', array('@data' => print_r($num_updated, TRUE)));
    } catch(Exception $e) {

      $errorinfo = $e->errorInfo;
      watchdog('order notify', 'update order table = <pre>@error</pre>', array('@error' => print_r($errorinfo, TRUE)));
    }

    //order pay OK
    //query order
    //change order status, and notify user and custom

    /*
    $library = libraries_load('wxpayapi');
		$input = new WxPayOrderQuery();
		$input->SetTransaction_id($notify['transaction_id']);
		$result = WxPayApi::orderQuery($input, 30);
    if ($result['result_code'] == 'SUCCESS' && $result['return_code'] == 'SUCCESS') {
      if ($result['trade_state'] == 'SUCCESS') {
      }
    }
    watchdog('wechat py mobile', 'query order <pre>@data</pre>', array('@data' => print_r($result, TRUE)));
    */

  } else {
    watchdog('wechat py mobile', 'notify <pre>@data</pre>', array('@data' => print_r($notify, TRUE)));
    watchdog('wechat py mobile', 'notify sign <pre>@data</pre>', array('@data' => print_r($sign, TRUE)));
    echo '<xml><return_code><![CDATA[FAIL]]></return_code><return_msg><![CDATA[签名失败]]></return_msg></xml>';
  }


/*
  $notify = new PayNotifyCallBack();
  $notify->Handle(false);
  */
}

function makeSign($data /*should be an array*/) {

  //签名步骤一：按字典序排序参数
  ksort($data);

  $params = ToUrlParams($data);

  //签名步骤二：在string后加入KEY
  $mchkey = variable_get('wechat_py_mchkey');
  $string = $params . "&key=" . $mchkey;
  //签名步骤三：MD5加密
  $string = md5($string);
  //签名步骤四：所有字符转为大写
  $result = strtoupper($string);
  return $result;
}

function ToUrlParams($data)
{
		$buff = "";
		foreach ($data as $k => $v)
		{
			if($k != "sign" && $v != "" && !is_array($v)){
				$buff .= $k . "=" . $v . "&";
			}
		}
		
		$buff = trim($buff, "&");
		return $buff;
}

/**
 * remove merchandise records from cart
 **/
function remove_records_from_user_cart($out_trade_no) {
  $query = db_select('mobile_shopping_user_order_table', 't')
         ->condition('out_trade_no', $out_trade_no)
         ->fields('t');
  $result = $query->execute();

  foreach ($result as $id => $data) {

    $openid = $data->openid;

    $m_query = db_select('mobile_shopping_user_order_detail_table', 't')
         ->condition('t.order_index', $data->id)
         ->condition('t.area_term_id', $data->area_id)
         ->fields('t');
    $d_result = $m_query->execute();
    foreach ($d_result as $item) {
        db_delete('mobile_shopping_user_cart_table')
        ->condition('openid', $openid)
        ->condition('merchandise_id', $item->merchandise_id)
        ->execute();
    }

  }
}

/**
 * End of wechat_py_mobile_pay_notify_url.inc
 */
