(function ($) {
  $(document).ready(function(){

    var uid = getUrlVars("uid");
    var img = getUrlVars("img");
    var title = "";
    var wechat_url = "http://mxweixin.dreamland360.com/wechat-ajax/xxzs/" + uid + "/" + img;

    
    var icon_room_area = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel_room_area.png";
    var icon_room_bed = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel_room_bed.png";
    var icon_people = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel_room_people.png";
    var icon_rmb = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel_room_rmb.png";
    var icon_smoking = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel_room_smoking.png";
    var icon_wifi = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel-icon_wifi.png";
    var icon_brft = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel_room_brft.png";
    var icon_window = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/hotel_room_window.png";
    var icon_book = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/room_book_icon1.png";

    $.ajax({
      method: "GET",
      cache: false,
      url: wechat_url 
    })
      .done(function(data){
        title = data.title;
        console.log(data);
        $.each(data, function(i, item){
          if(i === "img0"){
            $(".room-1st-image").find("img").attr('src', item);
          }
          if(i === "room_internet"){
            if(item != null){
              $row = $('<tr/>');
              $col1 = $('<td/>');
              $col1.append('<img src="' + icon_wifi + '"/>');
              $col2 = $('<td/>');
              $col2.append('宽带');
              $col3 = $('<td/>');
              $col3.append(item);
              $row.append($col1);
              $row.append($col2);
              $row.append($col3);
              $("table").append($row);
            }
          }
          if(i === "room_area"){
            if(item != null){
              $row = $('<tr/>');
              $col1 = $('<td/>');
              $col1.append('<img src="' + icon_room_area + '"/>');
              $col2 = $('<td/>');
              $col2.append('面积');
              $col3 = $('<td/>');
              $col3.append(item);
              $row.append($col1);
              $row.append($col2);
              $row.append($col3);
              $("table").append($row);
            }
          }
          if(i === "room_bed"){
            if(item != null){
              $row = $('<tr/>');
              $col1 = $('<td/>');
              $col1.append('<img src="' + icon_room_bed + '"/>');
              $col2 = $('<td/>');
              $col2.append('床型');
              $col3 = $('<td/>');
              $col3.append(item);
              $row.append($col1);
              $row.append($col2);
              $row.append($col3);
              $("table").append($row);
            }
          }
          if(i === "room_brft"){
            if(item != null){
              $row = $('<tr/>');
              $col1 = $('<td/>');
              $col1.append('<img src="' + icon_brft + '"/>');
              $col2 = $('<td/>');
              $col2.append('早餐');
              $col3 = $('<td/>');
              $col3.append(item);
              $row.append($col1);
              $row.append($col2);
              $row.append($col3);
              $("table").append($row);
            }
          }
          if(i === "room_extra_bed"){
            if(item != null){
              $row = $('<tr/>');
              $col1 = $('<td/>');
              $col1.append('<img src="' + icon_rmb + '"/>');
              $col2 = $('<td/>');
              $col2.append('加床');
              $col3 = $('<td/>');
              $col3.append(item);
              $row.append($col1);
              $row.append($col2);
              $row.append($col3);
              $("table").append($row);
            }
          }
          if(i === "room_number"){
            if(item != null){
              $row = $('<tr/>');
              $col1 = $('<td/>');
              $col1.append('<img src="' + icon_people + '"/>');
              $col2 = $('<td/>');
              $col2.append('人数');
              $col3 = $('<td/>');
              $col3.append(item);
              $row.append($col1);
              $row.append($col2);
              $row.append($col3);
              $("table").append($row);
            }
          }
          if(i === "room_smoking"){
            if(item != null){
              $row = $('<tr/>');
              $col1 = $('<td/>');
              $col1.append('<img src="' + icon_smoking + '"/>');
              $col2 = $('<td/>');
              $col2.append('无烟');
              $col3 = $('<td/>');
              $col3.append(item);
              $row.append($col1);
              $row.append($col2);
              $row.append($col3);
              $("table").append($row);
            }
          }
          if(i === "room_window"){
            if(item != null){
              $row = $('<tr/>');
              $col1 = $('<td/>');
              $col1.append('<img src="' + icon_window + '"/>');
              $col2 = $('<td/>');
              $col2.append('窗户');
              $col3 = $('<td/>');
              $col3.append(item);
              $row.append($col1);
              $row.append($col2);
              $row.append($col3);
              $("table").append($row);
            }
          }
        });
        
        $(".room-name").append(data.title);
        $(".price").append(data.room_price);
        //$(".book-button").append('<img src="' + icon_book + '"/>');

    });

    $(document).ajaxSuccess(function() {
      document.title =title;
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


