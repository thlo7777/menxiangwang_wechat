(function($){
  $(document).ready(function(){

    var ajax_url = "http://mxweixin.dreamland360.com/wechat-ajax/aboutus/data"; 
    var click_pyzxdh_flag = false;
    var pyzxdh_txt = "";

    $.ajax({  //get pyzxdh_txt
      url: ajax_url,
    }).done(function(data){
      //html = $.parseHTML("<p>" + data.pyzxdh_txt + "</p>");   //Have to conversion to html because of <br>
      pyzxdh_txt = data.pyzxdh_txt;
      //console.log(data);
    });
/*
    $("body").click(function(){
      alert("width: " + $(window).width() + "height: " + $(window).height());
    });
*/

    $(".item img").click(function(){

      if (click_pyzxdh_flag == false) {
        click_pyzxdh_flag = true;
        $(".item:nth-child(5)").append('<p class="pyzxdh"></p>');
        $(".pyzxdh").hide().html(pyzxdh_txt).fadeIn("slow");
        $('html, body').animate({scrollTop:$(document).height()}, 'slow');
      }else{
        $(".pyzxdh").fadeOut(400, function(){
          $(this).remove();
        });
        $('html, body').animate({ scrollTop: 0 }, 'slow');
        click_pyzxdh_flag = false;
      }

    });
  });
})(jQuery);
