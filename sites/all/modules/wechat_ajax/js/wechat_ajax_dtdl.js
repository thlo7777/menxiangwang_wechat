(function($){
  $(document).ready(function(){
    var map = new BMap.Map("allmap");
    var point = new BMap.Point(112.191006,37.210403);  //平遥古城和市楼之间center point
    map.centerAndZoom(point, 17);
    map.addControl(new BMap.ZoomControl());       

    /*
    var marker = new BMap.Marker(new BMap.Point(112.190072,37.210432));  //创建平遥古城标注
    map.addOverlay(marker);    // 将标注添加到地图中
    var opts = {
      width : 100,    // 信息窗口宽度
      height: 60,     // 信息窗口高度
      title : "平遥古城", // 信息窗口标题
      enableAutoPan : true //自动平移
    }
    var infoWindow = new BMap.InfoWindow("地址：山西省晋中市平遥县", opts);  // 创建信息窗口对象
    marker.addEventListener("click", function(){          
      map.openInfoWindow(infoWindow,point); //开启信息窗口
    });*/

    var local = new BMap.LocalSearch(map, {
      renderOptions:{map: map}
    });
    local.search("景点");

  }); //document ready
})(jQuery);
