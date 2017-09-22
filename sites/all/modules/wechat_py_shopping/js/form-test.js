(function($) {

  //for test async ajax 
  $.fn.save_submit = function(/*? no data pass?*/template_id, condition){
        var city_json_data = Drupal.array2json(city_array);
         var weight_json_data = Drupal.array2json(weight_array);
         if(city_array.length == 0) {
           alert("请选择城市");
           return;
         }
         if(weight_array.length == 0) {
           alert("请选择重量价格");
           return;
         }

         json_data = '{' + 
          '"template_id":"' + template_id + '",' + 
          '"city":' + city_json_data + ',' +
          '"weight":' + weight_json_data + ',' +
          '"condition":"' + condition + '"' +
         '}';

        var url_path = Drupal.settings.wechat_py_shopping.basePath;
        var request = $.ajax({
          timeout: 2000,
          //Because fail return status = 0 status text = error, then set async to false, and force 
          //ajax to sync 
          //async: false,
          //url: "http://mxweixin.dreamland360.com/wechat-py-shopping/wechat-merchant-express/form-test/ajax-json",
          url: url_path,

          method: "POST",
          data: json_data,
        });

        request.done(function() {
        });

        request.fail(function(jqXHR, textStatus, errorThrown) {
          /*
           * We found out that this could happen if the ajax request is getting canceled 
           * before it completes. We could reproduce the problem if we triggered the ajax request 
           * and then immediately click on a link to navigate away from the page. jQuery throws 
           * the error event when the user navigates away from the page either by refreshing, 
           * clicking a link, or changing the URL in the browser. 
           */
          if (jqXHR.readyState == 0 || jqXHR.status == 0) {
            return; //Skip this error
          }

          alert('上传失败:' + textStatus); //other error
        });

        request.always(function() {
          //alert('ok');
          //add list item into table
          console.log(json_data);
          //clear all content
          city_array.splice(0, city_array.length);
          weight_array.splice(0, weight_array.length);
          
        });
  };

  //Drupal.client_version = navigator.userAgent;
  Drupal.array2json = function (arr) {
    var parts = [];
    var is_list = (Object.prototype.toString.apply(arr) === '[object Array]');

    for(var key in arr) {
    	var value = arr[key];
        if(typeof value == "object") { //Custom handling for arrays
            if(is_list) parts.push(array2json(value)); 
            else parts[key] = array2json(value);
        } else {
            var str = "";
            //if(!is_list) str = '"' + key + '":';
            str = '"' + key + '":';

            //Custom handling for multiple data types
            if(typeof value == "number") str += value; //Numbers
            else if(value === false) str += 'false'; //The booleans
            else if(value === true) str += 'true';
            else str += '"' + value + '"'; //All other things
            // :TODO: Is there any more datatype we should be in the lookout for? (Functions?)

            parts.push(str);
        }
    }
    var json = parts.join(",");
    
    //if(is_list) return '[' + json + ']';//Return numerical JSON
    return '{' + json + 
    '}';//Return associative JSON
  };

  var city_array = [];
  var weight_array = [];
  var json_data;

  Drupal.behaviors.form_test = {
    attach: function(context, settings) {

      //alert(Drupal.client_version);

      $('#weight-multi-select-code', context).once('weight_multi_select', function () {

        $('#weight-multi-select-code').multiSelect({

          selectableHeader: "<div class='custom-header'>选择重量价格:</div>",
          selectionHeader: "<div class='custom-header'>已选择</div>",
          selectableHeader: "<div class='custom-header'>选择重量价格</div>" + 
                            "<input type='text' class='search-input' autocomplete='off' placeholder='\"20\"'>",
          selectionHeader: "<div class='custom-header'>已选</div>" + 
                           "<input type='text' class='search-input' autocomplete='off' placeholder='\"14\"'>",

          afterInit: function(ms){
            var that = this,
            $selectableSearch = that.$selectableUl.prev(),
            $selectionSearch = that.$selectionUl.prev(),
            selectableSearchString = '#'+that.$container.attr('id')+' .ms-elem-selectable:not(.ms-selected)',
            selectionSearchString = '#'+that.$container.attr('id')+' .ms-elem-selection.ms-selected';

            that.qs1 = $selectableSearch.quicksearch(selectableSearchString)
            .on('keydown', function(e){
              if (e.which === 40){
                that.$selectableUl.focus();
                return false;
              }
            });

            that.qs2 = $selectionSearch.quicksearch(selectionSearchString)
            .on('keydown', function(e){
              if (e.which == 40){
                that.$selectionUl.focus();
                return false;
              }
            });
          },

          afterSelect: function(values){
            weight_array.push(values.toString());
            this.qs1.cache();
            this.qs2.cache();
          },

          afterDeselect: function(values){
            weight_array.splice(weight_array.indexOf(values.toString()), 1);
            this.qs1.cache();
            this.qs2.cache();
          }

        });
      });

      $('#form-test-multi-select-code').multiSelect({

        selectableHeader: "<div class='custom-header'>可选</div>" + 
                          "<input type='text' class='search-input' autocomplete='off' placeholder='\"北京市\"'>",
        selectionHeader: "<div class='custom-header'>已选</div>" + 
                         "<input type='text' class='search-input' autocomplete='off' placeholder='\"上海市\"'>",

        afterInit: function(ms){
          var that = this,
          $selectableSearch = that.$selectableUl.prev(),
          $selectionSearch = that.$selectionUl.prev(),
          selectableSearchString = '#'+that.$container.attr('id')+' .ms-elem-selectable:not(.ms-selected)',
          selectionSearchString = '#'+that.$container.attr('id')+' .ms-elem-selection.ms-selected';

          that.qs1 = $selectableSearch.quicksearch(selectableSearchString)
          .on('keydown', function(e){
            if (e.which === 40){
              that.$selectableUl.focus();
              return false;
            }
          });

          that.qs2 = $selectionSearch.quicksearch(selectionSearchString)
          .on('keydown', function(e){
            if (e.which == 40){
              that.$selectionUl.focus();
              return false;
            }
          });
        },

        afterSelect: function(values){
          city_array.push(values.toString());

          this.qs1.cache();
          this.qs2.cache();

          //console.log(city_array.toString());
        },

        afterDeselect: function(values){
          city_array.splice(city_array.indexOf(values.toString()), 1);

          this.qs1.cache();
          this.qs2.cache();

          //console.log(city_array.toString());
        }
      });

      /*
      $('#save-city-submit', context).once('city-submit', function () {
      $('#save-city-submit').click(function(){


      });
      });
      */

    } //attach: function
  };

})(jQuery);
