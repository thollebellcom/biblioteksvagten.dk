(function ($) {
  Drupal.behaviors.voprosQuestion = {
    attach: function(context, settings) {
      $("#vopros-question-question-frontend-form .fake-form-item").tooltip({position: "right"});
      $("#vopros-question-question-frontend-form .fake-form-item").click(function() {
        $(this).parents('.fake-wrapper').hide().next().show();
      });
    }
  };
  Drupal.behaviors.voprosQuestionList = {
    attach: function(context, settings) {
      $("#views-exposed-form-vopros-question-list-page input.form-submit").hide();
      $("#views-exposed-form-vopros-question-list-page select, #views-exposed-form-vopros-question-list-page input").change(function() {
        $("#views-exposed-form-vopros-question-list-page input.form-submit").click();
        // We need to wait a little bit for IE to send the request and send
        // the request before disabling the dropdowns.
        setTimeout(function () {$("#views-exposed-form-vopros-question-list-page select").attr("disabled","disabled")}, 100);
      });
    }
  };
  Drupal.behaviors.voprosAnswerField = {
    attach: function(context, settings) {

      // Run the following after 3 seconds (we need to wait for CKeditor).
      setTimeout(function() {

        // Save the current value of the answer field.
        var $answer_field = CKEDITOR.instances['edit-answer-content-value'];
        var answer_on_pageload = $answer_field.getData();

        // Leaving the page
        $(window).bind('beforeunload', function(event){
          var answer_on_unload = $answer_field.getData();

          if (! answer_on_unload) {
            return Drupal.t('Du har ikke indtastet en besked. Er du sikker på at du vil forlade siden?');
          }

          if (answer_on_pageload != answer_on_unload) {
            return Drupal.t('Hvis du forlader siden, vil du miste det indtastede svar. Er du sikker på at du vil forlade siden?');
          }
        });

        // On form submit, we cancel the beforeunload event.
        $('form').submit(function(event) {
          var answer_on_submit = $answer_field.getData();

          // It's not an empty message, so we are okay unbinding.
          if (answer_on_submit) {
            $(window).unbind('beforeunload');

            return true;
          }
        });

      }, 3000);
    }
  };
})(jQuery);

