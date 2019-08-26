import React, { useState, useEffect, useContext } from 'react';
import truncate from 'voca/truncate';
import { Mutation } from 'react-apollo';

import { ChatContext, SET_ACTIVE_CHAT } from '../../context/ChatContext';
import AssignQuestionMutation from '../../../shared/Apollo/mutation/assignQuestion';
import NEW_MESSAGE_SUBSCRIPTION from '../../../shared/Apollo/subscription/newMessage';

import convertTimestampToDate from '../../../shared/utils/convertTimestampToDate';
import generateDateString from '../../../shared/utils/generateDateString';
import isOffline from '../../../shared/utils/calculateOffline';

const QuestionTeaser = ({
  canAssign,
  canSetActive,
  questionId,
  heading,
  text,
  source,
  createdAt,
  lastHeartbeat,
  subscribeToMore,
}) => {
  const convertedDate = convertTimestampToDate(createdAt);
  const myConsultantId = '666';
  const [hasUnreadMessages, setHasUnreadMessages] = useState(false);
  const [dateString, setDateString] = useState(
    generateDateString(convertedDate),
  );
  const [offline, setOffline] = useState(isOffline(lastHeartbeat));
  const [state, dispatch] = useContext(ChatContext);

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

  // Has unread messages.
  useEffect(() => {
    subscribeToMore({
      document: NEW_MESSAGE_SUBSCRIPTION,
      variables: {
        questionId,
      },
      updateQuery: (prev, { subscriptionData }) => {
        if (!subscriptionData.data) return prev;

        const { newMessage } = subscriptionData.data;

        // Message is sent by admin. (don't notify of own messages).
        if (newMessage.sentFrom === 'admin') {
          setHasUnreadMessages(false);

          return prev;
        }

        // The chat is open.
        if (state.backendChat && state.backendChat.questionId) {
          // It's the question viewed - no need to "new messages" for that.
          if (state.backendChat.questionId === newMessage.question.id) {
            setHasUnreadMessages(false);

            return prev;
          }
        }

        setHasUnreadMessages(true);

        return prev;
      },
    });
  }, [state]);

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

    setHasUnreadMessages(false);
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

          <div className="question__source">{truncate(source, 35)}</div>

          <small className="question__created-at">{dateString}</small>

          {hasUnreadMessages && (
            <small className="question__unread-messages">
              Der er ulæste beskeder
            </small>
          )}
        </div>
      )}
    </Mutation>
  );
};

export default QuestionTeaser;
