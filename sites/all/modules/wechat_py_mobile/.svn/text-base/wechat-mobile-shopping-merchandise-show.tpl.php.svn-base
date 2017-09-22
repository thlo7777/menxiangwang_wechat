<?php

/**
 * @file
 * Default theme implementation to display mobile shopping merchandise page.
 *
 * Variables:
 * - $head_title: A modified version of the page title, for use in the TITLE
 * - $css: An array of CSS files for the current page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 * - $page: The rendered page content.
 *
 */
/**
 * /var subscribe = "<?php echo $page['subscribe']; ?>";
 **/
?>

<!DOCTYPE html>
<html>

<head>
  <title><?php print $page['title']; ?></title>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  <meta name="viewport" content="width=device-width, user-scalable=0,initial-scale=1"/>
  <?php foreach($styles as $css): ?>
    <link rel="stylesheet" type="text/css" href="<?php print $css; ?>">
  <?php endforeach; ?>

  <?php if(!empty($page['inline_js'])): ?>
    <script type="text/javascript">
      <?php print $page['inline_js']; ?>

      var xyz = "<?php echo $page['xyz']; ?>";
      var nid = "<?php echo $page['nid']; ?>";
      var cart_url = "<?php echo $page['shopping_cart_url']; ?>";

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

    <div data-role="page" id="py-mobile-merchandise-show">

      <!--header for merchandise image -->
      <div data-role="header">
        <div class="swiper-container">
          <div class="swiper-wrapper">
            <?php if (!empty($page['images'])): ?>
              <?php foreach($page['images'] as $image): ?>
                <div class="swiper-slide"><?php print render($image); ?></div>
              <?php endforeach; ?>
            <?php endif; ?>
          </div>
          <!-- Add Pagination -->
          <div class="swiper-pagination"></div>
        </div>
      </div>


      <div role="main" class="ui-content">

        <div data-role="navbar" id="merchandise-name">
          <h3><?php print $page['title']; ?><?php print $page['pexp_free']; ?></h3>
          <?php if($page['max_points'] != 0): ?>
          <h4 style="margin: 0.5em 0;">可使用 <?php print $page['max_points']; ?> 个积分</h4>
          <?php endif; ?>
        </div><!-- /navbar -->

        <div data-role="navbar" id="merchandise-price">
          <h3 class="ui-btn-inline" style="color: #fa620e;"><?php print $page['pshopping_price']; ?></h3>
          <h3 class="ui-btn-inline"
              style="color: #666;text-decoration: line-through; font-size: 0.9em;">
            <?php print $page['pcost_price']; ?>
          </h3>

        </div><!-- /navbar -->

        <hr style= "margin: 0.3em 0 0.3em 0" color="#aaaaaa" size="1">

        <div data-role="navbar" id="merchandise-sku">
          <p><?php print $page['maker']; ?></p>
          <p><?php print $page['sku']; ?></p>
          <p><?php print $page['weight']; ?></p>
          <p><?php print $page['volume']; ?></p>
        </div><!-- /navbar -->

        <hr style= "margin: 0.3em 0 0.3em 0" color="#aaaaaa" size="1">


        <div data-role="tabs" style="padding: 0;">
          <div data-role="navbar">
            <ul>
              <li><a href="#merchandise-content" data-theme="a" data-ajax="false" class="ui-btn-active">商品详情</a></li>
              <li><a href="#merchandise-comments" data-theme="a" data-ajax="false">评论</a></li>
            </ul>
          </div>

          <div id="merchandise-content" class="ui-content">
            <?php print render($page['content']); ?>
          </div>

          <div id="merchandise-comments" class="ui-content" style="padding: 0;">

            <div data-role="navbar">
              <ul>
                <li><a href="#" id="add-comment" class="ui-btn ui-icon-edit ui-btn-icon-left ui-btn-active ui-corner-all">请留言</a></li>
              </ul>
            </div><!-- /navbar -->

            <ul data-role="listview" data-split-theme="a" data-inset="false" id="comments-listview">
              <?php if (!empty($page['comments'])): ?>
                <?php foreach($page['comments'] as $cm): ?>
                  <?php if($cm['pid'] == 0):?>
                    <li class="comment-left">
                      <img style="top: 0.2em; max-height: 4em; max-width: 4em;" class="comment-head-image" src="<?php print $cm['head_image_url']; ?>">
                      <p style="left: 0; position: absolute; top: 5.5em; max-width: 5em;"><?php print $cm['name']; ?></p>
                      <p><?php print $cm['created']; ?></p>
                      <p style="white-space: inherit;"><?php print $cm['subject']; ?></p>
                    </li>
                  <?php else: ?>
                    <li class="comment-right" style="padding-left: 1em;padding-right: 5.5em;">
                      <img style="left: inherit; right: 0;top: 0.2em; max-height: 4em; max-width: 4em;" class="comment-head-image" src="<?php print $cm['head_image_url']; ?>">
                      <p style="right: 0; position: absolute; top:5.5em; max-width: 5em;"><?php print $cm['name']; ?></p>
                      <p ><?php print $cm['created']; ?></p>
                      <p style="white-space: inherit;"><?php print $cm['subject']; ?></p>
                    </li>
                  <?php endif; ?>
                <?php endforeach; ?>
              <?php endif;?>

            </ul> <!-- comments list-view -->

          </div>
        </div>
        

      </div> <!-- div role="main" -->



      <div data-role="footer" data-position="fixed" data-theme="a" id="prepare-pay-footer" data-tap-toggle="false">
        <div data-role="navbar" data-iconpos="right">
          <ul>
            <li><a href="#" rel="external" data-icon="check" class="ui-btn-active ui-corner-all" id="pay-button">立即购买</a></li>
            <li><a href="#" data-ajax="false" data-icon="plus" class="ui-corner-all" id="cart-button">加入购物车</a></li>
          </ul>
        </div><!-- /navbar -->
      </div><!-- /footer -->

      <!-- comment add panel -->
      <div data-role="panel" id="add-comment-panel" data-display="overlay" data-position="right">
        <ul data-role="listview" data-icon="false" class="panel-list-view">
          <li>
            <legend>商品评价:</legend>
          </li>

          <li>
            <textarea cols="30" rows="7" data-clear-btn="true" name="textarea-comment" id="textarea-comment"></textarea>
          </li>
          <li><a href="#" id="addr-save" style="background-color: #38c; text-align: center;"
                 class="ui-btn ui-icon-check ui-btn-icon-left" data-rel="close">保存</a></li>
      </div><!-- /comment panel -->

      <!-- go to home page -->
      <a href="<?php print $page['home_page'];?>" id="goto-home">首页</a>

    </div>  <!-- div role="page" -->

  <!--**************javascript file load*************************-->
    <?php foreach($scripts as $js): ?>
      <script type="text/javascript" src="<?php print $js; ?>"></script>
    <?php endforeach; ?>
  <!--**************javascript file load*************************-->

  <?php endif; ?>


</body>

</html>



