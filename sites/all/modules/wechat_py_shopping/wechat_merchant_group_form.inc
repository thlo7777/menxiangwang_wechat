<?php

function menu_wechat_merchant_group_form($form, &$form_state){
  global $base_url;

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('微信小店商品分组管理'), 
    '#weight' => -10,
  );

  $form['fieldset']['intro'] = array(
    '#markup' => t('商品分组管理，可新建分组，加入商品到指定分组，
                    修改分组和删除分组。根据货架显示模式，分组有着不同的表现'),
    '#prefix' => '<div class="group-intro">',
    '#suffix' => '</div>',
  );

  $form['category'] = array(
    '#type' => 'fieldset',
    '#title' => t('微信小店商品分组管理'),
    '#weight' => -5,
  );

  $form['category']['link'] = array(
    '#type' => 'link',
    '#title' => '增加分组',
    '#href' => $base_url . '/wechat-py-shopping/wechat-merchant-group/add',
  );


  $term = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_group');
  
  include_once(drupal_get_path('module','taxonomy') . '/taxonomy.admin.inc' );
  $form['term_form'] = drupal_get_form('taxonomy_overview_terms', $term);
  $form['term_form']['actions']['#access'] = FALSE;  //remove save button

  //dpm($form);
  return $form;
}


//for wechat merchant group
function menu_wechat_merchant_group_add_form(){
  $term = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_group');
  
  include_once(drupal_get_path('module','taxonomy') . '/taxonomy.admin.inc' );
  $edit = array();
  $result = drupal_get_form('taxonomy_form_term', $edit, $term);

  return drupal_render($result);
}
/**
 * End of menu_wechat_merchant_group_form.inc file name
 */
