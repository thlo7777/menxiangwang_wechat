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
 
    //don't use fn, cause we want to use $.fun
    $.share_current_page = function(title, desc, link, imgUrl) {

        wx.ready(function () {  //should add wx ready when share, otherwise wechat js can't call share api
            //share to friend
            wx.onMenuShareAppMessage({
                title: title, // 分享标题
                desc: desc, // 分享描述
                link: link, // 分享链接，该链接域名或路径必须与当前页面对应的公众号JS安全域名一致
                imgUrl: imgUrl, // 分享图标
                success: function () { 
                    // 用户确认分享后执行的回调函数
                },
                cancel: function () { 
                    // 用户取消分享后执行的回调函数
                }
            });

            //share to friends
            wx.onMenuShareTimeline({
                title: title, // 分享标题
                link: link, // 分享链接，该链接域名或路径必须与当前页面对应的公众号JS安全域名一致
                imgUrl: imgUrl, // 分享图标
                success: function () { 
                    // 用户确认分享后执行的回调函数
                },
                cancel: function () { 
                    // 用户取消分享后执行的回调函数
                }
            });

            //share to QQ
            wx.onMenuShareQQ({
                title: title, // 分享标题
                desc: desc, // 分享描述
                link: link, // 分享链接
                imgUrl: imgUrl, // 分享图标
                success: function () { 
                   // 用户确认分享后执行的回调函数
                },
                cancel: function () { 
                   // 用户取消分享后执行的回调函数
                }
            });

            //share to weibo
            wx.onMenuShareWeibo({
                title: title, // 分享标题
                desc: desc, // 分享描述
                link: link, // 分享链接
                imgUrl: imgUrl, // 分享图标
                success: function () { 
                   // 用户确认分享后执行的回调函数
                },
                cancel: function () { 
                   // 用户取消分享后执行的回调函数
                }
            });

            //share to QZone
            wx.onMenuShareQZone({
                title: title, // 分享标题
                desc: desc, // 分享描述
                link: link, // 分享链接
                imgUrl: imgUrl, // 分享图标
                success: function () { 
                   // 用户确认分享后执行的回调函数
                },
                cancel: function () { 
                   // 用户取消分享后执行的回调函数
                }
            });

        });//wx.ready
        
    };  //end $.share_merchandise_page
})(jQuery);
