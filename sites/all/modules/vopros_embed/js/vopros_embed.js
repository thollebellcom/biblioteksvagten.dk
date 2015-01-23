/**
 *
 * This is not included with drupal_add_js, but outputted directly to
 * the browser. Some !variables will be replaced, @see
 * vopros_embed_question_modal_js().
 */

// Creating our own scope as to not pollute the global scope.
(function() {
  var $ = jQuery.noConflict(true);

  // Add stylesheet for magnificPopup.
  $('head').append('<link rel="stylesheet" href="!mag_style" type="text/css" />');
  // Add our own CSS.
  $('head').append('<link rel="stylesheet" href="!vopros_style" type="text/css" />');


  $(document).ready(function() {
    // Set up onmessage handler to close popup.
    $(window).on('message', function (e) {
      // jQuery doesn't know about the onmessage event, so the data
      // doesn't get copied to the JQ event. So we just look at the
      // original.
      if (e.originalEvent.data == 'ask_vopros_close') {
        $.magnificPopup.close();
      }
    });

    // Find any settings.
    var query = {};
    if (typeof window.ask_vopros != "undefined") {
      query = window.ask_vopros;
    }

    var popup = false;
    // Simple responsive: If the window is small, don't use the popup,
    // but let the link function normally instead.
    if (screen.width > 500) {
      query.popup = 'y';
      popup = true;
    }

    // URL is always set to the current location.
    query.url = window.location.href;

    // Fix urls and attach Magnific popup to the link.
    var links = $('a[href*="!ask_url"]');
    links.querystring(query);
    if (popup) {
      links.magnificPopup({
        type: 'iframe',
      });
    }
  });
})();
