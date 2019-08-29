import React, { useState } from 'react';
import { Mutation } from 'react-apollo';

import CLOSE_QUESTION_MUTATION from '../../../../shared/Apollo/mutation/closeQuestion';
import REOPEN_QUESTION_MUTATION from '../../../../shared/Apollo/mutation/reopenQuestion';

import Modal from '../../Modal';
import CloseButton from './CloseButton';
import ReopenButton from './ReopenButton';
import AnswerLaterButton from './AnswerLaterButton';
import StandardAnswerList from './StandardAnswerList';

const Actions = () => {
  const [showStandardAnswers, setShowStandardAnswers] = useState(false);
  const [showActions, setShowActions] = useState(false);

  const handleToggleStandardAnswers = visible => {
    setShowActions(false);
    setShowStandardAnswers(visible);
  };
  const handleToggleActions = visible => {
    setShowStandardAnswers(false);
    setShowActions(visible);
  };

  return (
    <div className="backend-chat__actions">
      <div className="button-list">
        <div className="button-list__item">
          <Modal
            toggle={handleToggleStandardAnswers}
            visible={showStandardAnswers}
            title="Standard svar"
          >
            <StandardAnswerList
              modalToggle={handleToggleStandardAnswers}
              modalVisible={showStandardAnswers}
            />
          </Modal>

          <button
            className="backend-chat__button"
            onClick={() => handleToggleStandardAnswers(!showStandardAnswers)}
          >
            Standard svar
          </button>
        </div>
        <div className="button-list__item">
          <button
            className="backend-chat__button"
            onClick={() => handleToggleActions(!showActions)}
          >
            Afslut samtale
          </button>
          <Modal
            toggle={handleToggleActions}
            visible={showActions}
            title="Afslut samtalen"
          >
            <div className="button-list">
              <div className="button-list__item">
                <Mutation mutation={REOPEN_QUESTION_MUTATION}>
                  {reopenQuestion => (
                    <ReopenButton reopenQuestion={reopenQuestion} />
                  )}
                </Mutation>
              </div>
              <div className="button-list__item">
                <Mutation mutation={CLOSE_QUESTION_MUTATION}>
                  {(closeQuestion, { loading, data }) => (
                    <CloseButton
                      text="Luk grundet spam"
                      confirmText="Vil du lukke dette spørgsmål og markere spørgsmålet som spam?"
                      reason="spam"
                      closeQuestion={closeQuestion}
                      loading={loading}
                      data={data}
                    />
                  )}
                </Mutation>
              </div>
              <div className="button-list__item">
                <Mutation mutation={CLOSE_QUESTION_MUTATION}>
                  {(closeQuestion, { loading, data }) => (
                    <CloseButton
                      text="Luk som besvaret"
                      confirmText="Vil du lukke dette spørgsmål og markere spørgsmålet som besvaret?"
                      reason="answered"
                      closeQuestion={closeQuestion}
                      loading={loading}
                      data={data}
                    />
                  )}
                </Mutation>
              </div>
              <div className="button-list__item">
                <Mutation mutation={CLOSE_QUESTION_MUTATION}>
                  {(closeQuestion, { loading, data }) => (
                    <AnswerLaterButton
                      closeQuestion={closeQuestion}
                      loading={loading}
                      data={data}
                    />
                  )}
                </Mutation>
              </div>
            </div>
          </Modal>
        </div>
      </div>
    </div>
  );
};

export default Actions;
