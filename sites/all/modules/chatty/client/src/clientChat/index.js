import React from 'react';

import App from './components/App';
import Apollo from '../shared/Apollo';
import Store from './context/Store';
import Settings from './components/Settings';

const Index = () => (
  <Apollo>
    <Store>
      <Settings>
        <App />
      </Settings>
    </Store>
  </Apollo>
);

export default Index;
