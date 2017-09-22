(function ($) {
  $(document).ready(function(){

    var uid = getUrlVars("uid");
    var img = getUrlVars("img");


    var wechat_url = "http://mxweixin.dreamland360.com/wechat-ajax/xxzs/" + uid + "/" + img;
    var icon_wifi = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel-icon_wifi.png";
    var icon_alarm = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel-icon_alert.png";
    var icon_baggage = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel-icon_baggage.png";
    var icon_hotwater = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel-icon_water.png";
    var icon_laundry = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel-icon_laundry.png";
    var icon_park = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel-icon_park.png";

    $.ajax({
      method: "GET",
      cache: false,
      url: wechat_url 
    })
      .done(function(data){
        document.title = data.title;
        $(".hotel-phone").append("酒店电话: " + data.phone);
        if(data.free_wifi === "1"){
          $("#col-wifi").find("img").attr('src', icon_wifi);
          $("#col-wifi").find("span").append("免费WIFI");
        }
        if(data.alarm === "1"){
          $("#col-alarm").find("img").attr('src', icon_alarm);
          $("#col-alarm").find("span").append("叫醒服务");
        }
        if(data.baggage === "1"){
          $("#col-baggage").find("img").attr('src', icon_baggage);
          $("#col-baggage").find("span").append("行李寄存");
        }
        if(data.hot_water === "1"){
          $("#col-hotwater").find("img").attr('src', icon_hotwater);
          $("#col-hotwater").find("span").append("全天热水");
        }
        if(data.laundry === "1"){
          $("#col-laundry").find("img").attr('src', icon_laundry);
          $("#col-laundry").find("span").append("洗衣服务");
        }
        if(data.car_park === "1"){
          $("#col-carpark").find("img").attr('src', icon_park);
          $("#col-carpark").find("span").append("停车服务");
        }

        $(".hotel-text").append(data.intro);
        //$.each(data, function(i, item){
        //});

    });

    function getUrlVars(sParam)
    {
      var sPageURL = window.location.search.substring(1);
      var sURLVariables = sPageURL.split('&');
      for (var i = 0; i < sURLVariables.length; i++) 
      {
        var sParameterName = sURLVariables[i].split('=');
        if (sParameterName[0] == sParam) 
        {
          return sParameterName[1];
        }
      }
    }
/*********end for document ready*************/
  });
})(jQuery);

