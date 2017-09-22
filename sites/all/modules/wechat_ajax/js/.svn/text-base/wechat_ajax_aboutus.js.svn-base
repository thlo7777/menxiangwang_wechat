(function($){
  $(document).ready(function(){


    var div_loader = {
      loader: $("<div />", {class: "loader"}),
      wrapper: $(".wrapper"),
      aboutus: $(".aboutus"),
      img_load: $(".img_load"),
    };

    //div_loader.wrapper.append(div_loader.loader);
    $("body").append("<div class='loader'></div>");

    $.ajax({
      url: 'http://mxweixin.dreamland360.com/wechat-ajax/aboutus/data',
      beforeSend: function() {
        //$('.wrapper').append("<div class='loader'></div>");
      },
      success: function (data) {
        //$(".wrapper").html(data);
        div_loader.aboutus.append('<h4>' + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + data.aboutus + "</h4>");
        div_loader.aboutus.find("h4").css("text-align", "left");
        div_loader.aboutus.find("h4").css("letter-spacing", "0px");
        div_loader.aboutus.find("h4").css("font-size", "1.2em");
        div_loader.img_load.append("<img src=" + data.img + " alt='wechat QR code img'>");

        $("img").one("load", function() {
          // do stuff
          //div_loader.wrapper.find(".loader").remove();
          $("body").find(".loader").remove();
          
        }).each(function() {
          if(this.complete) $(this).load();
        });
      }
    });
    
  });
})(jQuery);
