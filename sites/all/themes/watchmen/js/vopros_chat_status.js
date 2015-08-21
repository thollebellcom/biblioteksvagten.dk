/**
 * @file
 * JavaScript for the Vopos embed form.
 */

(function ($) {
  /**
   * Theme function for rendering the extend status info.
   */
  Drupal.theme.prototype.voprosChatStatus = function (vars) {
    return $('<p>').html(vars.text).prepend('<i class="fa fa-4x fa-fw fa-exclamation-triangle"></i>');
  };

  /**
   * Change handler for radios to add classes for styling.
   */
  Drupal.behaviors.watchmenRadios = {
    attach: function (context, settings) {
      var change_handler = function () {
        var radios = $('.form-item-question-deadline .form-radios');
        radios.find('.form-item').removeClass('checked');
        radios.find('input[type=radio]:checked').closest('.form-item').addClass('checked');
      };
      // IE is as usually broken. Doesn't support change() on radios,
      // and we need to trigger the selection of radio button on label
      // click ourselves.
      if ($.browser.msie) {
        $('.form-item-question-deadline label').click(function() {
          $(this).closest('.form-item').find('input[type=radio]').attr('checked', 'checked');
          change_handler();
        });
      }
      else {
        $('.form-item-question-deadline input:radio').change(change_handler);
      }
      // Trigger default state.
      change_handler();
    }
  };

  /**
   * Change handler for checkboxes to add classes for styling.
   */
  Drupal.behaviors.watchmenCheckboxes = {
    attach: function (context, settings) {
      var change_handler = function () {
        $(this).closest('.form-item').toggleClass('checked', this.checked);
        // var checkboxes = $('#vopros-embed-question .form-checkbox');
        // checkboxes.find('input[type=radio]:checked').closest('.form-item').addClass('checked');
      };
      $('#vopros-embed-question input:checkbox').change(change_handler);
      // Trigger default state.
      change_handler();
    }
  };

})(jQuery);
