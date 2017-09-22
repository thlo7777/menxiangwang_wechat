<?php

//page for city culture information page
function wechat_mobile_city_culture_page() {

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

  $page['title'] = '城镇文化介绍';


  //get all city culture vocabulary taxonomy for panel
  $page['vocs'] = get_all_city_culture_vocabularys();

  return $page;
}


function deliver_city_culture_page_html_page($page) {
  global $base_url;

  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/mobile-city-culture-page.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',

    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.ajax-retry.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/mobile_city_culture_page.js',
  );

  $render['html_page'] = array(
    '#theme' => 'wechat_mobile_city_culture_page',
    '#page' => $page,
    '#styles' => $css,
    '#scripts' => $js,
  );
  print drupal_render($render);
}

function get_all_city_culture_vocabularys() {
  global $base_url;
  $element = array();

  $vocs = taxonomy_vocabulary_get_names();
  $vocs_keys = array_keys($vocs);

  foreach ($vocs_keys as $key) {

    if (preg_match('/^mobile_city_culture_vocabulary_/', $key)) {
      $voc = taxonomy_vocabulary_machine_name_load($key);

      $split = preg_split('/_/', $voc->name); //remove prefix name
      $element[$voc->vid]['area_name'] = $split[1];

      $area_id = preg_split('/mobile_city_culture_vocabulary_/', $voc->machine_name);
      $element[$voc->vid]['area_id'] = $area_id[1];

      $terms = taxonomy_get_tree($voc->vid, 0, 1);
      $t_array = array();
      foreach ($terms as $id => $term) {
        $t_array[$id]['tid'] = $term->tid;
        $t_array[$id]['tname'] = $term->name;
      }

      if (count($t_array)) {
        $element[$voc->vid]['terms'] = $t_array;
      }

    }
  }

  return $element;
}


/**
 * End of wechat_mobile_city_culture_page.inc file name
 */
