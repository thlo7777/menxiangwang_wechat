//mobile_shopping_home_page.js

(function($){

  var term_filter = {
    name: '',
    vocid: 0,
    termid: 0,
    nids: [0],
    lastid: 10000000,
    numbers: 4,
    type: "volume", //current search condition
    sort : "DESC", //current search sorting
    end: 0,
    unfind: 0,    //can't find any result
  }

  function init_term_filter() {

    if ($('#term-filter').length > 0) { 
      /*
      term_name = $.trim($('#term-filter').text());
      var regexp = /^全部商品$/i;
      var found = term_name.match(regexp);
      if (found === null) {
        term_name = "term";
      } else {
        term_name = "all";
      }
      */

      voc_id = $.trim($('#voc-id').html());
      term_id = $.trim($('#term-id').html());
      //last_id = $.trim($('#last-id').html());
      term_filter.name = "all";
      term_filter.vocid = voc_id;
      term_filter.termid = term_id;
      //term_filter.lastid = last_id;

    } else {
      term_filter.name = "all";
      term_filter.vocid = 1;
      term_filter.termid = 1;
    }

    fetch_merchandise_ajax();

  }


  //Hence, to wait until the entire page is ready, you can use something like:
  $(window).load(function() {

    init_term_filter();

    //change footer navbar icon size when landscape
    $( window ).on( "orientationchange", function( event ) {
      if (event.orientation == "landscape") {
        $("#term-search-icon").width("40%");
        $("#order-icon").width("40%");
        $("#cart-icon").width("40%");
        $("#cart-icon-add").width("40%");
        $("#address-icon").width("40%");
      } else {
        $("#term-search-icon").width("80%");
        $("#order-icon").width("80%");
        $("#cart-icon").width("80%");
        $("#cart-icon-add").width("80%");
        $("#address-icon").width("80%");
      }
    });


    //detect page scroll down
    //can't work use $(window).scroll()
    $(document).on("scrollstop",function(event){
      event.preventDefault();
      if ($(document).scrollTop() + $(window).height() >= $(document).height()) {

        fetch_merchandise_ajax();

      }
    });

    //detect search-volume and search-views button
    $('#search-views').on("click", function(e) {
      if (term_filter.unfind) {
        return false;
      }

      $('#merchandise-list').empty();

      term_filter.type = "views",
      term_filter.lastid = 10000000;
      term_filter.end = 0;
      term_filter.nids.length = 1;

      e.preventDefault();
      fetch_merchandise_ajax();
    });

    //detect search-volume and search-views button
    $('#search-volume').on("click", function(e) {
      if (term_filter.unfind) {
        return false;
      }

      $('#merchandise-list').empty();
      term_filter.type = "volume",
      term_filter.lastid = 10000000;
      term_filter.end = 0;
      term_filter.nids.length = 1;

      e.preventDefault();
      fetch_merchandise_ajax();
    });


    //add merchandise to cart table
    $(document).on("click", "#cart-plus" , add_merchandise_to_cart_ajax);

    get_cart_records_ajax(); //temp solution, will use wechat redirect and state url
  });  //window load ready
  
   $(document).ready(function() {
        //handle all wx api function
        $.set_wx_config();
        $.share_current_page(document.title, "梦乡网，人人的故乡梦", share_home_page, share_image);

        var url = window.location.href;     // Returns full URL
        var reg = /new-tpl-search/i;
        //if (url.match(reg)) {
            get_all_service_category();

            //for panel category search
            $(document).on("click", ".search-panel-term", search_panel_products);
        //}
   }); //document ready

    function get_all_service_category() {
        $.ajaxSetup({ 
          url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
          cache: false,
          headers: { "cache-control": "no-cache" },
        });

        json_data = {
          ajax: "shopping_service_area",
          xyz: $.trim($('#xyz').html())
        };

        var request = $.ajax({
          method: "POST",
          data: JSON.stringify(json_data),
        }).retry({times:2, timeout:3000}).then(function(data){
	    data.sort(function(a, b) {
		  if (parseInt(a.weight) < parseInt(b.weight)) {
		    return -1;
		  }
		  if (parseInt(a.weight) > parseInt(b.weight)) {
		    return 1;
		  }
		  // a must be equal to b
		  return 0;
	    });
            insert_search_navbar(data);
        });

        request.fail(function(jqXHR, textStatus, errorThrown) {

          if (jqXHR.status != "200") {
            alert("add cart error: " + jqXHR.status + " " + jqXHR.statusText);
          }

        });
    }

    function insert_search_navbar(data) {

        $hr = $('.ui-content hr:first-child'); 
        if (data.length) {
/*
<div data-role="navbar" data-iconpos="right" id="search-navbar">
    <ul class="ui-grid-b">
        <li class="ui-block-a"><a href="#" data-icon="bullets" data-id = "<?php print $page['search_lv_items'][0]['tid']; ?>"
         class="ui-btn"><?php print $page['search_lv_items'][0]['name']; ?>
        </a></li>
        <li class="ui-block-b"><a href="#" data-icon="bullets" data-id = "<?php print $page['search_lv_items'][1]['tid']; ?>"
         class="ui-btn"><?php print $page['search_lv_items'][1]['name']; ?>
        </a></li>
        <li class="ui-block-c"><a href="#" data-icon="bullets" data-id = "<?php print $page['search_lv_items'][2]['tid']; ?>"
         class="ui-btn"><?php print $page['search_lv_items'][2]['name']; ?>
        </a></li>
        <li class="ui-block-a"><a href="#" data-icon="bullets" data-id = "<?php print $page['search_lv_items'][3]['tid']; ?>"
         class="ui-btn"><?php print $page['search_lv_items'][3]['name']; ?>
        </a></li>
        <li class="ui-block-b"><a href="#" data-icon="bullets" data-id = "<?php print $page['search_lv_items'][4]['tid']; ?>"
         class="ui-btn"><?php print $page['search_lv_items'][4]['name']; ?>
        </a></li>
        <li class="ui-block-c"><a href="#" data-icon="bullets" class="ui-btn">更多...</a></li>
    </ul>
</div><!-- /navbar -->
*/
            $div = $('<div>').attr({
                "data-role": "navbar",
                "data-iconpos": "right",
                "class": "ui-navbar",
                "role": "navigation",
                "id": "search-navbar"
                });
            $hr.after($div);

            $ul = $('<ul>').attr({
                "class": "ui-grid-b ui-grid-duo"
                }).appendTo($div);

            $.each(data, function(i, item) {
                if (i > 4) {
                    //only insert top 5 term
                    return false;
                }

                if ((i % 3) == 0) {
                    $li = $('<li>').attr({
                        "class": "ui-block-a"
                        }).appendTo($ul);
                } else if((i % 3) == 1) {
                    $li = $('<li>').attr({
                        "class": "ui-block-b"
                        }).appendTo($ul);
                } else if((i % 3) == 2) {
                    $li = $('<li>').attr({
                        "class": "ui-block-c"
                        }).appendTo($ul);
                }

                $('<a>').attr({
                    "href": "#",
                    "data-vid": 2,  //means voc wechat_shopping_merchant_vocabulary
                    "data-tid": item.tid,
                    "class": "search-button ui-btn ui-icon-carat-r ui-btn-icon-right" 
                    }).html(item.name).appendTo($li);
            });

            /*
             * add more... button
             */
            $li = $('<li>').attr({
                "class": "ui-block-c"
                }).appendTo($ul);

            $('<a>').attr({
                "href": "#service-area-list",
                "data-vid": -100,
                "data-tid": -100,
                "class": "search-button ui-btn ui-icon-carat-r ui-btn-icon-right"
                }).html("更多分类").appendTo($li);

            $(document).on("click", ".search-button", search_products);
        } else {
/*
<div data-role="navbar">
<ul>
<li><a href="#" class="ui-btn-active">One</a></li>
</ul>
</div><!-- /navbar -->
*/
            $div = $('<div>').attr({
                "data-role": "navbar",
                "class": "ui-navbar",
                "role": "navigation"
                });
            $hr.after($div);
            $('<ul>').attr({
                "class": "ui-grid-solo"
                }).html(
            '<li calss="ui-block-a"><a href="#" class="ui-btn-active ui-link ui-btn">没有服务区</a></li>'
            ).appendTo($div);
        }

    }


    function search_panel_products() {
        var vid = $(this).data('vid');
        var tid = $(this).data('tid');
        console.log(vid);
        console.log(tid);

        //close panel
        $('#service-area-list').panel('close');

        if (term_filter.unfind) {
            return false;
        }

        if (vid == 2 && tid == -100) {
            //search all
            //console.log('搜索全部');
            term_filter.name = "all";
            term_filter.vocid = 1;
            term_filter.termid = 1;
        } else {
            term_filter.vocid = vid;
            term_filter.termid = tid;
            console.log('搜索部分');
        }

        term_filter.lastid = 10000000;
        term_filter.type = "volume",
        term_filter.end = 0;
        term_filter.nids = [0];

        //clear main product list
        $('#merchandise-list').empty();
        fetch_merchandise_ajax();
    }

    function search_products() {
        term_filter.vocid = $(this).data('vid');
        term_filter.termid = $(this).data('tid');

        $('.search-button').removeClass('ui-btn-active');
        $(this).addClass('ui-btn-active');

        if (term_filter.vocid == -100 && term_filter.termid == -100) {
            return ;
        }

        if (term_filter.unfind) {
            return false;
        }

        $('#merchandise-list').empty();


        term_filter.type = "volume",
        term_filter.lastid = 10000000;
        term_filter.end = 0;
        term_filter.nids = [0];

        fetch_merchandise_ajax();
    }

  function add_merchandise_to_cart_ajax(e) {
    e.preventDefault();

    nid = $(this).attr('nid');

    json_data = {
      ajax: "shopping_add_cart_obj",
      xyz: $.trim($('#xyz').html()),
      nid: nid,
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:2, timeout:3000}).then(function(data){

      if (data.state == "0") {
        //animation cart icon
        //switch cart_icon and cart_icon_add
        $('#cart-icon').css({"display" : "none"});
        $('#cart-icon-add').css({"display" : "block"});
        
        //console.log(data);
      }

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {

      if (jqXHR.status != "200") {
        alert("add cart error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

    showEarnedPoints(new Position($(window).height()/3 + $(document).scrollTop(), $(window).width()/2 - 44));
  }


  function showEarnedPoints(position){
      label = new PointsLabel(position);
      label.fadeIn(function(){
          label.moveToTopRight(function(){
              label.fadeOut(function(){
                  label.destroy();
                  $("#cart-reminder").remove();
              });
          });
      });
  }

  function Position(top, right){
      this.top = top;
      this.right = right;
  }

  function PointsLabel(position){
      var html = '<div id="cart-reminder">加入购物车</div>'
      $("#py-mobile-home-page").append(html);
      this.domElement = $("#py-mobile-home-page #cart-reminder").last();
      this.domElement.css("top", position.top);
      this.domElement.css("right", position.right);
      
      this.fadeIn = function(callback){
        this.domElement.fadeIn("slow", callback);
      }
      this.fadeOut = function(callback){
        this.domElement.fadeOut("slow", callback);
      }
      this.moveToTopRight = function(callback){
        this.domElement.animate({top: ($(window).height()+ $(document).scrollTop()), right: ($(window).width()/2 - 44)}, 500, callback);
      }
      this.destroy = function(){
        this.domElement.remove();
      }
  }

  function get_cart_records_ajax() {
    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });

    json_data = {
      ajax: "shopping_get_cart_count_obj",
      xyz: $.trim($('#xyz').html()),
    };

    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:3000}).then(function(data){
      //alert("retry this");

      //console.log(data);
      if (typeof(data) === "undefined" || data === null || data == "0") {

        $('#cart-icon').css({"display": "block"});
        $('#cart-icon-add').css({"display": "none"});
      } else {

        $('#cart-icon').css({"display": "none"});
        $('#cart-icon-add').css({"display": "block"});
      }

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {
      //console.log(errorThrown);
      $.mobile.loading('hide');

      if (jqXHR.status != "200") {
        alert("get cart count error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }

  function fetch_merchandise_ajax() {

    if (parseInt(term_filter.end) == 1) {
      //has get all items
      return ;
    }

    $.mobile.loading('show', {
      text: "加载数据...",
      textVisible: true,
      theme: "b",
      textonly: false,
      html: ""
    });

    $.ajaxSetup({ 
      url: "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api",
      cache: false,
      headers: { "cache-control": "no-cache" },
    });


    json_data = {
      ajax: "shopping_smc_obj",
      term: term_filter.name,
      vocid: term_filter.vocid,
      termid: term_filter.termid,
      type: term_filter.type,
      sort: term_filter.sort,
      numbers: term_filter.numbers,
      lastid: term_filter.lastid,
      nids: term_filter.nids,
    };

    //console.log(json_data);
    var request = $.ajax({
      method: "POST",
      data: JSON.stringify(json_data),
    }).retry({times:3, timeout:3000}).then(function(data){
      //alert("retry this");
      //console.log(data);

      if (typeof data === "undefined" || data === null) {
        if ($('#search-error').length > 0) { 
          $("#search-error").remove();
        }

        //for search error if no search result
        pbody = $("<div>").attr({
          "class": "ui-body ui-body-a ui-corner-all",
          "id": "search-error",
          "style": "margin-top: 0.5em; background-color: #F1DD80; border-color: #333; text-shadow: 0 1px 0 #ffffff;"
        }).insertAfter("#search-type");

        perror = $("<p>").attr({
          "style": "text-align: center;"
        }).html("未找到搜索结果，请重新搜索").appendTo(pbody);

        term_filter.unfind = 1;   //can't find any result
        term_filter.end = 0;
        term_filter.lastid = 10000000;

        $.mobile.loading('hide');

        return ;

      }

      if ($('#search-error').length > 0) { 
        $("#search-error").remove();
      }

      if (data.end == 1 && data.data === null) {

        $('#term-filter').text(data.term_filter);
        term_filter.unfind = 0;   //find it
        term_filter.end = data.end;  //search finished

      //} else if (term_filter.end == 0 && parseInt(term_filter.lastid) >= parseInt(data.lastid)) {
      } else if (term_filter.end == 0) {

        $('#term-filter').text(data.term_filter);
        term_filter.unfind = 0;   //find it
        term_filter.end = data.end;
        //term_filter.lastid = data.lastid;

        //console.log(data);
        display_merchandise(data.data);
      }

      $.mobile.loading('hide');

    });

    request.fail(function(jqXHR, textStatus, errorThrown) {
      //console.log(errorThrown);
      $.mobile.loading('hide');

      if (jqXHR.status != "200") {
        alert("home page error: " + jqXHR.status + " " + jqXHR.statusText);
      }

    });

  }

  //show home page product list
  function display_merchandise(node) {

    if (node === null || typeof(node) === "undefined") {
      return ;
    }
    nodes = [];
    $.each(node, function(i, item) {
      nodes.push(item);
      term_filter.nids.push(i); //record has been getted node
    });

    //console.log(term_filter.nids);
    //sort all node DESC by volumen or views 
    nodes.sort(function(a, b) {
      return parseInt(b.order_id) - parseInt(a.order_id);
    });
    //fill lastnid to term_filter
    //term_filter.lastnid = nodes[nodes.length - 1].nid;
    //console.log(nodes[nodes.length - 1].nid);


    $.each(nodes, function(i, key){
      //console.log(node[key]); 
      if (i%2 == 0) {
        uibla = $("<div>").attr({"class": "ui-block-a", "id":"uibla"}).appendTo("#merchandise-list");
        bodya = $("<div>").attr({"class": "ui-body ui-body-a ui-corner-all"}).appendTo(uibla);
        purl = $("<a>").attr({"href": key.purl, "rel": "external"}).appendTo(bodya);
        //purl = $("<a>").attr({"href": node[key].purl}).appendTo(bodya);

        pimage = $("<img>").attr({
          "src": key.pimage,
          "class": "product-img",
          "style": "width: 100%; margin: 0 auto; display: block;"
        }).appendTo(purl);

        m_name = key.pname;
        if (key.pscore_points !== null) {
          m_name += key.pscore_points;
        }

        if (key.pdiscount !== null) {
          m_name += key.pdiscount;
        }

        if (key.pexp_free !== null) {
          m_name += key.pexp_free;
        }

        pname = $("<div>").attr({
          "class": "ui-body merchandise-name",
          "style": "height: 3.5em; word-wrap: break-word;"
        }).html(m_name).appendTo(bodya);

        price = $("<div>").attr({
          "class": "ui-body",
          "style": "float: left; margin: 0; padding: 0;"
        }).appendTo(bodya);
        cost_price = $("<div>").attr({
          "style": "font-weight: bold; color: #666; text-decoration: line-through; font-size: 0.9em;"
        }).html("¥" + key.pcost_price).appendTo(price);

        cart_div = $("<div>").attr({
          "id": "cart-plus",
          "nid": key.nid,
          "style": "float: right; margin: 0;"
        }).appendTo(bodya);
        cart_icon = $("<img>").attr({
          "src": key.cart_plus,
          "style": "width: 100%; float: right; display: block;"
        }).appendTo(cart_div);

        price = $("<div>").attr({
          "class": "ui-body",
          "style": "float: left; margin: 0; padding: 0;"
        }).appendTo(bodya);
        shopping_price = $("<div>").attr({
          "style": "font-weight: bold; color: #fa620e; font-size: 1.0em;"
        }).html("¥" + key.pshopping_price).appendTo(price);


      } else {
        uiblb = $("<div>").attr({"class": "ui-block-b", "id":"uiblb"}).appendTo("#merchandise-list");
        bodya = $("<div>").attr({"class": "ui-body ui-body-a ui-corner-all"}).appendTo(uiblb);
        purl = $("<a>").attr({"href": key.purl, "rel": "external"}).appendTo(bodya);
        //purl = $("<a>").attr({"href": node[key].purl}).appendTo(bodya);

        pimage = $("<img>").attr({
          "src": key.pimage,
          "class": "product-img",
          "style": "width: 100%; margin: 0 auto; display: block;"
        }).appendTo(purl);

        m_name = key.pname;
        if (key.pscore_points !== null) {
          m_name += key.pscore_points;
        }

        if (key.pdiscount !== null) {
          m_name += key.pdiscount;
        }

        if (key.pexp_free !== null) {
          m_name += key.pexp_free;
        }

        pname = $("<div>").attr({
          "class": "ui-body merchandise-name",
          "style": "height: 3.5em; word-wrap: break-word;"
        }).html(m_name).appendTo(bodya);

        price = $("<div>").attr({
          "class": "ui-body",
          "style": "float: left; margin: 0; padding: 0;"
        }).appendTo(bodya);
        cost_price = $("<div>").attr({
          "style": "font-weight: bold; color: #666; text-decoration: line-through; font-size: 0.9em;"
        }).html("¥" + key.pcost_price).appendTo(price);

        cart_div = $("<div>").attr({
          "id": "cart-plus",
          "nid": key.nid,
          //"style": "float: right; margin: 0 0 0 4em;"
          "style": "float: right; margin: 0;"
        }).appendTo(bodya);
        cart_icon = $("<img>").attr({
          "src": key.cart_plus,
          "style": "width: 100%; float: right; display: block;"
        }).appendTo(cart_div);

        price = $("<div>").attr({
          "class": "ui-body",
          "style": "float: left; margin: 0; padding: 0;"
        }).appendTo(bodya);
        shopping_price = $("<div>").attr({
          "style": "font-weight: bold; color: #fa620e; font-size: 1.0em;"
        }).html("¥" + key.pshopping_price).appendTo(price);

        
      }

    });

  } //show list function end

  function display_merchandise_old(node) {

    if (node === null || typeof(node) === "undefined") {
      return ;
    }
    //purl = $("<a>").attr({}).appendTo(bodya);
    //node = $.shopping_smc_obj.data;
    sortedKeys = Object.keys(node).sort(function(a, b) { return b - a; });
    $.each(sortedKeys, function(i, key){
      //console.log(node[key]); 
      if (i%2 == 0) {
        uibla = $("<div>").attr({"class": "ui-block-a", "id":"uibla"}).appendTo("#merchandise-list");
        bodya = $("<div>").attr({"class": "ui-body ui-body-a ui-corner-all"}).appendTo(uibla);
        purl = $("<a>").attr({"href": node[key].purl, "rel": "external"}).appendTo(bodya);
        //purl = $("<a>").attr({"href": node[key].purl}).appendTo(bodya);

        pimage = $("<img>").attr({
          "src": node[key].pimage,
          "class": "product-img",
          "style": "width: 100%; margin: 0 auto; display: block;"
        }).appendTo(purl);

        m_name = node[key].pname;
        if (node[key].pscore_points !== null) {
          m_name += node[key].pscore_points;
        }

        if (node[key].pdiscount !== null) {
          m_name += node[key].pdiscount;
        }

        if (node[key].pexp_free !== null) {
          m_name += node[key].pexp_free;
        }

        pname = $("<div>").attr({
          "class": "ui-body merchandise-name",
          "style": "height: 3.5em; word-wrap: break-word;"
        }).html(m_name).appendTo(bodya);

        price = $("<div>").attr({
          "class": "ui-body",
          "style": "float: left; margin: 0; padding: 0;"
        }).appendTo(bodya);
        cost_price = $("<div>").attr({
          "style": "font-weight: bold; color: #666; text-decoration: line-through; font-size: 0.9em;"
        }).html("¥" + node[key].pcost_price).appendTo(price);

        cart_div = $("<div>").attr({
          "id": "cart-plus",
          "nid": node[key].nid,
          "style": "float: right; margin: 0;"
        }).appendTo(bodya);
        cart_icon = $("<img>").attr({
          "src": node[key].cart_plus,
          "style": "width: 100%; float: right; display: block;"
        }).appendTo(cart_div);

        price = $("<div>").attr({
          "class": "ui-body",
          "style": "float: left; margin: 0; padding: 0;"
        }).appendTo(bodya);
        shopping_price = $("<div>").attr({
          "style": "font-weight: bold; color: #fa620e; font-size: 1.0em;"
        }).html("¥" + node[key].pshopping_price).appendTo(price);


      } else {
        uiblb = $("<div>").attr({"class": "ui-block-b", "id":"uiblb"}).appendTo("#merchandise-list");
        bodya = $("<div>").attr({"class": "ui-body ui-body-a ui-corner-all"}).appendTo(uiblb);
        purl = $("<a>").attr({"href": node[key].purl, "rel": "external"}).appendTo(bodya);
        //purl = $("<a>").attr({"href": node[key].purl}).appendTo(bodya);

        pimage = $("<img>").attr({
          "src": node[key].pimage,
          "class": "product-img",
          "style": "width: 100%; margin: 0 auto; display: block;"
        }).appendTo(purl);

        m_name = node[key].pname;
        if (node[key].pscore_points !== null) {
          m_name += node[key].pscore_points;
        }

        if (node[key].pdiscount !== null) {
          m_name += node[key].pdiscount;
        }

        if (node[key].pexp_free !== null) {
          m_name += node[key].pexp_free;
        }

        pname = $("<div>").attr({
          "class": "ui-body merchandise-name",
          "style": "height: 3.5em; word-wrap: break-word;"
        }).html(m_name).appendTo(bodya);

        price = $("<div>").attr({
          "class": "ui-body",
          "style": "float: left; margin: 0; padding: 0;"
        }).appendTo(bodya);
        cost_price = $("<div>").attr({
          "style": "font-weight: bold; color: #666; text-decoration: line-through; font-size: 0.9em;"
        }).html("¥" + node[key].pcost_price).appendTo(price);

        cart_div = $("<div>").attr({
          "id": "cart-plus",
          "nid": node[key].nid,
          //"style": "float: right; margin: 0 0 0 4em;"
          "style": "float: right; margin: 0;"
        }).appendTo(bodya);
        cart_icon = $("<img>").attr({
          "src": node[key].cart_plus,
          "style": "width: 100%; float: right; display: block;"
        }).appendTo(cart_div);

        price = $("<div>").attr({
          "class": "ui-body",
          "style": "float: left; margin: 0; padding: 0;"
        }).appendTo(bodya);
        shopping_price = $("<div>").attr({
          "style": "font-weight: bold; color: #fa620e; font-size: 1.0em;"
        }).html("¥" + node[key].pshopping_price).appendTo(price);

        
      }

    });

  } //show list function end


})(jQuery);

