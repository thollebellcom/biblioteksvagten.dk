import React, { useRef, useContext, useState } from 'react';
import TextareaAutosize from 'react-textarea-autosize';

import { ChatContext } from '../../context/ChatContext';

const Form = ({ createMessage, disabled }) => {
  const [state] = useContext(ChatContext);
  const [message, setMessage] = useState('');
  const formRef = useRef();

  const handleChange = event => setMessage(event.target.value);

  const handleKeyDown = event => {
    let eventFnc;

    // IE11 way to solve event creation. See: https://stackoverflow.com/a/49071358
    if (typeof (Event) === 'function') {
      eventFnc = new Event('submit');
    } else {
      eventFnc = document.createEvent('Event');
      eventFnc.initEvent('submit', true, true);
    }

    if (event.keyCode === 13 && !(event.keyCode === 13 && event.shiftKey)) {
      event.preventDefault();

      formRef.current.dispatchEvent(eventFnc);
    }
  };

  const handleSubmit = event => {
    event.preventDefault();

    if (message !== '') {
      createMessage({
        variables: {
          questionId: state.clientChat.questionId,
          text: message,
          sentFrom: 'user',
        },
      });

      // Clear the input.
      setMessage('');
    }
  };

  return (
    <div className="client-form">
      <form onSubmit={handleSubmit} ref={formRef}>
        <TextareaAutosize
          minRows={2}
          maxRows={5}
          value={message}
          placeholder="Indtast din besked..."
          onChange={handleChange}
          onKeyDown={handleKeyDown}
          disabled={disabled}
          autoFocus
        />
        <input type="submit" value="Send besked" />
      </form>
    </div>
  );
};

export default Form;
