(function($){
  $(document).ready(function(){

    $.ajax({
      url: '/wechat-ajax/lyxl/products',
      cache: false
    })
      .done(function( data ) {
        show_products(data);
      });
    
  }); /*document ready end*/

  /**
   * show lyxl product list 
   */
  var show_products = function(data) {
    //console.log(data);

    var el = {
      newDiv : $("<div>", {class: "products"}),
      newUl  : $("<ul>", {class: "ulclass"}),
    };

    $.each(data, function(i, elem){
      var item = {
        newLi  : $("<li>", {class: "item-li clearfix"}),
        splitLi : $("<li>", {class: "item-split-li clearfix"}),
        //newDiv : $("<div>", {class: "item-float"}),
        newImg : $("<img>", {class: "item-img"}),
        newName: $("<p>", {class: "item-p"}),
        newPrice: $("<p>", {class: "item-p"}),
        newButton: $("<p>", {class: "item-button"})
      };

      //item.newLi.addClass("item-li");
      //item.newImg.addClass("item-img");

      item.newImg.attr({ src: elem.img });
      item.newButton.on( "click", { nodeid: elem.node }, show_itempage );
      //item.newButton.attr({href: "/wechat-ajax/lyxl/"+elem.node});
      item.newButton.html("详细");
      item.newName.html(elem.name);
      item.newPrice.html(elem.price);
      //item.newDiv.append(item.newImg, item.newName);

      if (elem.name.length > 8) {
        /* Nothing*/
      } else {  /* <= 8 */
        item.newButton.css({
          "margin-top": "25px"
        });
      }

      item.newLi.append(item.newImg, item.newName, item.newPrice, item.newButton);
      item.newLi.appendTo(el.newUl);
      item.splitLi.appendTo(el.newUl);

    });

    el.newUl.appendTo(el.newDiv);
    el.newDiv.appendTo("#ajax-load-page");     

  };

  /**
   * show each page for lyxl
   */
  function show_itempage(event) {
    console.log(event.data.nodeid);
    $("#ajax-load-page").empty();
    $.ajax({
      url: '/wechat-ajax/lyxl/item/'+event.data.nodeid,
      cache: false
    })
      .done(function( data ) {
        //console.log(data);
        render_item(data);
      });
  }

  var render_item = function(data) {

    var node = {
      newName    : $("<p>", {class: "p-node-title"}),
      newSche    : $("<p>", {class: "p-node-sche"}),
      newBus     : $("<p>", {class: "p-node-bus"}),
      newHotel   : $("<p>", {class: "p-node-hotel"}),
      newMeal    : $("<p>", {class: "p-node-meal"}),
      newTicket  : $("<p>", {class: "p-node-ticket"}),
      newGuide   : $("<p>", {class: "p-node-guide"}),
      newInsur   : $("<p>", {class: "p-node-insur"}),
      newNotes   : $("<p>", {class: "p-node-notes"}),
    
      newDiv     : $("<div>", {class: "node-page"}),
      newUl      : $("<ul>", {class: "node-ul"}),
      newButton  : $("<p>", {class: "return-button", html: "返回"})
    };
    var iconUrl = "http://mxweixin.dreamland360.com/sites/all/modules/wechat_ajax/imgs/";

    $.each(data, function(name, value){
      if(value && value != ''){
      }else{
        value = '无';
      }

      if((name == '产品类型') && (value == '常规地接线路')){ /*地接线路二日游，三日游等*/
      }else{    /*半日游，一日游等*/
        switch(name) {
          case '产品名称':
            node.newName.html(value);
            break;
          case '具体行程':
            node.newSche.html(value);
            break;
          case '交通':
            node.newBus.html(name + "：" + value);
            var $newLi = $( "<li class='node-li clearfix'/>" );
            var $newIcon = $( "<img class='node-icon'/>" );
            $newIcon.attr("src", iconUrl + "lyxl-bus-icon.png");
            $newLi.append($newIcon, node.newBus);
            break;
          case '住宿':
            node.newHotel.html(name + "：" + value);
            var $newLi = $( "<li class='node-li clearfix'/>" );
            var $newIcon = $( "<img class='node-icon'/>" );
            $newIcon.attr("src", iconUrl + "lyxl-hotels-icon.png");
            $newLi.append($newIcon, node.newHotel);
            break;
          case '餐费':
            node.newMeal.html(name + "：" + value);
            var $newLi = $( "<li class='node-li clearfix'/>" );
            var $newIcon = $( "<img class='node-icon'/>" );
            $newIcon.attr("src", iconUrl + "lyxl-meal-icon.png");
            $newLi.append($newIcon, node.newMeal);
            break;
          case '门票':
            node.newTicket.html(name + "：" + value);
            var $newLi = $( "<li class='node-li clearfix'/>" );
            var $newIcon = $( "<img class='node-icon'/>" );
            $newIcon.attr("src", iconUrl + "lyxl-ticket-icon.png");
            $newLi.append($newIcon, node.newTicket);
            break;
          case '导游':
            node.newGuide.html(name + "：" + value);
            var $newLi = $( "<li class='node-li clearfix'/>" );
            var $newIcon = $( "<img class='node-icon'/>" );
            $newIcon.attr("src", iconUrl + "lyxl-guide-icon.png");
            $newLi.append($newIcon, node.newGuide);
            break;
          case '保险':
            node.newInsur.html(name + "：" + value);
            var $newLi = $( "<li class='node-li clearfix'/>" );
            var $newIcon = $( "<img class='node-icon'/>" );
            $newIcon.attr("src", iconUrl + "lyxl-insurance-icon.png");
            $newLi.append($newIcon, node.newInsur);
            break;
          case '温馨提示':
            node.newNotes.html(name + "：" + value);
            var $newLi = $( "<li class='node-li clearfix'/>" );
            var $newIcon = $( "<img class='node-icon'/>" );
            $newIcon.attr("src", iconUrl + "lyxl-notes-icon.png");
            $newLi.append($newIcon, node.newNotes);
            break;
          default:
            break;
        }
        node.newUl.append($newLi);
      }

      //console.log(name);
      //console.log(value);
    });

    node.newDiv.append(node.newName);
    node.newDiv.append(node.newSche);

    
    //node.newDiv1.append(node.newIcon, node.newBus);
    //node.newDiv.append(node.newDiv1);
/*
    node.newDiv.append($newDiv1, [node.newIcon, node.newBus]);

    newIconclone = node.newIcon.clone();
    newIconclone.attr("src", iconUrl + "lyxl-hotels-icon.png");
    node.newDiv1.empty();
    node.newDiv1.append(newIconclone, node.newHotel);
    node.newDiv.append(node.newDiv1);

    node.newDiv.append(node.newMeal);
    node.newDiv.append(node.newTicket);
    node.newDiv.append(node.newGuide);
    node.newDiv.append(node.newInsur);
    node.newDiv.append(node.newNotes);
*/
    node.newDiv.append(node.newUl);

    node.newButton.on( "click", return_to_lyxl_page);
    node.newDiv.append(node.newButton);
    node.newDiv.appendTo("#ajax-load-page");     
  };

  function return_to_lyxl_page() {
    window.location.replace("");
  }

})(jQuery);
