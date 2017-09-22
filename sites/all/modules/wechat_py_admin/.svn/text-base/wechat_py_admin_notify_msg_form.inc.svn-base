<?php

/**
 * wechat py admin notify message form
 */
function menu_wechat_py_admin_notify_msg_form($form, &$form_state){
  
  //insert daily news created after node submitted
  variable_del('py_daily_news_created');

  $form['create_news'] = array(
    '#type' => 'submit',
    '#value' => t('创建一组新消息'),
    '#suffix' => t('创建一组新消息, 最多为十条。'),
    '#submit' => array('news_create'),
    '#limit_validation_errors' => array(),
    '#validate' => array(),
    '#weight' => -1,
  );
  

  $header = array(
    'title' => t('新闻标题'),
    'created' => t('创建时间'),
    'picture' =>  t('新闻图片'),
    'issue' => t('是否发布'),
    'broadcast' => t('是否群发'),
    'node_id' => t('操作'));

  $options = array();
  //fetch news from wechat_py_daily_news_broadcast_table
  //$result = db_query("SELECT news_index, broadcast, created FROM {wechat_py_daily_news_broadcast_table}");

  global $user;
  $query = db_select('wechat_py_daily_news_broadcast_table', 't')
    ->fields('t', array(
      'news_index',
      'broadcast',
      'created',
      'issue',))
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

    $item_link_form = array(
      '#type' => 'link',
      '#title' => t('编辑'),
      '#href' => 'wechat-py-admin/notify-message/' . $item->news_index . '/edit',
    );

    $options[$item->news_index] = array(
      'title' => $node->title->value(),
      'created' => t(date('Y年m月d日G点i分s秒', $item->created)),
      'picture' => array(
        'data' => array('#markup' => drupal_render($image_form),),
        //'data' => array($image_form),
      ),
      'issue' => array(
        'data' => array('#markup' => drupal_render($issue_form),),
        //'data' => array($issue_form),
      ),
      'broadcast' => array(
        'data' => array('#markup' => drupal_render($broadcast_form),),
        //'data' => array($broadcast_form),
      ),
      'node_id' => array(
        'data' => array('#markup' => drupal_render($item_link_form),),
        //'data' => array($item_link_form),
      ),
    );
  }

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => '新闻消息列表',
  );

  $form['fieldset']['tabselect'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('当前没有记录'),
  );
  
  $form['fieldset']['delete_news'] = array(
    '#type' => 'submit',
    '#value' => t('删除消息'),
    '#submit' => array('news_delete_news'),
    '#name' => 'news_delete_news',
    //No values return if set #validate is null
    //'#limit_validation_errors' => array(),
    //'#validate' => array(),
    '#attributes' => array('style' => array('float:right;')),
  );

  return $form;
}

//for news table
function news_delete_news($form, &$form_state){
  $values = $form_state['values']['tabselect'];
  foreach($values as $id => $item){
    if($id == $item){
      //clear all news node
      $query = db_select('wechat_py_daily_news_table', 't')
        ->fields('t', array('node_id'))
        ->condition('news_index', $item, '=');
      $result = $query->execute()->fetchAll();
      $nids = array();
      foreach ($result as $node) {
        $nids[] = $node->node_id;
      }
      node_delete_multiple($nids);
      //clear all news from news item table
      db_delete('wechat_py_daily_news_table')
        ->condition('news_index', $item)
        ->execute();
      //claer news table
      db_delete('wechat_py_daily_news_broadcast_table')
        ->condition('news_index', $item)
        ->execute();
    }
  }
}

function news_create($form, &$form_state){
  //$form_state['rebuild'] = FALSE;
  variable_set('py_daily_news_created', time());
  //jump to add daily news page
  $form_state['redirect'] = 'node/add/wechat_daily_news';
}


/**
 * End of wechat py admin notify message form
 */
