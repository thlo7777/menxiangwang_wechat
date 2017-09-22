<?php

function wechat_py_mobile_xxzs_home_page() {

  global $base_url;
  $icon_path = $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/imgs/';

  $form['title'] = array(
    '#type' => 'hidden',
    '#value' => '服务指南',
  );

  $form['container1']  = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline', 'container-1')),
  );

  $form['container1']['image1']  = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'hotel_button.png',
    '#attributes' => array('class' => array('image-icon')),
    '#prefix' => '<a href="' . $base_url . '/wechat-ajax/xxzs">',
    '#suffix' => '</a>',
  );

  //food
  $form['container1']['image2']  = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'food_button.png',
    '#attributes' => array('class' => array('image-icon')),
    '#prefix' => '<a href="' . $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/xxzs-item-page/2">',
    '#suffix' => '</a>',
  );

  $form['container2']  = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline', 'container-1')),
  );

  //craft
  $form['container2']['image3']  = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'craft_button.png',
    '#attributes' => array('class' => array('image-icon')),
    '#prefix' => '<a href="' . $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/xxzs-item-page/3">',
    '#suffix' => '</a>',
  );

  //art
  $form['container2']['image4']  = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'art_button.png',
    '#attributes' => array('class' => array('image-icon')),
    '#prefix' => '<a href="' . $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/xxzs-item-page/4">',
    '#suffix' => '</a>',
  );

  $form['container3']  = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline', 'container-1')),
  );

  $form['container3']['image5']  = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'travel_button.png',
    '#attributes' => array('class' => array('image-icon')),
    '#prefix' => '<a href="' . $base_url . '/wechat-ajax/lyxl">',
    '#suffix' => '</a>',
  );

  //info
  $form['container3']['image6']  = array(
    '#theme' => 'image',
    '#path' => $icon_path . 'info_promote.png',
    '#attributes' => array('class' => array('image-icon')),
    '#prefix' => '<a href="' . $base_url . '/' . MENU_WECHAT_PY_MOBILE . '/xxzs-item-page/6">',
    '#suffix' => '</a>',
  );

  return $form;
}

function deliver_xxzs_home_page_callback($page_result) {

  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/xxzs_home_page.css',
  );

  $js = array();

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

function wechat_py_mobile_xxzs_item_page($item){
  global $base_url;

  $form = array();
  //get role id by item
  $rid = get_role_id($item);
  if($rid == -1){
    return $form;
  }

  switch ($item) {
    case '2': //food
      $form['title'] = array(
        '#type' => 'hidden',
        '#value' => '美食攻略',
      );
      break;
    case '3': //craft
      $form['title'] = array(
        '#type' => 'hidden',
        '#value' => '工艺精品',
      );
      break;
    case '4': //art
      $form['title'] = array(
        '#type' => 'hidden',
        '#value' => '字画篆刻',
      );
      break;
    case '6': //info
      $form['title'] = array(
        '#type' => 'hidden',
        '#value' => '其他推荐',
      );
      break;
    
    default:
      // code...
      break;
  }

  //get user id by role id
  $query = db_select('users_roles', 't')
    ->condition('t.rid', $rid)
    ->fields('t', array('uid'));
  $result = $query->execute();
  foreach ($result as $user) {

    $query = new entityfieldquery();

    $query->entitycondition('entity_type', 'node')
    ->entitycondition('bundle', 'py_issue_info')
    ->propertycondition('status', NODE_PUBLISHED)
    ->propertycondition('uid', $user->uid);

    $result = $query->execute();
    if(count($result)){
      $nodes = node_load_multiple(array_keys($result['node']));
      foreach($nodes as $node){
        $enode = entity_metadata_wrapper('node', $node);
        $title = $enode->title->value();
        $title_img = $enode->field_info_title_image->value();
        //$img_url = file_create_url($title_img['uri']);
        $title_intro = $enode->field_info_title_intro->value();

        $form['container-' . $user->uid] = array(
          '#type' => 'container',
          '#attributes' => array('class' => array('container-inline', 'clearfix'),
                                 'id' => array($node->nid)),
          '#prefix' => '<div class="item-user">',
          '#suffix' => '</div>',
        );
        $form['container-' . $user->uid]['title_image'] = array(
          '#theme' => 'image',
          '#path' => $title_img['uri'], 
          '#with' => '80px',
          '#height' => '80px',
          '#attributes' => array('class' => array('title-image')),
        );

        $items = array(
            $title,
            $title_intro,
        );

        $form['container-' . $user->uid]['title_intro'] = array(
          '#theme' => 'item_list',
          '#items' => $items,
          '#type' => 'ul',
          '#attributes' => array('class' => array('title-intro')),
        );

      }
    }
  }

  return $form;
}

function deliver_xxzs_page_item_callback($page_result) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/xxzs_item_page.css',
  );

  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/xxzs_item_page.js',
  );

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

function get_role_id($item) {
  //get user id by user role
  $roles = user_roles();
  foreach ($roles as $rid => $role) {
    switch ($item) {
      case '2': //food
        if($role == '美食攻略管理员')
        return $rid;
      case '3': //craft
        if($role == '工艺精品管理员')
        return $rid;
      case '4': //art
        if($role == '字画篆刻管理员')
        return $rid;
      case '6': //info
        if($role == '其他推荐管理员')
        return $rid;
      
      default:
        break;
    }
  }

  return -1;  //can't find role id
}


//show node page
function wechat_py_mobile_xxzs_node_page($nid) {
  global $base_url;

  $form = array();


  $node = node_load($nid);
  $enode = entity_metadata_wrapper('node', $node);
  $title = $enode->title->value();
  $form['title'] = array(
    '#type' => 'hidden',
    '#value' => $title,
  );

  $fc_item = $enode->field_info_prod_group->value();
  foreach ($fc_item as $id => $field) {
    $form['info_group_' . $id] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('info-group', 'clearfix')),
      '#prefix' => '<div class="item-info">',
      '#suffix' => '</div>',
    );

    $info_img = $field->field_product_image['und']['0'];
    $form['info_group_' . $id]['image'] = array(
      '#theme' => 'image',
      '#path' => $info_img['uri'], 
      '#attributes' => array('class' => array('info-image')),
    );

    $info_text = $field->field_product_intro['und']['0']['safe_value'];
    $form['info_group_' . $id]['text'] = array(
      '#markup' => '<p>' . $info_text . '</p>',
      '#prefix' => '<div class="info-text">',
      '#suffix' => '</div>',
    );
  }

  return $form;
}

//delivery node page to mobile screen
function deliver_xxzs_page_node_callback($page_result) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/xxzs_node_page.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/easing.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/scrollToTop.css',
  );

  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-scrollToTop.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/xxzs_node_page.js',
  );

  $title = $page_result['title']['#value'];

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
 * End of wechat_py_mobile_xxzs_home_page.inc file name
 */

