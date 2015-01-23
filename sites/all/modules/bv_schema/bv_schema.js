(function ($) {
  Drupal.behaviors.bVSchema = {
    attach: function(context, settings) {
      // Convert the string from drupal to JS function for beforeShowDay.
      if (Drupal.settings.datePopup) {
        $.each(Drupal.settings.datePopup, function (id) {
          if (Drupal.settings.datePopup[id].settings.beforeShowDay === 'onlyAllowMondays') {
            Drupal.settings.datePopup[id].settings.beforeShowDay = Drupal.behaviors.bVSchema.onlyAllowMondays;
          }
        });
      }
    },
    onlyAllowMondays: function (date) {
      // Only allow mondays
      return [date.getDay() === 1];
    }
  }
})(jQuery);
