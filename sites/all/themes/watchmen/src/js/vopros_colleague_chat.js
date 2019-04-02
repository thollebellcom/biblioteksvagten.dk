/**
 * Based upon https://www.scaledrone.com/blog/javascript-chat-room-tutorial/
 */
(function ($) {
  Drupal.behaviors.watchmenColleagueChat = {
    attach: function (context, settings) {
      const CLIENT_ID = 'bQcjq9NjKrmnGuDb';
      // const CLIENT_ID = 'rjgNL0l5SPR7XzY9'; // Development only!

      const drone = new ScaleDrone(CLIENT_ID, {
        data: { // Will be sent out as clientData via events
          name: getWhoIAm(),
        },
      });

      let members = [];

      drone.bind('open', error => {
        if (error) {
          return console.error(error);
        }

        const room = drone.subscribe('observable-room', {
          historyCount: 8 // ask for the 8 latest messages from history
        });
        room.bind('open', error => {
          if (error) {
            return console.error(error);
          }
        });

        room.bind('history_message', message => {
          let { name, text, date } = message.data;

          if (date === undefined) {
            date = null;
          }

          if (name !== undefined && text !== undefined) {
            addHistoryToListDOM(name, text, date);
          } else {
            console.error('Name or text undefined');
            console.error('Name:', name);
            console.error('Text:', text);
            console.error('Date:', date);
          }
        });

        room.bind('members', m => {
          members = m;

          updateMembersDOM();
        });

        room.bind('member_join', member => {
          members.push(member);

          updateMembersDOM();
        });

        room.bind('member_leave', ({id}) => {
          // const index = members.findIndex(member => member.id === id);
          const index = _.findIndex(members, member => member.id === id);
          members.splice(index, 1);

          updateMembersDOM();
        });

        room.bind('data', (text, member) => {
          if (member) {
            addMessageToListDOM(text, member);
          } else {
            // Message is from server
          }
        });
      });

      drone.bind('close');

      drone.bind('error', error => {
        console.error(error);
      });

      // Leaving the page
      $(window).bind('beforeunload', function (event) {
        drone.close();
      });

      function getRandomName() {
        const adjs = ["autumn", "hidden", "bitter", "misty", "silent", "empty", "dry", "dark", "summer", "icy", "delicate", "quiet", "white", "cool", "spring", "winter", "patient", "twilight", "dawn", "crimson", "wispy", "weathered", "blue", "billowing", "broken", "cold", "damp", "falling", "frosty", "green", "long", "late", "lingering", "bold", "little", "morning", "muddy", "old", "red", "rough", "still", "small", "sparkling", "throbbing", "shy", "wandering", "withered", "wild", "black", "young", "holy", "solitary", "fragrant", "aged", "snowy", "proud", "floral", "restless", "divine", "polished", "ancient", "purple", "lively", "nameless"];
        const nouns = ["waterfall", "river", "breeze", "moon", "rain", "wind", "sea", "morning", "snow", "lake", "sunset", "pine", "shadow", "leaf", "dawn", "glitter", "forest", "hill", "cloud", "meadow", "sun", "glade", "bird", "brook", "butterfly", "bush", "dew", "dust", "field", "fire", "flower", "firefly", "feather", "grass", "haze", "mountain", "night", "pond", "darkness", "snowflake", "silence", "sound", "sky", "shape", "surf", "thunder", "violet", "water", "wildflower", "wave", "water", "resonance", "sun", "wood", "dream", "cherry", "tree", "fog", "frost", "voice", "paper", "frog", "smoke", "star"];
        return (
            adjs[Math.floor(Math.random() * adjs.length)] +
            "_" +
            nouns[Math.floor(Math.random() * nouns.length)]
        );
      }

      //------------- DOM STUFF

      const DOM = {
        membersCount: document.querySelector('.colleague-chat__members-count'),
        membersList: document.querySelector('.colleague-chat__members-list'),
        messages: document.querySelector('.colleague-chat__messages'),
        input: document.querySelector('.colleague-chat__form__input'),
        form: document.querySelector('.colleague-chat__form'),
      };

      DOM.form.addEventListener('submit', sendMessage);

      function sendMessage() {
        const value = DOM.input.value;
        const sender = getWhoIAm();
        // const sender = getRandomName();
        const date = new Date();

        if (value === '') {
          return;
        }

        let message = {
          name: sender,
          text: value,
          date: date,
        };

        DOM.input.value = '';
        drone.publish({
          room: 'observable-room',
          message: message,
        });
      }

      function createMemberElement(member) {
        const { name } = member.clientData;
        const el = document.createElement('div');
        const me = getWhoIAm();
        let color = 'gray';

        if (me === name) {
          color = '#7394D0';
          el.className = 'member me';
        } else {
          el.className = 'member';
        }

        el.appendChild(document.createTextNode(name));
        el.style.color = color;

        return el;
      }

      function createHistoryMemberElement(name) {
        const el = document.createElement('div');
        const me = getWhoIAm();
        let color = 'gray';

        if (me === name) {
          color = '#7394D0';
        }

        el.appendChild(document.createTextNode(name));
        el.className = 'member';
        el.style.color = color;

        return el;
      }

      function createDateElement(date) {
        const el = document.createElement('div');

        if (! date) {
          return el;
        }

        const dateObj = new Date(date);
        const formattedDate = dateFns.format(dateObj, 'DD.MM.YYYY kl. HH:m'); // Ex. 25.12.2018 kl. 09:50

        el.appendChild(document.createTextNode(formattedDate));
        el.className = 'date';

        return el;
      }

      function updateMembersDOM() {
        let membersAdded = [];

        DOM.membersCount.innerText = 'Brugere online:';
        DOM.membersList.innerHTML = '';

        // Run through the member list.
        members.forEach(member => {
          if (typeof member.clientData !== 'undefined') {

            // Don't add duplicates.
            if (! _.find(membersAdded, { 'name': member.clientData.name })) {

              // Insert into DOM.
              DOM.membersList.appendChild(createMemberElement(member));

              // Add for later reference.
              membersAdded.push(member.clientData);
            }
          }
        });
      }

      function getWhoIAm() {
        const $chatWindow = $('.colleague-chat');
        const name = $chatWindow.data('name');

        if (name === undefined) {
          return 'Anonym';
        }

        return name;
      }

      function createMessageElement(text, member, date) {
        const $chatWindow = $('.colleague-chat');
        const el = document.createElement('div');
        const me = getWhoIAm();
        const { name } = member.clientData;
        el.appendChild(createDateElement(date));
        el.appendChild(createMemberElement(member));
        el.appendChild(document.createTextNode(text.text));
        el.className = 'message';

        // If the message is created by someone else.
        if (name !== me) {

          // Update the message status, so when the chat is closed, you get a supple notification about the new message.
          if (! $chatWindow.hasClass('open')) {
            $chatWindow.find('.colleague-chat__message-status').html('(ulæste beskeder)');
          }

          // Add a blinking background color.
          let int = 0;
          const updateStatus = setInterval(function(){
            $chatWindow.toggleClass("colleague-chat--new-message");

            if (int > 4) {
              clearInterval(updateStatus);
            }

            int++;
          }, 300);
        }

        return el;
      }

      function createHistoryMessageElement(text, name, date) {
        const el = document.createElement('div');
        el.appendChild(createDateElement(date));
        el.appendChild(createHistoryMemberElement(name));
        el.appendChild(document.createTextNode(text));
        el.className = 'message';

        return el;
      }

      function addMessageToListDOM(text, member) {
        const { date } = text;
        const el = DOM.messages;
        var content = document.getElementsByClassName("colleague-chat__content")[0];
        el.appendChild(createMessageElement(text, member, date));

        // Scroll to bottom of div when message was added to the DOM.
        content.scrollTop = content.scrollHeight;
      }

      function addHistoryToListDOM(name, text, date) {
        const $messages = $('.colleague-chat__messages');
        const messagesTextContent = DOM.messages.textContent;
        const newMessage = createHistoryMessageElement(text, name, date);
        const newMessageTextContent = newMessage.textContent;

        // Only add, if it is not previously added.
        if (_doesNotInclude(messagesTextContent, newMessageTextContent)) {
          $messages.append(newMessage);
        }
      }

      $('.colleague-chat__heading').bind('click', function(event) {
        var $element = $(this);
        var $chatWindow = $element.parents('.colleague-chat');
        var $messageStatus = $chatWindow.find('.colleague-chat__message-status');

        $chatWindow.toggleClass('open');

        // Resets the message status.
        $messageStatus.html('');

        // We need to set a session, so we can remember if the chat should be open or not.
        // This is most useful if the user is navigating around the site.
        var isOpen = $chatWindow.hasClass('open') ? 'true' : 'false';

        sessionStorage.setItem("chat_window_open", isOpen);
      });

      // On load.
      if (sessionStorage.getItem('chat_window_open') === 'true') {
        const $chatWindow = $('.colleague-chat');

        $chatWindow.addClass('open');
      }

      function _includes(container, value) {
        var returnValue = false;
        var pos = container.indexOf(value);
        if (pos >= 0) {
          returnValue = true;
        }
        return returnValue;
      }

      function _doesNotInclude(container, value) {
        var returnValue = false;
        var pos = container.indexOf(value);
        if (pos < 0) {
          returnValue = true;
        }
        return returnValue;
      }
    }
  };
})(jQuery);
