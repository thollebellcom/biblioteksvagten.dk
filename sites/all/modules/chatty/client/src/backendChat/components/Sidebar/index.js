import './index.css';
import React from 'react';

import AvailableQuestions from './AvailableQuestions';
import AssignedQuestions from './AssignedQuestions';

const Sidebar = () => (
  <div className="sidebar">
    <AvailableQuestions />
    <AssignedQuestions />
  </div>
);

export default Sidebar;
