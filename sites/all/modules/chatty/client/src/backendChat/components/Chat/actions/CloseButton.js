import React, { useContext } from 'react';

import { ChatContext, RESET_CHAT } from '../../../context/ChatContext';

const CloseButton = ({
  closeQuestion,
  confirmText,
  text,
  reason,
  data,
  loading,
}) => {
  const [state, dispatch] = useContext(ChatContext);

  if (!loading && data && data.closeQuestion.id) {
    dispatch({
      type: RESET_CHAT,
      payload: null,
    });
  }

  const handleClick = event => {
    event.preventDefault();

    if (window.confirm(confirmText)) {
      closeQuestion({
        variables: {
          reason,
          questionId: state.backendChat.questionId,
        },
      });
    }
  };

  if (loading) {
    return (
      <button
        className="backend-chat__button backend-chat__button--close-question"
        onClick={handleClick}
        disabled
      >
        Vent venligst...
      </button>
    );
  }

  return (
    <button
      className="backend-chat__button backend-chat__button--close-question"
      onClick={handleClick}
    >
      {text}
    </button>
  );
};

export default CloseButton;
