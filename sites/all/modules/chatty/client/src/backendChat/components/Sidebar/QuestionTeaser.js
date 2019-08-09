import React, { useState, useEffect, useContext } from 'react';
import truncate from 'voca/truncate';
import { Mutation } from 'react-apollo';

import { ChatContext, SET_ACTIVE_CHAT } from '../../context/ChatContext';
import AssignQuestionMutation from '../../../shared/Apollo/mutation/assignQuestion';

import convertTimestampToDate from '../../../shared/utils/convertTimestampToDate';
import generateDateString from '../../../shared/utils/generateDateString';
import isOffline from '../../../shared/utils/calculateOffline';

const QuestionTeaser = ({
  canAssign,
  canSetActive,
  questionId,
  heading,
  text,
  createdAt,
  lastHeartbeat,
  consultantId,
}) => {
  const convertedDate = convertTimestampToDate(createdAt);
  const myConsultantId = '666';
  const [dateString, setDateString] = useState(
    generateDateString(convertedDate),
  );
  const [offline, setOffline] = useState(isOffline(lastHeartbeat));
  const [, dispatch] = useContext(ChatContext);

  // DateString.
  useEffect(() => {
    // Update dateString every thirty second as time passes.
    const timer = setInterval(() => {
      setDateString(generateDateString(convertedDate));
    }, 1000 * 30);

    return () => clearInterval(timer);
  });

  // Offline.
  useEffect(() => {
    // Check if we are now offline.
    const timer = setInterval(() => {
      setOffline(isOffline(lastHeartbeat));
    }, 1000 * 10);

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

  if (offline) {
    heading = truncate(heading, 20) + ' (offline)';
  } else {
    heading = truncate(heading, 32);
  }

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
            <div className="question__heading__title">{heading}</div>
          </div>

          <div className="question__body">{truncate(text, 35)}</div>

          <small className="question__created-at">{dateString}</small>
        </div>
      )}
    </Mutation>
  );
};

export default QuestionTeaser;
