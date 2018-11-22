/**
 * This file is used for misc. JS fixes.
 */
(function ($) {
  Drupal.behaviors.watchmenSearch = {
    attach: function (context, settings) {

      // Add autocomplete=off to /search date fields.
      var $searchForm = $('#views-exposed-form-vopros-search-solr-page');

      if ($searchForm.length > 0) {
        var $dateFields = $searchForm.find('.hasDatepicker');

        $dateFields.attr('autocomplete', 'off');
      }
    }
  };
})(jQuery);
