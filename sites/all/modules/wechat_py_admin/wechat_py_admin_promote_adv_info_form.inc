<?php
function menu_wechat_py_admin_promote_adv_info_form($form, &$form_state){
  $form = array();
  global $user;
  global $base_url;

  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'py_issue_info')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->propertyCondition('uid', $user->uid);

  $result = $query->execute();
  if(count($result)){
    $nodes = node_load_multiple(array_keys($result['node']));
    foreach($nodes as $id => $node){
      drupal_goto('node/' . $node->nid);
      break;
    }
  }else{
    //py info issue panels
    $form['welcome'] = array(
      '#type' => 'link',
      '#title' => '创建信息发布',
      '#href' => $base_url . '/py-info-create-node',
      '#prefix' => '<strong>欢迎进入梦乡平遥游信息发布平台, 请点击</strong>',
    );
  }

  //drupal_goto('node/add/py_issue_info');
  return $form;
}
/**
 * End of wechat_py_admin_promote_adv_info_form.inc file name
 */

