import React from 'react';
import { Query } from 'react-apollo';

import GET_QUESTIONS from '../../../shared/Apollo/query/getQuestions';
import NEW_QUESTION_SUBSCRIPTION from '../../../shared/Apollo/subscription/newQuestion';
import QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionAssignedToConsultant';
import QUESTION_REOPENED_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionReopened';

import QuestionList from './QuestionList';

const AvailableQuestions = () => {
  let subscriptions = [];

  return (
    <Query
      query={GET_QUESTIONS}
      variables={{
        consultantId: null,
        statusType: 'pending',
      }}
    >
      {({ loading, data, subscribeToMore }) => {
        if (!data) return '';

        if (loading) {
          return 'Henter...';
        }

        // New questions added.
        subscriptions.push(() =>
          subscribeToMore({
            document: NEW_QUESTION_SUBSCRIPTION,
            variables: {
              consultantId: null,
              statusType: 'pending',
            },
            updateQuery: (prev, { subscriptionData }) => {
              if (!subscriptionData.data) return prev;

              const question = subscriptionData.data.newQuestion;

              return Object.assign({}, prev, {
                questions: [...prev.questions, question],
              });
            },
          }),
        );

        // Question assigned to consultant.
        subscriptions.push(() =>
          subscribeToMore({
            document: QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION,
            updateQuery: (prev, { subscriptionData }) => {
              if (!subscriptionData.data) return prev;

              const questionToRemove =
                subscriptionData.data.questionAssignedToConsultant;

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

              const questionToReadd = subscriptionData.data.questionReopened;

              const filteredQuestions = prev.questions.filter(
                question => question.id !== questionToReadd.id,
              );

              filteredQuestions.push(questionToReadd);

              return Object.assign({}, prev, {
                questions: filteredQuestions,
              });
            },
          }),
        );

        return (
          <QuestionList
            title="Tilgængelige spørgsmål"
            questions={data.questions}
            subscriptions={subscriptions}
            canAssign={true}
            canSetActive={true}
          />
        );
      }}
    </Query>
  );
};

export default AvailableQuestions;
