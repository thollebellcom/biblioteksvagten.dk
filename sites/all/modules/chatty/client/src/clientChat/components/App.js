import React, { useContext } from 'react';

import { ChatContext } from '../context/ChatContext';
import Question from './Question';
import Chat from './Chat';

const App = () => {
  const [state] = useContext(ChatContext);

  if (state.clientChat) {
    return <Chat />;
  }

  return <Question />;
};

export default App;
