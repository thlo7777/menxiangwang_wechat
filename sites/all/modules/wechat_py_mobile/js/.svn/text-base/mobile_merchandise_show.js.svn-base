//mobile_merchandise_show.js

(function($){

  $(document).ready(function() {

    //handle all wx api function
    $.set_wx_config();

    //add merchandise to cart
    $('#cart-button').on('click', function(e) {
      e.preventDefault();

      href = $(this).attr("href");
      if (href == "#") {
        //add merchandise to cart
        add_merchandise_to_cart_ajax();
      } else {
        //jump to cart page
        window.location.replace($(this).attr('href'));
      }

    });

    var desc = ($('#merchandise-name h3:first').html() === undefined ? '' :  $('#merchandise-name h3:first').html() ) + 
               ($('#merchandise-name h4').html() === undefined ? '' :  $('#merchandise-name h4').html()) + ' ' + 
               ($('#merchandise-price h3:first').html() === undefined ? '' :  $('#merchandise-price h3:first').html());
    var imageUrl = $('.swiper-container>.swiper-wrapper>.swiper-slide:first>img').attr('src');
    //console.log(window.location.href);
    var link = $(location).attr('href');
    $.share_current_page('【梦乡网】' + document.title, desc, link, imageUrl);

  }); //document ready

  $(window).load(function() {
    //send views
    send_views_ajax();

    //pay page
    $('#pay-button').on('click', function(e) {
      e.preventDefault();
      /*
      if (subscribe == 0) {
        e.preventDefault();
        // user unsubscribe
        alert('您没有关注服务号，请搜索我们的服务号并关注才能购买');
        return ;
      } else {
        //jump to payment page
        //track navigation history
        window.location.href = "http://mxweixin.dreamland360.com/wechat-py-mobile/pay-test/payment/nid/413";
        //can't track navigation history
        //window.location.replace("http://mxweixin.dreamland360.com/wechat-py-mobile/pay-test/payment/nid/413");
      }
      */
      //window.location.href = "http://mxweixin.dreamland360.com/wechat-py-mobile/pay-test/payment/nid/418";
      window.location.href = payment_url;
    });

    $('#add-comment').on('click', function(e) {
      e.preventDefault();
      add_merchandise_comment();
    });

    $('#addr-save').on('click', function(e) {
      e.preventDefault();

      comment_data = $('#textarea-comment').val();
      save_user_comment(comment_data);
    });

  }); //page load ready

  //add user comment to record
  function save_user_comment(comment) {

    json_data = {
      ajax: "shopping_save_user_comment",
      xyz: xyz,
      nid: nid,
      comment: comment,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:2, timeout:3000}).then(function(data){

      //should return nick name, head url, time 
      if (jQuery.isEmptyObject(data) || data === null) {
        alert('留言未能更新，请返回后再次进入');
      } else {
        //then insert new comment to list
        cm_li = $('<li>').attr({"class": "comment-left ui-li-static ui-body-inherit ui-li-has-thumb"});
        image = $('<img>').attr({"src": data.head_img_url,"class": "comment-head-image", "style": "top: 0.2em; max-height: 4em; max-width: 4em;"}).appendTo(cm_li);
        name_p = $('<p>').attr({"style": "left: 0; position: absolute; top: 5.5em; max-width: 5em;"}).html(data.nick_name).appendTo(cm_li);
        time_p = $('<p>').html(data.time).appendTo(cm_li);
        subject_p = $('<p>').attr({"style": "white-space: inherit;"}).html(comment).appendTo(cm_li);

        cm_li.prependTo("#comments-listview");

        console.log(data);
      }

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("save comment error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });
  }

  //check if user can leave message in a merchandise, user has to have a purchase record
  function add_merchandise_comment() {

    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });

    json_data = {
      ajax: "shopping_validate_comment_access",
      xyz: xyz,
      nid: nid,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:2, timeout:3000}).then(function(data){

      if (data.state == "1") {
        $( "#add-comment-panel" ).panel( "open" );
      } else if (data.state == "0") {
        alert('购买该商品后，才能留言。');
      } else {
        alert('购买该商品后，才能留言。');
      }

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("validation comment error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });
  }

  function add_merchandise_to_cart_ajax() {

    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });

    json_data = {
      ajax: "shopping_add_cart_obj",
      xyz: xyz,
      nid: nid,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:2, timeout:3000}).then(function(data){

      if (data.state == "0") {
        //modify cart-button icon to carat-r, and change text to 进入购物车
        $('#cart-button').buttonMarkup({ icon: "carat-r" });
        $('#cart-button').text("进入购物车");
        $('#cart-button').attr("href", cart_url);
      }

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("add cart from mer show page error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }

  function send_views_ajax() {
    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });

    json_data = {
      ajax: "shopping_merchandise_view_obj",
      nid: nid,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:3000}).then(function(data){
      //nothing to return
    });

    request.fail(function(jqXHR, textStatus, errorThrown) {
      //console.log(errorThrown);
      $.mobile.loading('hide');

      if (jqXHR.status != "200") {
        alert("send merchandise views error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });
  }

})(jQuery);


