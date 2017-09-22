(function($){
  $(document).ready(function(){

    $.ajaxSetup({ cache: false });
    var play = true;
    var yyhc_sub1_audio = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/1/audio";
    var play_audio = 'http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/play_icon1.png';
    var play_pause = 'http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/pause_icon1.png';
    var current_slide_index = 0;
    var audioA = new Array();
    var j = 1;



    var mySwiper = $('.swiper-container').swiper({
      //Your options here:
      pagination: '.pagination',
      mode:'horizontal',
      loop: true,
      //etc..
      onSlideChangeEnd: function(swiper){
        current_slide_index = swiper.activeLoopIndex; 

        $.each(audioA, function(i){
          audioA[i].currentTime = 0;
          audioA[i].pause();
        });

        if(current_slide_index != 0) {
          play = true;
          $("#anchor-audio").css("background", 'url('+play_audio+') center no-repeat');
          $("#anchor-audio").css("visibility","visible");
        }else{
          $("#anchor-audio").css("visibility","hidden");
        }
      }
    });

    if ($(window).width() > 320) {
      $(".swiper-slide img").css("width", "16.5em");
      $(".swiper-slide p").css("width", "15em");
    }

    $("#anchor-audio").css("width", $("#anchor").width());
    $("#anchor-audio").css("height", $("#anchor").height());

    $("#anchor-audio").click(function(){

      if(play == true) {

        audioA[current_slide_index - 1].play();
        $("#anchor-audio").css("background", 'url('+play_pause+') center no-repeat');
        play = false;
      }else{
        audioA[current_slide_index - 1].pause();
        $("#anchor-audio").css("background", 'url('+play_audio+') center no-repeat');
        play = true;
      }

    });

    $.ajax({
      url: yyhc_sub1_audio,
    })
      .done(function(data){
      $.each(data, function(i, element){
        var audioObj = new Audio(data[i]);

        audioObj.load();
        audioObj.addEventListener("ended", function() { 
          $("#anchor-audio").css("background", 'url('+play_audio+') center no-repeat');
        }, false);
        audioA.push(audioObj);
      })
    });

  });
})(jQuery);

