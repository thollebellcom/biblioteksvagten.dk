import React, { useContext } from 'react';

import { ChatContext, RESET_CHAT } from '../../../context/ChatContext';

const ReopenButton = ({ reopenQuestion }) => {
  const [state, dispatch] = useContext(ChatContext);

  const handleClick = event => {
    event.preventDefault();

    if (window.confirm('Vil du genåbne dette spørgsmål?')) {
      reopenQuestion({
        variables: {
          questionId: state.backendChat.questionId,
        },
      });

      dispatch({
        type: RESET_CHAT,
        payload: null,
      });
    }
  };

  return (
    <button
      className="backend-chat__button backend-chat__button--reopen-question"
      onClick={handleClick}
    >
      Forlad chat
    </button>
  );
};

export default ReopenButton;
