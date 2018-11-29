/**
 * This file is used for misc. JS fixes.
 */
(function ($) {
  Drupal.behaviors.watchmenSearch = {
    attach: function (context, settings) {

      // Add autocomplete=off to /search date fields.
      var $searchForm = $('#views-exposed-form-vopros-search-solr-page');

      if ($searchForm.length > 0) {
        var $dateFields = $searchForm.find('.form-type-date-popup .form-text');

        $dateFields.attr('autocomplete', 'off');
      }
    }
  };
  Drupal.behaviors.watchmenDefaultSearchDates = {
    attach: function (context, settings) {
      var now = new Date();
      var now_year = now.getFullYear();
      var now_month = now.getMonth();
      var now_day = now.getDate();

      var formattedDate = now_month + '/' + now_day + '/' + now_year;
      var from_hour = '00:00';
      var to_hour = '23:59';

      // Add autocomplete=off to /search date fields.
      var $searchForm = $('#views-exposed-form-vopros-search-solr-page');

      if ($searchForm.length > 0) {
        var $dateFrom = $searchForm.find('.form-item-date-from-date input');
        var $timeFrom = $searchForm.find('.form-item-date-from-time input');
        var $dateTo = $searchForm.find('.form-item-date-to-date input');
        var $timeTo = $searchForm.find('.form-item-date-to-time input');

        // Dates.
        if ($dateFrom.val() === '') {
          $dateFrom.val(formattedDate);
        }
        if ($dateTo.val() === '') {
          $dateTo.val(formattedDate);
        }

        // Time.
        if ($timeFrom.val() === '') {
          $timeFrom.val(from_hour);
        }
        if ($timeTo.val() === '') {
          $timeTo.val(to_hour);
        }
      }
    }
  };
})(jQuery);
