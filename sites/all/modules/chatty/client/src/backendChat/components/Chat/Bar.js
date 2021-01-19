import React, { useContext } from 'react';

import { ChatContext, RESET_CHAT } from '../../context/ChatContext';

const Bar = ({ name, email, source }) => {
  const [, dispatch] = useContext(ChatContext);

  const handleCloseChat = () => {
    dispatch({
      type: RESET_CHAT,
      payload: null,
    });
  };

  return (
    <div className="backend-bar">
      <div className="backend-bar__heading">
        <h2>{name}</h2>
        <h3>
          <a href={`mailto:${email}`}>{email}</a>
        </h3>
        <h4>{source}</h4>
      </div>

      <div className="backend-bar__spacer" />

      <span
        className="backend-bar__button bar__button--close"
        onClick={handleCloseChat}
        title="Klik for at lukke"
      >
        X
      </span>
    </div>
  );
};

export default Bar;
