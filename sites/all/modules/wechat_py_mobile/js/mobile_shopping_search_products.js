//search merchandise content for mobile shopping
(function($){

  //declare plugin function and variabal without any elements like $('xxx').
  $.extend({
    shopping_smc_obj: {
      ajax: "shopping_smc_obj",
      term: "all",  //all or term
      termid: 0,
      type: "volume", //current search condition
      sort : "DESC", //current search sorting
      numbers : 4, //number of get data items
      increase: 0,  //number increase
      total : 0, //current search totally number
      end: 0,
      lastid : 0,
      data : [],
    },

    shopping_smc_reset: function(term, termid, type, sort, numbers) {
      $.shopping_smc_obj.term = term;
      $.shopping_smc_obj.termid = termid;
      $.shopping_smc_obj.type = type;
      $.shopping_smc_obj.sort = sort;
      $.shopping_smc_obj.numbers = numbers;
      $.shopping_smc_obj.lastid = 0;
      $.shopping_smc_obj.increase = 0;
      $.shopping_smc_obj.total = 0;
      $.shopping_smc_obj.end = 0;
      $.shopping_smc_obj.data = [];
    },

    shopping_smc_search: function() {
      if ($.shopping_smc_obj.end) {
        //alert("end == 1");
        return;
      }

      var interval = setInterval(function(){
        $.mobile.loading('show', {
          text: "正在加载...",
          textVisible: true,
          theme: "b",
          textonly: false,
        });
        clearInterval(interval);
      },100);

      json_data = {
        ajax: $.shopping_smc_obj.ajax,
        term: $.shopping_smc_obj.term,
        termid: $.shopping_smc_obj.termid,
        type: $.shopping_smc_obj.type,
        sort: $.shopping_smc_obj.sort,
        numbers: $.shopping_smc_obj.numbers,
        lastid: $.shopping_smc_obj.lastid
      };

      var path = "http://mxweixin.dreamland360.com/wechat-py-mobile/data-api";

      $.ajaxSetup({ 
        cache: false,
        headers: { "cache-control": "no-cache" }
      });

      var request = $.ajax({
        method: "POST",
        url: path,
        timeout: 8000,
        data: JSON.stringify(json_data),
        ajax_owner: "shopping_smc_obj"  //private tag for check which ajax success in ajaxComplete
      });

      request.fail(function(jqXHR, textStatus, errorThrown) {
        alert('加载数据等待: ' + textStatus); //other error
      });

      request.always(function(data) {
      });

      request.done(function(data) {
        //console.log(data);
        $.shopping_smc_obj.total = parseInt(data.total);
        $.shopping_smc_obj.data = data.data;
        //$.shopping_smc_obj.increase += Object.keys(data.data).length;
        $.shopping_smc_obj.end = data.end;
        $.shopping_smc_obj.lastid = data.lastid;

      }); //end request.done

    },

  });

})(jQuery);
