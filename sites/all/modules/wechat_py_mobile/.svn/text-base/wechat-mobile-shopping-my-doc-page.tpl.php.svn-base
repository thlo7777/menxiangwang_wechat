<?php

/**
 * @file
 * Default theme implementation to display wechat py mobile my account html page
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

    <div data-role="page" id="py-mobile-my-doc-page">


      <!--Jquery mobile ui content -->
      <div role="main" class="ui-content">

        <div data-role="tabs">
          <div data-role="navbar">
            <ul>
              <li><a href="#points" data-theme="a" class="ui-btn-active" data-ajax="false">我的积分</a></li>
              <li><a href="#friends" data-theme="a" data-ajax="false">我的好友</a></li>
              <li><a href="#address" data-theme="a" data-ajax="false">我的地址</a></li>
            </ul>
          </div>

          <div id="friends" class="ui-content">

            <ul data-role="listview" data-split-icon="gear" data-split-theme="a" data-inset="true">

              <?php if (empty($page['friends'])): ?>
                <li style="white-space: inherit;">
                  <h2 style="white-space: inherit;">1. 长按下方图片，关注梦乡网，获取朋友积分, 优惠多多。</h2>
                </li>
                <li style="white-space: inherit;">
                  <h2 style="white-space: inherit;">2. 关注后，赶快到【我的积分】里转发专属你的积分二维码, 获得好友支持！</h2>
                </li>
                <img style="width: 20em; margin: 0 auto; display: block; margin-top: 1em; border: solid 1px;" src="<?php print $page['mxweixin_qr_code_image']; ?>">
              <?php else: ?>

                <?php foreach ($page['friends'] as $friend): ?>
                  <li>
                    <img style="margin: 0.6em 0.3em;" src="<?php print $friend['head_img']; ?>">
                    <h2><?php print $friend['nick_name']; ?></h2>
                    <p>加入时间: <?php print $friend['regist_time']; ?></p>
                  </a></li>
                <?php endforeach; ?>

              <?php endif; ?>
            </ul>

          </div>  <!-- my firends content -->

          <div id="points" class="ui-content">

            <?php if (empty($page['my_points'])): ?>
              <legend>Something error for my points!</legend>
            <?php else: ?>
              <legend style="font-size: 1.2em; padding: 0.2em 0;">我的历史积分: <span style="color: red;"><?php print $page['my_points']['total_points']; ?></span> 个积分</legend>
              <legend style="font-size: 1.2em; padding: 0.2em 0;">我的剩余积分: <span style="color: red;"><?php print $page['my_points']['curr_points']; ?></span> 个积分</legend>

              <div id="self-qr-scan-image" style="display: none;"><?php print $page['my_points']['qr_scan_image_url']; ?></div>
              <legend style="margin: 1em; padding: 0.2em 0;">如何获得积分: <?php print $page['my_points']['points_desc']; ?></legend>

            <?php endif; ?>

          </div>  <!-- my point content-->

          <div id="address" class="ui-content">

            <ul id="addr-listview" data-role="listview" data-split-icon="gear" data-split-theme="c" data-inset="true">
            </ul> <!-- listview -->

            <a href="#" id="add-addr" class="ui-btn ui-icon-plus ui-btn-corner-all ui-btn-icon-right">增加</a>
            <p style="text-align: center; font-size: 0.8em;">最多五个地址</p>

          </div>  <!-- address -->

        </div>  <!-- tabs -->

      </div><!-- /content -->

      <!-- footer for return mobile shopping home page -->
      <div data-role="footer" data-position="fixed" data-theme="a" data-tap-toggle="false">
        <div data-role="navbar" data-iconpos="right">
          <ul>
            <li><a href="<?php print $page['mobile_shopping_home_page']; ?>" data-icon="carat-r" class="ui-btn-active">
              进入微商城
            </a></li>
          </ul>
        </div><!-- /navbar -->
      </div><!-- /footer -->

      <!-- remove address panel -->
      <div data-role="panel" id="remove-addr-panel" data-display="overlay" data-position="right">
        <ul data-role="listview" data-icon="false" id="remove-panel-list-view">
          <div id="remove-detail-address">
          </div>

          <li><a href="#" id="delete-checkbox-a">
          </a></li>

          <li><a href="#" id="remove-addr-save" style="background-color: #38c; text-align: center;"
                 class="ui-btn ui-icon-check ui-btn-icon-left" data-rel="close">关闭</a></li>

        </ul>
      </div>  <!-- remove address panel -->

      <!-- /edit or add address -->
      <div data-role="panel" id="edit-addr-panel" data-display="overlay" data-position="right">
        <ul data-role="listview" data-icon="false" class="panel-list-view">
          <li><a href="#">
              <label for="text-name">姓名</label>
              <input type="text" data-mini="true" name="text-name" id="text-name" data-clear-btn="true" value="">
          </a></li>

          <li><a href="#">
              <label for="text-tel">电话</label>
              <input type="tel" data-clear-btn="true" data-mini="true" name="text-tel" id="text-tel" value="">
          </a></li>

          <li><a href="#">

            <fieldset data-role="controlgroup" data-mini="true">
              <legend>选择地区</legend>
              <label for="select-city-1">city 1</label>
              <select name="select-city-1" id="select-city-1">
                <option value="-1">选择省份</option>
              </select>

              <label for="select-city-2">city 2</label>
              <select name="select-city-2" id="select-city-2">
                <option value="-1">选择城市</option>
              </select>

              <label for="select-city-3">city 3</label>
              <select name="select-city-3" id="select-city-3">
                <option value="-1">选择区县</option>
              </select>

            </fieldset>

          </a></li>

          <li><a href="#">
              <label for="text-detail">详细地址</label>
              <input type="text" data-clear-btn="true" data-mini="true" name="text-detail" id="text-detail" value="">
          </a></li>

          <li><a href="#" id="addr-save" style="background-color: #38c; text-align: center;"
                 class="ui-btn ui-icon-check ui-btn-icon-left">保存</a></li>

        </ul>
      </div><!-- /eidt or address panel -->

    </div><!-- /page -->

  <!--**************javascript file load*************************-->
    <?php foreach($scripts as $js): ?>
      <script type="text/javascript" src="<?php print $js; ?>"></script>
    <?php endforeach; ?>
  <!--**************javascript file load*************************-->

  <?php endif; ?>

</body>

</html>


