(function($) {

Drupal.wechat_py_shopping = Drupal.wechat_py_shopping || {};


/*
Drupal.wechat_py_shopping.filesAddedCallback = function (up, files) {
  setTimeout(function(){up.start()}, 100);
};
Drupal.wechat_py_shopping.uploadCompleteCallback = function(up, files){
  console.log(up);

}
*/

/**
 * Attaches the Plupload behavior to each FileField Sources Plupload form element.
 */
Drupal.behaviors.wechat_py_shopping = {
  attach: function (context, settings) {
    $(".adv-image-upload-file .plupload-element", context).once('adv-img-plupload-init', function () {

      // Merge the default settings and the element settings to get a full
      // settings object to pass to the Plupload library for this element.
      var id = $(this).attr('id');
      var defaultSettings = settings.plupload['_default'] ? settings.plupload['_default'] : {};

      var elementSettings = (id && settings.plupload[id]) ? settings.plupload[id] : {};
      var pluploadSettings = $.extend({}, defaultSettings, elementSettings);

      // Initialize Plupload for this element.
      $(this).pluploadQueue(pluploadSettings);
      // Hide upload button. We will do this using uploader.start()
      $(this).find('.plupload_start').hide();
      // While we are at it, hide the redundant file validation help
      //$(this).closest('.adv-image-upload-file').find('div.description').hide();

      // Add button.
      var add_button = $(this).find('.plupload_button.plupload_add');

      // Intercept the submit to start uploading and ensure all files are done
      // uploading before triggering the ajax form update.
      //var submit = settings.plupload[id].submit_element;
      var $submit = $(this).closest('.adv-image-upload-file').find('.form-submit');

      var uploader_element = $(this).closest('.adv-image-upload-file').find('.plupload-element');
      var uploader = uploader_element.pluploadQueue();
      // Refresh for IE8
      uploader.refresh();

      uploader.bind('QueueChanged', function() {
        // If cardinality is NOT unlimited.
        if (pluploadSettings.cardinality > 0) {
          // Remove files exceeding the cardinality setting.
          if (uploader.files.length >= pluploadSettings.cardinality) {
            var i = 0;
            for (i=0;i<uploader.files.length;i++) {
              if (i >= pluploadSettings.cardinality) {
                uploader.removeFile(uploader.files[i]);
              }
            }
            add_button.hide();
          }
          else {
            add_button.show();
          }
        }
      });

/*
      $submit.bind('click', function(e) {
        e.preventDefault();

        uploader.bind('StateChanged', function() {
          if (uploader.total.uploaded == uploader.files.length) {
            // Custom ajax trigger
            //$submit.trigger('pud_update');
          }
        });
        if (uploader.files.length > 0) {
          $submit.val(Drupal.t('Uploading...'));
          uploader.start();
        }
        return true;
      });
*/

    });
  }
}

Drupal.behaviors.pluploadform = {
  attach: function(context, settings) {
    $('form', context).once('plupload-form', function() {
      var l1 = $(this).find('.plupload-element').length;
      if (0 < $(this).find('.plupload-element').length) {
        var $form = $(this);
        var originalFormAttributes = {
            'method': $form.attr('method'),
            'enctype': $form.attr('enctype'),
            'action': $form.attr('action'),
            'target': $form.attr('target')
        };

        $(this).submit(function(e) {
          var completedPluploaders = 0;
          var totalPluploaders = $(this).find('.plupload-element').length;
          var errors = '';

          $(this).find('.plupload-element').each( function(index){
            var uploader = $(this).pluploadQueue();

            var id = $(this).attr('id');
            var defaultSettings = settings.plupload['_default'] ? settings.plupload['_default'] : {};
            var elementSettings = (id && settings.plupload[id]) ? settings.plupload[id] : {};
            var pluploadSettings = $.extend({}, defaultSettings, elementSettings);

            //Only allow the submit to proceed if there are files and they've all
            //completed uploading.
            //TODO: Implement a setting for whether the field is required, rather
            //than assuming that all are.
            if (uploader.state == plupload.STARTED) {
              errors += Drupal.t("Please wait while your files are being uploaded.");
            }
            else if (uploader.files.length == 0 && !pluploadSettings.required) {
              completedPluploaders++;
            }

            else if (uploader.files.length == 0) {
              errors += Drupal.t("@index: You must upload at least one file.\n",{'@index': (index + 1)});
            }

            else if (uploader.files.length > 0 && uploader.total.uploaded == uploader.files.length) {
              completedPluploaders++;
            }

            else {
              var stateChangedHandler = function() {
                if (uploader.total.uploaded == uploader.files.length) {
                  uploader.unbind('StateChanged', stateChangedHandler);
                  completedPluploaders++;
                  if (completedPluploaders == totalPluploaders ) {
                    //Plupload's html4 runtime has a bug where it changes the
                    //attributes of the form to handle the file upload, but then
                    //fails to change them back after the upload is finished.
                    for (var attr in originalFormAttributes) {
                      $form.attr(attr, originalFormAttributes[attr]);
                    }
                    // Click a specific element if one is specified.
                    if (settings.plupload[id].submit_element) {
                      $(settings.plupload[id].submit_element).click();
                    }
                    else {
                      $form.submit();
                    }
                    return true;
                  }
                }
              };
              uploader.bind('StateChanged', stateChangedHandler);
              uploader.start();
            }

          });
          if (completedPluploaders == totalPluploaders) {
            //Plupload's html4 runtime has a bug where it changes the
            //attributes of the form to handle the file upload, but then
            //fails to change them back after the upload is finished.
            for (var attr in originalFormAttributes) {
              $form.attr(attr, originalFormAttributes[attr]);
            }
            return true;
          }
          else if (0 < errors.length){
            alert(errors);
          }

          return false;
        });
      }
    });
  }
};

})(jQuery);
