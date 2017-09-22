<?php
class wechat_py_shopping_views_handler_field_order_state extends views_handler_field {

  function render($values) {
    $value = $this->get_value($values);

    switch ($value) {
      case '1':
        $render['container'] = array(
          '#type' => 'container',
          '#attributes' => array('class' => array('container-inline')),
        );
        $render['container']['icon'] = array(
          '#theme' => 'image',
          '#width' => '20%',
          '#path' => drupal_get_path('module', 'wechat_py_shopping') . '/imgs/paid_icon.png',
          '#attributes' => array('style' => array('display: block; float: left; margin: 0.5em;')),
          
        );
        $render['container']['text'] = array(
          '#markup' => '<div style="display: block; padding: 0.7em;">已支付</div>',
        );


        //return t('已支付');
        return drupal_render($render);
        break;
      
      case '2':
        $render['container'] = array(
          '#type' => 'container',
          '#attributes' => array('class' => array('container-inline')),
        );
        $render['container']['icon'] = array(
          '#theme' => 'image',
          '#width' => '20%',
          '#path' => drupal_get_path('module', 'wechat_py_shopping') . '/imgs/dispatched_icon.png',
          '#attributes' => array('style' => array('display: block; float: left; margin: 0.5em;')),
          
        );
        $render['container']['text'] = array(
          '#markup' => '<div style="display: block; padding: 0.7em;">已发货</div>',
        );
        //return t('已发货');
        return drupal_render($render);
      default:
        // code...
        break;
    }
  }

}


