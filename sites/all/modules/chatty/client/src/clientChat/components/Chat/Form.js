import React, { useRef, useContext, useState } from 'react';
import TextareaAutosize from 'react-textarea-autosize';

import { ChatContext } from '../../context/ChatContext';

const Form = ({ createMessage, disabled }) => {
  const [state] = useContext(ChatContext);
  const [message, setMessage] = useState('');
  const formRef = useRef();

  const handleChange = event => setMessage(event.target.value);

  const handleKeyDown = event => {

    // cmd / Windows + enter || ctrl + enter.
    if ((event.keyCode === 13 && event.metaKey) || (event.keyCode === 13 && event.ctrlKey)) {
      formRef.current.dispatchEvent(new Event('submit'));
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
        />
      </form>
    </div>
  );
};

export default Form;
