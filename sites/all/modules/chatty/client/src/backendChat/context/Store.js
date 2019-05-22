import React from 'react';

import { ChatProvider } from './ChatContext';
import { SettingsProvider } from './SettingsContext';

const Store = ({ children }) => {
  return (
    <SettingsProvider>
      <ChatProvider>
        {children}
      </ChatProvider>
    </SettingsProvider>
  );
};

export default Store;
