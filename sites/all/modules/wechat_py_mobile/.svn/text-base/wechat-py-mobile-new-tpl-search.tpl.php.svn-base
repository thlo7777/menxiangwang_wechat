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
 //height=device-height, 
 //
 //data-dom-cache="true" 
 /* <?php print $page['term_filter']; ?> */
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
  <?php print $page['scripts']; ?>
</head>

<body>
  <?php if (!empty($page['error_info'])) :?>
    <div class="ui-body ui-body-a ui-corner-all"
         style= "margin-top: 0.5em; background-color: #F1DD80; border-color: #333; text-shadow: 0 1px 0 #ffffff;">
      <p><?php print $page['error_info']; ?></p>
    </div>
  <?php else: ?>

    <div data-role="page" id="py-mobile-home-page">

      <!--header for shopping adv image -->
      <div data-role="header">

        <div class="swiper-container">
          <div class="swiper-wrapper">
            <?php foreach($page['adv_container'] as $image): ?>
              <div class="swiper-slide"><?php print render($image); ?></div>
            <?php endforeach; ?>
          </div>
          <!-- Add Pagination -->
          <div class="swiper-pagination"></div>
        </div>
      </div>

      <!--Jquery mobile ui content -->
      <div role="main" class="ui-content">

        <hr style= "margin: 0.3em 0 0.3em 0" color="#F9F9F9" size="2">

        <!-- dispalay search information -->
        <div data-role="navbar" data-iconpos="left" id="search-info" style="display: none;">
          <button id="term-filter" style="font-size: 13px;">全部商品</button>

          <div id="voc-id" style="display: none;"><?php print $page['voc_id']; ?></div>
          <div id="term-id" style="display: none;"><?php print $page['term_id']; ?></div>
          <div id="last-id" style="display: none;"><?php print $page['last_id']; ?></div>
          <div id="xyz" style="display: none;"><?php print $page['xyz']; ?></div>
        </div><!-- /navbar -->

        <!-- volume and hot star -->
        <div data-role="navbar" data-iconpos="left" id="search-type">
          <ul>
            <li><a href="#" id="search-volume" data-icon="grid" class="ui-btn-active">按销量</a></li>
            <li><a href="#" id="search-views" data-icon="star">按人气</a></li>
          </ul>
        </div><!-- /navbar -->


        <hr style= "margin: 0.3em 0 0.3em 0" color="#F9F9F9" size="2">

        <!--page products image list-->
        <div class="ui-grid-a" id= "merchandise-list">
        </div>
        <!--page products image list-->

      </div><!-- /content -->

      <!--company information footer-->
      <hr style= "margin: 0.3em 0 0.3em 0" color="#ddd" size="2">
      <div data-role="navbar">
        <h4 class="company">北京梦乡文化有限公司</h4>
        <h6 class="company shadow-text"> 微信认证服务号</h6>
      </div><!-- /footer -->

      <!--icon button fix navbar-->
      <div data-role="footer" data-position="fixed" data-theme="a" id="icon-button" data-tap-toggle="false">
        <div data-role="navbar">
          <ul>
            <li>
              <!-- <a href="<?php /* print $page['search_url'];*/ ?>" id="search-icon" rel="external"> -->
                <a href="#service-area-list" id="search-icon" rel="external">
                <?php print render($page['button_container']['search_icon']);?>
              </a>
            </li>

            <li>
              <a href="<?php print $page['my_order_url']; ?>" rel="external">
                <?php print render($page['button_container']['order_icon']);?>
              </a>
            </li>

            <li>
              <a href="<?php print $page['cart_url']; ?>" rel="external">
                <?php print render($page['button_container']['cart_icon']);?>
                <?php print render($page['button_container']['cart_icon_add']);?>
              </a>
            </li>

            <li>
              <a href="<?php print $page['my_doc_url']; ?>" rel="external">
                <?php print render($page['button_container']['address_icon']);?>
              </a>
            </li>

          </ul>
        </div><!-- /navbar -->
      </div><!-- /footer -->

        <div data-role="panel" id="service-area-list" data-display="push" data-position="left">
          <ul data-role="listview" id="search-panel-lv">
            <li data-icon="back"><a href="#" data-rel="close" style="background-color: #EFBF3B;">返回</a></li>
            <?php if (empty($page['product_cat'])): ?>
                <li data-role="list-divider">没有记录</li>
            <?php else: ?>
                <?php foreach($page['product_cat'] as $terms): ?>
                    <?php if (empty($terms['child'])) : ?>
                        <li><a href="#" class="search-panel-term" data-vid="2" data-tid="<?php print $terms['tid']; ?>">
                            <?php print $terms['name']; ?>
                        </a></li>
                    <?php else: ?>
                        <li data-role="collapsible" data-inset="false" data-iconpos="right">
                            <h3><?php print $terms['name']; ?></h3>
                            <ul data-role="listview">
                                <li><a href="#" class="search-panel-term" data-vid="2" data-tid="<?php print $terms['tid']; ?>">
                                    全部
                                </a></li>
                            <?php foreach($terms['child'] as $cterm): ?>
                                <li><a href="#" class="search-panel-term" data-vid="2" data-tid="<?php print $cterm['tid']; ?>">
                                    <?php print $cterm['name']; ?>
                                </a></li>
                            <?php endforeach; ?>
                            </ul>
                        </li><!-- /collapsible -->
                    <?php endif; ?>
                <?php endforeach; ?>
                <li data-icon="refresh"><a href="#" class="search-panel-term" data-vid="2", data-tid="-100">所有商品</a></li>
            <?php endif; ?>

          </ul> <!-- root listview -->

        </div><!-- /panel -->

    </div><!-- /page -->

  <!--**************javascript file load*************************-->
  <?php foreach($scripts as $js): ?>
    <script type="text/javascript" src="<?php print $js; ?>"></script>
  <?php endforeach; ?>
  <!--**************javascript file load*************************-->
  <?php endif; ?>

</body>

</html>


