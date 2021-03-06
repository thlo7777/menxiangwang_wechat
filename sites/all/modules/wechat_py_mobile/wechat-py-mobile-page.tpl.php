<?php

/**
 * @file
 * Default theme implementation to display wechat py shopping home page
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
  <title><?php print $head_title; ?></title>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  <meta name="viewport" content="width=device-width, user-scalable=0,initial-scale=1.0,maximum-scale=1.0, minimum-scale=1.0"/>
  <?php foreach($styles as $css): ?>
  <link rel="stylesheet" type="text/css" href="<?php print $css; ?>">
  <?php endforeach; ?>
</head>

<body>
  <?php print drupal_render($page); ?>

  <?php foreach($scripts as $js): ?>
  <script type="text/javascript" src="<?php print $js; ?>"></script>
  <?php endforeach; ?>
</body>

</html>

