<?php

/**
 * search user and add user to forward table form
 *
 * @return form
 * @author Me
 **/
function menu_wechat_py_admin_forward_user_form($form, &$form_state){
  // code...
  $form['search'] = array(
    '#type' => 'fieldset',
    '#title' => t('搜索用户'),
  );

  $form['search']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix', 'container-inline')),
  );

  $form['search']['status']['keyword'] = array(
    '#type' => 'textfield',
    '#title' => t('输入用户昵称'), 
    '#default_value' => '',
    '#size' => 50,
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['search']['status']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('search'),
  );


  if(array_key_exists('keyword', $form_state['temporary'])) {

    $header = array(
      'subscribe' => '关注',
      'headimgurl' => '头像',
      'nickname' => '昵称',
      'sex' => '性别',
      'city' => '城市',
      'province' => '省份',
      'openid' => array('data' => t('关注用户ID'), 'field' => 't.openid'),
    );

    //start search by nickname
    $keyword = $form_state['temporary']['keyword'];
    $query = db_select('wechat_py_subscribe_user_table', 't')
             //->condition('nickname', '%' . db_like($keyword) . '%', 'LIKE')
             ->fields('t');
    $result = $query->execute();
    $options = array();
    foreach ($result as $id => $item) {

      $nick_name = base64_decode($item->nickname);
      if (!preg_match('/' . $keyword . '/', $nick_name)) {
        continue;
      }
      // code...
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

      //Should use ++$id, then options and tableselect can return correct index value. Do not use $id 
      $options[++$id] = array(
        'subscribe' => $item->subscribe ? '':'撤销',
        'headimgurl' => array(
          'data' => array(
            '#theme' => 'image',
            '#path' => $item->headimgurl,
            '#attributes' => array('style' => 'width:80px;'),
          ),
        ),
        'nickname' => $nick_name,
        'sex' => $gender,
        'city' => $item->city,
        'province' => $item->province,
        'openid' => $item->openid,
//        'openid' => array(
//          'data' => array(
//            '#type' => 'hidden',
//            '#value' => $item->openid,
//            '#name' => 'cell_openid_value[' . $id . ']',
//          ),
//        ),
      );
    }

    $form['search_user_result'] = array(
      '#type' => 'fieldset',
      '#title' => t('用户搜索结果'),
      '#prefix' => '<div id="search-user-result">',
      '#suffix' => '</div>',
    );
    
    $form['search_user_result']['theme_table_select'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t('当前没有记录'),
    );

    $form['search_user_result']['add_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Add'),
      '#prefix' => '<div>请选择用户并加入转发用户表</div>',
    );

  }


  //for name of openid column
  $form['cell_openid_value'] = array('#type' => 'value',);

  $form['#submit'][] = 'search_user_submit';

  return $form;
}

function search_user_submit($form, &$form_state){
  switch ($form_state['values']['op']) {
    case t('search'):
      $form_state['temporary']['keyword'] = $form_state['values']['keyword'];
      $form_state['rebuild'] = TRUE;
      break;
    case t('Add'):
      $selected = $form_state['values']['theme_table_select'];
      $openids = $form_state['values']['cell_openid_value'];
      foreach ($selected as $id => $index) {
        if ($id == $index) {
          $query = db_select('wechat_py_subscribe_user_table', 't')
                   ->condition('openid', $openids[$index])
                   ->fields('t');
          $result = $query->execute()->fetchAssoc();
          db_insert('wechat_py_forward_user_table')
            ->fields(array(
              'openid' => $result['openid'],
              'headimgurl' => $result['headimgurl'],
              'nickname' => $result['nickname'],
              'subscribe' => $result['subscribe'],
              'sex' => $result['sex'],
              'city' => $result['city'],
              'province' => $result['province'],
              'country' => $result['country'],))
            ->execute();
        }
      }
      break;
  }

}

/**
 * forward news to user form
 *
 * @return void
 * @author Me
 **/
function menu_wechat_py_admin_forward_news_form($form, &$form_state){
  global $user;

  $form['forward'] = forward_user_table_form();

  $header = array(
    'title' => t('新闻标题'),
    'picture' =>  t('新闻图片'),
    'created' => t('创建时间'),
    'issue' => t('发布'),
    'broadcast' => t('群发'));

  $options = array();
  $query = db_select('wechat_py_daily_news_broadcast_table', 't')
    ->fields('t')
    ->condition('userid', $user->uid, '=')
    ->orderBy('t.created', 'DESC');

  $result = $query->execute();
  foreach($result as $key => $item){
    //get the first news title and content for tableselect
    $news_query = db_select('wechat_py_daily_news_table', 't')
      ->fields('t', array('node_id'))
      ->condition('news_index', $item->news_index, '=')
      ->orderBy('t.node_id', 'ASC');
    $news_result = $news_query->execute()->fetchAssoc();
    if(!isset($news_result['node_id'])){
      continue;
    }

    $raw_node = node_load($news_result['node_id']);
    $node = entity_metadata_wrapper('node', $raw_node);

    $img_field = $node->field_news_picture->value();
    //Don't use absolutely dir for image_form, use publice://
    //$img_url = file_create_url($img_field['uri']);
    $image_form = array(
      '#theme' => 'image_style',
      '#path' => $img_field['uri'],
      '#style_name' => 'news_image160x100',
    );

    if($item->issue){
      $issue_form = array(
        '#type' => 'checkbox',
        //use attributes but #disabled
        '#attributes' => array('disabled' => 'disabled', 'checked' => true),
        //'#disabled' => true,
      );
    }else{
      $issue_form = array(
        '#type' => 'checkbox',
        //use attributes but #disabled
        '#attributes' => array('disabled' => 'disabled', 'unchecked' => true),
        //'#disabled' => true,
      );
    }
    if($item->broadcast){
      $broadcast_form = array(
        '#type' => 'checkbox',
        '#attributes' => array('disabled' => 'disabled', 'checked' => true),
      );
    }else{
      $broadcast_form = array(
        '#type' => 'checkbox',
        '#attributes' => array('disabled' => 'disabled', 'unchecked' => true),
      );
    }

    $options[$item->news_index] = array(
      'title' => $node->title->value(),
      'picture' => array(
        'data' => array('#markup' => drupal_render($image_form),),
        //'data' => array($image_form),
      ),
      'created' => t(date('Y年m月d日G点i分s秒', $item->created)),
      'issue' => array(
        'data' => array('#markup' => drupal_render($issue_form),),
        //'data' => array($issue_form),
      ),
      'broadcast' => array(
        'data' => array('#markup' => drupal_render($broadcast_form),),
        //'data' => array($broadcast_form),
      ),
    );
  }

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => '新闻消息列表',
  );

  $form['fieldset']['news_tableselect'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('当前没有记录'),
  );

  $form['forward_submit'] = array(
    '#type' => 'submit',
    '#value' => t('转发消息'),
    '#prefix' => '<div>请选择消息并转发</div>',
  );

  //for name of openid column
  $form['cell_openid_value'] = array('#type' => 'value',);

  $form['#submit'][] = 'forward_user_submit';

  return $form;
}

function forward_user_table_form()
{
  $query = db_select('wechat_py_forward_user_table', 't')->fields('t');
  $result = $query->execute();

  $header = array(
    'subscribe' => '关注',
    'headimgurl' => '头像',
    'nickname' => '昵称',
    'sex' => '性别',
    'city' => '城市',
    'province' => '省份',
    'openid' => array('data' => t('关注用户ID'), 'field' => 't.openid'),
  );

  $options = array();
  foreach ($result as $id => $item) {
      // code...
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

    $options[++$id] = array(
      'subscribe' => $item->subscribe ? '':'撤销',
      'headimgurl' => array(
        'data' => array(
          '#theme' => 'image',
          '#path' => $item->headimgurl,
          '#attributes' => array('style' => 'width:80px;'),
        ),
      ),
      'nickname' => $item->nickname,
      'sex' => $gender,
      'city' => $item->city,
      'province' => $item->province,
      'openid' => array(
        'data' => array(
          '#type' => 'hidden',
          '#value' => $item->openid,
          '#name' => 'cell_openid_value[' . $id . ']',
        ),
      ),
    );
  }

  $form['forward_user_table'] = array(
    '#type' => 'fieldset', 
    '#title' => t('转发用户表'), 
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );

  $form['forward_user_table']['theme_table_select'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('当前没有记录'),
  );

  $form['forward_user_table']['del_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
    '#prefix' => '<div>请选择用户删除</div>',
  );

  return $form;
}

function forward_user_submit($form, &$form_state){
  switch ($form_state['values']['op']) {
    case t('Delete'):
      $selected = $form_state['values']['theme_table_select'];
      $openids = $form_state['values']['cell_openid_value'];
      foreach ($selected as $id => $index) {
        if ($id == $index) {
          db_delete('wechat_py_forward_user_table')
            ->condition('openid', $openids[$index])
            ->execute();
        }
      }
      break;
    case t('转发消息'):
      $selected = $form_state['values']['news_tableselect'];
      foreach ($selected as $id => $index) {
        if ($id == $index) {
          //forward news to openids, use preview api
          forward_news_to_users($index);
        }
      }
      break;
  }
}

/*
 * forward news to selected users
 */
function forward_news_to_users($news_index){

  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');

  //get media_id from news table or compose it
  /*
  $news_result = db_select('wechat_py_daily_news_broadcast_table', 't')
                  ->condition('news_index', $news_index)
                  ->fields('t', array('media_id'))
                  ->execute()
                  ->fetchAssoc();

  if($news_result['media_id'] != ''){
    $media_id = $news_result['media_id'];
  }else{
    module_load_include('inc', 'wechat_py_admin', 'wechat_py_admin_notify_news_item_form');
    $jason_news = compose_broadcast_news_template($news_index);
    if($jason_news != ''){
      $media_id = $jason_news->media_id;
    }
  }
  */
  module_load_include('inc', 'wechat_py_admin', 'wechat_py_admin_notify_news_item_form');
  $jason_news = compose_broadcast_news_template($news_index);
  if($jason_news != ''){
    $media_id = $jason_news->media_id;
  }

  $forward_result = db_select('wechat_py_forward_user_table', 't')
                      ->fields('t', array('openid'))
                      ->execute();
  foreach ($forward_result as $item) {
    // code...
    $result = wechat_api_send_preview_to_openid($media_id, 'mpnews', $item->openid);
    if($result == ''){
      watchdog('forward news to user', 'forward news to user failed in @line line, @filename',
        array(
        '@line' => __LINE__,
        '@filename' => __FILE__,
        ),
        $severity = WATCHDOG_ERROR);
      continue;
    }
  }
}

/**
 * End of wechat py admin forward news to user management form
 */
