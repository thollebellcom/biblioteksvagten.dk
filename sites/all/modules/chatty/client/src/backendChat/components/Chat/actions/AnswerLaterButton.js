import React, { useContext, useState, useRef } from 'react';

import { ChatContext, RESET_CHAT } from '../../../context/ChatContext';

const AnswerLaterButton = ({ closeQuestion, data, loading }) => {
  const [state, dispatch] = useContext(ChatContext);
  const [showOptions, setShowOptions] = useState(false);
  const titleInputRef = useRef('');
  const keepConsultantRef = useRef('');

  if (!loading && data && data.closeQuestion.id) {
    dispatch({
      type: RESET_CHAT,
      payload: null,
    });
  }

  const showForm = event => {
    event.preventDefault();

    if (window.confirm('Vil du besvare dette spørgsmål senere?')) {
      setShowOptions(true);
    }
  };

  const handleSubmit = event => {
    event.preventDefault();

    closeQuestion({
      variables: {
        questionId: state.backendChat.questionId,
        reason: 'later',
        title: titleInputRef.current.value,
        keepConsultant: keepConsultantRef.current.checked,
      },
    });

    setShowOptions(false);
  };

  if (loading) {
    return (
      <button
        className="backend-chat__button backend-chat__button--answer-later"
        disabled
      >
        Vent venligst...
      </button>
    );
  }

  return (
    <div>
      <button
        className="backend-chat__button backend-chat__button--answer-later"
        onClick={showForm}
      >
        Besvar senere
      </button>

      {showOptions && (
        <form onSubmit={handleSubmit}>
          <div>
            <strong>Der er behov for ekstra informationer.</strong>

            <div>
              <label htmlFor="title">Titel</label>
              <input type="text" id="title" ref={titleInputRef} />
            </div>
            <div>
              <label htmlFor="keepConsultant">
                <input type="checkbox" id="keepConsultant" ref={keepConsultantRef} />
                Jeg besvarer selv spørgsmålet
              </label>
            </div>
          </div>
          <button type="submit">Send</button>
        </form>
      )}
    </div>
  );
};

export default AnswerLaterButton;
