import React, { useEffect } from 'react';

import QuestionTeaser from './QuestionTeaser';

const QuestionList = ({
  canAssign,
  canSetActive,
  title,
  questions,
  subscriptions,
  subscribeToMore,
}) => {
  const myConsultantId =
    window.Drupal &&
    window.Drupal.settings &&
    window.Drupal.settings.consultantId
      ? window.Drupal.settings.consultantId.toString()
      : '1';

  useEffect(() => {
    for (let i = 0; i < subscriptions.length; i++) {
      subscriptions[i]();
    }
    // eslint-disable-next-line
  }, []);

  const renderQuestions = () => {
    if (!questions || questions.length === 0) {
      return (
        <div className="backend-list__item backend-list__item--no-result">
          Ingen samtaler at vise.
        </div>
      );
    }

    return questions.map(question => (
      <div
        className={
          myConsultantId !== question.consultant
            ? 'backend-list__item backend-list__item--faded'
            : 'backend-list__item'
        }
        key={`question-${question.id}`}
      >
        <QuestionTeaser
          questionId={question.id}
          heading={question.authorName}
          text={question.subject}
          createdAt={question.createdAt}
          canAssign={canAssign}
          canSetActive={canSetActive}
          lastHeartbeat={question.lastHeartbeatAt}
          readOnly={myConsultantId !== question.consultant}
          subscribeToMore={subscribeToMore}
        />
      </div>
    ));
  };

  return (
    <div className="backend-list">
      <div className="backend-list__heading">
        <h4 className="backend-list__heading__title">{title}</h4>
      </div>
      <div className="backend-list__body">{renderQuestions()}</div>
    </div>
  );
};

export default QuestionList;
