<?php

//page for adv detail
function wechat_mobile_shopping_adv_page($arg){

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

  if ($arg > 3 || $arg < 1) {
    $page['error'] = array(
      '#markup' => '<div class="error-message">没有推广内容</div>',
    );
  }

  $icon_path = $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/imgs/';
  $page['cart_plus'] = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'cart_plus.png',
    '#attributes' => array('id' => array('cart-plus'),
                           'width' => array('18%'),
                           'style' => array('float: right; display: block;')),
  );

  $adv_detail = null;
  $merchandise_link = null;
  $node_list = null;
  $nid_list = null;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'mobile_shopping_adv_node')
    ->fieldCondition('field_default_adv_node', 'value', '1', '=')
    ->propertyCondition('status', NODE_PUBLISHED);

  $result = $query->execute();
  if (!empty($result)) {
    $nodes = node_load_multiple(array_keys($result['node']));
    if(count($nodes)) {
      foreach($nodes as $node){
        $rnode = entity_metadata_wrapper('node', $node);
        $fc_adv_items = $rnode->field_fc_adv_items->value();
        $fc_wrapper = entity_metadata_wrapper('field_collection_item', $fc_adv_items);

        switch ($arg) {
          case '1': //第一组内容
            $adv_detail = $fc_wrapper->field_first_adv_detail->value();
            /**
             * 0|根据商品名称选择
             * 1|根据商品分类选择
             * 2|根据积分规则分类选择
             * 3|根据促销规则分类选择
             * 4|根据快递分类选择
             **/
            $condition = $fc_wrapper->field_first_adv_link_condition->value();
            if ($condition == 1) {  //has merchandise link
              $term_con = $fc_wrapper->field_field_first_adv_condition->value();
              $term = null;
              switch ($term_con) {
                case '0':
                  $node_list = $fc_wrapper->field_first_adv_node_by_title->value();
                  break;
                case '1':
                  $term = $fc_wrapper->field_first_adv_term_merchandise->value();
                  break;
                case '2':
                  $term = $fc_wrapper->field_first_dv_term_points->value();
                  break;
                case '3':
                  $term = $fc_wrapper->field_first_dv_term_discount->value();
                  break;
                case '4':
                  $term = $fc_wrapper->field_first_adv_term_express->value();
                  break;
                default:
                  break;
              }
              $nid_list = $term ? taxonomy_select_nodes($term->tid, false) : null;
            }
            break;
          case '2': //第二组内容
            $adv_detail = $fc_wrapper->field_second_adv_detail->value();
            $condition = $fc_wrapper->field_second_adv_link_condition->value();
            if ($condition == 1) {  //has merchandise link
              $term_con = $fc_wrapper->field_second_adv_condition->value();
              $term = null;
              switch ($term_con) {
                case '0':
                  $node_list = $fc_wrapper->field_second_adv_node_by_title->value();
                  break;
                case '1':
                  $term = $fc_wrapper->field_second_adv_term_merchandis->value();
                  break;
                case '2':
                  $term = $fc_wrapper->field_second_dv_term_points->value();
                  break;
                case '3':
                  $term = $fc_wrapper->field_second_adv_term_discount->value();
                  break;
                case '4':
                  $term = $fc_wrapper->field_second_adv_term_express->value();
                  break;
                default:
                  break;
              }
              $nid_list = $term ? taxonomy_select_nodes($term->tid, false) : null;
            }
            break;
          case '3': //第三组内容
            $adv_detail = $fc_wrapper->field_third_adv_detail->value();
            $condition = $fc_wrapper->field_third_adv_link_condition->value();
            if ($condition == 1) {  //has merchandise link
              $term_con = $fc_wrapper->field_third_adv_condition->value();
              $term = null;
              switch ($term_con) {
                case '0':
                  $node_list = $fc_wrapper->field_third_adv_node_by_title->value();
                  break;
                case '1':
                  $term = $fc_wrapper->field_third_adv_term_merchandis->value();
                  break;
                case '2':
                  $term = $fc_wrapper->field_third_adv_term_points->value();
                  break;
                case '3':
                  $term = $fc_wrapper->field_third_adv_term_discount->value();
                  break;
                case '4':
                  $term = $fc_wrapper->field_third_adv_term_express->value();
                  break;
                default:
                  break;
              }
              $nid_list = $term ? taxonomy_select_nodes($term->tid, false) : null;
            }
            break;
          
          default:
            break;
        }

      }
    }
  }
  //内容详情
  if($adv_detail['format'] == 'filtered_html' || $adv_detail['format'] == 'plain_text'){
    $page['content']['#markup'] = $adv_detail['value'];
  }else if($adv_detail['format'] == 'full_html'){
    $page['content']['#markup'] = $adv_detail['safe_value'];
  }
  //商品链接
  if ($nid_list != null || !empty($nide_list)) {
    $page['merchandise_list'] = adv_content_pull_node(null, $nid_list);
  }
  if ($node_list != null || !empty($node_list)) {
    $page['merchandise_list'] = adv_content_pull_node($node_list, null);
  }

  $page['title'] = '微商城推广';

  return $page;
}

function deliver_adv_page_html_page($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/wechat-py-mobile-adv-page-tpl.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
  );

  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_shopping_adv_page',
    '#page' => $page,
    '#styles' => $css,
    '#scripts' => $js,
  );
  print drupal_render($render);
}

function adv_content_pull_node($node_list = null, $nid_list = null) {
  global $base_url;

  if ($node_list == null && $nid_list == null) {
    return null;
  }
  
      //watchdog('py mobile', 'nid_list <pre>@data</pre>', array('@data' => print_r($nid_list, TRUE)));
      //watchdog('py mobile', 'node_list <pre>@data</pre>', array('@data' => print_r($node_list, TRUE)));

  $element = array();
  if ($node_list == null) {
    foreach ($nid_list as $id => $nid) {
      $node = node_load($nid);
      if ($node->type != 'merchandise_input_ct') {
        continue;
      }

      $wnode = entity_metadata_wrapper('node', $node);
      //link
      $element[$id]['purl'] = $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/merchandise/' . $nid;
      //上架
      $on_shelf = $wnode->field_on_shelf->value();
      if ($on_shelf == 1) {
        continue;
      }
      //title
      $element[$id]['pname'] = $node->title;
      //home page
      $img_field = $wnode->field_home_page_img->value();
      $img_url = file_create_url($img_field['uri']);
      $element[$id]['pimage'] = array(
        '#theme' => 'image',
        '#path' => $img_url,
        '#attributes' => array('id' => array('product-img'),
                               'width' => array('100%'),
                               'style' => array('margin: 0 auto;display: block;')),
      );
      //express free
      $express_free = $wnode->field_product_express_free->value();
      $element[$id]['pexp_free'] = $express_free ? null : '【包邮】';
      $element[$id]['pcost_price'] = $wnode->field_product_cost_price->value();
      $element[$id]['pshopping_price'] = $wnode->field_product_shopping_price->value();
      
    }
  }

  if ($nid_list == null) {
    foreach ($node_list as $id => $node) {
      if ($node->type != 'merchandise_input_ct') {
        continue;
      }

      $wnode = entity_metadata_wrapper('node', $node);
      //link
      $element[$id]['purl'] = $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/merchandise/' . $node->nid;
      //上架
      $on_shelf = $wnode->field_on_shelf->value();
      if ($on_shelf == 1) {
        continue;
      }
      //title
      $element[$id]['pname'] = trim($node->title);
      //home page
      $img_field = $wnode->field_home_page_img->value();
      $img_url = file_create_url($img_field['uri']);
      $element[$id]['pimage'] = array(
        '#theme' => 'image',
        '#path' => $img_url,
        '#attributes' => array('id' => array('product-img'),
                               'width' => array('100%'),
                               'style' => array('margin: 0 auto;display: block;')),
      );
      //express free
      $express_free = $wnode->field_product_express_free->value();
      //watchdog('py mobile', 'express_free <pre>@data</pre>', array('@data' => print_r($express_free, TRUE)));
      $element[$id]['pexp_free'] = $express_free ? null : '【包邮】';
      $element[$id]['pcost_price'] = $wnode->field_product_cost_price->value();
      $element[$id]['pshopping_price'] = $wnode->field_product_shopping_price->value();
      
    }
  }

  return $element;
}
/**
 * End of wechat_mobile_shopping_adv_page.inc file name
 */
