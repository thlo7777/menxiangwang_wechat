(function($){
  $(document).ready(function(){

    var yyhc_main_url = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/data"; 
    var yyhc_sub1 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/1";
    var yyhc_sub2 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/2";
    var yyhc_sub3 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/3";
    var yyhc_sub4 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/4";
    var yyhc_sub5 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/5";
    var yyhc_sub6 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/6";
    var yyhc_sub7 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/7";
    var yyhc_sub8 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/8";
    var yyhc_sub9 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/9";
    var yyhc_sub10 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/10";
    var yyhc_sub11 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/11";
    var yyhc_sub12 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/12";
    var yyhc_sub13 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/13";
    var yyhc_sub14 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/14";
    var yyhc_sub15 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/15";
    var yyhc_sub16 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/16";
    var yyhc_sub17 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/17";
    var yyhc_sub18 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/18";
    var yyhc_sub19 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/19";
    var yyhc_sub20 = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/20";

    $.ajaxSetup({ cache: false });
    var div_loader = {
      loader: $("<div />", {class: "loader"}),
      wrapper: $(".wrapper"),
      yyhc: $(".head-title"),
      img_load: $(".head-img"),
    };

    $("body").append("<div class='loader'></div>");

    $.ajax({
      url: yyhc_main_url,
      success: function (data) {
        //$(".wrapper").html(data);
        div_loader.yyhc.append('<h4>' + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" + data.head_title + "</h4>");
        div_loader.yyhc.find("h4").css("text-align", "left");
        div_loader.yyhc.find("h4").css("letter-spacing", "0px");
        div_loader.yyhc.find("h4").css("font-size", "1.2em");
        div_loader.img_load.append("<img src=" + data.head_img + " alt='yyhc head'>");
        //$(".wrapper ul#yyhc-img-list").append("<li> <a href = " + ahref1 + "><img src=" + data.img1 + " alt='img1'/> </a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub1+"><img src=" + data.img1 + " alt='img1'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub2+"><img src=" + data.img2 + " alt='img2'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub3+"><img src=" + data.img3 + " alt='img3'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub4+"><img src=" + data.img4 + " alt='img4'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub5+"><img src=" + data.img5 + " alt='img5'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub6+"><img src=" + data.img6 + " alt='img6'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub7+"><img src=" + data.img7 + " alt='img7'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub8+"><img src=" + data.img8 + " alt='img8'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub9+"><img src=" + data.img9 + " alt='img9'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub10+"><img src=" + data.img10 + " alt='img10'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub11+"><img src=" + data.img11 + " alt='img11'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub12+"><img src=" + data.img12 + " alt='img12'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub13+"><img src=" + data.img13 + " alt='img13'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub14+"><img src=" + data.img14 + " alt='img14'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub15+"><img src=" + data.img15 + " alt='img15'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub16+"><img src=" + data.img16 + " alt='img16'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub17+"><img src=" + data.img17 + " alt='img17'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub18+"><img src=" + data.img18 + " alt='img18'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub19+"><img src=" + data.img19 + " alt='img19'/></a></li>");
        $(".wrapper ul#yyhc-img-list").append("<li> <a href = "+yyhc_sub20+"><img src=" + data.img20 + " alt='img20'/></a></li>");
        //console.log(data);
        
        $("body").find(".loader").remove();
      }
    });

  });
})(jQuery);
