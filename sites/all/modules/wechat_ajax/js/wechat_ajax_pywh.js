(function($){
  $(document).ready(function(){

    /*
    $(document).on('click','img',function() {
      alert("width: " + $(window).width() + "height: " + $(window).height());
    });
    $(".audio-head").click(function(){
      alert("width:" + $(window).width());
    });
    */

/*
    if ($(window).width() > 320) {
      $(".swiper-wrapper").css("margin-left", "10%");
    }
*/

    $('audio').audioPlayer();
    var mySwiper = new Swiper('.swiper-container',{
      pagination: '.pagination',
      mode: 'horizontal',
      loop: false
    });
    
  });
})(jQuery);
