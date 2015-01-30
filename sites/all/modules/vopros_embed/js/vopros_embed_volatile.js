(function ($) {

  var isTop = null;
  var isVolatile = null;
  var clients = [];
  /**
   * Client handle.
   */
  var volatileClient = function(message) {
    this.volatile = false;
    this.message = message ? message : "";
  };

  volatileClient.prototype.message = function(message) {
    this.message = message ? message : "";
  };

  volatileClient.prototype.set = function(state) {
    // Ensure we have a bolean.
    this.volatile = !!state;
    volatile.upstream();
  };

  volatileClient.prototype.is = function() {
    return this.volatile;
  };

  Drupal.voprosEmbed = Drupal.voprosEmbed || {};
  Drupal.voprosEmbed.volatile = Drupal.voprosEmbed.volatile || {};
  // Convenience var.
  var volatile = Drupal.voprosEmbed.volatile;

  /**
   * Beforeunload handler.
   *
   * Asks for confirmation if we're volatile.
   */
  var beforeunload = function(e) {
    var e = e || window.event;
    var messages = [];
    for (var index = 0; index < clients.length; ++index) {
      if (clients[index].is()) {
        messages.push(clients[index].message);
      }
    }

    if (messages.length > 0) {
      var message = messages.join("\n\n");
      // For IE and Firefox prior to version 4
      if (e) {
        e.returnValue = message;
      }

      // Apparently we need to return at least an empty string to trigger.
      return message + " ";
    }
    return;
  };

  /**
   * Initialize.
   *
   * If we're the top window, set an beforeunload handler to catch the
   * user leaving the page, and set up a cross frame listener to
   * listen for popup requesting to set the volatility.
   */
  volatile.init = function () {
    isTop = window === window.top;
    if (isTop) {
      // We're our own client.
      var client = volatile.client();

      // Listen for messages from other frames to set volatility.
      $(window).bind('message', function (e) {
        var data = e.originalEvent.data;
        if (typeof data.type === 'undefined' || data.type !== 'vopros_embed_volatile') {
          return;
        }
        client.message = data.message;
        client.set(data.state);
      });

      // Bind our handler.
      $(window).bind('beforeunload', beforeunload);
    }
  };

  /**
   * Get a client handle.
   */
  volatile.client = function(message) {
    var cl = new volatileClient(message);
    clients.push(cl);
    return cl;
  };

  /**
   * Update volatility info in a possible parent frame.
   */
  volatile.upstream = function () {
    if (!isTop)  {
      var messages = [];
      for (var index = 0; index < clients.length; ++index) {
        if (clients[index].is()) {
          messages.push(clients[index].message);
        }
      }

      // Post message to parent frame.
      var message = {
        type: 'vopros_embed_volatile',
        state: false,
        message: ""
      };

      if (messages.length > 0) {
        message.message = messages.join("\n\n");
        message.state = true;
      }

      window.top.postMessage(message, '*');
      return true;
    }

    return false;
  };

  /**
   * Query volatility.
   *
   * Returns whether we're volatile or not.
   */
  volatile.is = function () {
    for (var index = 0; index < clients.length; ++index) {
      if (clients[index].is()) {
        return true;
      }
    }
    return false;
  };

  volatile.clearAll = function() {
    for (var index = 0; index < clients.length; ++index) {
      clients[index].set(false);
    }
  }

  volatile.init();

})(jQuery);
