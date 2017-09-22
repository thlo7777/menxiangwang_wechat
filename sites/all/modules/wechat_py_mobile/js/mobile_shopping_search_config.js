//mobile_shopping_search_config.js

(function($){

  $(document).on( "mobileinit", function() {
 
    //config search local storage for home page search function
    //only read initialize data for first open shopping home page
    console.log($.jStorage.get("hello"));
    alert('first open home page');
  });

})(jQuery);


