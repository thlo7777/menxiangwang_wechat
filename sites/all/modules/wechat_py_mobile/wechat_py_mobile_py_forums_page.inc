<?php
function wechat_py_mobile_py_forums_page(){
  global $base_url;

  $click_icon = $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/imgs/hotel_forums_01.png';

  $form['title'] = array(
    '#type' => 'hidden',
    '#value' => '微论坛',
  );

  $query = new entityfieldquery();

  $query->entitycondition('entity_type', 'node')
  ->entitycondition('bundle', 'hotel_forums')
  ->propertycondition('status', NODE_PUBLISHED)
  ->propertyOrderBy('created', 'ASC');

  $result = $query->execute();
  if(count($result)){

    $nodes = node_load_multiple(array_keys($result['node']));
    foreach($nodes as $node){

      $enode = entity_metadata_wrapper('node', $node);
      $title = $enode->title->value();
      $title_img = $enode->field_hotel_image->value();
      $title_url = $enode->field_forum_url->value();

      $form['container-' . $node->nid] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('container-inline', 'clearfix'),
                               'id' => array($title)),
        '#prefix' => '<div class="item-list">',
        '#suffix' => '</div>',
        );

      $form['container-' . $node->nid]['title_image'] = array(
        '#theme' => 'image',
        '#path' => $title_img['uri'], 
        '#with' => '80px',
        '#height' => '80px',
        '#attributes' => array('class' => array('title-image')),
      );

      $form['container-' . $node->nid]['title'] = array(
        '#markup' => '<div class="title-text"><span>' . $title . '</span></div>', 
        '#attributes' => array('class' => array('title-title')),
      );

      $form['container-' . $node->nid]['click'] = array(
        '#theme' => 'image',
        '#path' => $click_icon, 
        '#with' => '40px',
        '#height' => '40px',
        '#attributes' => array('class' => array('title-click')),
      );

    }
  }

  return $form;
}

function deliver_py_forums_page_callback($page_result) {
  global $base_url;
  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/easing.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/scrollToTop.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/py_forums_page.css',
  );

  //$js = array();
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-scrollToTop.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/py_forums_page.js',
  );

/*
  echo '<pre>';
  print_r($page_result);
  echo '</pre>';
*/

  $title = $page_result['title']['#value'];
  $title .= '-梦乡平遥游';

  $render['html_page'] = array(
    '#theme' => 'wechat_py_mobile_page',
    '#head_title' => $title,
    '#page' => $page_result,
    '#styles' => $css,
    '#scripts' => $js,
  );

  print drupal_render($render);
}

/**
 * End of wechat_py_mobile_py_forums_page.inc file name
 */
