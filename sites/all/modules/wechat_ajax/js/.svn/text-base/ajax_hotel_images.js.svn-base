(function ($) {
  $(document).ready(function(){

    var uid = getUrlVars("uid");
    var img = getUrlVars("img");


    var wechat_url = "http://mxweixin.dreamland360.com/wechat-ajax/xxzs/" + uid + "/" + img;

    $.ajax({
      method: "GET",
      cache: false,
      url: wechat_url 
    })
      .done(function(data){
        document.title = data.title;
        $(".hotel-item").append(data.itemtitle);;

        $.each(data, function(i, item){
          if(i === "number") return false;
          img = '<div class="swiper-slide"><img src="' + item + '"/></div>';
          $(".swiper-wrapper").append(img);
        });

      var swiper = new Swiper('.swiper-container', {
          pagination: '.swiper-pagination',
          paginationClickable: '.swiper-pagination',
          nextButton: '.swiper-button-next',
          prevButton: '.swiper-button-prev',
          spaceBetween: 30        
      });
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
