<?php

/**
 * @file
 * Default theme implementation to display mobile shopping search dialog page.
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

  <?php if (!empty($page['error_info'])) :?>
    <div class="ui-body ui-body-a ui-corner-all"
         style= "margin-top: 0.5em; background-color: #F1DD80; border-color: #333; text-shadow: 0 1px 0 #ffffff;">
      <p><?php print $page['error_info']; ?></p>
    </div>
  <?php else: ?>
    <div data-role="page"  id="py-mobile-search-dialog">

      <div role="main" class="ui-content">

        <div id="search-container">

          <!-- first select for all vocbulary term -->
          <div class="ui-field-contain" id="uifc-search">
            <label for="select-search-1" class="select" style="display: none;"></label>
            <select name="select-native-1" id="select-search-1" data-native-menu="true">
              <!-- <option value="choose-one" data-placeholder="true">选择</option> -->
              <option value="1">全部商品</option>
              <option value="2">商品分类</option>
              <option value="3">积分商品</option>
              <option value="4">促销商品</option>
            </select>
          </div>
          <!-- sub term added by js -->

        </div>

               
        <!-- return button cannot use data-rel="back" for confirm button -->
        <div class="ui-grid-a">
          <div class="ui-block-a">
            <a href="<?php print $page['home_page']; ?>"
               id="search-back-confirm" 
               class="ui-btn ui-shadow ui-corner-all ui-btn-icon-left ui-icon-delete">确认</a>
          </div>
          <div class="ui-block-b">
            <!--use data-rel back for cancel button-->
            <a href="<?php print $page['home_page']; ?>"
               data-rel="back" 
               id="search-back-cancel" 
               class="ui-btn ui-shadow ui-corner-all ui-btn-icon-left ui-icon-delete">取消</a>
          </div>
        </div>

      </div> <!-- div role="main" -->

    </div>  <!-- div role="page" -->

<!--**************javascript file load*************************-->
  <?php foreach($scripts as $js): ?>
    <script type="text/javascript" src="<?php print $js; ?>"></script>
  <?php endforeach; ?>
<!--**************javascript file load*************************-->

  <?php endif; ?>

</body>

</html>


