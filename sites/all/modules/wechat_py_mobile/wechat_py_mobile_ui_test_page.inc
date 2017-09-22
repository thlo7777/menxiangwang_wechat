<?php

//page call for ui test page
function wechat_py_mobile_ui_test_page(){

  global $base_url;

  $library = libraries_load('wxpayapi');
  //$appid = variable_get('wechat_py_AppID');
  //$secret = variable_get('wechat_py_AppSecret');
  $mchid = variable_get('wechat_py_mchid');
  //$mchkey = variable_get('wechat_py_mchkey');
  //$notify_url = variable_get('wechat_py_notify_url');

  //①、获取用户openid
  //$tools = new JsApiPay($appid, $secret);
  $tools = new JsApiPay();
  $openid = $tools->GetOpenid();
  //$openid = 'oOTG9tzINV6zA_1vIBgWrqRRlTl0';
  //$address = $tools->GetEditAddressParameters();
  $address = 'dkdkdk';


  //②、统一下单
  $input = new WxPayUnifiedOrder();
  //$input->SetAppid($appid);//公众账号ID
  //$input->SetMch_id($mchid);//商户号
  //$input->SetMchKey($mchkey);//商户支付密钥

  $input->SetBody("test");
  $input->SetAttach("test");
  $input->SetOut_trade_no($mchid . date("YmdHis"));
  $input->SetTotal_fee("1");
  $input->SetTime_start(date("YmdHis"));
  $input->SetTime_expire(date("YmdHis", time() + 600));
  $input->SetGoods_tag("test");
  //$input->SetNotify_url("http://paysdk.weixin.qq.com/example/notify.php");
  //$input->SetNotify_url($notify_url);

  $input->SetTrade_type("JSAPI");
  $input->SetOpenid($openid);
  $order = WxPayApi::unifiedOrder($input, 30);
  //echo '<font color="#f00"><b>统一下单支付单信息</b></font><br/>';
  //watchdog('pay ui test', 'order <pre>@data</pre>', array('@data' => print_r($order, TRUE)));
  $jsApiParameters = $tools->GetJsApiParameters($order);
  //watchdog('pay ui test', 'jsApiParameters <pre>@data</pre>', array('@data' => print_r($jsApiParameters, TRUE)));


  $form['address_value'] = array(
                
    '#markup' => '<div id="address" style="display: none;">' . $address . '</div>',
  );

  $form['pay_value'] = array(
                
    '#markup' => '<div id="pay_value" style="display: none;">' . $jsApiParameters . '</div>',
  );

  $click_icon = $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/imgs/hotel_forums_01.png';

  $form['title'] = array(
    '#type' => 'hidden',
    '#value' => '测试页面',
  );

  $form['link'] = array(
    '#type' => 'link',
    '#title' => '测试外接口',
    '#href' => 'https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx9ee4070dc39cdedb' .
               '&redirect_uri=http://mxweixin.dreamland360.com/wechat-py-mobile/py-shopping-api' . 
               '&response_type=code' .
               '&scope=snsapi_base' .
               //'&scope=snsapi_userinfo' .
               '&state=oOTG9t-1993DOYJC23P7w_Jj6BNQ:http://wxpay.weixin.qq.com/pub_v2/pay/notify.v2.php' .
               '#wechat_redirect',
  );

  $scheme = variable_get('file_default_scheme', 'public') . '://';
  $path = $scheme . "/wechat_py_admin/123_0.jpg";

  $form['image'] = array(
    '#theme' => 'image',
    '#path' => $path,
    'width' => '100px',
    'height' => '80%',
    '#title' => 'Image Title',
    '#attributes' => array('class' => array('some-img'),
                           'id' => array('my-img'),
                           'style' => array('width: 100%;')),
  );

  $form['checkbox1'] = array(
    '#markup' => '<input type="checkbox" name="checkbox-mini-0" id="checkbox-mini-0" data-mini="true">
        <label for="checkbox-mini-0">I agree</label>', 
  );

  $form['get_address'] = array(
    '#type' => 'submit',
    '#value' => t('获取地址'),
    '#attributes' => array('data-icon' => array('delete'),
                           'data-iconpos' => array('left'),
                           'id' => array('get-addr')),
    
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('提交1分钱'),
    //'#attributes' => array('class' => array('ui-icon-delete', 'ui-btn-icon-left')),
    //'#prefix' => '<div class="ui-input-btn ui-btn ui-icon-delete ui-btn-icon-left">',
    //'#subfix' => '</div>',
    '#attributes' => array('data-icon' => array('delete'),
                           'data-iconpos' => array('right'),
                           'id' => array('testapi')),
    
  );

  return $form;
}

function deliver_ui_test_page_callback($page_result) {
  global $base_url;
  $css = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/jquery.mobile-1.4.5.min.css',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/scrollToTop.css',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/css/py_forums_page.css',
  );

  //One final thing to check is to make sure that you are not loading any plugins before you load jQuery
  $js = array(
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery-1.11.1.min.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jquery.mobile-1.4.5.min.js',
    'http://res.wx.qq.com/open/js/jweixin-1.0.0.js',
    //$base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/jweixin-1.0.0.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/Wxjsapi.js',
    $base_url . '/' . drupal_get_path('module', 'wechat_py_mobile') . '/js/py_ui_test_page.js',
  );


  $title = $page_result['title']['#value'];

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
 * End of wechat_py_mobile_ui_test_page.inc file name
 */
