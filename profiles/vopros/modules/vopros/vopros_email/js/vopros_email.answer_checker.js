(function ($) {
  Drupal.behaviors.voprosEmailAnswerChecker = {
    attach: function (context, settings) {
      document.querySelector('#vopros-email-form').addEventListener('submit', function(event) {
        var fields = ['input[name=subject]', 'textarea[name=email_content]'];
        var illegal = false;

        // Run through all the fields in the array.
        for (var int in fields) {
          var selector = fields[int];
          var field = document.querySelector(selector);

          if (field === null) continue;

          var value = field.value;

          // Perform checks
          if (_checkIfEmailInString(value)) {
            illegal = true;
          }
          if (/\d{8}/.test(value)) {
            illegal = true;
          }
          if (/\d{10}/.test(value)) {
            illegal = true;
          }
        }

        if (illegal) {
          var answer = confirm(Drupal.t('It appears that one or more fields contains either e-mail, phone number or CPR number. Click OK if you still want to submit the form.'));

          if (! answer) {
            event.preventDefault();
          }
        } else {
          var answer = confirm(Drupal.t('Have you checked that the inputs doesnt contain e-mails, phone numbers or CPR numbers? Click OK to continue.'));

          if (! answer) {
            event.preventDefault();
          }
        }
      });
    }
  };
})(jQuery);

// Grabbed from https://stackoverflow.com/questions/16424659/check-if-a-string-contains-an-email-address
function _checkIfEmailInString(text) {
  var re = /(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))/;

  return re.test(text);
}
