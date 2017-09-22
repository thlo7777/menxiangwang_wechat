(function ($) {
  $(document).ready(function(){

  var uid = getUrlVars("uid");
  var img = getUrlVars("img");

  var wechat_url = "http://mxweixin.dreamland360.com/wechat-ajax/xxzs/" + uid + "/" + img;
  var hotel_name = "";
  var hotel_longitude = 0;
  var hotel_latitude = 0;

  $.ajax({
    method: "GET",
    cache: false,
    url: wechat_url 
  })
  .done(function(data){
    document.title = hotel_name = data.hotel_name;
    hotel_longitude = data.hotel_longitude;
    hotel_latitude = data.hotel_latitude;
    console.log(data);
  });

  $(document).ajaxSuccess(function() {
    //初始化地图对象，加载地图
    var map = new AMap.Map("mapContainer",{
      resizeEnable: true,
        view: new AMap.View2D({
            center:new AMap.LngLat(hotel_longitude,hotel_latitude),//地图中心点
            zoom:17 //地图显示的缩放级别
        })
      });   
    //添加自定义点标记
    addMarker();
    
    //添加带文本的点标记覆盖物
    function addMarker(){ 
        //自定义点标记内容   
      var markerContent = document.createElement("div");
      markerContent.className = "markerContentStyle";
        
      //点标记中的图标
      var markerImg = document.createElement("img");
         markerImg.className = "markerlnglat";
       markerImg.src = "http://webapi.amap.com/images/0.png"; 
       markerContent.appendChild(markerImg);
       
       //点标记中的文本
       var markerSpan = document.createElement("span");
       markerSpan.innerHTML = hotel_name;
       markerContent.appendChild(markerSpan);
       var marker = new AMap.Marker({
        map:map,
        position: new AMap.LngLat(hotel_longitude,hotel_latitude), //基点位置
        offset: new AMap.Pixel(-18,-36), //相对于基点的偏移位置, for icon size offset
        draggable: false,  //是否可拖动
        content: markerContent   //自定义点标记覆盖物内容
      });
      marker.setMap(map);  //在地图上添加点
    }
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

