import React, { useContext } from 'react';

import { ChatContext, RESET_CHAT } from '../../context/ChatContext';

const Bar = ({ title }) => {
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
        <h4 className="backend-bar__heading__title">{title}</h4>
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
