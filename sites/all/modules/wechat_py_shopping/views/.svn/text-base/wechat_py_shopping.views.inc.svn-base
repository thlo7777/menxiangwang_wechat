<?php
/*
 * Implement hook_views_data
 */
function wechat_py_shopping_views_data() {
  $data['wechat_py_merchant_group_table']['table']['group'] = 'wechat_py_merchant_group_table';
  $data ['wechat_py_merchant_group_table']['table']['base'] = array(
    'field' => 'group_id', // This is the identifier field for the view.
    'title' => 'wechat_py_merchant_group_table',
    'help' => 'merchant group table',
    'weight' => -10,
  );

  // Next, describe each of the individual fields in this table to Views. This
  // is done by describing $data['example_table']['FIELD_NAME']. This part of
  // the array may then have further entries:
  //   - title: The label for the table field, as presented in Views.
  //   - help: The description text for the table field.
  //   - relationship: A description of any relationship handler for the table
  //     field.
  //   - field: A description of any field handler for the table field.
  //   - sort: A description of any sort handler for the table field.
  //   - filter: A description of any filter handler for the table field.
  //   - argument: A description of any argument handler for the table field.
  //   - area: A description of any handler for adding content to header,
  //     footer or as no result behaviour.
  //
  // The handler descriptions are described with examples below.

  $data ['wechat_py_merchant_group_table']['group_id'] = array(
    'title' => t('group id'),
    'help' => t('merchant group id from wechat.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data ['wechat_py_merchant_group_table']['group_name'] = array(
    'title' => t('group name'),
    'help' => t('merchant group name.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  //mobile shopping order table for views
  $data['mobile_shopping_user_order_table']['table']['group'] = 'mobile_shopping_user_order_table';

  $data['mobile_shopping_user_order_table']['table']['base'] = array(
    'field' => 'id',
    'title' => 'mobile_shopping_user_order_table',
    'help' => 'mobile shopping user order table',
    'weight' => -9,
  );

  $data['mobile_shopping_user_order_table']['id'] = array(
    'title' => t('纪录索引'),
    'help' => t('商城客户表记录索引'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  $data['mobile_shopping_user_order_table']['out_trade_no'] = array(
    'title' => t('订单号'),
    'help' => t('商城客户订单号'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mobile_shopping_user_order_table']['order_state'] = array(
    'title' => t('订单状态'),
    'help' => t('商城客户订单状态'),
    'field' => array(
      //'handler' => 'views_handler_field',
      'handler' => 'wechat_py_shopping_views_handler_field_order_state', 
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mobile_shopping_user_order_table']['time_end'] = array(
    'title' => t('订单支付时间'),
    'help' => t('商城客户订单支付时间'),
    'field' => array(
      'handler' => 'wechat_py_shopping_views_handler_field_time_end',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mobile_shopping_user_order_table']['area_id'] = array(
    'title' => t('区域分类'),
    'help' => t('商城客户订单区域分类'),
    'field' => array(
      //'handler' => 'views_handler_field',
      'handler' => 'wechat_py_shopping_views_handler_field_area_id',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mobile_shopping_user_order_table']['total_fee'] = array(
    'title' => t('订单金额'),
    'help' => t('商城客户订单金额'),
    'field' => array(
      //'handler' => 'views_handler_field',
      'handler' => 'wechat_py_shopping_views_handler_field_total_fee',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['mobile_shopping_user_order_table']['area_exp_fee'] = array(
    'title' => t('订单邮费'),
    'help' => t('商城客户订单邮费'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
  return $data;
}

/**
 * End of wechat_py_shopping.views.inc file name
 */
