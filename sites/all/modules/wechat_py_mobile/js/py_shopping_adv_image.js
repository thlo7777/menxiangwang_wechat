(function ($) {
  $(document).ready(function(){

    var swiper = new Swiper('.swiper-container', {
        pagination: '.swiper-pagination',
        paginationClickable: '.swiper-pagination',
        nextButton: '.swiper-button-next',
        prevButton: '.swiper-button-prev',
        spaceBetween: 30,
        autoplay: 1500, //ms
        autoplayDisableOnInteraction: true,
    });

/*********end for document ready*************/
  });
})(jQuery);
