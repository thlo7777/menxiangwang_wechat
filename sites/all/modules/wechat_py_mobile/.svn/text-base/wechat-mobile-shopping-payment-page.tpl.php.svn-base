<?php

/**
 * @file
 * Default theme implementation to display wechat py mobile payment page
 * Drupal page.
 *
 * Variables:
 * - $head_title: A modified version of the page title, for use in the TITLE
 * - $css: An array of CSS files for the current page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 * - $page: The rendered page content.
 *
 */
?>

<!DOCTYPE html>
<html>

<head>
  <title><?php print $page['title']; ?></title>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  <meta name="viewport" content="width=device-width, user-scalable=0, initial-scale=1"/>
  <?php foreach($styles as $css): ?>
    <link rel="stylesheet" type="text/css" href="<?php print $css; ?>">
  <?php endforeach; ?>
  
  <?php if(!empty($page['inline_js'])): ?>
    <script type="text/javascript">
      <?php print $page['inline_js']; ?>
      var xyz = "<?php echo $page['xyz']; ?>";
      <?php if (!empty($page['js_var'])): ?>
        var user_addr = <?php echo $page['js_var']; ?>;
      <?php else: ?>
        var user_addr = [];
      <?php endif;?>
    </script>
  <?php endif; ?>
</head>

<body>

  <?php if (!empty($page['error_info'])) :?>
    <div class="ui-body ui-body-a ui-corner-all"
         style= "margin-top: 0.5em; background-color: #F1DD80; border-color: #333; text-shadow: 0 1px 0 #ffffff;">
      <p><?php print $page['error_info']; ?></p>
    </div>
  <?php else: ?>

    <!-- page payment for user address -->
    <div data-role="page" id="pyment-address">


      <div role="main" class="ui-content">

        <div class="ui-bar ui-bar-a" style="padding: 0;">
          <div class="ui-body ui-body-d">
            <p style="text-align: center; margin: 0.5em 0;">选择收货地址</p>
          </div>
        </div>

        <!-- user address -->
        <ul id="user-addr-listview" data-role="listview" data-split-icon="delete" data-split-theme="a" data-inset="true">

        </ul>

        <a href="#" id="add-addr" class="ui-btn ui-icon-plus ui-btn-corner-all ui-btn-icon-right">增加</a>
        <p style="text-align: center; font-size: 0.8em;">最多五个地址</p>

      </div> <!-- div role="main" -->



      <div data-role="footer" data-position="fixed" data-theme="a" data-tap-toggle="false">
        <div data-role="navbar" data-iconpos="right">
          <ul>
            <li><a href="#payment-checklist" data-icon="carat-r" class="ui-btn-active" id="check-addr">
              下一步
            </a></li>
          </ul>
        </div><!-- /navbar -->
      </div><!-- /footer -->

      <!-- remove address panel -->
      <div data-role="panel" id="remove-addr-panel" data-display="overlay" data-position="right">
        <ul data-role="listview" data-icon="false" id="remove-panel-list-view">
          <div id="remove-detail-address">
          </div>

          <li><a href="#" id="delete-checkbox-a">
          </a></li>

          <li><a href="#" id="remove-addr-save" style="background-color: #38c; text-align: center;"
                 class="ui-btn ui-icon-check ui-btn-icon-left" data-rel="close">关闭</a></li>

        </ul>
      </div>  <!-- remove address panel -->

      <!-- /add address -->
      <div data-role="panel" id="edit-addr-panel" data-display="overlay" data-position="right">
        <ul data-role="listview" data-icon="false" class="panel-list-view">
          <li><a href="#">
              <label for="text-name">姓名</label>
              <input type="text" data-mini="true" name="text-name" id="text-name" data-clear-btn="true" value="">
          </a></li>

          <li><a href="#">
              <label for="text-tel">电话</label>
              <input type="tel" data-clear-btn="true" data-mini="true" name="text-tel" id="text-tel" value="">
          </a></li>

          <li><a href="#">

            <fieldset data-role="controlgroup" data-mini="true">
              <legend>选择地区</legend>
              <label for="select-city-1">city 1</label>
              <select name="select-city-1" id="select-city-1">
                <option value="-1">选择省份</option>
              </select>

              <label for="select-city-2">city 2</label>
              <select name="select-city-2" id="select-city-2">
                <option value="-1">选择城市</option>
              </select>

              <label for="select-city-3">city 3</label>
              <select name="select-city-3" id="select-city-3">
                <option value="-1">选择区县</option>
              </select>

            </fieldset>

          </a></li>

          <li><a href="#">
              <label for="text-detail">详细地址</label>
              <input type="text" data-clear-btn="true" data-mini="true" name="text-detail" id="text-detail" value="">
          </a></li>

          <li><a href="#" id="addr-save" style="background-color: #38c; text-align: center;"
                 class="ui-btn ui-icon-check ui-btn-icon-left">保存</a></li>

        </ul>
      </div><!-- /add address panel -->

    </div>  <!-- div role="page" page payment for user address -->


    <!-- page payment for check list-->
    <div data-role="page" id="payment-checklist">

      <div role="main" class="ui-content" style="padding: 0;">
        <!-- post address -->
        <div id="post-address" class="ui-body ui-body-a">
          
          <!-- Combining alt and nodisc button -->
          <div class="ui-nodisc-icon ui-alt-icon">
          <a href="#" data-mini="true" class="ui-btn ui-shadow ui-corner-all ui-icon-location ui-btn-icon-notext">location</a>
          </div>

        </div>

        <hr style= "margin: 0" color="#E8E8E8" size="10">
        <!-- post address -->
      
        <div id="merchandise-list" class="ui-body ui-body-a">

          <?php foreach($page['merchandise'] as $key => $area): ?>
            <!-- 区域 -->
            <p class="merchandise-area" style="background-color: #74D7E6; font-size: 1.3em; text-align: center;"><?php print $key; ?></p>
            <hr style= "margin: 0" color="#ddd" size="1">

            <?php foreach($area as $nid => $element): ?>


            <div class="ui-field-contain">
              <fieldset data-role="controlgroup" data-type="horizontal">
                <img id="<?php print 'm-purl' . $nid; ?>" class="p-img" src="<?php print $element['purl']; ?>">
                <p id="<?php print 'm-title' . $nid; ?>" class="merchandise-title"><?php print $element['pname']; ?></p>


                <!-- shopping price -->
                <div>
                  <p id="<?php print 's-price' . $nid; ?>" 
                     value="<?php print $element['pshopping_price']; ?>"
                     weight="<?php print $element['pweight']; ?>"
                     class="m-price"><?php print '¥' . $element['pshopping_price']; ?></p>
                  <div class="button-plus-minus">
                    <button index="<?php print $nid; ?>" class="volume-minus volume-price-minus" data-role="none">-</button>
                    <button id="<?php print "volume-number" . $nid; ?>" class="volume-text" data-role="none">
                      <?php print $element['volume']; ?></button>
                    <button index="<?php print $nid; ?>" class="volume-plus volume-price-plus" data-role="none">+</button>
                  </div>
                </div>
                <!-- shopping price -->

              </fieldset>
            </div>


            <!-- post fee -->
            <!-- <p class="express-name">运费</p> -->
            <?php $area_key_value = $element['area_key']; ?>
            <?php if ($element['pexp_free'] == 0): ?>
              <p id="<?php print "exp-fee" . $nid; ?>" value="0.00" class="express-fee" style="display: none">¥ 0.00</p>
            <?php else: ?>
              <p id="<?php print "exp-fee" . $nid; ?>" area_key="<?php print $element['area_key']; ?>" pexpid="<?php print $element['pexp_tid']; ?>"
                 index="<?php print $nid; ?>" value=""
                 class="express-fee" style="display: none"></p>
            <?php endif; ?>
            <!-- <p style="font-size: 0.9em; color: #999; margin: 0.3em; clear: both;">梦乡网<?php print $element['parea']; ?>配送</p> -->
            <!-- post fee -->

            <!-- score points or discount -->
            <?php if (!empty($element['score_points']) && $element['score_points']['valid_date'] == 1) : ?>
              <div id="<?php print "points-max" . $nid; ?>" 
                   value="<?php print $element['score_points']['points_max']; ?>" style="display: none"></div>
              <div id="<?php print "p-convert" . $nid; ?>" 
                   value="<?php print $element['score_points']['p_convert']; ?>" style="display: none"></div>

              <a id="<?php print "points-number" . $nid; ?>" index="<?php print $nid; ?>" 
                 value="<?php 
                   if ($page['my_curr_points'] >= $element['score_points']['points_max']) {
                     $nid_points = $element['score_points']['points_max'];
                     $page['my_curr_points'] = $page['my_curr_points'] - $element['score_points']['points_max'];
                   } else {
                     $nid_points = $page['my_curr_points'];
                     $page['my_curr_points'] = 0;
                   }
                   print number_format($element['score_points']['p_convert'] * $nid_points, 2, '.', '');
                 ?>"

                 href="#" class="points-price ui-btn ui-icon-arrow-r ui-btn-icon-left">
                 详情点击 积分抵扣: ¥ -<?php
                   print number_format($element['score_points']['p_convert'] * $nid_points, 2, '.', ''); ?>
              </a>

            <?php endif; ?> <!-- user points -->

            <?php if (!empty($element['vip_discount']) && $element['vip_discount']['valid_date'] == 1) : ?>
              <div id="<?php print "vip-discount" . $nid; ?>" 
                   value="<?php print $element['vip_discount']['vip_price']; ?>" style="display: none"></div>
              <p>会员优惠折扣: </p>
            <?php endif; ?>


            <p style="margin: 0.3em; float: left;" class="area-total">合计</p>
            <p index="<?php print $nid; ?>" area_key="<?php print $area_key_value; ?>"
               class="area-total area-total-price" value=""
               style=" float: right; color: #fa620e; margin: 0.3em;"></p>

            <hr style= "clear:both; margin: 0" color="#E8E8E8" size="10">

            <?php endforeach; ?>  <!-- foreach for nodeid-->

            <!-- <p class="express-name">运费</p> -->
            <p style="text-align: right; padding-right: 0.3em;" id="<?php print "area-exp-fee" . $area_key_value; ?>"
              class="area_exp_fee_total" area_key="<?php print $area_key_value; ?>"
              value="0.00"></p>
          <?php endforeach; ?>  <!-- for area array -->

          <!-- rest of points after initialize page -->
          <div id="my-curr-points" value="<?php print $page['my_curr_points'] ?>" style="display: none"></div>

          <!-- all of merchandise pay price -->
          <div class="ui-body ui-body-a">

            <!-- <p id="all-price" value="">商品合计</p> -->
            <!-- <p id="all-exp-fee" value="">所有运费</p> -->
            <p id="all-payment" value="" style="font-weight: 700; text-align: center; color: #fa620e;">共需支付</p>
          </div> <!-- all of merchandise pay price -->

        </div>  <!-- merchandise-list -->

      </div>  <!-- payment check list role = main-->

      <div data-role="footer" data-position="fixed" data-theme="a" data-tap-toggle="false">
        
        <div data-role="navbar" data-iconpos="left">
          <ul>
            <li><a href="#wechat-payment" data-icon="shop" class="ui-btn-active ui-corner-all" id="wxpay-send">
              微信安全支付
            </a></li>
          </ul>
        </div>  <!--/navbar -->
      </div><!-- /footer -->

      <!-- score points panel -->
      <div data-role="panel" id="score-points-panel" data-display="overlay" data-position="right">
        <ul id="score-points-listview" data-role="listview" data-icon="false">

          <li><a href="#">购买该商品最多使用积分:</a></li>
          <!-- <li><a href="#"> -->
          <li>
            <div class="button-plus-minus">
              <button id="volume-minus-point" index="<?php print $nid; ?>" class="volume-minus" data-role="none">-</button>
              <button id="score-points-panel-number" class="volume-text" data-role="none">1</button>
              <button id="volume-plus-point" index="<?php print $nid; ?>" class="volume-plus" data-role="none">+</button>
            </div>
            <p style="font-size: 1em; margin-left: 0.5em; float:left;">个积分点</p>
          </li>
          <!-- </a></li> -->
          <li><a id="score-points-panel-convert" href="#"></a></li>
          <li><a id="panel-rest-points" href="#"></a></li>

          <li><a href="#" id="save-points-number" style="background-color: #38c; text-align: center;"
                 class="ui-btn ui-icon-check ui-btn-icon-left" data-rel="close">保存</a></li>

          <li style="white-space: normal;">详细说明: </br>
          该积分规则为，用户购买商品时可以使用的积分兑换规则。例如用户有积分30点，某商品可一次性最多使用5个积分兑换，每积分可兑换2元人民币。该商品价格为100元，用户可使用5个积分抵扣部分商品价格。商品总价为100 - (5x2) = 90元</li>

          <li style="white-space: normal;">增加积分: </br>
          详情请返回主页点击"个人中心"-"我的积分"
          </li>
        </ul>
      </div> <!-- score points panel -->

    </div>  <!-- /div role="page" page payment for checklist -->


    <!-- /page payment pay -->
    <div data-role="page" id="payment-pay">
    </div>  <!-- /div role="page" payment for submit -->


  <!--**************javascript file load*************************-->
    <?php foreach($scripts as $js): ?>
      <script type="text/javascript" src="<?php print $js; ?>"></script>
    <?php endforeach; ?>
  <!--**************javascript file load*************************-->

  <?php endif; ?> <!-- right html page no error -->


</body>

</html>

