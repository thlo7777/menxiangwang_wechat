<?php

/**
 * wechat py admin  news item form
 */
function menu_wechat_py_admin_news_item_form($form, &$form_state, $variable){

  $form_state['news_index'] = $variable;

  //delete when insert news item into news table
  variable_del('py_daily_news_created');
  variable_del('py_daily_news_index');

  
  $header = array(
    'title' => t('新闻标题'),
    'picture' =>  t('新闻图片'),
    'node_id' => t('操作'));

  $query = db_select('wechat_py_daily_news_table', 't')
    ->fields('t', array('node_id'))
    ->condition('news_index', $variable, '=')
    ->orderBy('t.node_id', 'ASC');
  $result = $query->execute();

  $options = array();
  foreach($result as $id => $row){
    $raw_node = node_load($row->node_id);
    $node = entity_metadata_wrapper('node', $raw_node);
    $img_field = $node->field_news_picture->value();
      
    $item_link_form = array(
      '#type' => 'link',
      '#title' => t('编辑'),
      '#href' => 'node/' . $row->node_id . '/edit',
    );

    //Don't use absolutely dir for image_form, use publice://
    //$img_url = file_create_url($img_field['uri']);
    $image_form = array(
      '#theme' => 'image_style',
      '#path' => $img_field['uri'],
      '#style_name' => 'news_image160x100',
    );

    $options[$row->node_id] = array(
      'title' => $node->title->value(),
      'picture' => array(
        'data' => array('#markup' => drupal_render($image_form),),
        //'data' => array($image_form),
      ),
      'node_id' => array(
        'data' => array('#markup' => drupal_render($item_link_form),),
        //'data' => array($item_link_form),
      ),
    );
  }


  $form['table_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => '消息内容列表',
    '#description' => t('每次发布的消息最多为10条.'),
  );
  $form['table_fieldset']['tabselect'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('当前没有记录'),
  );


  $form['table_fieldset']['container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['table_fieldset']['container']['add_new_items'] = array(
    '#type' => 'submit',
    '#value' => t('增加一条新消息'),
    '#submit' => array('news_add_news_item'),
    '#name' => 'add_new_items',
    '#limit_validation_errors' => array(),
    '#validate' => array(),
  );

  $form['table_fieldset']['container']['delete_items'] = array(
    '#type' => 'submit',
    '#value' => t('删除消息'),
    '#submit' => array('news_delete_items'),
    '#name' => 'news_delete_items',
    //No values return if set #validate is null
    //'#limit_validation_errors' => array(),
    //'#validate' => array(),
    '#attributes' => array('style' => array('float:right;')),
  );

  //set issue checkbox
  $form['issue_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => '设置发布消息',
  );

  $form['issue_fieldset']['ajax_container'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="output_null">',
    '#suffix' => '</div>',
  );

  $issue_query = db_select('wechat_py_daily_news_broadcast_table', 't')
    ->fields('t', array(
      'broadcast',
      'issue',))
    ->condition('news_index', $variable, '=');
  $issue_result = $issue_query->execute()->fetchAssoc();

  $form['issue_fieldset']['issue'] = array(
    '#type' => 'checkbox',
    '#default_value' => $issue_result['issue'],
    '#title' => t('是否发布'),
    '#description' => t('选择即发布。选择后，用户可以从微信菜单热门活动里看到.'),
    '#ajax' => array(
      'callback' => 'ajax_set_issue_callback',
      'wrapper' => 'output_null',
      'effect' => 'fade',
    ),
  );

  $form['issue_fieldset']['broadcast'] = array(
    '#type' => 'checkbox',
    '#default_value' => $issue_result['broadcast'],
    '#title' => t('是否群发'),
    '#description' => t('选择即群发。选择群发后不能修改。每月群发消息最多为4条，群发前请在群发图文通知页面中仔细检查是否超过4条.'),

    '#ajax' => array(
      'callback' => 'ajax_set_broadcast_callback',
      'wrapper' => 'output_null',
      'effect' => 'fade',
    ),
  );
  if($issue_result['broadcast'] == 1){
    $form['issue_fieldset']['broadcast']['#disabled'] = TRUE;
  }

  //dpm($form);
  return $form;
}

//broadcast checkbox set
function ajax_set_broadcast_callback($form, $form_state) {
  //dpm($form);
  //dpm($form_state);
  if($form_state['values']['broadcast']){
    db_update('wechat_py_daily_news_broadcast_table')
    ->fields(array(
        'broadcast' => 1,
      ))
    ->condition('news_index', $form_state['news_index'])
    ->execute();

    //send news to all
    send_broad_news_all_users($form_state['news_index']);
  }
  $element = $form['issue_fieldset']['ajax_container'];

  return $element;
}

/*
 * send broad cast news to all users
 */
function send_broad_news_all_users($news_index){
  module_load_include('inc', 'wechat_api', 'wechat_api_send_msg_tpl');
  //compose news and upload to get mpnews media id
  $jason_news = compose_broadcast_news_template($news_index);
  if($jason_news != ''){
    //send to openid for test 
    //$result = wechat_api_send_preview_to_openid($jason_news->media_id, 'mpnews', 'o3plFw2bMRMzYBcBXCtx46DHNT9A');
    //$result = wechat_api_send_preview_to_openid($jason_news->media_id, 'mpnews', 'o3plFw2tpk_cnfW-aKm8D7OPwsp0');
    $result = wechat_api_send_news_to_all($jason_news->media_id, 'mpnews', true, 0);
    if($result == ''){
      watchdog('send news to all', 'send news to all failed in @line line, @filename',
        array(
        '@line' => __LINE__,
        '@filename' => __FILE__,
        ),
        $severity = WATCHDOG_ERROR);
    }
    return;
  }

  watchdog('send news to all', 'return null value in @line line:@filename',
    array(
    '@line' => __LINE__,
    '@filename' => __FILE__,
    ),
    $severity = WATCHDOG_ERROR);
}

//issue checkbox set
function ajax_set_issue_callback($form, $form_state) {
  //dpm($form);
  //dpm($form_state);
  if($form_state['values']['issue']){
    //update news table for issue checkbox
    db_update('wechat_py_daily_news_broadcast_table')
    ->fields(array(
        'issue' => 1,
      ))
    ->condition('news_index', $form_state['news_index'])
    ->execute();
  }else{
    db_update('wechat_py_daily_news_broadcast_table')
    ->fields(array(
        'issue' => 0,
      ))
    ->condition('news_index', $form_state['news_index'])
    ->execute();
  }

  $element = $form['issue_fieldset']['ajax_container'];
  return $element;
}


//for news item table
function news_delete_items($form, &$form_state){
  $values = $form_state['values']['tabselect'];

  $cleartable = true;
  foreach($values as $id => $item){
    if($id == $item){
      node_delete($item);
      db_delete('wechat_py_daily_news_table')
        ->condition('node_id', $item)
        ->execute();
    }else{
      $cleartable = false;
    }
  }
  if($cleartable){
    db_delete('wechat_py_daily_news_broadcast_table')
      ->condition('news_index', $form_state['news_index'])
      ->execute();
  }
}

function news_add_news_item($form, &$form_state){
  //$form_state['rebuild'] = FALSE;
  variable_set('py_daily_news_index', $form_state['news_index']);
  //jump to add daily news page
  $form_state['redirect'] = 'node/add/wechat_daily_news';
}

/**
 * Template to compose broadcast media news
 *
 * post data format 
 * {
 *    "articles": [
 * 		 {
 *       "thumb_media_id":"qI6_Ze_6PtV7svjolgs-rN6stStuHIjs9_DidOHaj0Q-mwvBelOXCFZiq2OsIU-p",
 *       "author":"xxx",
 * 			 "title":"Happy Day",
 * 			 "content_source_url":"www.qq.com",
 * 			 "content":"content",
 * 			 "digest":"digest",
 *       "show_cover_pic":"1"
 * 		 },
 * 		 {
 *       "thumb_media_id":"qI6_Ze_6PtV7svjolgs-rN6stStuHIjs9_DidOHaj0Q-mwvBelOXCFZiq2OsIU-p",
 *       "author":"xxx",
 * 			 "title":"Happy Day",
 * 			 "content_source_url":"www.qq.com",
 * 			 "content":"content",
 * 			 "digest":"digest",
 *       "show_cover_pic":"0"
 * 		 }
 *    ]
 * }
 */
function compose_broadcast_news_template($news_index){
  global $base_url;
  
  $result = '';

  $news_array = array();

  $query = db_select('wechat_py_daily_news_table', 't')
    ->fields('t', array('node_id'))
    ->condition('news_index', $news_index, '=')
    ->orderBy('t.node_id', 'ASC');
  $nids = $query->execute()->fetchAll();

  foreach ($nids as $key => $node_id) {
    $node = entity_metadata_wrapper('node', node_load($node_id->node_id));

    $title = $node->title->value();

    $img_field = $node->field_news_picture->value();
    $img_url = $img_field['uri'];
    $content = $node->field_news_content->value();

    //call temp media file to get image media_id
    $json_data = wechat_api_upload_temp_media_file($img_url, 'image');

    //$news['thumb_media_id'] = $json_data->media_id;
    $news['thumb_media_id'] = $node->field_cover_pic_thumb_media_id->value();
    $news['author'] = $node->field_news_author->value();
    $news['title'] = $title;
    $page_url = $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/news/' . $node_id->node_id . '/edit';
    //$news['content_source_url'] = $page_url;

    if($content['format'] == 'filtered_html' || $content['format'] == 'plain_text'){
      $value = $content['value'];
    }else if($content['format'] == 'full_html'){
      $value = $content['safe_value'];
    }
    //$news['content'] = find_text_from_html($value, 200); //define length is 200 chars
    $prepared_content = $node->field_send_prepared_content->value();
    $news['content'] = $prepared_content['value'];

    $news['digest'] = '';

//    if (empty($node->field_show_cover_pic->value())) {
//      dpm('null');
//    } else {
//      dpm($node->field_show_cover_pic->value());
//    }
    if (($node->field_show_cover_pic->value() == '0') ||
        empty($node->field_show_cover_pic->value())) {
      $news['show_cover_pic'] = '0';
    } else {
      $news['show_cover_pic'] = '1';
    }

    $news_array[] = $news;
  }

  $articles = array('articles' => $news_array);
  //check http://loosky.net/3069.html how to protect mess code
  $json_data = json_encode($articles, JSON_UNESCAPED_UNICODE);

  //call upload news api to get media news id
  $json_mediaid = wechat_api_upload_news_media($json_data);
  if($json_mediaid != ''){
    //update wechat_py_daily_news_broadcast_table, store media_id for upload news
    db_update('wechat_py_daily_news_broadcast_table')
    ->fields(array(
        'media_id' => $json_mediaid->media_id,
      ))
    ->condition('news_index', $news_index)
    ->execute();

    return $json_mediaid;
  }

  return $result;
}

function find_text_from_html($html, $length){
  $text = '';
  $html_obj = new simple_html_dom();

  $html_obj->load($html);
  $find_text = $html_obj->find('text');
  foreach($find_text as $value){
    $text .= trim($value->innertext);
  }
  $html_obj->clear(); 
  unset($html_obj);
  if($length < drupal_strlen($text)){
    $text = drupal_substr($text, 0, $length);
  }
  return $text;
}

/**
 * End of wechat py admin notify message form
 */
