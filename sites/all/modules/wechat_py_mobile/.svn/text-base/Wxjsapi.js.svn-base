//for ajax get signpackage and set wx config plugin
(function($) {
 
    //don't use fn, cause we want to use $.fun
    $.set_wx_config = function() {
        var path = "http://mxweixin.dreamland360.com/wechat-py-mobile/py-shopping-api";
        var url = window.location.href;     // Returns full URL
        //console.log(url);

        //1. get signpackage from server by ajax
        var request = $.ajax({
          method: "GET",
          url: path,
          data: {code: "url", name: url} 
        });

        request.fail(function(jqXHR, textStatus, errorThrown) {
          alert('获取json失败:' + textStatus); //other error
        });

        request.always(function(data) {
        });

        request.done(function(data) {
          //2. config wx.config
          wx.config({
            debug: false,
            appId: data.appId,
            nonceStr: data.nonceStr,
            timestamp: data.timestamp,
            signature: data.signature,
            jsApiList: [
              'checkJsApi',
              'onMenuShareTimeline',
              'onMenuShareAppMessage',
              'onMenuShareQQ',
              'onMenuShareWeibo',
              'onMenuShareQZone',
              'hideMenuItems',
              'showMenuItems',
              'hideAllNonBaseMenuItem',
              'showAllNonBaseMenuItem',
              'translateVoice',
              'startRecord',
              'stopRecord',
              'onVoiceRecordEnd',
              'playVoice',
              'onVoicePlayEnd',
              'pauseVoice',
              'stopVoice',
              'uploadVoice',
              'downloadVoice',
              'chooseImage',
              'previewImage',
              'uploadImage',
              'downloadImage',
              'getNetworkType',
              'openLocation',
              'getLocation',
              'hideOptionMenu',
              'showOptionMenu',
              'closeWindow',
              'scanQRCode',
              'chooseWXPay',
              'openProductSpecificView',
              'addCard',
              'chooseCard',
              'openCard'
            ]
          }); //end wx.config

        }); //end request.done
    };  //end $.set_wx_config
 
})(jQuery);
