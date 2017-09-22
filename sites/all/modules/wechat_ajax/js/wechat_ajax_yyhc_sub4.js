(function($){
  $(document).ready(function(){

    $.ajaxSetup({ cache: false });
    
    var mySwiper = new Swiper('.swiper-container',{
      pagination: '.pagination',
      mode: 'horizontal',
      loop: false
    });

/*
    $('body').click(function() {
      alert("width: " + $(window).width() + "height: " + $(window).height());
    });
*/

/*
    if ($(window).width() > 320) {
      $(".swiper-slide img").css("width", "16.5em");
      $(".swiper-slide p").css("width", "15em");
    }
*/

    $('audio').audioPlayer();

  });
})(jQuery);

