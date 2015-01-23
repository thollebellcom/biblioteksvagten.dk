/**
 * Styling.
 */
(function ($) {
  $(document).ready(function () {

    /**
     * Set active state/class to the chosen answer type.
     * This is done with JS due to the lack of IE8 support.
     */
    var active_answer_type = 'active_answer_type';
    var disabled_answer_type = 'disabled_answer_type';
    var answer_type = $('#edit-user-answer-preference');
    var answer_input = $('input', answer_type);

    // Set the active and disabled class to the checked radio on page load.
    answer_type.find('input:checked').parent().addClass(active_answer_type);

    // When the user clicks a new input, we want to remove the old state
    // and set the newly clicked input to active.
    answer_input.change(function() {
      if (!$(this).parent().hasClass(disabled_answer_type)) {
        answer_input.parent().removeClass(active_answer_type);
        $(this).parent().addClass(active_answer_type);
      }
    });

    /**
     * Title margin!
     *
     * Set the margin of the title after loading all images (the logo)
     * on the page.
     */
    $(window).load(function(){
      var header = $('.header');
      var title = $('#page-title');
      var header_height = parseFloat(header.outerHeight());
      var header_padding_top = parseFloat(header.css('padding-top'));
      var title_height = parseFloat(title.outerHeight());
      // Subtract title height from the header and divide it by 2.
      // Then subtract the header's top padding.
      title.css('margin-top', ((header_height - title_height) / 2) - header_padding_top);
    });

  });
})(jQuery);
