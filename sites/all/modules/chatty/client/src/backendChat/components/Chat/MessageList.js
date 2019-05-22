import React, { useEffect, useContext } from 'react';

import NEW_MESSAGE_SUBSCRIPTION from '../../../shared/Apollo/subscription/newMessage';
import { ChatContext } from '../../context/ChatContext';

import Message from './Message';
import scrollToBottom from '../../../shared/utils/scrollToBottom';

const MessageList = ({
  subject,
  questionCreatedAt,
  messages,
  subscribeToMore,
}) => {
  const [state] = useContext(ChatContext);

  useEffect(() => {
    subscribeToMore({
      document: NEW_MESSAGE_SUBSCRIPTION,
      variables: {
        questionId: state.backendChat.questionId,
      },
      updateQuery: (prev, { subscriptionData }) => {
        if (!subscriptionData.data) return prev;

        return Object.assign({}, prev, {
          ...prev,
          question: {
            ...prev.question,
            messages: [
              ...prev.question.messages,
              subscriptionData.data.newMessage,
            ],
          },
        });
      },
    });
  }, []);

  useEffect(() => {
    // Scroll to the bottom of the messages.
    scrollToBottom(document.querySelector('.backend-chat__messages'));
  });

  const renderMessages = () =>
    messages.map((message, index) => (
      <div id="messages" key={`backend-message-${index}-${message.id}`}>
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

  return (
    <div className="backend-chat__messages">
      {renderSubject()}
      {renderMessages()}
    </div>
  );
};

export default MessageList;
