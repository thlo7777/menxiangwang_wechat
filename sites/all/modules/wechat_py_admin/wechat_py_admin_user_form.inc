<?php

/**
 * wechat py admin follow user mangement form
 */
function menu_wechat_py_admin_user_form($form, &$form_state){

  $form['filter'] = wechat_user_filter_form();

  $session = isset($_SESSION['wechat_user_filter']) ? $_SESSION['wechat_user_filter'] : NULL;
  $session_nickname = isset($_SESSION['wechat_user_filter_nickname']) ? $_SESSION['wechat_user_filter_nickname'] :NULL;

  if ($session_nickname) {
      $form['filter']['filters']['status']['search_nickname']['#default_value'] = $session_nickname;
  }

  if (isset($session)) {
    switch ($session) {
      case 'unsubscribe':
          if ($session_nickname) {
            $total = db_select('wechat_py_subscribe_user_table', 't')
                     ->fields('t')
                     ->condition('subscribe', 0)
                     ->condition('nickname', base64_encode($session_nickname))
                     ->execute()
                     ->rowCount();

            $query = db_select('wechat_py_subscribe_user_table', 't')
                     ->condition('subscribe', 0)
                     ->condition('nickname', base64_encode($session_nickname))
                     ->extend('PagerDefault')
                     ->extend('TableSort')
                     ->fields('t');
          } else {
            $total = db_select('wechat_py_subscribe_user_table', 't')
                     ->fields('t')
                     ->condition('subscribe', 0)
                     ->execute()
                     ->rowCount();

            $query = db_select('wechat_py_subscribe_user_table', 't')
                     ->condition('subscribe', 0)
                     ->extend('PagerDefault')
                     ->extend('TableSort')
                     ->fields('t');
          }
        break;

    }
  }else{
    if ($session_nickname) {
        $total = db_select('wechat_py_subscribe_user_table', 't')
                 ->fields('t')
                 ->condition('nickname', base64_encode($session_nickname))
                 ->execute()
                 ->rowCount();

        $query = db_select('wechat_py_subscribe_user_table', 't')
                 ->condition('nickname', base64_encode($session_nickname))
                 ->extend('PagerDefault')
                 ->extend('TableSort')
                 ->fields('t');
             //->orderBy('t.subscribe_time', 'ASC');
    } else {
        $total = db_select('wechat_py_subscribe_user_table', 't')->fields('t')->execute()->rowCount();

        $query = db_select('wechat_py_subscribe_user_table', 't')
                 ->extend('PagerDefault')
                 ->extend('TableSort')
                 ->fields('t');
             //->orderBy('t.subscribe_time', 'ASC');
    }

  }

  $header = array(
    'subscribe' => '关注',
    'headimgurl' => '头像',
    'nickname' => '昵称',
    'subscribe_time' => array('data' => t('关注时间'), 'field' => 't.subscribe_time'),
    'sex' => '性别',
    'city' => '城市',
    'province' => '省份',
    'openid' => array('data' => t('关注用户ID'), 'field' => 't.openid'),
  );

  $result = $query
            ->orderByHeader($header)
            ->limit(30)
            ->execute();

  $options = array();
  foreach($result as $id => $item){
    $image_form = array(
      '#theme' => 'image_style',
      '#path' => $item->headimgurl,
      '#style_name' => 'thumbnail',
    );

    if($item->sex == 1){
      $gender = '男';
    }else if($item->sex == 2){
      $gender = '女';
    }else{
      $gender = '未知';
    }

    $options[] = array(
      'subscribe' => $item->subscribe ? '':'撤销',
      'headimgurl' => array(
        'data' => array(
          '#theme' => 'image',
          '#path' => $item->headimgurl,
          '#attributes' => array('style' => 'width:80px;'),
        ),
      ),
      'nickname' => base64_decode($item->nickname),
      //'nickname' => $item->nickname,
      'subscribe_time' => date('Y年m月d日G点i分s秒', $item->subscribe_time),
      'sex' => $gender,
      'city' => $item->city,
      'province' => $item->province,
      'openid' => $item->openid,
//      'openid' => array(
//        'data' => array(
//          '#type' => 'hidden',
//          '#value' => $item->openid,
//          '#name' => 'cell_openid_value[' . $id . ']',
//        ),
//      ),
    );
  }


  $form['user_info_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('关注用户信息列表'),
    '#prefix' => '<div id="user-info-fieldset">',
    '#suffix' => '</div>',
    '#weight' => 1,
  );

  $form['user_info_fieldset']['pager'] = array('#markup' => theme('pager'));

  //theme table for variables theme_theming_qrscene_list_table_variables
  $form['user_info_fieldset']['theme_table_select'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('当前没有记录'),
  );

  $form['user_info_fieldset']['total number'] = array(
    '#markup' => '累计关注人数总计: ' . $total,
  );

/*
  $form['user_info_fieldset']['submit_test'] = array(
    '#type' => 'submit',
    '#value' => t('新消息'),
    '#submit' => array('test_options'),
    //'#limit_validation_errors' => array(),
    //'#validate' => array(),
  );
*/

  $form['cell_openid_value'] = array('#type' => 'value',);

  $form['#submit'][] = 'user_form_submit';
  return $form;
}

function wechat_user_filters() {
  // Regular filters
  $filters = array(
    'title' => t('用户信息'),
    'options' => array(
      '[any]' => t('any'),
      'unsubscribe' => t('取消关注'),
    ),
  );
  return $filters;
}

function wechat_user_filter_form() {

  $session = isset($_SESSION['wechat_user_filter']) ? $_SESSION['wechat_user_filter'] : NULL;
  $session_nickname = isset($_SESSION['wechat_user_filter_nickname']) ? $_SESSION['wechat_user_filter_nickname'] :NULL;

  // Regular filters
  $filters = wechat_user_filters();

  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only items where'),
  );

  $form['filters']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix', 'container-inline')),
  );

  $form['filters']['status']['filters'] = array(
    '#type' => 'select',
    '#options' => $filters['options'],
    '#title' => $filters['title'],
    '#default_value' => '[any]',
    '#attributes' => array('class' => array('filters')),
  );
  if (isset($session)) {
    $form['filters']['status']['filters']['#value'] = $session;
  }

  $form['filters']['status']['search_nickname'] = array(
    '#type' => 'textfield', 
    '#title' => t('用户昵称搜索'), 
    '#default_value' => "", 
    '#size' => 40, 
    '#maxlength' => 128, 
  );

  $form['filters']['status']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['filters']['status']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
  );

  if (isset($session) || $session_nickname) {
    $form['filters']['status']['actions']['undo'] = array('#type' => 'submit', '#value' => t('Undo'));
  }

  return $form;
}

function user_form_submit($form, &$form_state) {

  switch ($form_state['values']['op']) {
    case t('Filter'):
      // Apply every filter that has a choice selected other than 'any'.
      if($form_state['values']['filters'] != '[any]') {
        $_SESSION['wechat_user_filter'] = $form_state['values']['filters'];
        
      }
      
      if (!empty($form_state['values']['search_nickname']) && $form_state['values']['search_nickname'] != "") {
          $_SESSION['wechat_user_filter_nickname'] = $form_state['values']['search_nickname'];
      }
      break;
    case t('Undo'):
      unset($_SESSION['wechat_user_filter']);
      unset($_SESSION['wechat_user_filter_nickname']);
      break;
  }

}

/**
 * End of wechat py admin py user management form
 */
