/*
 * py shopping multi select for nation area code
 */

(function($) {

  //for weight multi select
  Drupal.behaviors.edit_express_template = {
    attach: function(context, settings) {

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

            this.qs1.cache();
            this.qs2.cache();
          },

          afterDeselect: function(values){

            this.qs1.cache();
            this.qs2.cache();
          }

        });
      });

      $('#city-multi-select-code', context).once('city_multi_select', function () {

        $('#city-multi-select-code').multiSelect({

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

            this.qs1.cache();
            this.qs2.cache();

            //console.log(city_array.toString());
          },

          afterDeselect: function(values){

            this.qs1.cache();
            this.qs2.cache();

            //console.log(city_array.toString());
          }
        });
      });


    } //attach: function
  };

})(jQuery);

