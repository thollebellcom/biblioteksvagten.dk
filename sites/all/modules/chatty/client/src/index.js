import './index.css';
import React from 'react';
import ReactDOM from 'react-dom';

import getUrlParams from './shared/utils/getUrlParams';
import ClientChat from './clientChat';
import BackendChat from './backendChat';

// Render only one.
if (getUrlParams('renderOnly') !== '') {
  if (getUrlParams('renderOnly') === 'backend') {
    if (document.getElementById('chatty_backend')) {
      ReactDOM.render(
        <BackendChat />,
        document.getElementById('chatty_backend'),
      );
    }
  }

  if (getUrlParams('renderOnly') === 'client') {
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
