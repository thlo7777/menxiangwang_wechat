(function($){
  $(document).ready(function(){

    $.ajaxSetup({ cache: false });
    var play = true;
    var yyhc_sub2_audio = "http://mxweixin.dreamland360.com/wechat-ajax/yyhc/2/audio";
    var play_audio = 'http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/play_icon1.png';
    var play_pause = 'http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/pause_icon1.png';
    var current_slide_index = 0;
    var audioA = new Array();
    var j = 1;
    
    //var audioObj = new Audio();
    //var audioObj = document.createElement('audio');


    //$.ajax({
    //  url: yyhc_sub2_audio,
    //  success: function (data) {
        //$.each(data, function(i, element){
          //if(i == ("audio" + current_slide_index)) {
            //audioObj.innerHTML = '<source src="' + data[i] + '" type="audio/mp3"></source>';
            //audioObj.load();
            //audioObj.setAttribute('src', data[i]);
            //audioObj.src = data[i]; 
            //addSource(audioelem, data[i]);
            //audioelem.appendTo("body");
            //$("#myaud")[0].play();
            //console.log(data[i]);
            /*
            audioelem.addEventListener('ended', function(){
              $("#anchor-audio p").replaceWith(play_audio);
              play = true;
            });
            //console.log(data[i]);
            return false;
            window.audioEmbed.attr("src", data[i]);
            audioElem.append(window.audioEmbed);
            audiodiv.append(window.audioElem);
            */
          //}
        //})
      //}
    //});

    var mySwiper = $('.swiper-container').swiper({
      //Your options here:
      pagination: '.pagination',
      mode:'horizontal',
      loop: true,
      //etc..
      onSlideChangeEnd: function(swiper){
        current_slide_index = swiper.activeLoopIndex; 
        //if(audioObj.currentSrc != "")
        //{
        $.each(audioA, function(i){
          audioA[i].currentTime = 0;
          audioA[i].pause();
        });
          //audioObj.currentTime = 0;
          //audioObj.pause();
        //}
/*
        if(audioObj.currentSrc != "")
        {
          audioObj.pause();
          audioObj.currentTime = 0;
        }
*/
        //$("audio").remove();
        //window.audioEmbed.remove();
        if(current_slide_index != 0) {
          play = true;
          //$("#anchor-audio").css({"visibility":"visible", "opacity":"1", "transition-delay":"0s"});
          //$("#anchor-audio").hide();
          //$("#anchor-audio").fadeIn("slow");
          $("#anchor-audio").css("background", 'url('+play_audio+') center no-repeat');
          $("#anchor-audio").css("visibility","visible");
        }else{
          $("#anchor-audio").css("visibility","hidden");
          //play = false;
          //$("#anchor-audio").fadeOut("slow");
        }
      }
    });


    /*
      <object>
      <param name="src" value="horse.mp3">
      <param name="autoplay" value="true">
      <embed src="horse.mp3" hidden="true" width = "0" height="0" controller="false" autoplay="true" autostart="True" type="audio/mp3" /> 
      </object>
    */


    if ($(window).width() > 320) {
      $(".swiper-slide img").css("width", "16.5em");
      $(".swiper-slide p").css("width", "15em");
    }

    $("#anchor-audio").css("width", $("#anchor").width());
    $("#anchor-audio").css("height", $("#anchor").height());
    //$("#anchor-audio").hide();
    //$("#anchor-audio").fadeOut("fast");
    /*
    $("#anchor").click(function(){
      alert("width: " + $(this).width() + "height" + $(this).height());
    });
    */

    //var audioObj = new Audio();
    //audioObj.innerHTML = '<source src="http://mxweixin.dreamland360.com/sites/default/files/maytj01.mp3" type="audio/mp3"></source>';
    $("#anchor-audio").click(function(){

      if(play == true) {

        //audioObj.src = "http://mxweixin.dreamland360.com/sites/default/files/maytj01.mp3"; 
        //audioObj.src = audio_url[current_slide_index];
        //audioObj.load();  /*need load*/
        //audioObj.play();
        audioA[current_slide_index - 1].play();
        $("#anchor-audio").css("background", 'url('+play_pause+') center no-repeat');
        play = false;
      }else{
        //$("audio").remove();
        //window.audioEmbed.remove();
        //$("#myaud")[0].pause();
        //audioObj.currentTime = 0;
        //audioObj.pause();
        audioA[current_slide_index - 1].pause();
        /*
        audioObj.src = "http://mxweixin.dreamland360.com/sites/default/files/maytj02.mp3"; 
        audioObj.load();
        audioObj.play();
        */
        $("#anchor-audio").css("background", 'url('+play_audio+') center no-repeat');
        play = true;
      }

    });

    $.ajax({
      url: yyhc_sub2_audio,
    })
      .done(function(data){
      $.each(data, function(i, element){
        var audioObj = new Audio(data[i]);

        audioObj.load();
        audioObj.addEventListener("ended", function() { 
          $("#anchor-audio").css("background", 'url('+play_audio+') center no-repeat');
        }, false);
        audioA.push(audioObj);
        //console.log(data[i]);
      })
    });

  });
})(jQuery);

/*
*/
