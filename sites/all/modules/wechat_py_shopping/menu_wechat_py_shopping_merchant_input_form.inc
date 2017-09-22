<?php

/*
 * Implement menu_wechat_py_shopping_merchant_list_form for input merchant form page
 */

function menu_wechat_py_shopping_merchant_list_form($form, &$form_state){

  $form['add_link'] = array(
    '#type' => 'link',
    '#title' => t('添加新商品'),
    '#href' => 'wechat-py-shopping/merchant-input',
    '#attributes' => array('class' => array('button'),
                           'style' => array('display: block; clear: both;')),
  );

  $view = views_get_view('shopping_merchant_list');
  $view->set_display('test');
  $view->pre_execute();
  $html = $view->render('test');
  $form['view'] = array(
    '#markup' => $html,
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_input_form.css',
  );
  
  return $form;
}

function menu_wechat_py_shopping_merchant_input_form(){
  global $user;
  module_load_include('inc', 'node', 'node.pages');
  $form = node_add('mobile_shopping_product_input');

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/js/merchant_input_form.js',
  );

  //dpm($form);
  return drupal_render($form);
}


/**
 * Implements called by wechat_py_shopping_node_view_alter
 **/
function _merchant_input_node_view_alter(&$build){
  drupal_add_css(drupal_get_path('module', 'wechat_py_shopping') . '/css/merchant_input_form.css');
}


/**
 * End of menu_wechat_py_shopping_merchant_input_form.inc file name
 */
