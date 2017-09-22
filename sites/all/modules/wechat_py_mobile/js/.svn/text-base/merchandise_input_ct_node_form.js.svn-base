(function($) {

    Drupal.wechat_py_mobile = Drupal.wechat_py_mobile || {};

    //drepal document ready
    Drupal.behaviors.wechat_py_mobile = {
      attach: function (context, settings) {
        settings.wechat_py_mobile = settings.wechat_py_mobile || Drupal.settings.wechat_py_mobile;
        if (settings.wechat_py_mobile == undefined) {
            return;
        }
        console.log(settings);


        var $tab = $(settings.wechat_py_mobile.formid + ' .horizontal-tab-button-2 > a').on('click', function(e) {

            var $category_level1 = $(settings.wechat_py_mobile.formid +
                ' #edit-field-product-category-term-und-0-tid-select-1 > option');
            $category_level1.each(function() {
                if ((settings.wechat_py_mobile.tid != $(this)[0].value) && ($(this)[0].value != '_none')) {
                    $(this).remove();
                }
            });

//            var $points_level1 = $(settings.wechat_py_mobile.formid +
//                ' #edit-field-product-user-point-term-und-0-tid-select-1');
//            $points_level1.each(function() {
//                if ((settings.wechat_py_mobile.tid != $(this)[0].value) && ($(this)[0].value != '_none')) {
//                    $(this).remove();
//                }
//            });

        });

      }
    };



})(jQuery);
