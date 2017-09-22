//mobile_shopping_cart_page.js

(function($){



  var cart_animation = document.getElementById("cart-save");

  total_price_value = 0;
  listitem = null;

  var cart_recs = [{}];

  //Hence, to wait until the entire page is ready, you can use something like:
  $(document).ready(function() {

    //load db records.
    cart_load_records();
    //calculate total price when initial open page.
    cart_total_price();

    //delete list item 
    $(".delete-row").on( "click", function(e) {
      e.preventDefault();

      listitem = $(this).parent( "li" );
      confirmAndDelete();

    });


    //jump to payment page
    $("#btn-checkin").on("click", function(e) {
      e.preventDefault();
      if ($(this).hasClass('disable-anchor')) return;
      //window.location.href = "http://mxweixin.dreamland360.com/wechat-py-mobile/pay-test/payment/cart";
      window.location.href = payment_url;
    });

    $("#cart-save").on('click', function(e) {
      e.preventDefault();

      
      if (cart_animation.classList.contains("cart-save-animation") == true) {
        
        cart_animation.classList.remove("cart-save-animation");
        
        cart_compare_save();
      }

    });

    //check in on/off
    $('.checkin-icon').on('click', function(e) {
      e.preventDefault();

      //start animation
      cart_animation.classList.add("cart-save-animation");
      
      check = $(this).has('.checkmark');

      index = $(this).parent("a").attr("index");

      if (check.length == 1) {

        $(this).children(".checkmark").remove();
        checkmark = $("<span>").attr({"class": "uncheckmark"}).appendTo($(this));
        $("<div>").attr({"class": "uncheckmark_circle" }).appendTo(checkmark);

        cart_set_checkin_onoff(index, 0);
        cart_total_price();

      } else {

        //set checkmark
        $(this).children(".uncheckmark").remove();
        checkmark = $("<span>").attr({"class": "checkmark"}).appendTo($(this));
        $("<div>").attr({"class": "checkmark_circle" }).appendTo(checkmark);
        $("<div>").attr({"class": "checkmark_stem" }).appendTo(checkmark);
        $("<div>").attr({"class": "checkmark_kick" }).appendTo(checkmark);

        cart_set_checkin_onoff(index, 1);
        cart_total_price();

      }
    });

    //minus volume
    $('.volume-minus').on('click', function(e) {
      e.preventDefault();

      //start animation
      cart_animation.classList.add("cart-save-animation");

      volume = $(this).next('.volume-text').text();

      if (parseInt(volume) > 1) {
        val = parseInt(volume) - 1;
        $(this).next('.volume-text').text(parseInt(val));

        index = $(this).parent().parent().attr("index");
        cart_set_volume(index, parseInt(val));
        cart_total_price();
      }

    });

    //add volume
    $('.volume-plus').on('click', function(e) {
      e.preventDefault();

      //start animation
      cart_animation.classList.add("cart-save-animation");

      volume = $(this).prev('.volume-text').text();

      if (parseInt(volume) < 999) {
        val = parseInt(volume) + 1;
        $(this).prev('.volume-text').text(parseInt(val));
       
        index = $(this).parent().parent().attr("index");
        cart_set_volume(index, parseInt(val));
        cart_total_price();

      }

    });

    //checkin all
    $('#check-in-all').on('click', function(e) {
      e.preventDefault();

      //start animation
      cart_animation.classList.add("cart-save-animation");

      //set uncheckmark
      val = $(this).is(':checked');
      if (val == true) {

        //set checkmark
        $('.checkin-icon').children(".checkmark").remove();
        $('.checkin-icon').children(".uncheckmark").remove();
        checkmark_all = $("<span>").attr({"class": "checkmark"}).appendTo($('.checkin-icon'));
        $("<div>").attr({"class": "checkmark_circle" }).appendTo(checkmark_all);
        $("<div>").attr({"class": "checkmark_stem" }).appendTo(checkmark_all);
        $("<div>").attr({"class": "checkmark_kick" }).appendTo(checkmark_all);

        cart_set_checkin_onoff(-1, 1);

      } else {

        //set all uncheckmark
        $('.checkin-icon').children(".checkmark").remove();
        $('.checkin-icon').children(".uncheckmark").remove();
        checkmark_all = $("<span>").attr({"class": "uncheckmark"}).appendTo($('.checkin-icon'));
        $("<div>").attr({"class": "uncheckmark_circle" }).appendTo(checkmark_all);

        cart_set_checkin_onoff(-1, 0);
      }

      cart_total_price();

    });


  }); //document ready


  function confirmAndDelete() {

    // Show the confirmation popup
    $("#confirm").panel("open");

    $("#confirm #del-close").on("click", function() {

      val = $('#confirm #checkbox-mini-0').is(':checked');
      if (val == true) {

        //check off
        $('#confirm #checkbox-mini-0').prop('checked', false).checkboxradio('refresh');

        index = listitem.attr("index");
        cart_remove_by_key(index);

        //remove list li
        listitem.remove();
        $("#listview").listview("refresh");

        //start animation
        cart_animation.classList.add("cart-save-animation");

        //recalculate
        cart_total_price();
      }
      
    });

  }


  function cart_load_records() {
    if (cart_db_records == 0) {
      $( "#check-in-all" ).prop( "disabled", true );
      $( "#btn-checkin" ).addClass("disable-anchor");
      return;
    }

    $.each(cart_db_records, function(i, data) {
      cart_recs[i] = {
        key: data.index,
        checkin: data.checkin,  //0 uncheck, 1 checkin, 2 delete
        volume: data.volume,
        price: data.pshopping_price
      };
    });
  }

  function cart_remove_by_key(key) {
    $.each(cart_recs, function(i, data) {
      if (data.key == key) {
        data.checkin = 2; //remove
      }
    });
  }

  function cart_set_volume(key, vol) {
    $.each(cart_recs, function(i, data) {
      if (data.key == key) {
        data.volume = vol;
      }
    });
  }

  function cart_set_checkin_onoff(key, on) {
    if (key == -1) { //set all 

      $.each(cart_recs, function(i, data) {
        if (data.checkin != "2") {
          data.checkin = on;
        }
      });
 
    } else {

      $.each(cart_recs, function(i, data) {
        if (data.key == key) {
          data.checkin = on;
        }
      });
    }

  }

  function cart_total_price() {
    
    total = 0;

    $.each(cart_recs, function(i, data) {

      if (data.checkin == "1") {
        total = parseFloat(total) + parseFloat(data.volume) * parseFloat(data.price);
      }

    });
  
    total_price_value = total.toFixed(2);

    $('#total').text("合计: ¥" + total_price_value );
  }

  function cart_compare_save() {
    if (cart_recs.length != cart_db_records.length) {
      console.log('no change');
      //send data to server
      return;
    }

    flag = 0;
    $.each(cart_db_records, function(i, data) {
      if (cart_recs[i].checkin == "2") {
        flag = 1;
        return false;
      }
      if (data.index == cart_recs[i].key &&
          data.checkin == cart_recs[i].checkin &&
          parseInt(data.volume) == parseInt(cart_recs[i].volume) &&
          parseFloat(data.pshopping_price) == parseFloat(cart_recs[i].price)) {
      } else {
        flag = 1;
        return false; //break loop
      }
    });

    if (flag == 1) {
      card_data_ajax(cart_recs);
    } else {
      console.log('no changed');
    }

  }

  function card_data_ajax(data) {

    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });

    json_data = {
      ajax: "shopping_update_cart_obj",
      xyz: xyz,
      data: data,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:3000}).then(function(data){

      console.log('ok');
    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("cart update error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });
  }

})(jQuery);

