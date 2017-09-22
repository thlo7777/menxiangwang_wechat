<?php

/**
 * @file
 * Default theme implementation to display order detail for custome services
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

    <div data-role="page" id="py-mobile-cs-order-detail-page">


      <!--Jquery mobile ui content -->
      <div role="main" class="ui-content">

        <?php if (!empty($page['order_detail'])) :?>
          <div class="ui-body ui-body-a ui-corner-all">
            <p>地区分类: <?php print $page['order_detail']['area_name']; ?></p>
            <p>订单编号: <br /> <?php print $page['order_detail']['out_trade_no']; ?></p>
            <p>支付时间: <?php print $page['order_detail']['time_start']; ?></p>
            <?php if ($page['order_detail']['order_state'] == 1) :?>
              <p>订单状态: 已支付，未发货</p>
            <?php elseif ($page['order_detail']['order_state'] == 2) : ?>
              <p>订单状态: 已发货</p>
            <?php else: ?>
              <p>订单状态: <?php print $page['order_detail']['order_state']; ?></p>
            <?php endif; ?>

            <p>订单金额: ¥ <?php print $page['order_detail']['total_fee']; ?></p>
            <p>订单邮费: ¥ <?php print $page['order_detail']['order_exp_fee']; ?></p>

            <p>收货地址: <br /><?php print $page['order_detail']['order_addr']; ?></p>
            <p>商品详情: <br /><?php print $page['order_detail']['order_detail']; ?></p>
          </div>
        <?php endif; ?>

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




