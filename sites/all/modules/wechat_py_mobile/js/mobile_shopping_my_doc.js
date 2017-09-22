//mobile_shopping_my_doc.js

(function($){


  var handle_4_qr_scan_si = 0;

  var city_1 =[];
  var city_2 =[];
  var city_3 =[];
  var user_addr = [];
  var curr_addr = null;

  var save_addr = {
    user_name: '',
    user_tel: '',
    city_1: '',
    city_1_code: '',
    city_2: '',
    city_2_code: '',
    city_3: '',
    city_3_code: '',
    detail_address: '',
  };

  get_city_ajax(1, 0);
  get_user_addr_ajax();

  //Hence, to wait until the entire page is ready, you can use something like:
  $(document).ready(function() {

    $('#add-addr').on('click', function(e) {
      e.preventDefault();

      if ($('.edit-addr').length >= 5) {
        return ;
      }

      edit_add_address(null);
      //open panel to add address
    });

    $(document).on("change", "#select-city-1", select_city_1_change);
    $(document).on("change", "#select-city-2", select_city_2_change);
    $(document).on("change", "#select-city-3", select_city_3_change);
    $(document).on("click", ".edit-addr", edit_address);

    $("#addr-save").on('click', function() {
      validate_save_user_addr();
    });


    $('#remove-addr-save').on('click', function(e) {
      val = $('#delete-flip-checkbox').is(':checked');
      if (val == true) {
        addr_li = $("#addr-listview").find("[index='" + curr_addr.id + "']");
        if (addr_li.length > 0) {
          addr_li.remove();
          remove_addr_ajax(curr_addr);
        }
      }
    });

    //set timer to find qr scan image if ready
    handle_4_qr_scan_si = setInterval(get_self_qr_scan_image, 5000);

    $.mobile.loading('show', {
      text: "正在读取积分二维码...",
      textVisible: true,
      theme: "b",
      textonly: false,
      html: ""
    });

  }); //document ready

  //to get self qr scan image if ready
  function get_self_qr_scan_image() {
    qr_scan_file_url = $.trim($('#self-qr-scan-image').html());

    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });

    json_data = {
      ajax: "shopping_get_self_qr_scan_image_obj",
      file_url: qr_scan_file_url,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3}).then(function(data){

      if (data == 1) {
        $.mobile.loading('hide');
        clearInterval(handle_4_qr_scan_si);    //clear setInterval for get_self_qr_scan_image
        handle_4_qr_scan_si = 0;
        image = $('<img>').attr({"src": qr_scan_file_url, "style": "margin: 0 auto; display: block; margin-top: 1em; border: solid 1px;"}).insertAfter('#self-qr-scan-image');
      }


    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        clearInterval(handle_4_qr_scan_si);    //clear setInterval for get_self_qr_scan_image
        handle_4_qr_scan_si = 0;
        alert("save user address error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });
  }

  function remove_addr_ajax(curr_addr) {

    json_data = {
      ajax: "shopping_remove_address_obj",
      addr: curr_addr,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){


    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("remove address error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }


  function edit_address(e) {

    e.preventDefault();

    index = $(this).parent("li").attr("index");

    $.each(user_addr, function(i, addr) {
      if (index == addr.id) {
        curr_addr = addr;
        return false;
      }
    });

    //console.log(curr_addr);

    $("#remove-detail-address").empty();
    $("<p>姓名: " + curr_addr.user_name + "</p>").appendTo("#remove-detail-address");
    $("<p>电话: " + curr_addr.user_tel + "</p>").appendTo("#remove-detail-address");
    $("<p>"+curr_addr.city_1+"-"+curr_addr.city_2+"-"+curr_addr.city_3+"</p>").appendTo("#remove-detail-address");
    $("<p>" + curr_addr.detail_address + "</p>").appendTo("#remove-detail-address");

    //for delte checkbox remove and plus
    $("#delete-checkbox-a").empty();

    $("<label>").attr({"for": "delete-flip-checkbox"}).html("删除该地址").appendTo("#delete-checkbox-a");
    $("<input>").attr({
      "type": "checkbox",
      "data-role": "flipswitch",
      "name": "delete-flip-checkbox",
      "id": "delete-flip-checkbox",
      "data-on-text": "删除",
      "data-off-text": " ",
      "data-mini": "true",
    }).appendTo("#delete-checkbox-a");

    $("#delete-checkbox-a").trigger('create');
    //for delte checkbox remove and plus
    
    $("#remove-addr-panel").panel("open");

  }

  function validate_save_user_addr() {
    if ((save_addr.user_name = $("#text-name").val()) == '') {
      alert('请输入姓名');
      return ;
    }
    if ((save_addr.user_tel = $("#text-tel").val()) == '') {
      alert('请输入电话');
      return ;
    }

    if ($("#select-city-1").val() == -1) {
      alert('请选择省会或直辖市');
      return ;
    }
    if ($("#select-city-2").val() == -1) {
      alert('请选择城市');
      return ;
    }
    if ($("#select-city-3").val() == -1) {
      alert('请选择区县');
      return ;
    }

    if ((save_addr.detail_address = $("#text-detail").val()) == '') {
      alert('请输入详细地址和城市');
      return ;
    }

    send_user_addr_ajax(save_addr);
    $("#edit-addr-panel").panel("close");

//    if ((save_addr.user_name = $("#text-name").val()) == '') {
//      return ;
//    }
//    if ((save_addr.user_tel = $("#text-tel").val()) == '') {
//      return ;
//    }
//    if ((save_addr.detail_address = $("#text-detail").val()) == '') {
//      return ;
//    }
//
//    send_user_addr_ajax(save_addr);
  }

  function send_user_addr_ajax(save_addr) {

    json_data = {
      ajax: "shopping_save_addr_obj",
      xyz: xyz,
      save_addr: save_addr,
    };
    //console.log(save_addr);
    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){

      //remove all user addr list and refresh
      $("#addr-listview").empty();
      get_user_addr_ajax();
    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("save user address error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }


  function get_user_addr_ajax() {
    json_data = {
      ajax: "shopping_user_address_obj",
      xyz: xyz,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){

      if (typeof(data) === "undefined") {
        alert("get user address error: " + jqXHR.status + " " + jqXHR.statusText);
      } else {
        if (data === null || data.length == 0) {
          //show no record
          //console.log(data);
        } else {
          $.each(data, function(i, addr) {
            user_addr[i] = addr;
            show_user_addr_list(addr);
            $("#addr-listview").listview("refresh");
          });
          //console.log(user_addr);
          //show_user_addr_list
        }
      }

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("get user address error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });
  }

  function show_user_addr_list(addr) {
    addr_li = $("<li>").attr({"index": addr.id }).appendTo("#addr-listview");
    addr_a = $("<a>").attr({"href": "#" }).appendTo(addr_li);
    $("<p>").html(addr.user_name).appendTo(addr_a);
    $("<p>").html(addr.user_tel).appendTo(addr_a);
    $("<p>").html(addr.city_1 + addr.city_2 + addr.city_3 + addr.detail_address).appendTo(addr_a);
    $("<a>").attr({"href": "#", "class": "edit-addr"}).appendTo(addr_li);
  }

  function get_city_ajax(level, tid) {

    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });

    json_data = {
      ajax: "shopping_address_city_obj",
      xyz: xyz,
      level: level,
      term: tid,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){

      if (typeof(data) !== "undefined" && data !== null) {
        //console.log(data);
        if (data.term.length > 0 && data.xyz == xyz) {

          if (data.level == 1) {

            $.each(data.term, function(i, city) {
              city_1[i] = city;
              value = '<option value="' + city.tid + '">' + city.name + '</option>';
              $("#select-city-1").append(value);

            });


            $("#select-city-1").selectmenu( "refresh" );

          } else if (data.level == 2) {

            $.each(data.term, function(i, city) {
              city_2[i] = city;
              value = '<option value="' + city.tid + '">' + city.name + '</option>';
              $("#select-city-2").append(value);
            });

            $("#select-city-2").selectmenu( "refresh" );

          } else if (data.level == 3) {

            $.each(data.term, function(i, city) {
              city_3[i] = city;
              value = '<option value="' + city.tid + '">' + city.name + '</option>';
              $("#select-city-3").append(value);

            });

            $("#select-city-3").selectmenu( "refresh" );

          }
        }
      }

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("get address city_1 error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }

  //open panel to add/edit user address 
  function edit_add_address(li) {
    
    if (li === null) {
      // Show the confirmation popup
      $("#edit-addr-panel").panel("open");

    } 
  }

  //select_city_1_change onchange event
  function select_city_1_change(e) {
    e.preventDefault();
    if (this.value == -1) {
      return ;
    }

    text = $("#select-city-1 option:selected" ).text();
    save_addr.city_1 = text;
    save_addr.city_1_code = this.value;

    if (text == "北京市" ||
        text == "上海市" ||
        text == "天津市" ||
        text == "重庆市") {

      $("#select-city-2").find('option').remove();
      $("#select-city-2").append('<option value="-1">选择城市</option>');
      $("#select-city-2").append('<option value="' + this.value + '">' + text + '</option>');
      $("#select-city-2").selectmenu( "refresh" );
      $("#select-city-3").find('option').remove();
      $("#select-city-3").append('<option value="-1">选择区县</option>');
      $("#select-city-3").selectmenu( "refresh" );
      return ;
    }

    $("#select-city-2").find('option').remove();
    $("#select-city-2").append('<option value="-1">选择城市</option>');
    $("#select-city-2").selectmenu( "refresh" );
    $("#select-city-3").find('option').remove();
    $("#select-city-3").append('<option value="-1">选择区县</option>');
    $("#select-city-3").selectmenu( "refresh" );
    get_city_ajax(2, this.value);
    //show city to city
  }

  //select_city_2_change onchange event
  function select_city_2_change(e) {
    e.preventDefault();
    if (this.value == -1) {
      return ;
    }

    text = $("#select-city-2 option:selected" ).text();
    save_addr.city_2 = text;
    save_addr.city_2_code = this.value;
    $("#select-city-3").find('option').remove();
    $("#select-city-3").append('<option value="-1">选择区县</option>');
    $("#select-city-3").selectmenu( "refresh" );
    get_city_ajax(3, this.value);
  }

  //select_city_3_change onchange event
  function select_city_3_change(e) {
    e.preventDefault();
    if (this.value == -1) {
      return ;
    }

    text = $("#select-city-3 option:selected" ).text();
    save_addr.city_3 = text;
    save_addr.city_3_code = this.value;
  }

})(jQuery);

