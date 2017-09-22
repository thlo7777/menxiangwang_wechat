<?php

//page for city culture information page
function wechat_mobile_city_culture_article_page($arg) {

  global $base_url;
  $page = array();

  //check if it's a mobile browser, use touch event feature to test.
  $page['scripts'] = 
  '<script>
    function isMobile() {
      try{ document.createEvent("TouchEvent"); return true; }
      catch(e){ return false; }
    }
    if (!isMobile()) {
      window.location.replace("http://mxweixin.dreamland360.com/content/默认的404错误");
    }
  </script>';

  $node = node_load($arg);
  if ($node == false) {
    $page['title'] = '城镇文化介绍';
    $page['error'] = array(
      '#markup' => '<div class="error-message">未找到相关内容</div>',
    );
    return $page;
  }

  $wnode = entity_metadata_wrapper('node', $node);

  $page['article_title'] = $wnode->title->value(); 

  //内容详情
  $article = $wnode->field_article_content->value();
  if($article['format'] == 'filtered_html' || $article['format'] == 'plain_text'){
    $page['content']['#markup'] = $article['value'];
  }else if($article['format'] == 'full_html'){
    $page['content']['#markup'] = $article['safe_value'];
  }

  //get merchandise link
  $m_nodes = $wnode->field_link_merchandise->value();
  if (count($m_nodes)) {

    $page['m_links'] = link_merchandise_node($m_nodes);
  }
  
  //get area name as title
  $fields = $wnode->getPropertyInfo();
  foreach ($fields as $field => $ct) {
    if (preg_match('/field_area_term_/', $field)) {
      $value = $wnode->$field->value();
      if ($value) {
        $page['title'] = $value->name;
      }
    }
  }

  return $page;
}


function deliver_city_culture_article_page_html_page($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile-city-culture-article-page.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',

    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_city_culture_page.js',
  );

  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_city_culture_article_page',
    '#page' => $page,
    '#styles' => $css,
    '#scripts' => $js,
  );
  print drupal_render($render);
}


function link_merchandise_node($node_list = null) {
  global $base_url;

  if ($node_list == null) {
    return null;
  }
  
    //watchdog('py mobile', 'nid_list <pre>@data</pre>', array('@data' => print_r($nid_list, TRUE)));
    //watchdog('py mobile', 'node_list <pre>@data</pre>', array('@data' => print_r($node_list, TRUE)));

  $element = array();

  $output = array_slice($node_list, 0, 3);  //only use first three nodes
  foreach ($output as $id => $node) {
    if ($node->type != 'merchandise_input_ct') {
      continue;
    }

    $wnode = entity_metadata_wrapper('node', $node);

    //上架
    $on_shelf = $wnode->field_on_shelf->value();
    if ($on_shelf == 1) {
      continue;
    }

    //link to merchandise show page
    $node_req_url = t(
      variable_get('oauth2 redirect request'),
      array(
        '@APPID' => variable_get('wechat_py_AppID'),
        '@URL' => $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/merchandise/' . $node->nid . "/show",
        '@SNSAPI' => "snsapi_base",
        '@STATE' => "100",
      )
    );

    $element[$id]['purl'] = $node_req_url;
    //title
    $element[$id]['pname'] = trim($node->title);
    //home page
    $img_field = $wnode->field_home_page_img->value();
    $element[$id]['pimage'] = file_create_url($img_field['uri']);
    $element[$id]['pshopping_price'] = $wnode->field_product_shopping_price->value();
    
  }

  return $element;
}
/**
 * End of wechat_mobile_city_culture_page.inc file name
 */

