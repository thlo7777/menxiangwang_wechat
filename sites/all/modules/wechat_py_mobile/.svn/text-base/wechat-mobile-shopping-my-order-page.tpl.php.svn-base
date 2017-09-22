<?php

/**
 * @file
 * Default theme implementation to display wechat py mobile user orders html page
 *
 * Variables:
 * - $head_title: A modified version of the page title, for use in the TITLE
 * - $css: An array of CSS files for the current page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 * - $page: The rendered page content.
 *
 */
 //height=device-height, 
 //
 //data-dom-cache="true" 
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

    <div data-role="page" id="py-mobile-my-order-page">


      <!--Jquery mobile ui content -->
      <div role="main" class="ui-content">


        <ul data-role="listview" class="ui-alt-icon">

          <?php if (!empty($page['paid'])) :?>
            <?php foreach($page['paid'] as $order_no => $paid_order): ?>
              <li data-role="collapsible" data-iconpos="right" data-inset="false">
                <h2 id="order-title">
                  <p style="white-space: initial;">收货地址: <?php print $paid_order['order_addr']; ?></p>
                  <p>订单编号: <?php print $paid_order['out_trade_no']; ?></p>
                  <p>支付时间: <?php print $paid_order['time_end']; ?></p>
                  <p>商品金额: ¥ <?php print number_format(floatval($paid_order['total_fee'])/100, 2); ?></p>
                  <p>邮费: ¥ <?php print number_format(floatval($paid_order['order_exp_fee']), 2); ?></p>
                </h2>
                <ul class="order-detail-item" data-role="listview" data-theme="c">
                  <li style="margin:0.5em 0;">
                    <p style="margin: 1em; white-space: initial;"><?php print $paid_order['order_detail']; ?></p>
                  </li>
                </ul>
              </li>
            <?php endforeach; ?>
          <?php endif; ?>

        </ul>


      </div><!-- /content -->


    </div><!-- /page -->

  <!--**************javascript file load*************************-->
    <?php foreach($scripts as $js): ?>
      <script type="text/javascript" src="<?php print $js; ?>"></script>
    <?php endforeach; ?>
  <!--**************javascript file load*************************-->

  <?php endif; ?>

</body>

</html>



