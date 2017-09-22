<?php

//page call for ui test page
function wechat_mobile_shopping_test_any_page(){

  global $base_url;
  $page = array();


  $page['title'] = '开发测试页面';

  return $page;
}

function deliver_test_any_page_callback($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/swiper.min.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/swiper.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_shopping_test_any_page.js',
  );


  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_test_any_page',
    '#page' => $page,
    '#styles' => $css,
    '#scripts' => $js,
  );

  print drupal_render($render);
}



/**
 * End of wechat_mobile_shopping_test_any_page.inc file name
 */
