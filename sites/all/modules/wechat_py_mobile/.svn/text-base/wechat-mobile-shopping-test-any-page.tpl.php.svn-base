<?php

/**
 * @file
 * Default theme implementation to test any soultion for mobile shopping page.
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
</head>

<body>

    <div data-role="page"  id="mobile-shopping-test-any">

      <div role="main" class="ui-content">

        <a href="#" id="node-list" class="ui-btn ui-icon-shop ui-btn-icon-left">node list</a>

      </div> <!-- div role="main" -->

    </div>  <!-- div role="page" -->

<!--**************javascript file load*************************-->
  <?php foreach($scripts as $js): ?>
    <script type="text/javascript" src="<?php print $js; ?>"></script>
  <?php endforeach; ?>
<!--**************javascript file load*************************-->

</body>

</html>


