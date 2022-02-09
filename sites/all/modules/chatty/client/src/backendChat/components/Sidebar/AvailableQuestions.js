import React from 'react';
import { Query } from 'react-apollo';
import UIfx from 'uifx';

import GET_QUESTIONS from '../../../shared/Apollo/query/getQuestions';
import NEW_QUESTION_SUBSCRIPTION from '../../../shared/Apollo/subscription/newQuestion';
import QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionAssignedToConsultant';
import QUESTION_REOPENED_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionReopened';
import QUESTION_HEARTBEAT_SUBSCRIPTION from '../../../shared/Apollo/subscription/questionHeartbeat';

import QuestionList from './QuestionList';
import audioFile from './message.mp3'

const AvailableQuestions = () => {
  const beep = new UIfx(
    audioFile,
    {
      volume: 1
    }
  );
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

              const notifyEndUser = function() {
                beep.play();
		const delay = 10000;
                if (document.body.classList.contains('blured')) {
                  console.log('Page is blured play sound again in ' + delay + ' miliseconds');
                  setTimeout(function () {notifyEndUser(); }, delay);
                }
                else {
                  console.log('Page is active. Do not play sound anymore.');
                }
              }

              notifyEndUser();

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

        // Question heartbeat.
        subscriptions.push(() =>
          subscribeToMore({
            document: QUESTION_HEARTBEAT_SUBSCRIPTION,
            updateQuery: (prev, { subscriptionData }) => {
              if (!subscriptionData.data) return prev;

              const questionHeartbeat = subscriptionData.data.questionHeartbeat;
              const currentQuestion = prev.questions.find(
                question => question.id === questionHeartbeat.id,
              );

              if (!currentQuestion) return prev;

              const mutatedQuestion = {
                ...currentQuestion,
              };

              const filteredQuestions = prev.questions.filter(
                question => question.id !== questionHeartbeat.id,
              );

              filteredQuestions.push(mutatedQuestion);

              return Object.assign({}, prev, {
                questions: filteredQuestions,
              });
            },
          }),
        );

        return (
          <QuestionList
            title="Chats, Afventer svar"
            questions={data.questions}
            subscriptions={subscriptions}
            subscribeToMore={subscribeToMore}
            canAssign={true}
            canSetActive={true}
          />
        );
      }}
    </Query>
  );
};

export default AvailableQuestions;
