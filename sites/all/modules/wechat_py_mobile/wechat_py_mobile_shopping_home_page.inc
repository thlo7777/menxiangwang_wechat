<?php

function wechat_py_mobile_shopping_home_page(){
  global $base_url;
  //广告位栏目表图片查询
  //搜索栏
  //商品类目按钮，我的订单按钮，购物车按钮，我的地址按钮
  //显示分类，依照人气或者销量显示两张商品图片
  //页面底部信息
  //返回首页按钮

  //广告位栏目表图片查询
  $form['adv_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('adv-container')),
  );

  $form['adv_container']['swiper_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('swiper-container')),
  );
  $form['adv_container']['swiper_container']['swiper_wrapper'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('swiper-wrapper')),
  );
  
  $query = db_select('wechat_py_shopping_adv_table', 't')
    ->fields('t')
    ->orderBy('t.id', 'ASC');
  $result = $query->execute();
  foreach ($result as $id => $row) {
    $form['adv_container']['swiper_container']['swiper_wrapper']['image_' . $id] = array(
      '#theme' => 'image',
      '#path' => $row->image, 
      '#prefix' => '<div class="swiper-slide">',
      '#suffix' => '</div>',
    );
  }

  $form['adv_container']['swiper_container']['swiper_pagination'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('swiper-pagination')),
  );
  $form['adv_container']['swiper_container']['swiper_button_next'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('swiper-button-next')),
  );
  $form['adv_container']['swiper_container']['swiper_button_prev'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('swiper-button-prev')),
  );

  $icon_path = $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/imgs/';

  //搜索栏
  $form['search_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('search-container', 'container-inline', 'clearfix')),
  );
  $form['search_container']['text'] = array(
    '#type' => 'textfield', 
    '#size' => 15, 
    '#maxlength' => 128, 
    '#attributes' => array('class' => array('search-text'), 'placeholder' => array('搜索商品')),
  );
  $form['search_container']['search_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_search.png',
    '#attributes' => array('class' => array('search-icon')),
  );

  $form['search'] = array(
    '#markup' => '<input type="search" name="search-11" id="search-11" value="Value">',
  );
  //商品类目按钮，我的订单按钮，购物车按钮，我的地址按钮
  $form['button_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('button-container', 'container-inline', 'clearfix')),
  );
  $form['button_container']['category_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_mer_cat.png',
    '#attributes' => array('class' => array('category-icon'),
                           'width' => array('18%')),
  );
  $form['button_container']['order_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_my_ord.png',
    '#attributes' => array('class' => array('order-icon'),
                           'width' => array('18%')),
  );
  $form['button_container']['cart_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_sho_car.png',
    '#attributes' => array('class' => array('cart-icon'),
                           'width' => array('18%')),
  );
  $form['button_container']['address_icon'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'shopping_per_cen.png',
    '#attributes' => array('class' => array('address-icon'),
                           'width' => array('18%')),
  );

  $form['commodity_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('commodity-container')),
  );

  $form['footer_container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('footer-container')),
  );

/*
  echo '<pre>';
  print_r($content);
  echo '</pre>';
*/

  return $form;
}


function deliver_shopping_home_page_callback($page_result) {
  global $base_url;
  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/swiper.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/shopping_home_page.css',
  );

  //$js = array();
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/py_shopping_adv_image.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/swiper.jquery.min.js',
  );

/*
  echo '<pre>';
  print_r($page_result);
  echo '</pre>';
  */

  $title = '梦乡平遥游微商城';

  $render['html_page'] = array(
    '#theme' => 'wechat_py_shopping_home_page',
    '#head_title' => $title,
    '#page' => $page_result,
    '#styles' => $css,
    '#scripts' => $js,
  );

  print drupal_render($render);
}

/**
 * End of wechat py mobile shopping home page
 */
