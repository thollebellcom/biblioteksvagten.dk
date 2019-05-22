import React, { useEffect } from 'react';

import QuestionTeaser from './QuestionTeaser';

const QuestionList = ({
  canAssign,
  canSetActive,
  title,
  questions,
  subscriptions,
}) => {
  useEffect(() => {
    for (let i = 0; i < subscriptions.length; i++) {
      subscriptions[i]();
    }
  }, []);

  const renderQuestions = () => {
    if (questions.length === 0) {
      return (
        <div className="list__item list__item--no-result">
          Ingen samtaler at vise.
        </div>
      );
    }

    return questions.map(question => (
      <div className="list__item" key={`question-${question.id}`}>
        <QuestionTeaser
          questionId={question.id}
          heading={question.authorName}
          text={question.subject}
          createdAt={question.createdAt}
          canAssign={canAssign}
          canSetActive={canSetActive}
        />
      </div>
    ));
  };

  return (
    <div className="list">
      <div className="list__heading">
        <h4 className="list__heading__title">{title}</h4>
      </div>
      <div className="list__body">{renderQuestions()}</div>
    </div>
  );
};

export default QuestionList;
