import React, { Fragment, useContext } from 'react';

import { ChatContext } from '../context/ChatContext';
import Sidebar from './Sidebar';
import Chat from './Chat';

const App = () => {
  const [state] = useContext(ChatContext);

  const renderChat = state.backendChat ? <Chat /> : '';

  return (
    <Fragment>
      <Sidebar />
      {renderChat}
    </Fragment>
  );
};

export default App;
