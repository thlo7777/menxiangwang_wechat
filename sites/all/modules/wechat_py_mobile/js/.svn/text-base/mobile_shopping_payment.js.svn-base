//mobile_shopping_payment.js
(function($){


  var check_addr_btn_click = true;  //for stop next button to click again when ajax has not finished.

  var curr_addr = null;
  var city_1 =[];
  var city_2 =[];
  var city_3 =[];

  var s_addr = null;  //payment checklist
  var user_rest_points = 0; //rest of points for this user

  var exp_list = null;

  //for save address
  var save_addr = {
    id: '',
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

  $(document).ready(function() {

    //handle all wx api function
    $.set_wx_config();
    wx.ready(function () {
      // 在这里调用 API
      //
      //check jsapi version
      // 1 判断当前版本是否支持指定 JS 接口，支持批量判断
      wx.checkJsApi({
        jsApiList: [
          'getNetworkType',
          'previewImage',
          'chooseWXPay'
        ],
        success: function (res) {
          
          var errmsg = res.errMsg;
          var regexp = /checkJsApi:ok/i;
          var found = errmsg.match(regexp);
          if(found === null) {
            alert("您的微信版本太低，请下载最新版本！");
            alert(JSON.stringify(res));
            return;
          }
        }
      });
    });//wx.ready

    //wx error handle
    wx.error(function (res) {
      alert(res.errMsg);
    });

    /**
     *  user address page
     */
    list_user_addr(user_addr);

    //select check icon check or uncheck for each user addr
    $(document).on("click", ".each-item", check_or_uncheck);

    //next to paymeny checklist user addr
    $('#check-addr').on('click', function(e) {
      checkid = $(".checkmark").attr('id');
      checkmark = document.getElementById(checkid);

      if (checkmark === null) {
        e.preventDefault();
        alert("请选择收货地址");
        return ;
      }

      if (exp_list === null) {
        e.preventDefault();
        
        alert("该用户地址无法计算运费，请重新选择收货地址");
        return ;
      }
    });

    //city select change event
    $(document).on("change", "#select-city-1", select_city_1_change);
    $(document).on("change", "#select-city-2", select_city_2_change);
    $(document).on("change", "#select-city-3", select_city_3_change);
    //remove user addr
    $(document).on("click", ".edit-addr", edit_address);

    //save user addr
    $("#addr-save").on('click', function(e) {
      e.preventDefault();
      validate_save_user_addr();
    });

    //remove addr and save to server
    $('#remove-addr-save').on('click', function(e) {
      val = $('#delete-flip-checkbox').is(':checked');
      if (val == true) {
        addr_li = $("#user-addr-listview").find("[index='" + curr_addr.id + "']");
        if (addr_li.length > 0) {
          addr_li.remove();
          remove_addr_ajax(curr_addr);

          index = -1;
          $.each(user_addr, function(i, addr) {
            if (addr.id == curr_addr.id) {
              return index = i;
            }
          });

          if (index != -1) {
            user_addr.splice(index, 1);
            //console.log(user_addr);
          }
        }
      }

    });

    //add user address and send ajax to server
    $('#add-addr').on('click', function(e) {
      e.preventDefault();

      if ($('.edit-addr').length >= 5) {
        alert('最多保存5个地址');
        return ;
      }

      edit_add_address(null);
      //open panel to add address
    });
    /*
     *  end user address page
     */

    /*
     * payement check list
     */
    //add volume
    $('.volume-price-plus').on('click', function(e) {
      e.preventDefault();

      volume = $(this).prev('.volume-text').text();

      if ((val = parseInt(volume)) < 999) {
        val = val + 1;
        $(this).prev('.volume-text').text(parseInt(val));

        //change score points
        index = $(this).attr('index');
        points_max = parseInt($('#points-max' + index).attr('value'));
        p_convert = $('#p-convert' + index).attr('value');
        sp = points_max * val;
        curr_points = parseInt($('#my-curr-points').attr('value'));

        if (sp > curr_points) {
          spp = sp * parseFloat(p_convert);
          $('#my-curr-points').attr('value', 0);
        } else {
          spp = sp * parseFloat(p_convert);
          //$('#my-curr-points').attr('value', curr_points - points_max);
          $('#my-curr-points').attr('value', curr_points - spp);
          $('#points-number' + index).attr('value', spp.toFixed(2));
          $('#points-number' + index).html('详情点击 积分抵扣: ¥ -' + spp.toFixed(2));
        }

        //calcuate area-total-price
        calculate_exp_fee();
        //calculate_area_total_price();
      }

    });

    $('.volume-price-minus').on('click', function(e) {
      e.preventDefault();

      volume = $(this).next('.volume-text').text();

      if ((val =parseInt(volume)) > 1) {
        val = val - 1;
        $(this).next('.volume-text').text(parseInt(val));

        //change score points
        index = $(this).attr('index');
        points_max = $('#points-max' + index).attr('value');
        p_convert = $('#p-convert' + index).attr('value');
        sp = parseInt(points_max) * val;
        curr_points = $('#my-curr-points').attr('value');
        curr_points = parseInt(curr_points);
        $('#my-curr-points').attr('value', curr_points + parseInt(points_max));
        spp = sp * parseFloat(p_convert);
        $('#points-number' + index).attr('value', spp.toFixed(2));
        $('#points-number' + index).html('详情点击 积分抵扣: ¥ -' + spp.toFixed(2));
        //calcuate area-total-price
        calculate_exp_fee();
        //calculate_area_total_price();
      }

    });

    /*
     * end payement check list
     */

  }); //document ready


  $(window).load(function() {


    /*
     * if use history, only change url parameter since browser can't change domain name for security reason.
     * Can't change history url from internal domain to outer domain url. 
     * replaceState and pushState will meet compile error.
    page = "http://mxweixin.dreamland360.com/wechat-py-mobile/my-doc";
    page = 'https://open.weixin.qq.com/connect/oauth2/authorize?appid=wx9ee4070dc39cdedb' +
               '&redirect_uri=http://mxweixin.dreamland360.com/wechat-py-mobile/my-doc' + 
               '&response_type=code' +
               '&scope=snsapi_base' +
               '&state=100' +
               '#wechat_redirect';
    console.log(history.state); 
    history.replaceState(page, '', page);

    window.addEventListener('popstate', function(event) {
      alert('hello');
    });
    */

    //send payment list to server
    $('#wxpay-send').on('click', function(e) {
      e.preventDefault();
	alert('正在迁移公众号，目前暂时不能支付，敬请谅解');
      //collect_all_detail($(this));
    });

    //score points panel
    $('.points-price').on('click', function(e) {
      index = $(this).attr("index");
      //set index to each score points
      $('#volume-minus-point').attr('index', index);
      $('#volume-plus-point').attr('index', index);

      points_max = $('#points-max' + index).attr('value');
      p_convert = $('#p-convert' + index).attr('value');

      curr_point_price = $('#points-number'+index).attr("value");

      curr_point = parseInt(curr_point_price)/parseInt(p_convert);
      //points max
      $('#score-points-panel-number').text(curr_point);
      //points exchange
      $('#score-points-panel-convert').html("每积分可兑换: " + p_convert + "元");

      /*
       * get my-curr-points after doc ready
       */
      user_rest_points = $('#my-curr-points').attr('value');
      $('#panel-rest-points').html('您还剩余 <span style="color: red;">' + user_rest_points + "</span> 个积分");

      $('#score-points-panel').panel("open");
    });

    $('#volume-minus-point').on('click', function(e) {
      e.preventDefault();

      point = $('#score-points-panel-number').text();
      if ((val =parseInt(point)) >= 1) {
        val = val - 1;
        user_rest_points++;
        $('#panel-rest-points').html('您还剩余 <span style="color: red;">' + user_rest_points + "</span> 个积分");
        $('#score-points-panel-number').text(parseInt(val));

      }
    });

    $('#volume-plus-point').on('click', function(e) {
      e.preventDefault();

      index = $(this).attr("index");
      points_max = $('#points-max' + index).attr('value');
      point = $('#score-points-panel-number').text();

      if ((val = parseInt(point)) < parseInt(points_max) && user_rest_points > 0) {
        val = val + 1;
        $('#score-points-panel-number').text(parseInt(val));

        user_rest_points--;
        $('#panel-rest-points').html('您还剩余 <span style="color: red;">' + user_rest_points + "</span> 个积分");
      }
    });

    $('#save-points-number').on('click', function(e) {

      index = $('#volume-minus-point').attr('index');
      point = $('#score-points-panel-number').text();
      p_convert = $('#p-convert' + index).attr('value');

      //save rest of points
      $('#my-curr-points').attr('value', user_rest_points);

      point_price = parseFloat(point)*parseFloat(p_convert);
      price = point_price.toFixed(2);
      $('#points-number'+index).attr("value", price);
      html = "详情点击  " + "积分抵扣: ¥ -" + price;
      $('#points-number'+index).html(html);
      //calcuate area-total-price
      calculate_area_total_price();
    });


  });   //window onload ready

  //collect all merchandise detail and send to server, prepare unifiedorder
  function collect_all_detail(send_self) {

    //item_array = new Array();
    item_array = [];

    item_sum = $('.area-total-price');
    if (item_sum.length > 0) {

      $.each(item_sum, function(i, item) {

        m_detail = {};
        index = $(item).attr("index");
        m_detail['index'] = index;
        m_detail['area_key'] = $(item).attr("area_key");
        m_title = $('#m-title' + index).html().trim();
        m_detail['m_title'] = m_title;
        m_purl = $('#m-purl' + index).prop('src');
        m_detail['m_purl'] = m_purl;
        s_price = $('#s-price' + index).attr('value');
        m_detail['s_price'] = s_price;
        volume = $('#volume-number' + index).text().trim();
        m_detail['volume'] = volume;
        exp_fee = $('#exp-fee' + index).attr("value");
        m_detail['exp_fee'] = exp_fee;
        point_p = $('#points-number'+index).attr("value");
        if (typeof point_p !== "undefined") {
          m_detail['point_p'] = point_p;
          point_c = $('#p-convert' + index).attr('value');
          point = parseInt(point_p)/parseInt(point_c);
          m_detail['point'] = point;
        } else {
          m_detail['point_p'] = 0;
          m_detail['point'] = 0;
        }
        item_total = $(item).attr("value");
        m_detail['item_total'] = item_total;

/*
        m_detail = {
          nid: index,
          m_title: m_title,
          s_price: s_price,
          volume: volume,
          exp_fee: exp_fee,
          point: point,
          point_p: point_p,
          //discount:,
          item_total: item_total,
        };
        */

        item_array.push(m_detail);
      });

      //console.log(item_array);
      all_pay = $('#all-payment').attr('value');

      //rest points
      rest_points = $('#my-curr-points').attr('value');

      //area total express fee
      exp_fee_array = [];
      area_exp_fee = $('.area_exp_fee_total');
      if (area_exp_fee.length > 0) {

        $.each(area_exp_fee, function(i, item) {
          exp_detail = {};
          area_key = $(item).attr("area_key");
          exp_detail[area_key] = $(item).attr("value");
          exp_fee_array.push(exp_detail);
        });

      }

      send_self.addClass('ui-disabled');
      $.mobile.loading('show', {
        text: "正在努力加载...",
        textVisible: true,
        theme: "b",
        textonly: false,
        html: ""
      });

      json_data = {
        ajax: "shopping_unfiedorder_data_obj",
        xyz: xyz,
        s_addr: s_addr,
        items: item_array,
        area_exp_fee: exp_fee_array,
        all_pay: all_pay,
        rest_points: rest_points,
      };

      var request = $.ajax({
        method: "POST",
        data: JSON.stringify(json_data),
      }).retry({times:3, timeout:5000 /* align with unified order time out*/}).then(function(data){

        $.mobile.loading('hide');
        //get prepay id and sign from server
        if (jQuery.isEmptyObject(data) || data === null) {
          alert("订单无法支付, 请检查网络");
          //alert("用户地址无法计算运费，请返回联系客服");
          send_self.removeClass('ui-disabled');
          return false;
        }


        //success pay
        if (data.hasOwnProperty('package')) {

          //call wx pay
          wx.chooseWXPay({
            timestamp: data.timeStamp,
            nonceStr: data.nonceStr,
            package: data.package,
            signType: data.signType, // 注意：新版支付接口使用 MD5 加密
            paySign: data.paySign,
            success: function (res) {
            // 支付成功后的回调函数
              send_self.removeClass('ui-disabled');
              var errmsg = res.errMsg;
              var regexp = /chooseWXPay:ok/i;
              var found = errmsg.match(regexp);
              if(found === null) {
                alert("支付系统返回错误");
                alert(JSON.stringify(res));
              }
            }
            
          });

        }

        //return error
        if (data.hasOwnProperty('return_code')) {
          alert("支付系统返回错误: " + data.return_code + " " + data.return_msg);
        }

        if (data.hasOwnProperty('err_code')) {
          alert("支付系统返回错误: " + data.err_code + " " + data.err_code_des);
        }
        //console.log(data);
        send_self.removeClass('ui-disabled');

      });

      request.fail(function(jqXHR, textStatus, errorThrown) {

        send_self.removeClass('ui-disabled');
        if (jqXHR.status != "200") {
          alert("get jsApiParameters error: " + jqXHR.status + " " + jqXHR.statusText);
          alert("网络错误，订单无法支付, 请检查网络");
        }

      });
    }
  }
  
  function calculate_area_total_price() {
    area_total_price = $('.area-total-price');
    all_payment = 0;
    area_key = 0;

    $.each(area_total_price, function(i, item) {
      index = $(item).attr("index");
      
      area_key = $(item).attr("area_key");
      //merchandise price * volume
      s_price = $('#s-price' + index).attr('value');
      s_volume = $('#volume-number' + index).text();
      //post express fee
      exp_fee = $('#exp-fee' + index).attr("value");

      //points price
      points = $('#points-number' + index);
      if (points.length > 0) {
        points_price = points.attr('value');
      } else {
        points_price = 0;
      }

      //total_price = parseFloat(s_price) * parseInt(s_volume) + parseFloat(exp_fee) - parseFloat(points_price);
      total_price = parseFloat(s_price) * parseInt(s_volume) - parseFloat(points_price);
      all_payment += total_price;
      //discount price
      $(item).html("¥" + total_price.toFixed(2));
      $(item).attr("value", total_price.toFixed(2));
    });

    //calculate express fee
    area_key_exp_fee = $('.area_exp_fee_total');
    $.each(area_key_exp_fee, function(i, item) {

      area_key_fee_price = $(item).attr("value");
      all_payment += parseFloat(area_key_fee_price);
    });

    $('#all-payment').attr('value', all_payment.toFixed(2));
    $('#all-payment').html("共需支付: ¥" + all_payment.toFixed(2));
  }

  /*
   * payment checklist
   */
  function set_post_address() {


    checkid = $(".checkmark");
    //selected addr for jump to next
    index = checkid.parent("a").attr("index");
    $.each(user_addr, function(i, addr) {
      if (index == addr.id) {
        s_addr = jQuery.extend(true, {}, addr);
        return false;
      }
    });

    if (s_addr !== null) {
      $('#post-address > a.name-addr').remove();
      $('#post-address > a.detail-addr').remove();
      $('<a>').attr({"href": "#", "class": "name-addr"}).html('收货人: ' + s_addr.user_name + " " + s_addr.user_tel).appendTo('#post-address');
      $('<a>').attr({"href": "#", "class": "detail-addr"}).html('收货地址: ' + s_addr.city_1 + 
                                   s_addr.city_2 + 
                                   s_addr.city_3 + 
                                   s_addr.detail_address).appendTo('#post-address');
    }

    //get express template from sever
    get_express_template_ajax(s_addr);

  }

  function get_express_template_ajax(s_addr) {
    all_exp_item = $('.express-fee');

    head = {
      city_1_code: s_addr.city_1_code,
      city_2_code: s_addr.city_2_code,
      city_3_code: s_addr.city_3_code,
    };
    exp_list_data = {};

    $.each(all_exp_item, function(i, exp_item) {
      if ((pexpid = $(exp_item).attr('pexpid'))) {
        obj = {};
        index = $(exp_item).attr("index");
        obj[index] = pexpid;
        exp_list_data = $.extend(head, obj);
      }
    });

    //if all of merchandises are free for express fee, then return
    if (jQuery.isEmptyObject(exp_list_data)) {

      //calcuate area-total-price
      calculate_area_total_price();
      //set exp_list is free
      exp_list = 0;
      return ;
    }

    json_data = {
      ajax: "shopping_get_express_obj",
      term: exp_list_data,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){

      //get data should is [nid](initfw, initfw_p, stepfw, stepfw_p, wsfw1, stepwsfw1_p, wsfw2, stepwsfw2_p ....)
      if (jQuery.isEmptyObject(data) || data === null) {
        alert("该用户地址无法得到运费，请重新选择收货地址");
        //alert("用户地址无法计算运费，请返回联系客服");
        return false;
      }

      //calculate exp fee
      exp_list = data;
      calculate_exp_fee();

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("get express tamplate error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });
  }

  function calculate_exp_fee() {
    if (exp_list !== null || exp_list !== 0) {

      area_nodes = {};
      $.each(exp_list, function(i, node_exp) {

        temp = $('#exp-fee' + i).attr('area_key');
        if (typeof area_nodes[temp] === "undefined") {
          //area_nodes[temp] = {node_exp.tid);  //{"tid": node_exp.tid, "nodes": [i]};
          tid_arr = new Object();
          tid_arr[node_exp.tid] = [i];
          area_nodes[temp] = tid_arr; 
          //area_nodes[temp][node_exp.tid] = [i];
        } else {

          if (typeof area_nodes[temp][node_exp.tid] === "undefined") {
            tid_arr = new Object();
            tid_arr[node_exp.tid] = [i];
            area_nodes[temp] = $.extend({}, area_nodes[temp], tid_arr); 
            //area_nodes[temp] = $.extend({}, area_nodes[temp], {node_exp.tid: node_exp.tid, "nodes": [i]});
          } else {
            area_nodes[temp][node_exp.tid].push(i);
          }
        }

      });
      //console.log(area_nodes);

      /*
       * cacluate area express fee
       */
      $.each(area_nodes, function(index, area_ns) {
        //console.log(area_ns);
        area_area_total = 0;

        $.each(area_ns, function(i, data) {

          var m_nodes = 0;
          $.each(data, function(i, nid) {
            s_weight = $('#s-price' + nid).attr('weight');
            s_volume = $('#volume-number' + nid).text();
            m_nodes = m_nodes + parseInt(s_weight) * parseInt(s_volume);
          });
          area_nodes_total = calculate_same_tid_exp(m_nodes, i);
          area_area_total += parseFloat(area_nodes_total);

//          console.log('start');
//          console.log(i);
//          console.log(m_nodes);
//          console.log(area_nodes_total);
//          console.log('end');
        });

        //console.log(area_area_total.toFixed(2));

        $('#area-exp-fee' + index).attr('value', area_area_total.toFixed(2));
        $('#area-exp-fee' + index).html("运费: ¥" + area_area_total.toFixed(2));
      });

      /*
       *
       */
      //console.log(exp_list);
      $.each(exp_list, function(i, node_exp) {

        if (node_exp === null) {
          alert("商品运费计算错误，请返回联系客服");
          return false;
        }

        s_weight = $('#s-price' + i).attr('weight');
        s_volume = $('#volume-number' + i).text();
        //express fomula
        exp_fee = calculate_detail_exp(s_weight, s_volume, node_exp);
        $('#exp-fee' + i).attr('value', exp_fee);
        //$('#exp-fee' + i).html('¥' + exp_fee);

      });

      //calcuate area-total-price
      calculate_area_total_price();
    } else {
      alert("运费计算错误，请返回联系客服");
      return false;
    }
  }

  function calculate_same_tid_exp(weight, tid) {
    area_nodes_total = 0;
    $.each(exp_list, function(i, node_exp) {
      if (node_exp.tid == tid) {
        area_nodes_total = calculate_tid_weight_exp(weight, node_exp);
        return false;
      }
    });
    return area_nodes_total;
  }

  function calculate_tid_weight_exp(weight, node_exp) {
    init_weight = parseInt(node_exp.init_weight) * 1000; //server store kg, merchandise use g
    init_weight_price = parseFloat(node_exp.init_weight_price).toFixed(2);
    step_weight = parseFloat(node_exp.step_weight) * 1000;
    step_weight_price = parseFloat(node_exp.step_weight_price).toFixed(2);

    if (parseInt(weight) <= init_weight) {   //小于1KG

      return init_weight_price; 
    }

    if (jQuery.isEmptyObject(node_exp.over_wc) 
        || jQuery.type(node_exp.over_wc) === "undefined"
        || jQuery.type(node_exp.over_wc) === "null") {

      if (parseFloat(weight) > init_weight) {   //大于1KG
        step_number = (parseInt(weight) - init_weight) / step_weight;

        if ((step_number - parseInt(step_number)) == 0) {

          if (parseInt(step_number) == 0) {
            step_number++;
          }
          exp_fee = parseFloat(init_weight_price) + parseInt(step_number) * parseFloat(step_weight_price);
        } else {
          step_number++;
          exp_fee = parseFloat(init_weight_price) + parseInt(step_number) * parseFloat(step_weight_price);
        }

        return exp_fee.toFixed(2);
      }

    } else {
      
      //console.log(node_exp.over_wc);
      over_wc_array = new Array();
      $.each(node_exp.over_wc, function(i, over_wc) {
        over_wc_array.push(over_wc);
      });

      exp_fee = 0;

      $.each(over_wc_array, function(i, over_wc) {

        owc = parseFloat(over_wc.owc) * 1000;
        owc_price = parseFloat(over_wc.owc_price).toFixed(2);

        if (i == 0) { //first over weight condition

          if (parseFloat(weight) > init_weight
              && parseFloat(weight) <= owc) {   //大于1KG 小于指定公斤数
            step_number = (parseInt(weight) - init_weight) / step_weight;


            if ((step_number - parseInt(step_number)) == 0) {

              if (parseInt(step_number) == 0) {
                step_number++;
              }
              exp_fee = parseFloat(init_weight_price) + parseInt(step_number) * parseFloat(step_weight_price);
            } else {
              step_number++;
              exp_fee = parseFloat(init_weight_price) + parseInt(step_number) * parseFloat(step_weight_price);
            }

            return exp_fee.toFixed(2);
          }

        } else {

          cycle = i;
          while (cycle > 0) {
            cycle --;
            prev_owc = parseFloat(over_wc_array[cycle].owc) * 1000;
            prev_owc_price = parseFloat(over_wc_array[cycle].owc_price).toFixed(2);

            if (parseFloat(weight) > prev_owc
                && parseFloat(weight) <= owc) {   //大于1KG 小于指定公斤数
              step_number = (parseInt(weight) - prev_owc) / step_weight;


              if ((step_number - parseInt(step_number)) == 0) {

                if (parseInt(step_number) == 0) {
                  step_number++;
                }
                exp_fee += parseInt(step_number) * parseFloat(owc_price/2);
                if (cycle == 0) {
                  exp_fee += parseFloat(init_weight_price)
                             + parseFloat((prev_owc - init_weight)/1000 * step_weight_price / (step_weight/1000));
                  return false;
                }
              } else {
                step_number++;
                exp_fee += parseInt(step_number) * parseFloat(owc_price/2);
                if (cycle == 0) {
                  exp_fee += parseFloat(init_weight_price)
                             + parseFloat((prev_owc - init_weight)/1000 * step_weight_price / (step_weight/1000));
                  return false;

                }
              }

            }

          } //while cycle > 0
          

        }


      });

      toal = exp_fee;
      return toal.toFixed(2);
    
    }


  }

  function calculate_detail_exp(weight, volume, node_exp) {
    init_weight = parseInt(node_exp.init_weight) * 1000; //server store kg, merchandise use g
    init_weight_price = parseFloat(node_exp.init_weight_price).toFixed(2);
    step_weight = parseFloat(node_exp.step_weight) * 1000;
    step_weight_price = parseFloat(node_exp.step_weight_price).toFixed(2);

    if (parseInt(weight) * parseInt(volume) <= init_weight) {   //小于1KG

      return init_weight_price; 
    }

    if (jQuery.isEmptyObject(node_exp.over_wc) 
        || jQuery.type(node_exp.over_wc) === "undefined"
        || jQuery.type(node_exp.over_wc) === "null") {

      if (parseFloat(weight) * parseInt(volume) > init_weight) {   //大于1KG
        step_number = (parseInt(weight) * parseInt(volume) - init_weight) / step_weight;

        if ((step_number - parseInt(step_number)) == 0) {

          if (parseInt(step_number) == 0) {
            step_number++;
          }
          exp_fee = parseFloat(init_weight_price) + parseInt(step_number) * parseFloat(step_weight_price);
        } else {
          step_number++;
          exp_fee = parseFloat(init_weight_price) + parseInt(step_number) * parseFloat(step_weight_price);
        }

        return exp_fee.toFixed(2);
      }

    } else {
      
      //console.log(node_exp.over_wc);
      over_wc_array = new Array();
      $.each(node_exp.over_wc, function(i, over_wc) {
        over_wc_array.push(over_wc);
      });

      exp_fee = 0;

      $.each(over_wc_array, function(i, over_wc) {

        owc = parseFloat(over_wc.owc) * 1000;
        owc_price = parseFloat(over_wc.owc_price).toFixed(2);

        if (i == 0) { //first over weight condition

          if (parseFloat(weight) * parseInt(volume) > init_weight
              && parseFloat(weight) * parseInt(volume) <= owc) {   //大于1KG 小于指定公斤数
            step_number = (parseInt(weight) * parseInt(volume) - init_weight) / step_weight;


            if ((step_number - parseInt(step_number)) == 0) {

              if (parseInt(step_number) == 0) {
                step_number++;
              }
              exp_fee = parseFloat(init_weight_price) + parseInt(step_number) * parseFloat(step_weight_price);
            } else {
              step_number++;
              exp_fee = parseFloat(init_weight_price) + parseInt(step_number) * parseFloat(step_weight_price);
            }

            return exp_fee.toFixed(2);
          }

        } else {

          cycle = i;
          while (cycle > 0) {
            cycle --;
            prev_owc = parseFloat(over_wc_array[cycle].owc) * 1000;
            prev_owc_price = parseFloat(over_wc_array[cycle].owc_price).toFixed(2);

            if (parseFloat(weight) * parseInt(volume) > prev_owc
                && parseFloat(weight) * parseInt(volume) <= owc) {   //大于1KG 小于指定公斤数
              step_number = (parseInt(weight) * parseInt(volume) - prev_owc) / step_weight;


              if ((step_number - parseInt(step_number)) == 0) {

                if (parseInt(step_number) == 0) {
                  step_number++;
                }
                exp_fee += parseInt(step_number) * parseFloat(owc_price/2);
                if (cycle == 0) {
                  exp_fee += parseFloat(init_weight_price)
                             + parseFloat((prev_owc - init_weight)/1000 * step_weight_price / (step_weight/1000));
                  return false;
                }
              } else {
                step_number++;
                exp_fee += parseInt(step_number) * parseFloat(owc_price/2);
                if (cycle == 0) {
                  exp_fee += parseFloat(init_weight_price)
                             + parseFloat((prev_owc - init_weight)/1000 * step_weight_price / (step_weight/1000));
                  return false;

                }
              }

            }

          } //while cycle > 0
          

        }


      });

      toal = exp_fee;
      exp_fee = 0;  //clear exp_fee for next calculate
      return toal.toFixed(2);
    
    }


  }

  /*
   * user address page
   */
  //check or uncheck when select
  function check_or_uncheck(e) {
    e.preventDefault();

    check_icon = $(this).children("div");
    if (check_icon.hasClass('uncheckmark')) {

      checkid = $(".checkmark").attr('id');
      checkmark = document.getElementById(checkid);

      if (checkmark !== null) {
        checkmark.classList.remove("checkmark");
        checkmark.classList.add("uncheckmark");
      }

      uncheckmark = document.getElementById(check_icon.attr('id'));
      uncheckmark.classList.remove("uncheckmark");
      uncheckmark.classList.add("checkmark");

      set_post_address();
    }
  }

  //remove user addr
  function remove_addr_ajax(curr_addr) {

    json_data = {
      ajax: "shopping_remove_address_obj",
      addr: curr_addr,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){

      //nothing to do

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("remove address error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }
  //init get city level 1 
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

  function list_user_addr(user_addr) {

    if (user_addr.length != 0) {
      //console.log(user_addr);
      $.each(user_addr, function(i, addr) {
        //console.log(addr);
        addr_li = $('<li>').attr({"index": addr.id});
        addr_a = $('<a>').attr({"index": addr.id, "href": "#", "class": "each-item", "style": "padding: 0.7em 0.5em;"}).appendTo(addr_li);
        if (i == 0) {
          addr_check = $('<div>').attr({"id": "check" + addr.id, "class": "checkmark"}).appendTo(addr_a);
        } else {
          addr_check = $('<div>').attr({"id": "check" + addr.id, "class": "uncheckmark"}).appendTo(addr_a);
        }
        addr_p = $('<p>').html("姓名: " + addr.user_name).appendTo(addr_a);
        addr_p = $('<p>').html("电话: " + addr.user_tel).appendTo(addr_a);
        addr_p = $('<p>').html("地址: " + addr.city_1 + "-" + addr.city_2 + "-" + addr.city_3).appendTo(addr_a);
        addr_p = $('<p>').html(addr.detail_address).appendTo(addr_a);
        addr_panel = $('<a>').attr({"href": "#", "class": "edit-addr"}).appendTo(addr_li);

        addr_li.appendTo("#user-addr-listview");
        $("#user-addr-listview").listview("refresh");

      });

      //initial should use i == 0 user address to get exp template and calculate exp fee
      set_post_address();
    }
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
    $("<p>姓名: " + curr_addr.user_name + "</p>").css({padding: "0 0.5em"}).appendTo("#remove-detail-address");
    $("<p>电话: " + curr_addr.user_tel + "</p>").css({padding: "0 0.5em"}).appendTo("#remove-detail-address");
    $("<p>"+curr_addr.city_1+"-"+curr_addr.city_2+"-"+curr_addr.city_3+"</p>").css({padding: "0 0.5em"}).appendTo("#remove-detail-address");
    $("<p>" + curr_addr.detail_address + "</p>").css({padding: "0 0.5em"}).appendTo("#remove-detail-address");

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

  //save user address from panel save button
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
  }

  //save user addr to server
  function send_user_addr_ajax(save_addr) {

    json_data = {
      ajax: "shopping_save_addr_obj",
      xyz: xyz,
      save_addr: save_addr,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){

      save_addr.id = data.index;
      //deep clone save addr object
      test1 = jQuery.extend(true, {}, save_addr);
      user_addr.push(test1);

      //console.log(user_addr);
      //console.log(save_addr);
      append_new_user_addr_to_listview(save_addr);
    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("save user address error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }

  //insert saved user addr to listview
  function append_new_user_addr_to_listview(save_addr) {
    addr_li = $('<li>').attr({"index": save_addr.id});
    addr_a = $('<a>').attr({"index": save_addr.id, "href": "#", "class": "each-item", "style": "padding: 0.7em 0.5em;"}).appendTo(addr_li);
    addr_check = $('<div>').attr({"id": "check" + save_addr.id, "class": "uncheckmark"}).appendTo(addr_a);
    addr_p = $('<p>').html("姓名: " + save_addr.user_name).appendTo(addr_a);
    addr_p = $('<p>').html("电话: " + save_addr.user_tel).appendTo(addr_a);
    addr_p = $('<p>').html("地址: " + save_addr.city_1 + "-" + save_addr.city_2 + "-" + save_addr.city_3).appendTo(addr_a);
    addr_p = $('<p>').html(save_addr.detail_address).appendTo(addr_a);
    addr_panel = $('<a>').attr({"href": "#", "class": "edit-addr"}).appendTo(addr_li);

    addr_li.appendTo("#user-addr-listview");
    $("#user-addr-listview").listview("refresh");
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
  /*
   *  end user address page
   */

})(jQuery);
