import React, { useState, useEffect, useContext } from 'react';
import truncate from 'voca/truncate';
import { Mutation } from 'react-apollo';

import { ChatContext, SET_ACTIVE_CHAT } from '../../context/ChatContext';
import AssignQuestionMutation from '../../../shared/Apollo/mutation/assignQuestion';

import convertTimestampToDate from '../../../shared/utils/convertTimestampToDate';
import generateDateString from '../../../shared/utils/generateDateString';

const QuestionTeaser = ({
  canAssign,
  canSetActive,
  questionId,
  heading,
  text,
  createdAt,
}) => {
  const convertedDate = convertTimestampToDate(createdAt);
  const myConsultantId = '666';
  const [dateString, setDateString] = useState(
    generateDateString(convertedDate),
  );
  const [, dispatch] = useContext(ChatContext);

  useEffect(() => {
    // Update dateString every thirty second as time passes.
    const timer = setInterval(() => {
      setDateString(generateDateString(convertedDate));
    }, 1000 * 30);

    return () => clearInterval(timer);
  });

  const handleAssignQuestion = assign => {
    if (window.confirm('Vil du overtage dette spørgsmål?')) {
      assign({
        variables: {
          questionId: questionId,
          consultantId: myConsultantId,
        },
      });
    }
  };

  const handleSetActive = () => {
    dispatch({
      type: SET_ACTIVE_CHAT,
      payload: questionId,
    });
  };

  return (
    <Mutation mutation={AssignQuestionMutation}>
      {assignQuestion => (
        <div
          className="question question--teaser"
          onClick={() => {
            if (canAssign) {
              handleAssignQuestion(assignQuestion);
            }

            if (canSetActive) {
              handleSetActive();
            }
          }}
        >
          <div className="question__heading">
            <div className="question__heading__title">
              {truncate(heading, 32)}
            </div>
          </div>

          <div className="question__body">{truncate(text, 35)}</div>

          <small className="question__created-at">{dateString}</small>
        </div>
      )}
    </Mutation>
  );
};

export default QuestionTeaser;
