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
      var now_month = now.getMonth() + 1;
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
          $dateFrom.val('1/1/2010');
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
  Drupal.behaviors.watchmenSearchHTMLEntityDecode = {
    attach: function (context, settings) {
      var view = document.querySelector('.view-vopros-search-solr');

      if (view) {
        var questionContents = view.querySelectorAll('.views-field-question-question-content span');

        if (questionContents !== null) {
          var decodeHTML = function (html) {
            var txt = document.createElement('textarea');
            txt.innerHTML = html;

            return txt.value;
          };

          questionContents.forEach(function(el) {
            var markup = el.innerHTML;
            var decodedMarkup = decodeHTML(markup);

            el.innerHTML = decodedMarkup;
          });
        }
      }
    }
  };
  Drupal.behaviors.setAutocomplete = {
    attach: function (context, settings) {
      var $input = $('#edit-bv-schema-date-datepicker-popup-0');

      $input.attr('autocomplete', 'off');
    }
  };
  Drupal.behaviors.exportAsCSV = {
    attach: function (context, settings) {
      function exportTableToCSV($table, filename) {
        var $headers = $table.find('tr:has(th)')
            ,$rows = $table.find('tr:has(td)')

            // Temporary delimiter characters unlikely to be typed by keyboard
            // This is to avoid accidentally splitting the actual contents
            ,tmpColDelim = String.fromCharCode(11) // vertical tab character
            ,tmpRowDelim = String.fromCharCode(0) // null character

            // actual delimiter characters for CSV format
            ,colDelim = '","'
            ,rowDelim = '"\r\n"';

        // Grab text from table into CSV formatted string
        var csv = '"';
        csv += formatRows($headers.map(grabRow));
        csv += rowDelim;
        csv += formatRows($rows.map(grabRow)) + '"';

        // Data URI
        var csvData = 'data:application/csv;charset=utf-8,' + encodeURIComponent(csv);

        // For IE (tested 10+)
        if (window.navigator.msSaveOrOpenBlob) {
          var blob = new Blob([decodeURIComponent(encodeURI(csv))], {
            type: "text/csv;charset=utf-8;"
          });
          navigator.msSaveBlob(blob, filename);
        } else {
          $(this)
              .attr({
                'download': filename
                ,'href': csvData
                //,'target' : '_blank' //if you want it to open in a new window
              });
        }

        //------------------------------------------------------------
        // Helper Functions
        //------------------------------------------------------------
        // Format the output so it has the appropriate delimiters
        function formatRows(rows){
          return rows.get().join(tmpRowDelim)
              .split(tmpRowDelim).join(rowDelim)
              .split(tmpColDelim).join(colDelim);
        }
        // Grab and format a row from the table
        function grabRow(i,row){

          var $row = $(row);
          //for some reason $cols = $row.find('td') || $row.find('th') won't work...
          var $cols = $row.find('td');
          if(!$cols.length) $cols = $row.find('th');

          return $cols.map(grabCol)
              .get().join(tmpColDelim);
        }
        // Grab and format a column from the table
        function grabCol(j,col){
          var $col = $(col),
              $text = $col.text();

          return $text.replace('"', '""'); // escape double quotes

        }
      }

      // Format ugly views table.
      var $container = $('.view-display-id-page_statistics .view-content');
      var $newTable = $('<table />');

      // Remove zero as an option.
      $container.find('table').first().remove();

      var $tables = $container.find('table');

      // Insert thead
      $newTable.append($('<thead><th>Anmeldelse</th><th>Rating</th></thead>'));

      $tables.find('caption').remove();

      $tables.each(function(index, item) {
        var $innerContent = item.innerHTML;

        $newTable.append($innerContent);
      });

      $tables.remove();

      $container.append($newTable);

      // Click event triggers a download.
      $('.view-display-id-page_statistics .download-as-csv').click(function (event) {
        event.preventDefault();

        // Export as CSV.
        var options = {
          "filename": "eksport.csv",
        };
        $('.view-display-id-page_statistics .view-content table')
            .first()
            .table2csv('download', options);
      });
    }
  };
})(jQuery);
