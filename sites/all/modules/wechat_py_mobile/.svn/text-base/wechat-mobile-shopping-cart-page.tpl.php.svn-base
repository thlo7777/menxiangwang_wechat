<?php

/**
 * @file
 * Default theme implementation to display wechat py mobile html structure of a single
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

      <?php if(!empty($page['js_var'])): ?>
        var cart_db_records = <?php echo $page['js_var']; ?>;
      <?php else: ?>
        var cart_db_records = 0;
      <?php endif;?>
      var xyz = "<?php echo $page['xyz']; ?>";
      var payment_url = "<?php echo $page['shopping_payment_url']; ?>";
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

    <div data-role="page" id="mobile-shopping-cart-page">

      <div data-role="header" data-position="fixed" data-theme="a" data-tap-toggle="false" style="height: 3.2em;">

        <a id="checkbox-a" href="#">
          <label id="checkbox-label" ><input type="checkbox" name="check-in-all" id="check-in-all" >全选</label>
        </a>

        <a href="#" id="cart-save" class="ui-btn ui-corner-all ui-btn-inline ui-mini ui-btn-icon-right ui-icon-lock">保存</a>
      </div>

      <!--Jquery mobile ui content -->
      <div role="main" class="ui-content">

        <ul id="listview" data-role="listview" data-split-icon="delete" data-split-theme="a" data-inset="true">

          <?php if (empty($page['records'])): ?>
            <li><h3 style="text-align: center;">没有纪录</h3></li>
          <?php else: ?>

            <?php foreach($page['records'] as $node): ?>
              <li index="<?php print $node['index']; ?>">
                <a href="#" id="list-item-row" index="<?php print $node['index']; ?>">

                  <?php if ($node['checkin'] == "0"): ?>
                    <div class="checkin-icon">
                      <span class="uncheckmark">
                        <div class="uncheckmark_circle"></div>
                      </span>
                    </div>
                  <?php else: ?>
                    <div class="checkin-icon">
                      <span class="checkmark">
                        <div class="checkmark_circle"></div>
                        <div class="checkmark_stem"></div>
                        <div class="checkmark_kick"></div>
                      </span>
                    </div>
                  <?php endif; ?>

                  <img src="<?php print $node['img_url']; ?>" style="margin-right: 5px; width: 30%; display: block; float: left">
                  <h2><?php print $node['title']; ?></h2>
                  <p class="shopping-price" price="<?php print $node['pshopping_price'];?>" >
                    <?php print '¥' . $node['pshopping_price'];?>
                  </p>

                  <div class="button-plus-minus">
                    <button class="volume-minus" data-role="none">-</button>
                    <button class="volume-text" volume="<?php print $node['volume'];?>"
                            data-role="none"><?php print $node['volume'];?></button>
                    <button class="volume-plus" data-role="none">+</button>
                  </div>

                </a>


                <a href="#" class="delete-row">delete and volume</a>

              </li>
            <?php endforeach; ?>
          <?php endif; ?>

        </ul>

      </div><!-- /content -->

      <div data-role="panel" id="confirm" data-display="overlay" data-position="right">
        <ul data-role="listview" data-icon="false">

          <li id="del-close" data-icon="delete"><a href="#" data-rel="close">关闭</a></li>

          <li>
            <input type="checkbox" name="checkbox-mini-0" id="checkbox-mini-0" data-mini="true">
            <label for="checkbox-mini-0">删除记录</label>

          </li>

        </ul>
      </div><!-- /panel -->

      <!--icon button fix navbar-->
      <div data-role="footer" data-position="fixed" data-theme="a" data-tap-toggle="false" >

        <a href="#" id="total" class="ui-btn ui-corner-all ui-btn-inline ">合计: </a>
        <a href="#" id="btn-checkin" class="ui-btn ui-corner-all ui-btn-inline ui-mini ui-btn-icon-right ui-icon-carat-r">结算</a>

      </div><!-- /footer -->



    </div><!-- /page -->

  <!--**************javascript file load*************************-->
    <?php foreach($scripts as $js): ?>
      <script type="text/javascript" src="<?php print $js; ?>"></script>
    <?php endforeach; ?>
  <!--**************javascript file load*************************-->

  <?php endif; ?>

</body>

</html>


