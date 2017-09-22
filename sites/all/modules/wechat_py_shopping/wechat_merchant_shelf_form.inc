<?php
function menu_wechat_merchant_shelf_form($form, &$form_state){

  $form['fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('所有货架信息'), 
  );

  $value = get_merchant_shelf_all();

  $data = drupal_json_decode($value);
  dpm($data);
  $form['fieldset']['group_info'] = array(
    '#type' => 'item',
    '#markup' => '<div>' . $value . '</div>',
  );


    /**
     * test any page
     **/

//    $voc = taxonomy_vocabulary_machine_name_load('wechat_shopping_merchant_vocabulary');
//    
//    if (!$voc) {
//        return NULL;
//    }
//
//    $element = array();
//    $terms = taxonomy_get_tree($voc->vid, 0, 1);
//    usort($terms, "cmp_termid");
//
//    foreach($terms as $delta => $term) {
//        $cterms = taxonomy_get_tree($voc->vid, $term->tid, 1);
//        $element[$delta] = array(
//            'tid' => $term->tid,
//            'name' => $term->name
//        );
//
//        if (empty($cterms)) {
//            $element[$delta]['child'] = array();
//        } else {
//            usort($cterms, "cmp_termid");
//            foreach ($cterms as $id => $cterm) {
//                $element[$delta]['child'][$id] = array(
//                    'tid' => $cterm->tid,
//                    'name' => $cterm->name,
//                );
//            }
//        }
//    }
//
//    dpm($element);
//
//    $query = db_select('wechat_py_welcome_page_table', 't')->fields('t', array('welcome_text'));
//    $result = $query->execute();
//    $row = $result->fetchAssoc();
//
//    $content = $row['welcome_text'];
//    $content .= $content . '
//        您已有50个积分，可用于在线商城消费。
//    ';
//    dpm($content);
    if ($cache = cache_get('mobile_shopping_express_template_cache')) {
      $express_cache_list = $cache->data;
      dpm($express_cache_list);
    }


    $my_array = array(
        'name' => 'hhh',
        'child' => array('1' => 'ttt', '2' => null, '3' => '34'),
    );

    dpm($my_array);

    if (isset($my_array['child']['2'])) {
        dpm('null');
    } else {
        dpm('has');
    }


  return $form;
}


function cmp_termid($a, $b) {
    return intval($a->tid) - intval($b->tid);
}

function get_merchant_shelf_all(){
  module_load_include('inc', 'wechat_api', 'wechat_api_php5');
  $req_url = t(
    //variable_get('所有货架-货架管理接口-微信小店'),
    variable_get('所有模版-邮费模板-微信小店'),
    array('@ACCESS_TOKEN' => variable_get('access_token'))
  );
  $result = wechat_php_curl_https_get($req_url);
  if (!$result)
  {
    watchdog('wechat get all merchant shelf info', 'get error in @line line:@filename',
      array(
      '@line' => __LINE__,
      '@filename' => __FILE__,
      ),
      $severity = WATCHDOG_ERROR);
    return ;
  }
  return $result;
}
/**
 * End of wechat_merchant_shelf_form.inc file name
 */
