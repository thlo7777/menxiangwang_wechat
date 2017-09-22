/* 
 * py mobile for wechat_py_mobile_new_tpl.inc
 */

(function($) {
  var input_radio_head = "input[name='field_product_sku_list[und][";
  var input_radio_tail_score = "][field_product_has_score][und]']";
  var input_radio_tail_post = "][field_product_post_free][und]']";

  var sku_list_head = "#edit-field-product-sku-list-und-";

  var sku_list_tail_sco_max = "-field-product-score-max";
  var sku_list_tail_sco_exc = "-field-product-score-exchange";
  var sku_list_tail_sta_dat = "-field-score-start-date";
  var sku_list_tail_end_dat = "-field-score-end-date";

  var class_field_sco_max   = ".field-name-field-product-score-max";
  var class_field_sco_exc   = ".field-name-field-product-score-exchange";
  var class_field_sta_dat   = ".field-name-field-score-start-date";
  var class_field_end_dat   = ".field-name-field-score-end-date";

  var sku_list_tail_exp_id  = "-field-express-template-id";
  var sku_list_tail_cha_con = "-field-product-charge-condition";
  var sku_list_tail_pos_tem = "-field-product-post-template";
  var sku_list_tail_pos_uni = "-field-product-post-unit";

  var class_field_exp_id  = ".field-name-field-express-template-id";
  var class_field_cha_con = ".field-name-field-product-charge-condition";
  var class_field_pos_tem = ".field-name-field-product-post-template";
  var class_field_pos_uni = ".field-name-field-product-post-unit";

  var score_post_array = [];

  function score_radio_click_exe(radio_name, value) {
    for (var i = 0; i < score_post_array.length; i++) {
      if (score_post_array[i].score.indexOf(radio_name) >= 0) {
        if (value == 0) {

          each_field_id(class_field_sco_max, score_post_array[i].score_max, "hide");
          each_field_id(class_field_sco_exc, score_post_array[i].score_exchange, "hide");
          each_field_id(class_field_sta_dat, score_post_array[i].score_start_data, "hide");
          each_field_id(class_field_end_dat, score_post_array[i].score_end_date, "hide");
        } else {
          each_field_id(class_field_sco_max, score_post_array[i].score_max, "show");
          each_field_id(class_field_sco_exc, score_post_array[i].score_exchange, "show");
          each_field_id(class_field_sta_dat, score_post_array[i].score_start_data, "show");
          each_field_id(class_field_end_dat, score_post_array[i].score_end_date, "show");
        }
        //alert(value);
      }
    };
  }

  function post_radio_click_exe(radio_name, value) {
    for (var i = 0; i < score_post_array.length; i++) {
      if (score_post_array[i].post.indexOf(radio_name) >= 0) {
        if (value == 0) {
          each_field_id(class_field_exp_id, score_post_array[i].post_express_id, "show");
          each_field_id(class_field_cha_con, score_post_array[i].post_charge, "hide");
          each_field_id(class_field_pos_tem, score_post_array[i].post_template, "hide");
          each_field_id(class_field_pos_uni, score_post_array[i].post_unit, "hide");
        } else if (value == 1) {
          each_field_id(class_field_exp_id, score_post_array[i].post_express_id, "hide");
          each_field_id(class_field_cha_con, score_post_array[i].post_charge, "hide");
          each_field_id(class_field_pos_tem, score_post_array[i].post_template, "hide");
          each_field_id(class_field_pos_uni, score_post_array[i].post_unit, "hide");
        } else {
          each_field_id(class_field_exp_id, score_post_array[i].post_express_id, "show");
          each_field_id(class_field_cha_con, score_post_array[i].post_charge, "show");
          each_field_id(class_field_pos_tem, score_post_array[i].post_template, "show");
          each_field_id(class_field_pos_uni, score_post_array[i].post_unit, "show");
        }
        //alert(value);
      }
    };
  }

  function each_field_id(class_name, id_name, action) {
    var id = $(class_name).attr('id');
    $(class_name).each(function(){
      var id = "#" + $(this).attr('id');
      if (id.indexOf(id_name) >= 0) {
        if (action == "hide") {
          $(id).hide();
        }
        if (action == "show") {
          $(id).show();
        }
        //console.log(id);
      }
    });
    /*
    $(".field-name-field-product-score-max").find("div").each(function(){
      console.log(this.id);
    });
    */
  }

  Drupal.behaviors.merchant_input_score_post = {
    attach: function(context, settings) {

    for (var i = 0; i < 10; i++) {
      var score_radio_checked = input_radio_head + i + input_radio_tail_score + ":checked"; 
      var score_radio_click = input_radio_head + i + input_radio_tail_score; 
      var post_radio_checked = input_radio_head + i + input_radio_tail_post + ":checked"; 
      var post_radio_click = input_radio_head + i + input_radio_tail_post; 

      if(($(score_radio_click).length > 0) && ($(post_radio_click).length > 0)) {
        var score_max         = sku_list_head + i + sku_list_tail_sco_max;
        var score_exchange    = sku_list_head + i + sku_list_tail_sco_exc;
        var score_start_data  = sku_list_head + i + sku_list_tail_sta_dat;
        var score_end_date    = sku_list_head + i + sku_list_tail_end_dat;
        var post_express_id   = sku_list_head + i + sku_list_tail_exp_id ;
        var post_charge       = sku_list_head + i + sku_list_tail_cha_con;
        var post_template     = sku_list_head + i + sku_list_tail_pos_tem;
        var post_unit         = sku_list_head + i + sku_list_tail_pos_uni;
        score_post_array[i] = {index: i,
                               score: score_radio_click,
                               post: post_radio_click,
                               score_max: score_max,
                               score_exchange: score_exchange,
                               score_start_data: score_start_data,  
                               score_end_date: score_end_date, 
                               post_express_id: post_express_id, 
                               post_charge: post_charge,
                               post_template: post_template,
                               post_unit: post_unit,
                               };
        //alert('yes' + score_radio_click);
      } else {
        break;
      }

    };

    //console.log(score_post_array);

    for (var i = 0; i < score_post_array.length; i++) {
      var score_radio_checked = score_post_array[i].score + ":checked"; 
      var checked = $(score_radio_checked).val();
      if(checked == 0) {
        each_field_id(class_field_sco_max, score_post_array[i].score_max, "hide");
        each_field_id(class_field_sco_exc, score_post_array[i].score_exchange, "hide");
        each_field_id(class_field_sta_dat, score_post_array[i].score_start_data, "hide");
        each_field_id(class_field_end_dat, score_post_array[i].score_end_date, "hide");
      }
      var post_free_checked = score_post_array[i].post + ":checked";
      checked = $(post_free_checked).val();
      if(checked == 0) {
        each_field_id(class_field_exp_id, score_post_array[i].post_express_id, "show");
        each_field_id(class_field_cha_con, score_post_array[i].post_charge, "hide");
        each_field_id(class_field_pos_tem, score_post_array[i].post_template, "hide");
        each_field_id(class_field_pos_uni, score_post_array[i].post_unit, "hide");
      } else if(checked == 1) {
        each_field_id(class_field_exp_id, score_post_array[i].post_express_id, "hide");
        each_field_id(class_field_cha_con, score_post_array[i].post_charge, "hide");
        each_field_id(class_field_pos_tem, score_post_array[i].post_template, "hide");
        each_field_id(class_field_pos_uni, score_post_array[i].post_unit, "hide");
      }
      
      var score_radio_click = score_post_array[i].score; 
      $(score_radio_click).unbind().click(function() {
        var radio_name = $(this).attr('name');
        var val = $(this).val();
        score_radio_click_exe(radio_name, val);
        return true;
      });

      var post_radio_click = score_post_array[i].post; 
      $(post_radio_click).unbind().click(function() {
        var radio_name = $(this).attr('name');
        var val = $(this).val();
        post_radio_click_exe(radio_name, val);
        return true;
      });
      //console.log(score_post_array[i].post);
    };

    } //attach: function
  };  //Drupal.behaviors.merchant_input_score_post

})(jQuery);

