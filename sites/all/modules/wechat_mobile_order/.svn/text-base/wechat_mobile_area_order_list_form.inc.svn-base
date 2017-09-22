<?php

/**
 * wechat_mobile_area_order_list_form.inc
 */
function menu_wechat_mobile_area_order_list_form($form, &$form_state){

  global $user;

  $curr_user = user_load($user->uid);
  if (empty($curr_user->field_product_category_term)) {
	$form['error'] = array (
		'#markup' => '没有地区分类，无法查询',
	);
	return $form;
  }

  $term_id = $curr_user->field_product_category_term['und'][0]['tid'];

  $form = area_order_list_filter_form();

  $session = isset($_SESSION['wechat_area_order_filter']) ? $_SESSION['wechat_area_order_filter'] : NULL;

  //dpm($session);


  $form['#submit'][] = 'area_order_form_submit';

  $query = NULL;
  $total_order = 0;
  if ($session == NULL) {
    $date1 = date('Ymd', strtotime("first day of this month"));
    $date2 = date('Ymd') . '235959';
    $query = db_select('mobile_shopping_user_order_table', 't')
             ->condition('t.time_end', $date1, '>=')
             ->condition('t.time_end', $date2, '<=')
             ->condition('t.order_state', 2, '=')
             ->condition('t.area_id', $term_id, '=')
             ->extend('PagerDefault')
             ->extend('TableSort')
             ->fields('t');

  } else {
    $date1 = date('Ymd', strtotime($session['date1']));
    $date2 = date('Ymd', strtotime($session['date2'])) . '235959';

    $query = db_select('mobile_shopping_user_order_table', 't')
             ->condition('t.time_end', $date1, '>=')
             ->condition('t.time_end', $date2, '<=')
             ->condition('t.order_state', 2, '=')
             ->condition('t.area_id', $term_id, '=')
             ->orderBy('t.time_end', 'DESC')
             ->extend('PagerDefault')
             ->extend('TableSort')
             ->fields('t');
  }

  $header = array(
    //'openid' => '用户ID',
    'out_trade_no' => '订单号',
    'order_state' => '订单状态',
    'time_end' => array('data' => t('支付时间'), 'field' => 't.time_end'),
    'total_fee' => '订单价格',
    'area_exp_fee' => '邮费',
    //'order_detail' => '订单详情',
    //'order_addr' => '收货地址',
    'area_id' => '区域',
  );

  $result = $query
            ->orderByHeader($header)
            ->limit(30)
            ->execute();

  $options = array();
  $order_total = 0.00;
  $order_exp_fee = 0.00;
  foreach ($result as $row) {
    $total_order += 1;
    $order_total += floatval($row->total_fee)/100;
    $order_exp_fee += floatval($row->area_exp_fee);

    $os_text = '';
    switch ($row->order_state) {
      case '2':
        $os_text = '已发货';
        break;
      default:
        $os_text = '未发货';
        break;
    }


    $area_term = taxonomy_term_load($row->area_id);
    $area_name = $area_term ? $area_term->name : '';

//    $$order_no_link = array(
//      '#markup' => l($row->out_trade_no, 'wechat-py-mobile/user-order-detail/' . $row->out_trade_no),
//    );
    $order_no_link = array(
      '#type' => 'link',
      '#title' => $row->out_trade_no,
      '#href' => 'wechat-mobile-order/order-detail/' . $row->out_trade_no . '/' . $row->area_id,
    );

    $options[] = array(
      //'openid' => $row->openid,
      'out_trade_no' => drupal_render($order_no_link),
      'order_state' => $os_text,
      'time_end' => date('Y-m-d H:i:s', strtotime($row->time_end)),
      'total_fee' => number_format(floatval($row->total_fee)/100, 2),
      'area_exp_fee' => number_format($row->area_exp_fee, 2),
      //'order_detail' => $row->order_detail,
      //'order_addr' => $row->order_addr,
      'area_id' => $area_name,
    );
  }
  
  $form['theme_table'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('当前没有记录'),
  );

  $form['pager'] = array('#markup' => theme('pager'));

  $form['order_total'] = array(
    '#markup' => '本页 订单数量: ' . $total_order . 
                 '个 订单总金额: ' . number_format($order_total, 2) .
                 '  邮费合计: ' . number_format($order_exp_fee, 2),
  );



  return $form;
}

function area_order_list_filter_form() {

  $session = isset($_SESSION['wechat_area_order_filter']) ? $_SESSION['wechat_area_order_filter'] : NULL;
  // Regular filters

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('查询条件'),
  );

  $form['filters']['datec'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix', 'container-inline')),
  );

  $today = date('Y-m-d');

  $form['filters']['datec']['date1_filters'] = array(
    '#type' => 'date_popup',
    //'#default_value' => $today,
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => 'm/d/Y',
    '#date_increment' => 1,
    '#date_year_range' => '-3:+5',
  );

  if ($session != NULL) {
    $form['filters']['datec']['date1_filters']['#default_value'] = $session['date1'];
  } else {
    $form['filters']['datec']['date1_filters']['#default_value'] = date('Y-m-d', strtotime("first day of this month"));
  }

  $form['filters']['datec']['date2_filters'] = array(
    '#type' => 'date_popup',
    //'#default_value' => $today,
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => 'm/d/Y',
    '#date_increment' => 1,
    '#date_year_range' => '-3:+5',
  );
  if ($session != NULL) {
    $form['filters']['datec']['date2_filters']['#default_value'] = $session['date2'];
  } else {
    $form['filters']['datec']['date2_filters']['#default_value'] = $today;
  }

  $form['filters']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['filters']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
  );

  if (isset($session)) {
    $form['filters']['actions']['undo'] = array('#type' => 'submit', '#value' => t('Undo'));
  }

  return $form;
}

function area_order_form_submit($form, &$form_state) {

  //dpm($form_state);
  switch ($form_state['values']['op']) {
    case t('Filter'):
      // Apply every filter that has a choice selected other than 'any'.
      $_SESSION['wechat_area_order_filter'] = array (
        'date1' => $form_state['values']['date1_filters'],
        'date2' => $form_state['values']['date2_filters'],
      );
      break;
    case t('Undo'):
      unset($_SESSION['wechat_area_order_filter']);
      break;
  }

}
/**
 * wechat_mobile_order_list_form.inc
 */

