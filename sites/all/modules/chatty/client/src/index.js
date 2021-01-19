import 'core-js';
import './index.css';
import React from 'react';
import ReactDOM from 'react-dom';

import getUrlParam from './shared/utils/getUrlParam';
import ClientChat from './clientChat';
import BackendChat from './backendChat';

// Render only one.
if (getUrlParam('renderOnly') !== '') {
  if (getUrlParam('renderOnly') === 'backend') {
    if (document.getElementById('chatty_backend')) {
      ReactDOM.render(
        <BackendChat />,
        document.getElementById('chatty_backend'),
      );
    }
  }

  if (getUrlParam('renderOnly') === 'client') {
    if (document.getElementById('chatty_client')) {
      ReactDOM.render(<ClientChat />, document.getElementById('chatty_client'));
    }
  }
} else {
  if (document.getElementById('chatty_client')) {
    ReactDOM.render(<ClientChat />, document.getElementById('chatty_client'));
  }

  if (document.getElementById('chatty_backend')) {
    ReactDOM.render(<BackendChat />, document.getElementById('chatty_backend'));
  }
}
