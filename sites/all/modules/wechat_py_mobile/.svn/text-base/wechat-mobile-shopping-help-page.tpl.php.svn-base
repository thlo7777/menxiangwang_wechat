<?php

/**
 * @file
 * Default theme implementation to display wechat py mobile user orders html page
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
      var xyz = "<?php echo $page['xyz']; ?>";
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

    <div data-role="page" id="py-mobile-shopping-help-page">


      <!--Jquery mobile ui content -->
      <div role="main" class="ui-content">

        <div data-role="navbar">
            <ul>
                <li><a href="#" class="ui-btn-active">视频很大，为节省流量，请连接Wi-Fi观看</a></li>
            </ul>
        </div><!-- /navbar -->

        <ul data-role="listview" data-inset="true" data-shadow="false">
            <?php foreach ($page['video'] as $title => $video_group): ?>
                <li data-role="collapsible" data-iconpos="right" data-inset="false">
                    <h2><?php print $title; ?></h2>
                    <ul data-role="listview">
                        <?php foreach ($video_group as $video): ?>
                            <li><a href="#">
                                <video class="video-item video-js vjs-default-skin vjs-big-play-centered"
                                    controls preload="auto" data-setup='{"example_option":true}'>
                                    <source src="<?php print $video; ?>" type="video/mp4"/>
                                </video>
                            </a></li>
                        <?php endforeach; ?>
                    </ul>
                </li>
            <?php endforeach; ?>
        </ul>   <!-- listview -->


      </div><!-- /content -->


    </div><!-- /page -->

  <!--**************javascript file load*************************-->
    <?php foreach($scripts as $js): ?>
      <script type="text/javascript" src="<?php print $js; ?>"></script>
    <?php endforeach; ?>
  <!--**************javascript file load*************************-->

  <?php endif; ?>

</body>

</html>




