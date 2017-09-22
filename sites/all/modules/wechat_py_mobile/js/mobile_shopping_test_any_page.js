//mobile_shopping_test_any_page.js

(function($){
  $(document).ready(function(){

    var path = "http://mxweixin.dreamland360.com/wechat-py-mobile/py-shopping-api";
    var parameters = "?code=test_node_list&type=volume&lastid=10000000&sort=DESC&numbers=4";

    $('#node-list').on('click', function(e) {

      var request = $.ajax({
        method: "GET",
        url: path,
        data: {code: "test_node_list", type: "views", lastid: "10000000", sort: "DESC", numbers: "4"} 
      }).retry({times:3, timeout:1000}).then(function(data){

        console.log(data);
        nodes = [];
        $.each(data.data, function(i, item) {
          nodes.push(item);
        });

        console.log(nodes);

        nodes.sort(function(a, b) {
          return parseInt(b.order_id) - parseInt(a.order_id);
        });

        $.each(nodes, function(i, key){
          console.log(i); 
          if (i%2 == 0) {
            console.log(key);
            console.log('i is even');
          }else{
            console.log(key);
            console.log('i is odd');
          }
        });

      });

      request.fail(function(jqXHR, textStatus, errorThrown) {

        if (jqXHR.status != "200") {
          alert("test ajax error: " + jqXHR.status + " " + jqXHR.statusText);
        }

      });

    });

  }); //document ready

})(jQuery);


