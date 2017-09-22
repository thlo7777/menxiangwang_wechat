<?php

/*
 * Implement wechat_mobile_order_detail_form for mobile shopping order detail
 */
function wechat_mobile_order_detail_form($form, &$form_state, $order_id, $area_id){

  $area_term = taxonomy_term_load($area_id);
  $area_name = $area_term ? $area_term->name : '';

  $query = db_select('mobile_shopping_user_order_table', 't')
         ->condition('t.out_trade_no', $order_id)
         ->condition('t.area_id', $area_id)
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
      $t_order['area'] = $area_name;
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
      '#markup' => '<div>采购商品所在区域: ' . $t_order['area'] . '</div>',
    );
    $form['detail_info']['order_no'] = array(
      '#markup' => '<div>订单编号: ' . $order_id . '</div>',
    );
    $form['detail_info']['total_exp_fee'] = array (
      '#markup' => '订单邮费: ' .  $t_order['exp_fee'],
    );
    $form['detail_info']['order_no_value'] = array(
      '#type' => 'value',
      '#value' => $order_id,
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

    }

    $form['return link'] = array(
      '#type' => 'link',
      '#title' => t('返回订单列表'),
      '#href' => 'wechat-mobile-order/order-list',
      '#prefix' => '<div class="return-key" style="float: right;">',
      '#suffix' => '</div>', 
    );

  } else {
    //This order can't belong to the shopping admin area.
    $form['no_record'] = array(
      '#type' => 'fieldset',
      '#title' => t('订单信息'), 
      '#weight' => 5, 
    );

    $form['no_record']['info'] = array(
      '#markup' => '没有订单详情，请仔细核对订单号',
    );

    $form['no_record']['link'] = array(
      '#markup' => '没有订单详情，请仔细核对订单号',
      '#type' => 'link',
      '#title' => t('返回'),
      '#href' => 'wechat-mobile-order/order-list',
      '#prefix' => '<div class="return-key" style="float: right;">',
      '#suffix' => '</div>', 
    );

  }
  return $form;
}


/**
 * End of wechat_mobile_order_detail_form.inc file name
 */

