import React, { useEffect, useContext } from 'react';

import NEW_MESSAGE_SUBSCRIPTION from '../../../shared/Apollo/subscription/newMessage';
import QUESTION_CLOSED_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionClosed';
import QUESTION_ASSIGNED_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionAssigned';
import QUESTION_REOPENED_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionReopened';
import { ChatContext } from '../../context/ChatContext';
import { RESET_CHAT } from '../../../backendChat/context/ChatContext';

import Message from './Message';
import scrollToBottom from '../../../shared/utils/scrollToBottom';

const MessageList = ({
  disabled,
  subject,
  questionCreatedAt,
  messages,
  subscribeToMore,
}) => {
  const [state, dispatch] = useContext(ChatContext);

  useEffect(() => {
    // New message.
    subscribeToMore({
      document: NEW_MESSAGE_SUBSCRIPTION,
      variables: {
        questionId: state.clientChat.questionId,
      },
      updateQuery: (prev, { subscriptionData }) => {
        if (!subscriptionData.data) return prev;

        const newObject = Object.assign({}, prev, {
          ...prev,
          question: {
            ...prev.question,
            messages: [
              subscriptionData.data.newMessage,
            ],
          },
        });

        if (prev.question.messages) {
          newObject.question.messages = [
            ...prev.question.messages,
            subscriptionData.data.newMessage,
          ];
        }

        return newObject;
      },
    });

    // Question assigned.
    subscribeToMore({
      document: QUESTION_ASSIGNED_SUBSCRIPTION,
      variables: {
        questionId: state.clientChat.questionId,
      },
      updateQuery: (prev, { subscriptionData }) => {
        if (!subscriptionData.data) return prev;

        return Object.assign({}, prev, {
          ...prev,
          question: {
            ...prev.question,
            ...subscriptionData.data.questionAssigned,
          },
        });
      },
    });

    // Close question.
    subscribeToMore({
      document: QUESTION_CLOSED_SUBSCRIPTION,
      variables: {
        questionId: state.clientChat.questionId,
      },
      updateQuery: (prev, { subscriptionData }) => {
        if (!subscriptionData.data) return prev;

        // Reset the chat.
        dispatch({
          type: RESET_CHAT,
          payload: null,
        });

        return Object.assign({}, prev, {
          ...prev,
          question: null,
        });
      },
    });

    // Question repeoned.
    subscribeToMore({
      document: QUESTION_REOPENED_SUBSCRIPTION,
      variables: {
        questionId: state.clientChat.questionId,
      },
      updateQuery: (prev, { subscriptionData }) => {
        if (!subscriptionData.data) return prev;

        return Object.assign({}, prev, {
          ...prev,
          question: {
            ...prev.question,
            ...subscriptionData.data.questionReopened,
          },
        });
      },
    });
    // eslint-disable-next-line
  }, []);

  useEffect(() => {
    // Scroll to the bottom of the messages.
    scrollToBottom(document.querySelector('.client-messages'));
  });

  const renderMessages = () =>
    messages.map((message, index) => (
      <div key={`client-message-${index}-${message.id}`}>
        <Message
          text={message.text}
          createdAt={message.createdAt}
          sentFrom={message.sentFrom}
        />
      </div>
    ));

  const renderSubject = () => (
    <Message text={subject} createdAt={questionCreatedAt} sentFrom="user" />
  );

  const renderLoading = () => {
    if (disabled) {
      return (
        <div className="loading">
          <div />
          <div />
        </div>
      );
    }
  };

  return (
    <div
      className={
        disabled
          ? 'client-messages client-messages--disabled'
          : 'client-messages'
      }
    >
      {renderLoading()}
      {renderSubject()}
      {renderMessages()}
    </div>
  );
};

export default MessageList;
