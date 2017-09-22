<?php

function wechat_py_mobile_news_page($nid){

  $node = entity_metadata_wrapper('node', node_load($nid));

  $title = $node->title->value();
  $created = $node->created->value();
  $img_field = $node->field_news_picture->value();
  $img_url = file_create_url($img_field['uri']);
  $content = $node->field_news_content->value();

  $form['container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('top-line')),
  );

  $form['title'] = array(
    '#prefix' => '<div class="news-title"><h2>',
    '#markup' => $title,
    '#suffix' => '</h2></div>', 
  );

  $time = date('Y年m月d日 ', $created);
  $form['wechat_service'] = array(
    '#prefix' => '<div class="wechat-service">',
    '#markup' => $time . '<a href="weixin://profile/gh_cfb05884c3e6">梦乡网</a>',
    '#suffix' => '</div>', 
  );

  $form['image'] = array(
    '#theme' => 'image',
    '#path' => $img_field['uri'], 
    '#attributes' => array('class' => 'news_picture'),
  );

/*
  echo '<pre>';
  print_r($content);
  echo '</pre>';
*/

  if($content['format'] == 'filtered_html' || $content['format'] == 'plain_text'){
    $value = $content['value'];
  }else if($content['format'] == 'full_html'){
    $value = $content['safe_value'];
  }

  $form['content'] = array(
    '#prefix' => '<div class="news-content">',
    //use safe_value when textarea format is full_html
    '#markup' => $value,
    '#suffix' => '</div>', 
  );

  //$node = node_load($nid);
  //return node_view($node);
  return $form;
}

function deliver_news_html_page_callback($page_result) {
  global $base_url;
  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/news_page.css',
  );

  $js = array();
/*
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-ui.min.js',
  );
*/

/*
  echo '<pre>';
  print_r($page_result);
  echo '</pre>';
*/

  $title = $page_result['title']['#markup'];
  $title .= '-梦乡网';

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
 * End of wechat py admin notify message form
 */
