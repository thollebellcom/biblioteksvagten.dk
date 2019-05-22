import React, { useContext } from 'react';

import { ChatContext, SET_CHAT_MESSAGE_TEXT } from '../../context/ChatContext';

const Form = ({ createMessage }) => {
  const [state, dispatch] = useContext(ChatContext);

  const handleChange = event => {
    dispatch({
      type: SET_CHAT_MESSAGE_TEXT,
      payload: event.target.value,
    });
  };

  const handleSubmit = event => {
    event.preventDefault();

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
  };

  return (
    <div className="backend-form">
      <form onSubmit={handleSubmit}>
        <input
          type="text"
          placeholder="Skriv en besked ..."
          required={true}
          value={state.backendChat.message}
          onChange={handleChange}
        />
      </form>
    </div>
  );
};

export default Form;
