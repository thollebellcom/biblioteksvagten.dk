import React, { useRef, useContext } from 'react';

import { ChatContext } from '../../context/ChatContext';

const Form = ({ createMessage, disabled }) => {
  const [state] = useContext(ChatContext);
  const messageInput = useRef(null);

  const handleSubmit = event => {
    event.preventDefault();

    createMessage({
      variables: {
        questionId: state.clientChat.questionId,
        text: messageInput.current.value,
        sentFrom: 'user',
      },
    });

    messageInput.current.value = '';
  };

  return (
    <div className="client-form">
      <form onSubmit={handleSubmit}>
        <input
          type="text"
          placeholder="Skriv en besked ..."
          required={true}
          ref={messageInput}
          disabled={disabled}
        />
      </form>
    </div>
  );
};

export default Form;
