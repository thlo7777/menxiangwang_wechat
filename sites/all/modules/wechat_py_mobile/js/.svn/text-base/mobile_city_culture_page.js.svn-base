//mobile_city_culture_page.js
(function($){

  curr_unix_time = parseInt(new Date().getTime()/1000 + 100000);  //for search last info time
  var search_result = {
    ct: '',
    area: 0,
    type: '',
    para: '',
    time: curr_unix_time,

    last_row: 0,

  }

  //Hence, to wait until the entire page is ready, you can use something like:
  $(window).load(function() {

    //detect page scroll down
    //can't work use $(window).scroll()
    $(document).on("scrollstop",function(event){
      event.preventDefault();
      if ($(document).scrollTop() + $(window).height() >= $(document).height()) {
        if (search_result.last_row == 0) {
          pull_info(search_result.ct, search_result.area, search_result.type, search_result.para, search_result.time);
        }
      }
    });

  }); //window load ready

  $(document).ready(function() {

    pull_info('mobile_city_culture_input_ct', 0, 'all', 0, curr_unix_time);

    //click search all
    $('#reset-info').on("click", function(e) {
      e.preventDefault();
      $("#info-container").empty();
      pull_info('mobile_city_culture_input_ct', 0, 'all', 0, curr_unix_time);
      $("#culture-search").panel( "close" );
    });

    //search category click
    $('.term-id').on("click", function(e) {
      e.preventDefault();
      tid = $(e.target).attr('tid');  //get current event target attribution
      areaid = $(e.target).attr('area-id');
      pull_info('mobile_city_culture_input_ct', areaid, 'term', tid, curr_unix_time);
      $("#info-container").empty();
      $("#culture-search").panel( "close" );
    });

    //send reading views to server, dynamic click event since js create article-list class
    $(document).on("click", ".article-list" , jump_to_article);

  }); //document ready

  function jump_to_article(e) {
    e.preventDefault();
    nid = $(e.currentTarget).attr('id');  //get current article node id
    send_views_to_node(nid);
  }

  //send article of views to server
  function send_views_to_node(nid) {

    json_data = {
      ajax: "mobile_set_article_views_obj",
      info: nid,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){
      //do nothing
    });

    request.fail(function(jqXHR, textStatus, errorThrown) {
      if (jqXHR.status != "200") {
        alert("set views error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });
  }

  //pull info from server
  //ct: content type
  //type: all/term
  //para: "all"/term id
  //time:
  function pull_info(ct, area, type, para, time) {

    //set search filter
    search_result.ct = ct;
    search_result.area = area;
    search_result.type = type;
    search_result.para = para;
    search_result.time = time;

    info_data = {
      ct: ct,
      area: area,
      type: type,
      para: para,
      time: time,
      range: 4,
    };

    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });

    json_data = {
      ajax: "mobile_get_article_info_obj",
      info: info_data,
    };

    $.mobile.loading('show', {
      text: "正在努力加载...",
      textVisible: true,
      theme: "b",
      textonly: false,
      html: ""
    });

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:1000}).then(function(data){

      $.mobile.loading('hide');

      if (jQuery.isEmptyObject(data) || data === null) {
        //alert("没有找到搜索结果，请重新选择搜索条件");
        return false;
      }
      if (typeof data.last_row === 'undefined') {
        search_result.last_row = 0;
        display_info_container(data);
      } else {
        search_result.last_row = data.last_row;
        //finished search
      }

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      $.mobile.loading('hide');
      if (jqXHR.status != "200") {
        alert("pull article list error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }

  //display info container (info-head, image etc)
  function display_info_container(data) {

    nodes = [];
    $.each(data, function(i, item) {
      item.nid = i;
      nodes.push(item);
    });

    //sort all node DESC by time changed 
    nodes.sort(function(a, b) {
      return parseInt(b.info_time) - parseInt(a.info_time);
    });

    $.each(nodes, function(i, node) {

      //set minimum time article from search result
      search_result.time = node.info_time;

      if (node.link_or_article == "0") {
        //if article is text or image
        ///city-culture/%/show
        node_url = 'http://mxweixin.dreamland360.com/wechat-py-mobile/city-culture/' + node.nid + '/show';
      } else if (node.link_or_article == "1") {
        //if article is link
        node_url = node.link;
      }

      if ( $('#info-container').children().length == 0 ) {
        div_custom = $("<div>").attr({
          "class": "ui-corner-all custom-corners article-list",
          "id": node.nid,
          "onclick": "location.href='" + node_url + "';",
        }).appendTo("#info-container");
      } else {
        div_custom = $("<div>").attr({
          "class": "ui-corner-all custom-corners article-list",
          "id": node.nid,
          "style": "margin-top: 1em;",
          "onclick": "location.href='" + node_url + "';",
        }).appendTo("#info-container");
      }

      div_bar = $("<div>").attr({"class": "ui-bar ui-bar-a info-head"}).appendTo(div_custom);
      h3_head = $("<h3>").html(node.info_head).appendTo(div_bar);
      div_body = $("<div>").attr({"class": "ui-body ui-body-a info-box"}).appendTo(div_custom);
      div_grid = $("<div>").attr({"class": "ui-grid-a info-grid"}).appendTo(div_body);
      div_bla = $("<div>").attr({"class": "ui-block-a"}).appendTo(div_grid);
      div_blb = $("<div>").attr({"class": "ui-block-b"}).appendTo(div_grid);

      pdate = new Date(parseInt(node.info_time) * 1000);
      p_time = $("<p>").attr({
        "class": "info-time",
        "style": "color: #B5B5B5; font-size: 0.8em;",
      }).html(pdate.getFullYear() + '年' + parseInt(pdate.getMonth() + 1) + '月' + pdate.getDate() + '日').appendTo(div_bla);
      //getMonth return value is 0-11 month

      p_view = $("<p>").attr({
        "class": "info-views",
        "style": "text-align: right; color: #B5B5B5; font-size: 0.8em;",
      }).html('阅读' + node.info_views + '次').appendTo(div_body).appendTo(div_blb);

      if (node.link_or_article == "0") {
        //if article is text or image
        if (typeof node.info_image === 'undefined') {
          p_article = $("<p>").attr({
            "class": "info-text",
          }).html(node.article + '...').appendTo(div_body);
        }

        if (typeof node.article === 'undefined') {
          pimage = $("<img>").attr({
            "src": node.info_image,
            "class": "info-image",
            "style": "width: 100%; margin: 0 auto; display: block;"
          }).appendTo(div_body);
        }
      } 

      if (node.link_or_article == "1") {
        if (typeof node.article === 'undefined') {
          pimage = $("<img>").attr({
            "src": node.info_image,
            "class": "info-image",
            "style": "width: 100%; margin: 0 auto; display: block;"
          }).appendTo(div_body);
        }
      }

      p_link = $("<p>").attr({
        "class": "info-full",
      }).html('阅读全文>>').appendTo(div_body);

    });

  }

})(jQuery);

