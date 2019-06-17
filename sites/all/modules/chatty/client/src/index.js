import './index.css';
import React from 'react';
import ReactDOM from 'react-dom';

import ClientChat from './clientChat';
import BackendChat from './backendChat';

if (document.getElementById('chatty_client')) {
  ReactDOM.render(<ClientChat />, document.getElementById('chatty_client'));
}

if (document.getElementById('chatty_backend')) {
  ReactDOM.render(<BackendChat />, document.getElementById('chatty_backend'));
}
