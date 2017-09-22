//py_ui_test_page.js

(function($){
  $(document).ready(function(){

    /***************************** all js api ***************************/
    //handle all wx api function
    $.set_wx_config();
    wx.ready(function () {
      // 在这里调用 API
      //
      //check jsapi version
      // 1 判断当前版本是否支持指定 JS 接口，支持批量判断
      wx.checkJsApi({
        jsApiList: [
          'getNetworkType',
          'previewImage',
          'chooseWXPay'
        ],
        success: function (res) {
          
          var errmsg = res.errMsg;
          var regexp = /checkJsApi:ok/i;
          var found = errmsg.match(regexp);
          if(found === null) {
            alert("您的微信版本太低，请下载最新版本！");
            alert(JSON.stringify(res));
            return;
          }
        }
      });


      // 7.2 获取当前地理位置
      //document.querySelector('#getLocation').onclick = function () {
      /*
        wx.getLocation({
          success: function (res) {
            alert('get location hahaha!');
            alert(JSON.stringify(res));
          },
          cancel: function (res) {
            alert('用户拒绝授权获取地理位置');
          },
          fail: function (res) {
            alert(JSON.stringify(res));
          }

        });
      */
      //};

      // pay test
      $("#testapi" ).click(function(){
        value = $("#pay_value").html();
        if(value === '') {
          alert("订单调用为空");
          return;
        }

        data = $.parseJSON(value);
        wx.chooseWXPay({
          timestamp: data.timeStamp,
          nonceStr: data.nonceStr,
          package: data.package,
          signType: data.signType, // 注意：新版支付接口使用 MD5 加密
          paySign: data.paySign,
          success: function (res) {
          // 支付成功后的回调函数
            var errmsg = res.errMsg;
            var regexp = /chooseWXPay:ok/i;
            var found = errmsg.match(regexp);
            if(found === null) {
              alert("支付系统返回错误");
              alert(JSON.stringify(res));
            }
          }

          
        });

      });

    });//wx.ready

    //wx error handle
    wx.error(function (res) {
      alert(res.errMsg);
    });

    /***************************** pay and address api ***************************/
    //template function for product
    $("#get-addr").on("click", wechat_get_addr);
    //获取共享地址
    function wechat_get_addr()
    {
      value = $("#address").html();
      if(value === '') {
        alert("找不到用户地址");
        return;
      }

      if (typeof WeixinJSBridge == "undefined"){
        if( document.addEventListener ){
          //alert('addEventListener');
          document.addEventListener('WeixinJSBridgeReady', editAddress, false);
        }else if (document.attachEvent){
          //alert('attachEvent');
          document.attachEvent('WeixinJSBridgeReady', editAddress); 
          document.attachEvent('onWeixinJSBridgeReady', editAddress);
        }
      } else {
        data = $.parseJSON(value);
        editAddress(data);
      }

    }// end function wechat_get_addr

    function editAddress(data)
    {

      WeixinJSBridge.invoke('editAddress', data,
        function(res){
          var errmsg = res.err_msg;
          var regexp = /edit_address:ok/gi;
          var found = errmsg.match(regexp);
          if(found === null) {
            alert('没有选取地址');
            //alert(JSON.stringify(res));
          } else {
            var value1 = res.proviceFirstStageName;
            var value2 = res.addressCitySecondStageName;
            var value3 = res.addressCountiesThirdStageName;
            var value4 = res.addressDetailInfo;
            var tel = res.telNumber;
            
            alert(value1 + value2 + value3 + value4 + ":" + tel);
          }
        }
      );
    }


    //$("#testapi" ).on("click", wechat_submit_pay);
    //get data and sumit to wechat
    function wechat_submit_pay() {
      value = $("#pay_value").html();
      if(value === '') {
        alert("订单调用为空");
        return;
      }

      if (typeof WeixinJSBridge == "undefined"){
        if( document.addEventListener ){
            document.addEventListener('WeixinJSBridgeReady', jsApiCall, false);
        }else if (document.attachEvent){
            document.attachEvent('WeixinJSBridgeReady', jsApiCall); 
            document.attachEvent('onWeixinJSBridgeReady', jsApiCall);
        }
      }else{
        data = $.parseJSON(value);
        jsApiCall(data);
      }
    }// end function wechat_submit_pay

    function jsApiCall(data)
    {

      WeixinJSBridge.invoke('getBrandWCPayRequest',
        data,
        function(res){
          alert(JSON.stringify(res));
          WeixinJSBridge.log(res.err_msg);
          //alert(res.err_code+res.err_desc+res.err_msg);
        }
      );
    }

  }); //document ready
})(jQuery);

