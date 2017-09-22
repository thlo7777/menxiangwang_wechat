<?php
//for wechat online shopping
function menu_wechat_py_commodity_category_page_form($form, &$form_state){
  global $base_url;

  $form['category'] = array(
    '#type' => 'fieldset',
    '#title' => t('微商城商品分类'),
    '#weight' => -10,
  );

  $form['category']['link'] = array(
    '#type' => 'link',
    '#title' => '增加商品分类',
    '#href' => $base_url . '/wechat-py-shopping/commodity-category/add',
    '#weight' => -10,
  );

  $term = taxonomy_vocabulary_machine_name_load('wechat_py_product_category');
  
  include_once(drupal_get_path('module','taxonomy') . '/taxonomy.admin.inc' );
  $form['term_form'] = drupal_get_form('taxonomy_overview_terms', $term);
  //$edit = array();
  //$form =drupal_get_form('taxonomy_form_term', $edit, 'wechat_py_product_category');

  //dpm($form);
  //$form['term_form']['actions']['#access'] = FALSE;  //remove save button

  return $form;
}

//for wechat shopping
function menu_wechat_py_commodity_category_page_add_form(){
  
  /*
  include_once(drupal_get_path('module','taxonomy') . '/taxonomy.admin.inc' );
  $edit = array();
  $form = array();
  $form_state = array();
  $result = drupal_get_form('taxonomy_form_term', $edit, $term);

  return drupal_render($result);
  */

  // Build a taxonomy_form_term form.
  $vocabulary = taxonomy_vocabulary_machine_name_load('wechat_py_product_category');
  dpm($vocabulary);

  $tree = taxonomy_get_tree($vocabulary->vid);
  dpm($tree);
  $form_state = array('build_info' => array('args' => array(array(), $vocabulary)));
  $form_id    = 'taxonomy_form_term';
  form_load_include($form_state, 'inc', 'taxonomy', 'taxonomy.admin');
  $form_state['redirect'] = 'wechat-py-shopping/commodity-category';
  $form = drupal_build_form($form_id, $form_state);
  return drupal_render($form);
}




//for own custome online shopping -------------------
function old_menu_wechat_py_commodity_category_page_form($form, &$form_state){

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/css/py_commodity_category.css',
  );
  /*
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'wechat_py_shopping') . '/js/py_commodity_category.js',
  );
  */

  $form['category_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => '商品分类表',
    '#attributes' => array('class' => array('category-container')),
    '#weight' => 0, 
  );

  $items = category_parent_get_data();
  
  /*
  echo '<pre>';
  print_r($items);
  echo '</pre>';
  */
  /*
  $items = array();
  $items[] = array(
    'data' => '杂粮等',
    'children' => array(
      '22222',
      '1111',
      array(
        '3333',
        'children' => array(
          'li 3.3.1',
          'li 3.3.2',
          'li 3.3.3',
        ),
      ),
      'li 3.2',
      array(
        'li 3.4',
        'children' => array(
          'li 3.4.1',
          'li 3.4.2',
          'li 3.4.3',
        ),
      ),
    ),
  );
  */

  if($items == 0){
    $form['category_fieldset']['empty_record'] = array(
      '#markup' => '当前没有记录, 请选择增加一级分类',
      '#attributes' => array('style' => array('margin: 0 auto;')),
    );

  }else{

    $form['category_fieldset']['first_item_list'] = array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#type' => 'ul',
      '#attributes' => array('class' => array('first-level-category'),
                             'style' => array('padding: 0 0 0 0.8em;'),),
    );
  }

  $form['container'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['container']['first_level'] = array(
    '#type' => 'textfield', 
    '#title' => t('输入商品一级分类名称'),
    '#size' => 60, 
    '#maxlength' => 128, 
  );
  $form['container']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('提交一级分类'),
    '#validate' => array('add_category_validation'),
  );

  $form['#submit'][] = 'add_first_level_submit';

  return $form;
}


function add_category_validation($form, &$form_state){
  $text = strlen(trim($form_state['values']['first_level']));
  if($text == 0){
    form_set_error('first_level', t('分类名称不能为空'));
  }

}

//record all all submit event
function add_first_level_submit($form, &$form_state){
  $op = $form_state['values']['op'];
  switch ($op) {
    case '提交一级分类':
      $name = $form_state['values']['first_level'];
      $level = 1;
      $pid = 0;
      db_insert('wechat_py_commodity_category_table')
              ->fields(array(
                'name' => $name,
                'level' => $level,
                'pid' => $pid,
                ))->execute();
      break;

    default:
      break;
  }
}

function category_parent_get_data() {
  // Get all 'root node' items (items with no parents), sorted by weight.
  $query = db_select('wechat_py_commodity_category_table', 't')
    ->condition('t.pid', 0)
    ->fields('t')
    ->orderBy('t.id', 'ASC');
  $result = $query->execute();

  $count = $result->rowCount();
  if($count == 0){
    return 0;
  }

  //$items = array();
  // Initialize a variable to store our ordered tree structure.
  $itemtree = array();
  // Loop through the root nodes, and add their trees to the array.
  global $base_url;
  $menu_path = '/wechat-py-shopping/commodity-category/add/';
  foreach ($result as $child) {
    // Add the parent item to the tree.
    $url_req = $base_url . $menu_path . $child->id . '/' . $child->level;
    $data = array('#markup' => '<a href="' . $url_req . '">' . $child->name . '</a>');
    $itemtree[$child->id] = array(
      'data' => drupal_render($data),
      //'id' => 'level-' . $level . '-' . $parentitem->id,
      'class' => array('category-li-items'),
    );

    category_get_tree($child, $itemtree[$child->id], $child->level);
  }

  return $itemtree;
}

function category_get_tree($parentitem, &$itemtree = array(), $level) {

  global $base_url;
  $menu_path = '/wechat-py-shopping/commodity-category/add/';

  // Retrieve each of the children belonging to this parent.
  $query = db_select('wechat_py_commodity_category_table', 't')
    ->condition('t.pid', $parentitem->id)
    ->fields('t')
    ->orderBy('t.id', 'ASC');
  $result = $query->execute();

  $count = $result->rowCount();
  if($count == 0){
    return 0;
  }

  foreach ($result as $child) {
    $url_req = $base_url . $menu_path . $child->id . '/' . $child->level;
    $data = array('#markup' => '<a href="' . $url_req . '">' . $child->name . '</a>');
    $children = !empty($itemtree['children']) ? $itemtree['children'] : array();

    if(check_child($child->id)){
      $id = $child->id;
      $itemtree['children'][$id] = array(drupal_render($data));
      category_get_tree($child, $itemtree['children'][$id], $level);
    }else{
      $itemtree['children'] = array_merge(array(drupal_render($data)), $children);
      category_get_tree($child, $itemtree['children'], $level);
    }
  }
}

function check_child($id) {
  $query = db_select('wechat_py_commodity_category_table', 't')
    ->condition('t.pid', $id)
    ->fields('t')
    ->orderBy('t.id', 'ASC');
  $result = $query->execute();

  $count = $result->rowCount();
  if($count == 0){
    return 0;
  }else{
    return 1;
  }
}

/**
 * End of menu_wechat_py_commodity_category_page_form.inc file name
 */
