/**
 *
 * This is not included with drupal_add_js, but outputted directly to
 * the browser. Some !variables will be replaced, @see
 * vopros_embed_question_modal_js().
 */

// Creating our own scope as to not pollute the global scope.
(function($) {
  var settings = !settings;

  // Add stylesheet for magnificPopup.
  $.each(settings.styles, function(index, style) {
    $('head').append('<link rel="stylesheet" href="' + style + '" type="text/css" />');
  });

  // Hack to make the volatile script not pollute the global namespace.
  var Drupal = {};
  !volatile;
  var volatile = Drupal.voprosEmbed.volatile;

  /**
   * Patch in confirmation to closing of popup when we're volatile.
   */
  $.magnificPopup.instance.close = function() {
    if (volatile.is()) {
      if (!confirm(settings.confirm_message)) {
        return;
      }
    }

    // We assume that we're nonvolatile when the popup requested to be closed.
    volatile.clearAll();
    $.magnificPopup.proto.close.call(this);
  }

  $(document).ready(function() {
    // Set up onmessage handler to close popup.
    $(window).on('message', function (e) {
      // jQuery doesn't know about the onmessage event, so the data
      // doesn't get copied to the JQ event. So we just look at the
      // original.
      if (e.originalEvent.data == 'vopros_embed_close') {
        $.magnificPopup.close();
      }
    });

    if (settings.add_tab) {
      $('body').append($('<span>').addClass('ask-vopros-tab-placeholder'));
    }

    // Replace tab placeholders with our own rendering.
    $('.ask-vopros-tab, .ask-vopros-tab-placeholder').each(function () {
      var tab = $(settings.tab).addClass('ask-vopros-tab');
      $(this).replaceWith(tab);
    });

    // Find any settings.
    var query = settings.query;
    if (typeof window.ask_vopros != "undefined") {
      $.each(window.ask_vopros, function (key, value) {
        query[key] = value;
      });
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
    var links = $('a[href*="' + settings.ask_url + '"]');
    links.querystring(query);

    if (popup) {
      links.magnificPopup({
        type: 'iframe',
        closeOnContentClick: false,
        closeOnBgClick: false,
        showCloseBtn: true,
        enableEscapeKey: false,
      });
    }
  });
})(jQuery.noConflict(true));
