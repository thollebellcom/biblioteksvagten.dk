import React, { useState, useEffect } from 'react';

import convertTimestampToDate from '../../../shared/utils/convertTimestampToDate';
import generateDateString from '../../../shared/utils/generateDateString';

const Message = ({ sentFrom, text, createdAt }) => {
  const convertedDate = convertTimestampToDate(createdAt);
  const [dateString, setDateString] = useState(
    generateDateString(convertedDate),
  );

  useEffect(() => {
    // Update dateString every thirty second as time passes.
    const timer = setInterval(() => {
      setDateString(generateDateString(convertedDate));
    }, 1000 * 30);

    return () => clearInterval(timer);
  });

  return (
    <div className={`backend-message backend-message--${sentFrom}`}>
      <div className="backend-message__box">
        <div className="backend-message__text">{text}</div>
      </div>
      {sentFrom === 'system' ? (
        ''
      ) : (
        <div className="backend-message__created-at">{dateString}</div>
      )}
    </div>
  );
};

export default Message;
