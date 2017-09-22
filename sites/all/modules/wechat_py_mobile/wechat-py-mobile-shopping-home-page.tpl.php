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
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 *
 * @ingroup themeable
 */

?>
<!DOCTYPE html>
<html>

<head>
  <title><?php print $head_title; ?></title>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  <meta name="viewport" content="width=device-width, user-scalable=0,initial-scale=1.0,maximum-scale=1.0, minimum-scale=1.0"/>
  <?php foreach($styles as $css): ?>
  <link rel="stylesheet" type="text/css" href="<?php print $css; ?>">
  <?php endforeach; ?>
</head>

<body>
  <div data-role="page">
    <div role="main" class="ui-content">

    <div class="ui-grid-a">
      <div class="ui-block-a"><div class="ui-bar ui-bar-a" style="height:60px">Block A</div></div>
      <div class="ui-block-b"><div class="ui-bar ui-bar-a" style="height:60px">Block B</div></div>
    </div><!-- /grid-a -->



    <div class="ui-grid-b">
      <div class="ui-block-a"><div class="ui-bar ui-bar-a" style="height:60px">Block A</div></div>
      <div class="ui-block-b"><div class="ui-bar ui-bar-a" style="height:60px">Block B</div></div>
      <div class="ui-block-c"><div class="ui-bar ui-bar-a" style="height:60px">Block C</div></div>
    </div><!-- /grid-b -->

      <?php print drupal_render($page); ?>




    </div>

  </div>

  <?php foreach($scripts as $js): ?>
  <script type="text/javascript" src="<?php print $js; ?>"></script>
  <?php endforeach; ?>
</body>

</html>

