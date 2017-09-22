<?php
function menu_wechat_py_event_statistic_form($form, &$form_state){
//function menu_wechat_py_event_statistic_form(){

  $form = array();

  $query = db_select('wechat_event_statistic_table', 't')
           ->extend('PagerDefault')
           ->extend('TableSort')
           ->fields('t');

  $header = array(
    'openid' => '用户id',
    'msgtype' => array('data' => t('消息类型'), 'field' => 't.msgtype'),
    'event' => array('data' => t('事件类型'), 'field' => 't.event'),
    'eventkey' => '事件值',
    'createtime' => array('data' => t('接收时间'), 'field' => 't.createtime'),
  );

  $result = $query
            ->orderByHeader($header)
            ->limit(30)
            ->execute();

  $options = array();
  foreach($result as $id => $item){

    $options[] = array(
      'openid' => $item->openid,
      'msgtype' => $item->msgtype,
      'event' => $item->event,
      'eventkey' => $item->eventkey,
      'createtime' => date('Y年m月d日G点i分s秒', $item->createtime),
    );
  }


  $form['event_fieldset'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<div id="event-fieldset">',
    '#suffix' => '</div>',
    '#weight' => 1,
  );

  $form['event_fieldset']['pager'] = array('#markup' => theme('pager'));

  //theme table for variables theme_theming_qrscene_list_table_variables
  $form['event_fieldset']['theme_table_select'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('当前没有记录'),
  );


  return $form;

}

/**
 * End of wechat_py_admin_event_statistic_form.inc file name
 */
