<?php
function menu_wechat_py_admin_hotel_community_form($form, &$form_state){

  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'hotel_forums')
  ->propertyCondition('status', NODE_PUBLISHED)
  ->propertyOrderBy('created', 'ASC');

  $items = array();
  $result = $query->execute();
  if(count($result)){
    $nodes = node_load_multiple(array_keys($result['node']));
    foreach($nodes as $id => $node){
      $enode = entity_metadata_wrapper('node', $node);

      $title = $enode->title->value();
      $img_url = $enode->field_hotel_image->value();

      $render['container'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('container-inline')),
      );
      $render['container']['image'] = array(
        '#theme' => 'image',
        '#path' => $img_url['uri'], 
        '#with' => '80px',
        '#height' => '80px',
        '#attributes' => array('class' => array('title-image')),
      );
      $render['container']['text'] = array(
        '#markup' => '<div class="title-text"><span>' . $title . '</span></div>', 
      );
      $render['container']['link'] = array(
        '#type' => 'link',
        '#title' => '编辑', 
        '#href' => 'node/' . $node->nid . '/edit',
        '#attributes' => array('class' => array('title-link')),
        '#prefix' => '<div class="link-center">',
        '#suffix' => '</div',
      );
      $items[] = array(
        'data' => drupal_render($render['container']),
        'id' => 'item-id-' . $id,
        'class' => array('forum-each-item'),
      );
    }

    $form['title_intro'] = array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#type' => 'ul',
      '#attributes' => array('class' => array('title-intro'),
                             'style' => array('padding: 0;')),
    );

  }else{
    $form['welcome'] = array(
      '#type' => 'fieldset',
      '#prefix' => '<strong>目前没有记录</strong>',
      '#weight' => 1,
    );
  }

  $form['add'] = array(
    '#type' => 'submit',
    '#value' => t('增加'),
    '#weight' => 100,
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_admin') . '/css/hotel_community_form.css',
  );

  $form['#submit'][] = 'add_first_level_submit';
  return $form;
}

//record all all submit event
function add_first_level_submit($form, &$form_state){
  $op = $form_state['values']['op'];
  switch ($op) {
    case '增加':
      drupal_goto('node/add/hotel_forums');
      break;

    default:
      break;
  }
}

/**
 * End of wechat_py_admin_hotel_community_form.inc file name
 */
