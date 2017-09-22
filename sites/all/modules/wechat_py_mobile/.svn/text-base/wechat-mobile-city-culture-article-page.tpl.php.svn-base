<?php

/**
 * @file
 * Default theme implementation to display mobile city culture article
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

  <div data-role="page" id="mobile-city-culture-article">

    <!--Jquery mobile ui content -->
    <div role="main" class="ui-content">
      <?php if (!empty($page['error'])): ?>
        <div class="ui-body ui-body-a ui-corner-all">
          <?php print render($page['error']); ?>
        </div>
      <?php else: ?>

        <div id="article-container">
          <div class="ui-bar ui-bar-a article-title">
            <h3><?php print $page['article_title']; ?></h3>
          </div>

          <div class="ui-body ui-body-a article-body">
            <?php print render($page['content']); ?>
          </div>

          <!-- merchandise link -->
          <?php if (!empty($page['m_links'])) :?>
            <hr style= "margin: 0" color="#ddd" size="1">

            <div style="padding: 3px;" class="ui-body ui-body-a merchandise-link">
              <div class="ui-grid-b">

                <div class="ui-block-a"
                  style="padding: 2px; border-right-width: 1px; border-right-style: solid; border-right-color: #ddd;"
                  onclick="<?php print "location.href='" . $page['m_links'][0]['purl'] . "';"; ?>">
                  <img style="margin:0 auto; width: 100%;" src="<?php print $page['m_links'][0]['pimage']; ?>">
                  <p style="font-size: 0.7em;"><?php print $page['m_links'][0]['pname']; ?></p>
                  <div style="font-weight: bold;color: #fa620e;font-size: 0.8em;">
                    <?php print '¥' . number_format($page['m_links'][0]['pshopping_price'], 2); ?>
                  </div>
                </div>

                <div class="ui-block-b"
                  style="padding: 2px; border-right-width: 1px; border-right-style: solid; border-right-color: #ddd;"
                  onclick="<?php print "location.href='" . $page['m_links'][1]['purl'] . "';"; ?>">
                  <img style="margin:0 auto; width: 100%;" src="<?php print $page['m_links'][1]['pimage']; ?>">
                  <p style="font-size: 0.7em;"><?php print $page['m_links'][1]['pname']; ?></p>
                  <div style="font-weight: bold;color: #fa620e;font-size: 0.8em;">
                    <?php print '¥' . number_format($page['m_links'][1]['pshopping_price'], 2); ?>
                  </div>
                </div>

                <div class="ui-block-c" style="padding: 2px;"
                  onclick="<?php print "location.href='" . $page['m_links'][2]['purl'] . "';"; ?>">
                  <img style="margin:0 auto; width: 100%;" src="<?php print $page['m_links'][2]['pimage']; ?>">
                  <p style="font-size: 0.7em;"><?php print $page['m_links'][2]['pname']; ?></p>
                  <div style="font-weight: bold;color: #fa620e;font-size: 0.8em;">
                    <?php print '¥' . number_format($page['m_links'][2]['pshopping_price'], 2); ?>
                  </div>
                </div>

              </div><!-- /grid-b -->
            </div>

          <?php endif;?>
        </div>  <!-- container for all articles information -->
        
      <?php endif; ?> <!-- page no error -->

    </div><!-- /content -->


    <!--company information footer-->
    <div data-role="footer">
      <h4 class="company">关注梦乡网</h4>
      <h6 class="company shadow-text"> 微信认证服务号</h6>
    </div><!-- /footer -->
    


  </div><!-- /page -->

  <?php foreach($scripts as $js): ?>
    <script type="text/javascript" src="<?php print $js; ?>"></script>
  <?php endforeach; ?>
</body>

</html>



