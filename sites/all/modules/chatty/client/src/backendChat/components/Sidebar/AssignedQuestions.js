import React from 'react';
import { Query } from 'react-apollo';

import GET_QUESTIONS from '../../../shared/Apollo/query/getQuestions';
import QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionAssignedToConsultant';
import QUESTION_REOPENED_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionReopened';
import ASSIGNED_QUESTION_CLOSED_SUBSCRIPTION from '../../../shared/Apollo/subscription/assignedQuestionClosed';

import QuestionList from './QuestionList';

const AssignedQuestions = () => {
  let subscriptions = [];
  const myConsultantId = '666';

  return (
    <Query
      query={GET_QUESTIONS}
      variables={{
        statusType: 'assigned',
        consultantId: myConsultantId,
      }}
    >
      {({ loading, data, subscribeToMore }) => {
        if (!data) return '';

        if (loading) {
          return 'Henter...';
        }

        // Question assigned to consultant.
        subscriptions.push(() =>
          subscribeToMore({
            document: QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION,
            variables: {
              consultantId: myConsultantId,
            },
            updateQuery: (prev, { subscriptionData }) => {
              if (!subscriptionData.data) return prev;

              const question =
                subscriptionData.data.questionAssignedToConsultant;

              return Object.assign({}, prev, {
                questions: [...prev.questions, question],
              });
            },
          }),
        );

        // Question closed.
        subscriptions.push(() =>
          subscribeToMore({
            document: ASSIGNED_QUESTION_CLOSED_SUBSCRIPTION,
            variables: {
              consultantId: myConsultantId,
            },
            updateQuery: (prev, { subscriptionData }) => {
              if (!subscriptionData.data) return prev;

              const questionToRemove =
                subscriptionData.data.assignedQuestionClosed;

              // Remove the ID from the current questions list.
              const filteredQuestions = prev.questions.filter(
                question => question.id !== questionToRemove.id,
              );

              return Object.assign({}, prev, {
                questions: filteredQuestions,
              });
            },
          }),
        );

        // Question reopened.
        subscriptions.push(() =>
          subscribeToMore({
            document: QUESTION_REOPENED_SUBSCRIPTION,
            updateQuery: (prev, { subscriptionData }) => {
              if (!subscriptionData.data) return prev;

              const questionToRemove = subscriptionData.data.questionReopened;

              const filteredQuestions = prev.questions.filter(
                question => question.id !== questionToRemove.id,
              );

              return Object.assign({}, prev, {
                questions: filteredQuestions,
              });
            },
          }),
        );

        return (
          <QuestionList
            title="Tildelte spørgsmål"
            questions={data.questions}
            subscriptions={subscriptions}
            canAssign={false}
            canSetActive={true}
            subscribeToMore={subscribeToMore}
          />
        );
      }}
    </Query>
  );
};

export default AssignedQuestions;
