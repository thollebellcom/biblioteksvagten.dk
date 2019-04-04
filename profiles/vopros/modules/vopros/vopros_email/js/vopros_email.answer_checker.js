(function ($) {
  Drupal.behaviors.voprosEmailAnswerChecker = {
    attach: function (context, settings) {
      document.querySelector('#vopros-email-form').addEventListener('submit', function(event) {
        // event.preventDefault(); // Just for testing!!!!
        var subjectField = document.querySelector('input[name=subject]');
        var illegal = false;
        var $body = document.querySelector('body');

        if ($body.classList.contains('has-reminded')) return;

        // Check "subject" field.
        var subjectValue = subjectField.value;
        if (_isValid(subjectValue) !== true) {
          illegal = true;
        }

        // Check CKeditor field.
        if (typeof window.CKEDITOR != 'undefined') {
          var ckeditorValue = (CKEDITOR.instances['edit-email-content-value']).getData();

          if (_isValid(ckeditorValue) !== true) {
            illegal = true;
          }
        }

        if (illegal) {
          var answer = confirm(Drupal.t('It appears that one or more fields contains either e-mail, phone number or CPR number. Click OK if you still want to submit the form.'));

          if (! answer) {
            event.preventDefault();
          }
        }
        // else {
        //   var answer = confirm(Drupal.t('Have you checked that the inputs doesnt contain e-mails, phone numbers or CPR numbers? Click OK to continue.'));
        //
        //   if (! answer) {
        //     event.preventDefault();
        //   }
        // }

        $body.classList.add('has-reminded');
      });
    }
  };
})(jQuery);

function _isValid(value) {
  var isValid = true;

  if (_checkIfEmailInString(value)) {
    isValid = false;
  }
  if (/\d{8}/.test(value)) {
    isValid = false;
  }
  if (/\d{10}/.test(value)) {
    isValid = false;
  }

  return isValid;
}

// Grabbed from https://stackoverflow.com/questions/16424659/check-if-a-string-contains-an-email-address
function _checkIfEmailInString(text) {
  var re = /(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))/;

  return re.test(text);
}
