import React, { useEffect } from 'react';

import Message from './Message';
import scrollToBottom from '../../../shared/utils/scrollToBottom';

const MessageList = ({
  author,
  subject,
  questionCreatedAt,
  messages,
}) => {
  const consultantName =
    window.Drupal &&
      window.Drupal.settings &&
      window.Drupal.settings.consultantName
      ? window.Drupal.settings.consultantName.toString()
      : 'ikke defineret';

  useEffect(() => {
    // Scroll to the bottom of the messages.
    scrollToBottom(document.querySelector('.backend-chat__messages'));
  });

  const renderMessages = () =>
    messages.map((message, index) => {
      let submittedBy = '';

      if (message.sentFrom === 'admin') {
        submittedBy = consultantName;
      }
      else if (message.sentFrom === 'user') {
        submittedBy = author;
      }

      return (
        <div key={`backend-message-${index}-${message.id}`}>
          <Message
            submittedBy={submittedBy}
            text={message.text}
            createdAt={message.createdAt}
            sentFrom={message.sentFrom}
          />
        </div>
      );
    });

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
