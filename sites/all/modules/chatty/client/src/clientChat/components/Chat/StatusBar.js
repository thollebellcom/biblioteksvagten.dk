import React, { useContext } from 'react';

import { SettingsContext } from '../../context/SettingsContext';

const StatusBar = ({ status }) => {
  const [state] = useContext(SettingsContext);

  if (status === 'pending') {
    return (
      <div className={`client-status-bar client-status-bar--${status}`}>
        {state.messages.chatPending}
      </div>
    );
  }

  return '';
};

export default StatusBar;
