import React, { useContext } from 'react';

import {
  ChatContext,
  SET_CHAT_MESSAGE_TEXT,
} from '../../../context/ChatContext';
import { SettingsContext } from '../../../context/SettingsContext';

const StandardAnswerList = ({ modalToggle, modalVisible }) => {
  const [state] = useContext(SettingsContext);
  const [, dispatch] = useContext(ChatContext);
  const standardAnswers = state.standardAnswers;

  const handleApplyStandardAnswer = text => {
    dispatch({
      type: SET_CHAT_MESSAGE_TEXT,
      payload: text,
    });

    modalToggle(!modalVisible);
  };

  const renderList = Object.keys(standardAnswers).map((headingKey, index) => {
    const heading = headingKey;
    const items = standardAnswers[headingKey];

    const renderItems = Object.keys(items).map((itemKey, index) => {
      const heading = itemKey;
      const text = items[itemKey];

      return (
        <div
          className="standard-answer"
          key={`answer-item-${itemKey}-${index}`}
          onClick={() => handleApplyStandardAnswer(text)}
        >
          <div className="standard-answer__heading">
            <h4 className="standard-answer__heading__title">{heading}</h4>
          </div>

          <div className="standard-answer__text">{text}</div>
        </div>
      );
    });

    return (
      <div
        className="standard-answer-list__item"
        key={`answer-${headingKey}-${index}`}
      >
        <div className="standard-answer-list__item__heading">
          <h3 className="standard-answer-list__item__heading__title">
            {heading}
          </h3>
        </div>
        <div className="standard-answer-list__item__content">{renderItems}</div>
      </div>
    );
  });

  return <div className="standard-answer-list">{renderList}</div>;
};

export default StandardAnswerList;
