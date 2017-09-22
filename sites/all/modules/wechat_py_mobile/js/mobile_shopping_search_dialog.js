//mobile_shopping_search_dialog.js

(function($){

  var shopping_term_obj = {
    ajax: "shopping_term_obj",
    m_term: {},
    p_term: {},
    d_term: {},
  };

  var term_filter = {
    search: [],
    vocid: 0,
    termid: 0,
  };

  //Hence, to wait until the entire page is ready, you can use something like:
  $(window).load(function() {
  //$(document).ready(function(){

    //get all term id
    get_all_term_ajax();

    $('#select-search-1').val("1").attr('selected', true).selectmenu("refresh");
    $('#select-search-1').on('change', function(){
      //console.log(this.value);
      $('#select-search-1-button').css({
        "background-color": "#38c",
        "border-color": "#38c",
        "color": "#fff",
        "text-shadow": "0 1px 0 #059",
      });
      
      if (this.value == "1") {
        remove_all_select();
      }
      display_mterm_select(this.value);
      display_pterm_select(this.value);
      display_dterm_select(this.value);

      term_filter.search.length = 0; //clear all term from search array
      text = $(this).find("option:selected").text();
      term_filter.search.push(text);
      term_filter.vocid = this.value;   //only for first select menu to get which vocbulary
      term_filter.termid = this.value;
      //console.log(term_filter);

    });

    
    //take all term filter and send back to shopping home page
    $("#search-back-confirm").click(function(e) {
      e.preventDefault();
      //Can't work for JQM $(this).attr("href", this.href + "?search=m_term&search=fenlei商品&termid=1");
      if (term_filter.search.length == 0) {
        term_filter.search.push("全部商品");
        term_filter.vocid = "1";
        term_filter.termid = "1";
      }
      /*
      request_url = "?";
      $.each(term_filter.search, function(i, value) {
        request_url += "search[]=" + value + "&";
      });
      request_url += "vocid=" + term_filter.vocid + "&";
      request_url += "termid=" + term_filter.termid;
      */

      request_url = "&state=101" + "vocid" + term_filter.vocid + "termid" + term_filter.termid + "#wechat_redirect";
      //console.log(request_url);

      //clear search dialog page in browser histroy
      window.location.replace($(this).attr('href') + request_url);
      //console.log(window.location.href);
    });


  }); //document ready()

  function get_all_term_ajax() {

    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" }
    });

    json_data = {
      ajax: shopping_term_obj.ajax,
    };
    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:3000}).then(function(data){

      if (typeof data === "undefined" || data === null) {
        //for search error if no search result

        if ($('#uifc-search').length > 0) { 
          $("#uifc-search").remove();
        }
        
        pbody = $("<div>").attr({
          "class": "ui-body ui-body-a ui-corner-all",
          "id": "search-error",
          "style": "margin-top: 0.5em; background-color: #F1DD80; border-color: #333; text-shadow: 0 1px 0 #ffffff;"
        }).insertAfter("#search-container");

        perror = $("<p>").attr({
          "style": "text-align: center;"
        }).html("未找到分类，点击取消重新打开此页面").appendTo(pbody);
        return;

      }
      $.each(data, function(i, term){
        //console.log(term);
        switch(i) {
          case "m_term":
            $.extend(shopping_term_obj.m_term, term);
            break;
          case "p_term":
            $.extend(shopping_term_obj.p_term, term);
            break;
          case "d_term":
            $.extend(shopping_term_obj.d_term, term);
            break;
          default:
            // code
        }

      });

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {
      if (jqXHR.status != "200") {
        alert("term error: " + jqXHR.status + " " + jqXHR.statusText);
      }
    });

  } //get_all_term_ajax()

  function remove_all_select() {
    remove_all_mterm_select();
    remove_all_pterm_select();
    remove_all_dterm_select();
  }

  //*************** process merchandise term select menu and sub term menu
  //show or remove merchandise term select menu, add or remove onchange event
  function display_mterm_select(index) {

    if (index != '2') {
      if ($('#uifc-search-mterm').length > 0) { 
        $("#uifc-search-mterm").remove();
      }
      $(document).off("change", "#select-search-mterm" , mterm_select_change);
      remove_all_mterm_select();
      return ;
    }

    p_fc_name = $("<div>").attr({
      "class": "ui-field-contain",
      "id": "uifc-search-mterm",
    });

    p_select_label = $("<label>").attr({
      "for": "select-search-mterm",
      "class": "select",
      "style": "display: none;",
      }).appendTo(p_fc_name);

    p_select_name = $("<select>").attr({
      "name": "select-native-mterm",
      "id": "select-search-mterm",
      "data-native-menu": "true"
      }).appendTo(p_fc_name);

/*
    p_choose_option = $("<option>").attr({
      "value": "choose-one",
      "data-placeholder": "true"
      }).html("选择").appendTo(p_select_name);
*/

    p_all = $("<option>").attr({
      "value": "1",
      }).html("全部").appendTo(p_select_name);
    $('#select-search-mterm').val("1").attr('selected', true).selectmenu("refresh");

    $.each(shopping_term_obj.m_term, function(i, term){

      p_all = $("<option>").attr({
        "value": i,
        }).html(term.name).appendTo(p_select_name);
    });

    p_fc_name.appendTo("#search-container");
    $('select').selectmenu();

    //bind self change event
    //add change select menu and active color for dynamic created elemen by js
    $(document).on("change", "#select-search-mterm" , mterm_select_change);

  } //display_mterm_select()

  function mterm_select_change() {
    //console.log(this.value);
    $('#select-search-mterm-button').css({
      "background-color": "#38c",
      "border-color": "#38c",
      "color": "#fff",
      "text-shadow": "0 1px 0 #059",
    });

    //set term id
    if (term_filter.search.length > 1) {
      term_filter.search.length = 1;
    }
    term_filter.termid = this.value; //set termid
    text = $(this).find("option:selected").text();
    term_filter.search.push(text);
    //console.log(term_filter);

    //handle sub term select
    remove_all_mterm_select();

    index = this.value;
    if (index == "1") {
      return ;
    }
    term = shopping_term_obj.m_term;
    get_mterm_sub_term(term, index);

  }

  //remove all m_term sub select
  function remove_all_mterm_select() {
    term = shopping_term_obj.m_term;
    $.each(term, function(index) {
      //remove all sub term select menu and event if it has
      if ($("#uifc-search-mterm-" + index).length > 0) { 
        $("#uifc-search-mterm-" + index).remove();
      }
      $(document).off("change", "#select-search-mterm-" + index, mterm_sub_term_select_change);
    });
  }

  //show m_term subterm select menu
  function get_mterm_sub_term(term, index) {

    if (test = 'children' in term[index]) {

      // add index select menu
      p_fc_name = $("<div>").attr({
        "class": "ui-field-contain",
        "id": "uifc-search-mterm-" + index,
      });

      p_select_label = $("<label>").attr({
        "for": "select-search-mterm-" + index,
        "class": "select",
        "style": "display: none;",
      }).appendTo(p_fc_name);

      p_select_name = $("<select>").attr({
        "name": "select-search-mterm-" + index,
        "id": "select-search-mterm-" + index,
        "data-native-menu": "true"
        //"data-native-menu": "false"
      }).appendTo(p_fc_name);

/*
      p_choose_option = $("<option>").attr({
        "value": "choose-one",
        "data-placeholder": "true"
      }).html("选择").appendTo(p_select_name);
*/

      p_all = $("<option>").attr({
        "value": index, //if is all select parent term id
      }).html("全部").appendTo(p_select_name);
      $("select-search-mterm-" + index).val(index).attr('selected', true).selectmenu("refresh");
      
      subterm = term[index].children;
      $.each(subterm, function(i, term) {
        //console.log(term);
        p_all = $("<option>").attr({
          "value": i,
        }).html(term.name).appendTo(p_select_name);
      });

      p_fc_name.appendTo("#search-container");
      $('select').selectmenu();

    //bind self change event
    //add change select menu and active color for dynamic created elemen by js
      $(document).on("change", "#select-search-mterm-" + index, index, mterm_sub_term_select_change);
    }
  }

  //add subterm onchange event
  function mterm_sub_term_select_change(e) {

    $('#select-search-mterm-' + e.data + '-button').css({
      "background-color": "#38c",
      "border-color": "#38c",
      "color": "#fff",
      "text-shadow": "0 1px 0 #059",
    });

    //set term id
    if (term_filter.search.length > 2) {
      term_filter.search.length = 2;
    }
    term_filter.termid = this.value; //set termid
    text = $(this).find("option:selected").text();
    term_filter.search.push(text);
    console.log(term_filter);
  }


  //*************** process points term select menu and sub term menu
  //show or remove points term select menu, add or remove onchange event
  function display_pterm_select(index) {

    if (index != '3') {
      if ($('#uifc-search-pterm').length > 0) { 
        $("#uifc-search-pterm").remove();
      }
      $(document).off("change", "#select-search-pterm" , pterm_select_change);
      remove_all_pterm_select();
      return ;
    }

    p_fc_name = $("<div>").attr({
      "class": "ui-field-contain",
      "id": "uifc-search-pterm",
    });

    p_select_label = $("<label>").attr({
      "for": "select-search-pterm",
      "class": "select",
      "style": "display: none;",
      }).appendTo(p_fc_name);

    p_select_name = $("<select>").attr({
      "name": "select-native-pterm",
      "id": "select-search-pterm",
        "data-native-menu": "true"
        //"data-native-menu": "false"
      }).appendTo(p_fc_name);

/*
    p_choose_option = $("<option>").attr({
      "value": "choose-one",
      "data-placeholder": "true"
      }).html("选择").appendTo(p_select_name);
*/

    p_all = $("<option>").attr({
      "value": "1",
      }).html("全部").appendTo(p_select_name);
    $('#select-search-pterm').val("1").attr('selected', true).selectmenu("refresh");

    $.each(shopping_term_obj.p_term, function(i, term){

      p_all = $("<option>").attr({
        "value": i,
        }).html(term.name).appendTo(p_select_name);
    });

    p_fc_name.appendTo("#search-container");
    $('select').selectmenu();

    //add change select menu and active color for dynamic created elemen by js
    $(document).on("change", "#select-search-pterm" , pterm_select_change);
  } //display_pterm_select()

  function pterm_select_change() {
    //console.log(this.value);
    $('#select-search-pterm-button').css({
      "background-color": "#38c",
      "border-color": "#38c",
      "color": "#fff",
      "text-shadow": "0 1px 0 #059",
    });

    //set term id
    if (term_filter.search.length > 1) {
      term_filter.search.length = 1;
    }
    term_filter.termid = this.value; //set termid
    text = $(this).find("option:selected").text();
    term_filter.search.push(text);
    console.log(term_filter);

    //get children

    //handle sub term select
    remove_all_pterm_select();

    index = this.value;
    if (index == "1") {
      return ;
    }
    term = shopping_term_obj.p_term;
    get_pterm_sub_term(term, index);
  }

  //remove all p_term sub select
  function remove_all_pterm_select() {
    term = shopping_term_obj.p_term;
    $.each(term, function(index) {
      //remove all sub term select menu and event if it has
      if ($("#uifc-search-pterm-" + index).length > 0) { 
        $("#uifc-search-pterm-" + index).remove();
      }
      $(document).off("change", "#select-search-pterm-" + index, pterm_sub_term_select_change);
    });
  }
  //show p_term subterm select menu
  function get_pterm_sub_term(term, index) {

    if (test = 'children' in term[index]) {

      // add index select menu
      p_fc_name = $("<div>").attr({
        "class": "ui-field-contain",
        "id": "uifc-search-pterm-" + index,
      });

      p_select_label = $("<label>").attr({
        "for": "select-search-pterm-" + index,
        "class": "select",
        "style": "display: none;",
      }).appendTo(p_fc_name);

      p_select_name = $("<select>").attr({
        "name": "select-search-pterm-" + index,
        "id": "select-search-pterm-" + index,
        "data-native-menu": "true"
        //"data-native-menu": "false"
      }).appendTo(p_fc_name);

/*
      p_choose_option = $("<option>").attr({
        "value": "choose-one",
        "data-placeholder": "true"
      }).html("选择").appendTo(p_select_name);
*/

      p_all = $("<option>").attr({
        "value": index, //if is all select parent term id
      }).html("全部").appendTo(p_select_name);
      $("select-search-pterm-" + index).val(index).attr('selected', true).selectmenu("refresh");
      
      subterm = term[index].children;
      $.each(subterm, function(i, term) {
        //console.log(term);
        p_all = $("<option>").attr({
          "value": i,
        }).html(term.name).appendTo(p_select_name);
      });

      p_fc_name.appendTo("#search-container");
      $('select').selectmenu();

    //bind self change event
    //add change select menu and active color for dynamic created elemen by js
      $(document).on("change", "#select-search-pterm-" + index, index, pterm_sub_term_select_change);
    }
  }

  //add subterm onchange event
  function pterm_sub_term_select_change(e) {

    $('#select-search-pterm-' + e.data + '-button').css({
      "background-color": "#38c",
      "border-color": "#38c",
      "color": "#fff",
      "text-shadow": "0 1px 0 #059",
    });

    //set term id
    if (term_filter.search.length > 2) {
      term_filter.search.length = 2;
    }
    term_filter.termid = this.value; //set termid
    text = $(this).find("option:selected").text();
    term_filter.search.push(text);
    console.log(term_filter);
  }


  //*************** process discount term select menu and sub term menu
  //show or remove discount term select menu, add or remove onchange event
  function display_dterm_select(index) {

    if (index != '4') {
      if ($('#uifc-search-dterm').length > 0) { 
        $("#uifc-search-dterm").remove();
      }
      $(document).off("change", "#select-search-dterm" , dterm_select_change);
      remove_all_dterm_select();
      return ;
    }

    p_fc_name = $("<div>").attr({
      "class": "ui-field-contain",
      "id": "uifc-search-dterm",
    });

    p_select_label = $("<label>").attr({
      "for": "select-search-dterm",
      "class": "select",
      "style": "display: none;",
      }).appendTo(p_fc_name);

    p_select_name = $("<select>").attr({
      "name": "select-native-dterm",
      "id": "select-search-dterm",
        "data-native-menu": "true"
        //"data-native-menu": "false"
      }).appendTo(p_fc_name);

/*
    p_choose_option = $("<option>").attr({
      "value": "choose-one",
      "data-placeholder": "true"
      }).html("选择").appendTo(p_select_name);
*/

    p_all = $("<option>").attr({
      "value": "1",
      }).html("全部").appendTo(p_select_name);
    $('#select-search-dterm').val("1").attr('selected', true).selectmenu("refresh");

    $.each(shopping_term_obj.d_term, function(i, term){

      p_all = $("<option>").attr({
        "value": i,
        }).html(term.name).appendTo(p_select_name);
    });

    p_fc_name.appendTo("#search-container");
    $('select').selectmenu();

    //add change select menu and active color for dynamic created elemen by js
    $(document).on("change", "#select-search-dterm" , dterm_select_change);
  } //display_dterm_select()

  function dterm_select_change() {
    //console.log(this.value);
    $('#select-search-dterm-button').css({
      "background-color": "#38c",
      "border-color": "#38c",
      "color": "#fff",
      "text-shadow": "0 1px 0 #059",
    });

    if (term_filter.search.length > 1) {
      term_filter.search.length = 1;
    }
    term_filter.termid = this.value; //set termid
    text = $(this).find("option:selected").text();
    term_filter.search.push(text);
    console.log(term_filter);

    //get children

    //handle sub term select
    remove_all_dterm_select();
    index = this.value;
    if (index == "1") {
      return ;
    }

    term = shopping_term_obj.d_term;
    get_dterm_sub_term(term, index);
  }

  //remove all d_term sub select
  function remove_all_dterm_select() {
    term = shopping_term_obj.d_term;
    $.each(term, function(index) {
      //remove all sub term select menu and event if it has
      if ($("#uifc-search-dterm-" + index).length > 0) { 
        $("#uifc-search-dterm-" + index).remove();
      }
      $(document).off("change", "#select-search-dterm-" + index, dterm_sub_term_select_change);
    });
  }
  //show d_term subterm select menu
  function get_dterm_sub_term(term, index) {

    if (test = 'children' in term[index]) {

      // add index select menu
      p_fc_name = $("<div>").attr({
        "class": "ui-field-contain",
        "id": "uifc-search-dterm-" + index,
      });

      p_select_label = $("<label>").attr({
        "for": "select-search-dterm-" + index,
        "class": "select",
        "style": "display: none;",
      }).appendTo(p_fc_name);

      p_select_name = $("<select>").attr({
        "name": "select-search-dterm-" + index,
        "id": "select-search-dterm-" + index,
        "data-native-menu": "true"
        //"data-native-menu": "false"
      }).appendTo(p_fc_name);

/*
      p_choose_option = $("<option>").attr({
        "value": "choose-one",
        "data-placeholder": "true"
      }).html("选择").appendTo(p_select_name);
*/

      p_all = $("<option>").attr({
        "value": index, //if is all select parent term id
      }).html("全部").appendTo(p_select_name);
      $("select-search-dterm-" + index).val(index).attr('selected', true).selectmenu("refresh");
      
      subterm = term[index].children;
      $.each(subterm, function(i, term) {
        //console.log(term);
        p_all = $("<option>").attr({
          "value": i,
        }).html(term.name).appendTo(p_select_name);
      });

      p_fc_name.appendTo("#search-container");
      $('select').selectmenu();

    //bind self change event
    //add change select menu and active color for dynamic created elemen by js
      $(document).on("change", "#select-search-dterm-" + index, index, dterm_sub_term_select_change);
    }
  }

  //add subterm onchange event
  function dterm_sub_term_select_change(e) {

    $('#select-search-dterm-' + e.data + '-button').css({
      "background-color": "#38c",
      "border-color": "#38c",
      "color": "#fff",
      "text-shadow": "0 1px 0 #059",
    });

    //set term id
    if (term_filter.search.length > 2) {
      term_filter.search.length = 2;
    }
    term_filter.termid = this.value; //set termid
    text = $(this).find("option:selected").text();
    term_filter.search.push(text);
    console.log(term_filter);
  }

})(jQuery);


