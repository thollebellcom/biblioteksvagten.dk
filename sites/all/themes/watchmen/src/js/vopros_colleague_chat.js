/**
 * Based upon https://www.scaledrone.com/blog/javascript-chat-room-tutorial/
 */
const CLIENT_ID = 'bQcjq9NjKrmnGuDb';

const drone = new ScaleDrone(CLIENT_ID, {
  data: { // Will be sent out as clientData via events
    name: getWhoIAm(),
    color: getRandomColor(),
  },
});

let members = [];

drone.bind('open', error => {
  if (error) {
    return console.error(error);
  }
  console.log('Successfully connected to Scaledrone');

  const room = drone.subscribe('observable-room');
  room.bind('open', error => {
    if (error) {
      return console.error(error);
    }
    console.log('Successfully joined room');
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
    const index = members.findIndex(member => member.id === id);
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

drone.bind('close', event => {
  console.log('Connection was closed', event);
});

drone.bind('error', error => {
  console.error(error);
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

function getRandomColor() {
  return '#' + Math.floor(Math.random() * 0xFFFFFF).toString(16);
}

//------------- DOM STUFF

const DOM = {
  membersCount: document.querySelector('.members-count'),
  membersList: document.querySelector('.members-list'),
  messages: document.querySelector('.colleague-chat__messages'),
  input: document.querySelector('.colleague-chat__form__input'),
  form: document.querySelector('.colleague-chat__form'),
};

DOM.form.addEventListener('submit', sendMessage);

function sendMessage() {
  const value = DOM.input.value;
  if (value === '') {
    return;
  }
  DOM.input.value = '';
  drone.publish({
    room: 'observable-room',
    message: value,
  });
}

function createMemberElement(member) {
  const { name, color } = member.clientData;
  const el = document.createElement('div');
  el.appendChild(document.createTextNode(name));
  el.className = 'member';
  el.style.color = color;
  return el;
}

function updateMembersDOM() {
  DOM.membersCount.innerText = `${members.length} users in room:`;
  DOM.membersList.innerHTML = '';
  members.forEach(member =>
      DOM.membersList.appendChild(createMemberElement(member))
  );
}

function getWhoIAm() {
  const $chatWindow = jQuery('.colleague-chat');
  const name = $chatWindow.data('name');

  return name;
}

function createMessageElement(text, member) {
  const $chatWindow = jQuery('.colleague-chat');
  const el = document.createElement('div');
  const me = getWhoIAm();
  const { name } = member.clientData;
  el.appendChild(createMemberElement(member));
  el.appendChild(document.createTextNode(text));
  el.className = 'message';

  // If the message is created by someone else.
  if (name !== me) {

    // Update the message status, so when the chat is closed, you get a supple notification about the new message.
    if (! $chatWindow.hasClass('open')) {
      console.log('The window was closed, so we will add a supple notification...');

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

function addMessageToListDOM(text, member) {
  const el = DOM.messages;
  const wasTop = el.scrollTop === el.scrollHeight - el.clientHeight;
  el.appendChild(createMessageElement(text, member));
  if (wasTop) {
    el.scrollTop = el.scrollHeight - el.clientHeight;
  }
}

jQuery('.colleague-chat__heading').bind('click', function(event) {
  var $element = jQuery(this);
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
  const $chatWindow = jQuery('.colleague-chat');

  $chatWindow.addClass('open');
}
