<?php

/**
 * @file
 * Default theme implementation to display wechat py mobile adv page structure of a single
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
  <meta name="viewport" content="width=device-width, user-scalable=0,initial-scale=1"/>
  <?php foreach($styles as $css): ?>
    <link rel="stylesheet" type="text/css" href="<?php print $css; ?>">
  <?php endforeach; ?>
  <?php print $page['scripts']; ?>
</head>

<body>
  <div data-role="page" id="py-mobile-adv-page">

    <!--Jquery mobile ui content -->
    <div role="main" class="ui-content">
    <?php if (!empty($page['error'])): ?>
      <div class="ui-body ui-body-a ui-corner-all">
        <?php print render($page['error']); ?>
      </div>
    <?php else: ?>
      <div class="ui-body ui-body-a adv-item-content" id="mobile-adv-content">
        <?php print render($page['content']); ?>
      </div>

      <hr color="green" size="6">

      <!--page products image list-->
      <?php if(array_key_exists('merchandise_list', $page)): ?>
        <div class="ui-grid-a">
          <?php foreach ($page['merchandise_list'] as $key => $node): ?>
          <?php if ($key % 2 == 0): ?>
            <div class="ui-block-a uibla">
              <div class="ui-body ui-body-a ui-corner-all">
                <a href="<?php print $node['purl']; ?>">
                  <?php print render($node['pimage']); ?>
                </a>
                <div class="ui-body merchandise-name" style="height: 3em;word-wrap: break-word;">
                  <?php print $node['pname']; ?>
                  <?php print $node['pexp_free']; ?>
                </div>
                <div class="ui-body" style="margin: 0; padding: 0;">
                  <div style="font-weight: bold;color: #666;text-decoration: line-through;font-size: 0.9em;">
                    <?php print '¥' . number_format($node['pcost_price'], 2); ?>
                  </div>
                </div>
                <div class="ui-body" style="margin: 0; padding: 0;">
                  <div style="float: left; font-weight: bold;color: #fa620e;font-size: 1.0em;">
                    <?php print '¥' . number_format($node['pshopping_price'], 2); ?>
                  </div>
                    <?php print render($page['cart_plus']); ?>
                </div>
              </div>
            </div>
          <?php else: ?>
            <div class="ui-block-b uibla">
              <div class="ui-body ui-body-a ui-corner-all">
                <a href="<?php print $node['purl']; ?>">
                  <?php print render($node['pimage']); ?>
                </a>
                <div class="ui-body merchandise-name" style="height: 3em;word-wrap: break-word;">
                  <?php print $node['pname']; ?>
                  <?php print $node['pexp_free']; ?>
                </div>
                <div class="ui-body" style="margin: 0; padding: 0;">
                  <div style="font-weight: bold;color: #666;text-decoration: line-through;font-size: 0.9em;">
                    <?php print '¥' . number_format($node['pcost_price'], 2); ?>
                  </div>
                </div>
                <div class="ui-body" style="margin: 0; padding: 0;">
                  <div style="float: left; font-weight: bold;color: #fa620e;font-size: 1.0em;">
                    <?php print '¥' . number_format($node['pshopping_price'], 2); ?>
                  </div>
                    <?php print render($page['cart_plus']); ?>
                </div>
              </div>
            </div>
          <?php endif; ?>
          <?php endforeach; ?>
        </div>
      <?php endif; ?> <!-- page products image list -->
      
    <?php endif; ?>

    </div><!-- /content -->


    <!--company information footer-->
    <div data-role="footer">
      <h4 class="company">北京梦乡文化有限公司</h4>
      <h6 class="company shadow-text"> 微信认证服务号</h6>
    </div><!-- /footer -->



  </div><!-- /page -->

  <?php foreach($scripts as $js): ?>
    <script type="text/javascript" src="<?php print $js; ?>"></script>
  <?php endforeach; ?>
</body>

</html>

