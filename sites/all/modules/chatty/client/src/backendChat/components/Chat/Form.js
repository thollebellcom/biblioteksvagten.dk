import React, { useContext, useRef } from 'react';
import TextareaAutosize from 'react-textarea-autosize';

import { ChatContext, SET_CHAT_MESSAGE_TEXT } from '../../context/ChatContext';

const Form = ({ createMessage }) => {
  const [state, dispatch] = useContext(ChatContext);
  const formRef = useRef();

  const handleChange = event => {
    dispatch({
      type: SET_CHAT_MESSAGE_TEXT,
      payload: event.target.value,
    });
  };

  const handleKeyDown = event => {
    let eventFnc;

    // IE11 way to solve event creation. See: https://stackoverflow.com/a/49071358
    if (typeof (Event) === 'function') {
      eventFnc = new Event('submit');
    } else {
      eventFnc = document.createEvent('Event');
      eventFnc.initEvent('submit', true, true);
    }

    // enter (submit) - NOT when using shift.
    if (event.keyCode === 13 && !(event.keyCode === 13 && event.shiftKey)) {
      event.preventDefault();
      
      formRef.current.dispatchEvent(eventFnc);
    }
  };

  const handleSubmit = event => {
    event.preventDefault();

    if (state.backendChat.message !== '') {
      createMessage({
        variables: {
          questionId: state.backendChat.questionId,
          text: state.backendChat.message,
          sentFrom: 'admin',
        },
      });

      // Clear the input.
      dispatch({
        type: SET_CHAT_MESSAGE_TEXT,
        payload: '',
      });
    }
  };

  return (
    <div className="backend-form">
      <form onSubmit={handleSubmit} ref={formRef}>
        <TextareaAutosize
          minRows={2}
          maxRows={5}
          value={state.backendChat.message}
          placeholder="Indtast din besked..."
          onChange={handleChange}
          onKeyDown={handleKeyDown}
          autoFocus
        />
      </form>
    </div>
  );
};

export default Form;
