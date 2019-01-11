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
      if ($('body').hasClass('page-admin-vopros-answers-edit')) {

        // Run the following after 10 seconds (we need to wait for CKeditor).
        // setTimeout(function () {
        //
        //   if (typeof window.CKEDITOR != 'undefined') {
        //
        //     // Save the current value of the answer field.
        //     var $answer_field = CKEDITOR.instances['edit-answer-content-value'];
        //
        //     if (!$answer_field) return;
        //
        //     var answer_on_pageload = $answer_field.getData();
        //
        //     // Leaving the page
        //     $(window).bind('beforeunload', function (event) {
        //       var answer_on_unload = $answer_field.getData();
        //
        //       if (!answer_on_unload) {
        //         return Drupal.t('Du har ikke indtastet en besked. Er du sikker på at du vil forlade siden?');
        //       }
        //
        //       if (answer_on_pageload != answer_on_unload) {
        //         return Drupal.t('Hvis du forlader siden, vil du miste det indtastede svar. Er du sikker på at du vil forlade siden?');
        //       }
        //     });
        //
        //     // On form submit, we cancel the beforeunload event.
        //     $('form').submit(function (event) {
        //       var answer_on_submit = $answer_field.getData();
        //
        //       // It's not an empty message, so we are okay unbinding.
        //       if (answer_on_submit) {
        //         $(window).unbind('beforeunload');
        //
        //         return true;
        //       }
        //     });
        //   }
        // }, 10000);
      }
    }
  };
  Drupal.behaviors.voprosAnswerFeed = {
    attach: function(context, settings) {
      var $outgoingFeedItems = $('.vopros-email-display.outgoing');
      var $ingoingFeedItems = $('.vopros-email-display.ingoing');

      $outgoingFeedItems.each(function(index, item) {
        var $item = $(this);

        $item.find('.type > .count').html(index + 1);
      });

      $ingoingFeedItems.each(function(index, item) {
        var $item = $(this);

        $item.find('.type > .count').html(index + 1);
      });
    }
  };
  Drupal.behaviors.voprosAnswerFeedDuplicateQuestion = {
    attach: function(context, settings) {
      if ($('body').hasClass('page-admin-vopros-answers-edit')) {
        var $question = $('.question-content');
        var $feedWrapper = $('#edit-question-feed').find('.fieldset-wrapper');
        var $newItem = $('<div class="vopros-email-display question"><div class="type">' + Drupal.t('Spørgsmål') + '</div><div class="body clearfix">' + $question.html() + '</div></div>');

        $feedWrapper.prepend($newItem);
      }
    }
  };
  Drupal.behaviors.voprosAnswerLatestResponse = {
    attach: function(context, settings) {
      if ($('body').hasClass('page-admin-vopros-answers-edit')) {
        var $responses = $('.vopros-email-display.ingoing');
        var numberOfResponses = $responses.length;
        var $questionContent = $('.question-content');

        // Only copy if we have a response.
        if (numberOfResponses > 0) {
          var $latestResponse = $responses[numberOfResponses - 1];
          var $copiedResponse = $('<div />').addClass('copied-latest-response').html($latestResponse);

          $copiedResponse.find('.type').html(Drupal.t('Seneste tilbagemelding fra bruger'));

          $questionContent.append($copiedResponse);
        }
      }
    }
  };
})(jQuery);

