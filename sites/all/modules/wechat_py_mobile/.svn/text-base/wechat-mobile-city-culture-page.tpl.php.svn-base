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

  <div data-role="page" id="mobile-city-culture-page">

    <!--Jquery mobile ui content -->
    <div role="main" class="ui-content">
    <?php if (!empty($page['error'])): ?>
      <div class="ui-body ui-body-a ui-corner-all">
        <?php print render($page['error']); ?>
      </div>
    <?php else: ?>

      <div id="info-container">
        <!-- dynamic create article info -->
      </div>  <!-- container for all articles information -->
      
    <?php endif; ?> <!-- page no error -->

    </div><!-- /content -->

    <div data-role="panel" id="culture-search" data-display="push" data-position="left">

      <ul data-role="listview">

        <li data-icon="delete"><a href="#" data-rel="close" style="background-color: #EFBF3B;">关闭</a></li>

        <?php if (!empty($page['vocs'])): ?>
          <?php foreach($page['vocs'] as $id => $voc): ?>
            <?php if (empty($voc['terms'])): ?>
              <li id="<?php print 'voc-' . $id; ?>" vid="<?php print $id; ?>"><a href="#"><?php print $voc['area_name']; ?></a></li>
            <?php else: ?>
              <li id="<?php print 'voc-' . $id; ?>" vid="<?php print $id; ?>" data-role="collapsible" data-iconpos="right" data-inset="false">
                <h2><?php print $voc['area_name']; ?></h2>
                <ul data-role="listview" data-theme="b">
                  <?php foreach($voc['terms'] as $term): ?>
                    <li class="term-id"><a area-id="<?php print $voc['area_id']; ?>" tid="<?php print $term['tid']; ?>" href="#"><?php print $term['tname']; ?></a></li>
                  <?php endforeach; ?>
                </ul>
              </li>
            <?php endif; ?>
          <?php endforeach; ?>
        <?php endif; ?>

        <li data-icon="refresh"><a href="#" id="reset-info">全部</a></li>
      </ul> <!-- root listview -->

    </div><!-- /panel -->

    <div data-role="footer" data-position="fixed" data-theme="a" data-tap-toggle="false" >

      <div data-role="navbar" data-iconpos="right">
        <ul>
          <li><a href="#culture-search" data-icon="search" class="ui-btn-active" id="button-search">
            分类搜索
          </a></li>
        </ul>
      </div><!-- /navbar -->

    </div><!-- /footer -->

  </div><!-- /page -->

  <?php foreach($scripts as $js): ?>
    <script type="text/javascript" src="<?php print $js; ?>"></script>
  <?php endforeach; ?>
</body>

</html>


