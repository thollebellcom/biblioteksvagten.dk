
/**
 * Add a close button to the page if we've been iframed.
 */
(function ($) {
  $(document).ready(function () {
    if (window != window.top) {
      $('.close-popup.element-hidden').each(function () {
        $(this).click(function (e) {
          e.preventDefault();
          // Post message to parent frame.
          window.top.postMessage('vopros_embed_close', '*');
          return false;
        }).removeClass('element-hidden');
      });
    }
  });
})(jQuery);
