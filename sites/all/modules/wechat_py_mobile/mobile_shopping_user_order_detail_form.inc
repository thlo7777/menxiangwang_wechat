<?php

/*
 * Implement mobile_shopping_user_order_detail_form for mobile shopping order detail
 */
function mobile_shopping_user_order_detail_form($form, &$form_state, $order_id, $area_id){

  global $user;

  $user_profile = entity_metadata_wrapper('user', $user->uid);
  $user_term_id = $user_profile->field_product_category_term->value();
  //dpm($user_term_id);
  $term = taxonomy_get_term_by_name($area_id, 'wechat_shopping_merchant_vocabulary');
  $term_object = array_shift($term);


  $query = db_select('mobile_shopping_user_order_table', 't')
         ->condition('t.out_trade_no', $order_id)
         ->condition('t.area_id', $term_object->tid)
         ->fields('t');
  $result = $query->execute();


  $t_order = array();
  foreach ($result as $order) {
    $t_order['openid'] = $order->openid;
    $t_order['order_state'] = $order->order_state;
    $time = strtotime($order->time_end);
    $time_end = date('Y年m月d日 H:i',$time);
    $t_order['time_end'] = $time_end;
    $t_order['order_addr'] = $order->order_addr;
    $t_order['exp_fee'] = $order->area_exp_fee;

    $m_query = db_select('mobile_shopping_user_order_detail_table', 't')
         ->condition('order_index', $order->id)
         ->fields('t');
    $m_result = $m_query->execute();
    $element = array();
    foreach ($m_result as $item) {
      if ($user_term_id !== null) {
        //user has same area and roles include page_admin
        if ($user_term_id->tid == $item->area_term_id || in_array('page_admin', $user->roles, true)) {
          
          //$t_order['area'] = $user_term_id->name;
          $element[$item->id]['m_title'] = $item->m_title;
          $element[$item->id]['m_purl'] = $item->m_purl;
          $element[$item->id]['m_price'] = $item->m_price;
          $element[$item->id]['m_volume'] = $item->m_volume;
          //$element[$item->id]['exp_fee'] = $item->exp_fee;
          $element[$item->id]['point_p'] = $item->point_p;
          $element[$item->id]['point'] = $item->point;
          $element[$item->id]['discount'] = $item->discount;
          $element[$item->id]['item_total'] = $item->item_total;
          $d_time = strtotime($item->exp_time_end);
          $d_time_end = date('Y年m月d日 H:i',$d_time);
          $element[$item->id]['exp_time_end'] = $d_time_end;
          $element[$item->id]['exp_no'] = $item->exp_no;
          $element[$item->id]['exp_company_name'] = $item->exp_company_name;

        }
      }
    }

  }

  if (count($element)) {
    $t_order['detail'] = $element;
    //dpm($t_order);

    $form['user_info'] = array(
      '#type' => 'fieldset',
      '#title' => t('客户信息'),
    );

    module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
    $result = wechat_api_get_user_info($t_order['openid']);

    if($result == ''){  //can't get user head and nick name
      $form['user_info']['user_addr'] = array(
        '#markup' => '<div>' . $t_order['order_addr'] . '</div>',
      );

      $form['user_info']['openid'] = array(
        '#type' => 'value',
        '#value' => $t_order['openid'],
      );
    }else{

      $headimgurl = "";
      if (property_exists($result, "headimgurl")) {
        $headimgurl = $result->headimgurl;
      } 
      //user info header
      $form['user_info']['header'] = array(
        '#theme' => 'image',
        '#path' => $headimgurl,
        '#title' => '头像',
        '#width' => '50%',
        '#height' => '50%',
      );

      $nick_name = "匿名用户";
      if (property_exists($result, "nickname")) {
        $nick_name = $result->nickname;
      }

      $form['user_info']['nickname'] = array(
        '#markup' => '<div>' . $nick_name . '</div>',
      );
      $form['user_info']['user_addr'] = array(
        '#markup' => '<div>' . $t_order['order_addr'] . '</div>',
      );

      $form['user_info']['openid'] = array(
        '#type' => 'value',
        '#value' => $t_order['openid'],
      );
    }

    //order detail 
    $form['detail_info'] = array(
      '#type' => 'fieldset',
      '#title' => t('已支付订单详细信息'),
    );

    $form['detail_info']['area'] = array(
      '#markup' => '<div>采购商品所在区域: ' . $area_id . '</div>',
    );
    $form['detail_info']['order_no'] = array(
      '#markup' => '<div>订单编号: ' . $order_id . '</div>',
    );
    $form['detail_info']['total_exp_fee'] = array (
      '#markup' => '<div>订单邮费: ' .  $t_order['exp_fee'] . '</div>',
    );
    $form['detail_info']['order_no_value'] = array(
      '#type' => 'value',
      '#value' => $order_id,
    );

    $form['detail_info']['order_area_id'] = array(
      '#type' => 'value',
      '#value' => $term_object->tid,
    );

    $header = array(
      'image' => t('图片'),
      'title' =>  t('商品名称'),
      'price' => t('价格'),
      'volume' => t('购买件数'),
      //'exp_fee' => t('邮费'),
      'point_p' => t('积分折扣'),
      'discount' => t('促销折扣'),
      'item_total' => t('合计'),
    );

    $options = array();
    foreach($t_order['detail'] as $id => $d_item) {
      $image_theme = array(
        '#theme' => 'image',
        '#path' => $d_item['m_purl'],
        '#with' => '60px',
        '#height' => '60px',
        '#attributes' => array(
          'class' => array('title-image'),
          'style' => array('vertical-align: top;'),
        ),
      );

      $options[$id] = array(
        'image' => array(
          'data' => array(
            '#markup' => drupal_render($image_theme),
          ),
        ),
        'title' => $d_item['m_title'],
        'price' => $d_item['m_price'],
        'volume' => $d_item['m_volume'],
        //'exp_fee' => $d_item['exp_fee'],
        'point_p' => $d_item['point_p'],
        'discount' => $d_item['discount'],
        'item_total' => $d_item['item_total'],
      );
    }

    $form['detail_info']['detail_table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $options,
      '#empty' => t('当前没有记录'),
    );

    //dpm($form);

    //order state 1, 已支付, 2 已发货
    if ($t_order['order_state'] == '2') {
      $form['exp_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('发货信息'),
      );

      $form['exp_info']['exp_no'] = array(
        '#markup' => '<div>快递单号: ' . $d_item['exp_no'] . '</div>',
      );

      $form['exp_info']['exp_time'] = array(
        '#markup' => '<div>发货时间: ' . $d_item['exp_time_end'] . '</div>',
      );

      $form['exp_info']['exp_company_name'] = array(
        '#markup' => '<div>快递公司名称: ' . $d_item['exp_company_name'] . '</div>',
      );

    } else {
      //fill exp info
      $form['exp_info'] = array(
        '#type' => 'fieldset',
        '#title' => t('准备发货'),
        '#description' => t('发货信息一旦提交，会自动发送微信给用户，请仔细检查快递单号，不能有错，因为不能修改。'),
      );
     
      $form['exp_info']['exp_no'] = array(
        '#type' => 'textfield',
        '#title' => t('填写快递单号:    '),
        '#default_value' => '',
        '#size' => 64,
        '#maxlength' => 64,
        '#attributes' => array('style' => array('margin: 1em 0;')),
      );

      $form['exp_info']['exp_company_name'] = array(
        '#type' => 'textfield',
        '#title' => t('发货快递公司名称与联系电话: '),
        '#default_value' => '',
        '#description' => t('请填写快递公司名称和联系电话，方便用户查询。'),
        '#size' => 64,
        '#maxlength' => 128,
        '#attributes' => array('style' => array('margin: 1em 0;')),
      );

      $form['exp_info']['actions'] = array(
        '#type' => 'actions',
      );
      $form['exp_info']['actions']['save'] = array(
        '#type' => 'submit',
        '#value' => t('保存'),
        '#validate' => array('save_exp_info_validate'),
        '#submit' => array('save_exp_info'),
      );
 
    }


  } else {
    //This order can't belong to the shopping admin area.
    $form['no_record'] = array(
      '#type' => 'fieldset',
      '#title' => t('订单信息'), 
      '#weight' => 5, 
    );

    $form['no_record']['info'] = array(
      '#markup' => '没有记录，请仔细核对订单号',
    );

    $form['no_record']['link'] = array(
      '#markup' => '没有记录，请仔细核对订单号',
      '#type' => 'link',
      '#title' => t('返回'),
      '#href' => 'mobile-shopping-user-order-views',
      '#prefix' => '<div class="return-key" style="float: right;">',
      '#suffix' => '</div>', 
    );

  }
  return $form;
}

//submit exp info to user deatil table
function save_exp_info($form, $form_state) {

  //change order state from 1 paid to 2 dispatched
  $order_no = $form['detail_info']['order_no_value']['#value'];
  $area_id = $form['detail_info']['order_area_id']['#value'];
  db_update('mobile_shopping_user_order_table')
    ->condition('out_trade_no', $order_no)
    ->condition('area_id', $area_id)
    ->fields(array('order_state' => 2,))
    ->execute();

  /**
   * ???????????  if has split order, how to update multiple detail order
   **/
  //update exp info into user deatil table
  $exp_no_value = $form_state['values']['exp_no'];
  $exp_company_name = $form_state['values']['exp_company_name'];

  $rows = $form['detail_info']['detail_table']['#rows'];

  $remark = "订单号:" . "\n" . $order_no . "\n";
  $remark .= '商品信息: ' . "\n";
  foreach ($rows as $id => $row) {
    db_update('mobile_shopping_user_order_detail_table')
      ->condition('id', $id)
      ->fields(array(
        'exp_no' => $exp_no_value,
        'exp_company_name' => $exp_company_name,
        'exp_time_end' => date("YmdHis"),
      ))
      ->execute();

    $remark .= $row['title'] . ' ' . $row['volume'] . '件' . "\n";
  }
  //dpm($form);
  //send wechat template notify to user
  $openID = $form['user_info']['openid']['#value'];
  $post_data['touser'] = $openID;
  $post_data['template_id'] = 'H36KpZSi-MFZylmeAD5VAS8QZmzqsn5AeVgLFni98NA';
  $post_data['url'] = ''; //blank for servie url, ios is blank page, android nothing

  $element['first'] = array(
    'value' => "亲，宝贝已经启程了，好想快点来到你身边",
    'color' => "#173177",
  );
  $element['delivername'] = array(
    'value' => $exp_company_name,
  );

  $element['ordername'] = array(
    'value' => $exp_no_value,
  );

  $element['remark'] = array(
    'value' => $remark,
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

//validate submit value for exp no
function save_exp_info_validate($form, &$form_state){
  $exp_no_value = $form_state['values']['exp_no'];

  if ($exp_no_value == '') {
    form_set_error('exp_no', t('填写快递单号'));
  }


  $exp_company_name = $form_state['values']['exp_company_name'];
  if ($exp_company_name == '') {
    form_set_error('exp_company_name', t('填写快递公司和联系电话'));
  }
}
/**
 * End of mobile_shopping_user_order_detail_form.inc file name
 */

