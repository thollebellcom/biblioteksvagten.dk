
/**
 * Add a close button to the page if we've been iframed.
 */
(function ($) {
  $(document).ready(function () {
    if (window != window.top) {
      var close_button = $('<a href="#">').text(Drupal.t('Close window'));
      close_button.click(function () {
        // Post message to parent frame.
        window.top.postMessage('ask_vopros_close', '*');
      });

      $('#content').append(close_button.wrap('<p></p>').parent().get(0));
    }
  });
})(jQuery);
