const { withFilter } = require('apollo-server-express');

const {
  NEW_MESSAGE,
  NEW_QUESTION,
  QUESTION_ASSIGNED,
  QUESTION_ASSIGNED_TO_CONSULTANT,
  ASSIGNED_QUESTION_CLOSED,
  QUESTION_CLOSED,
  QUESTION_REOPENED,
  QUESTION_HEARTBEAT,
} = require('../../shared/constants');

const resolver = {
  Subscription: {
    newQuestion: {
      subscribe: withFilter(
        (_, __, { pubsub }) => pubsub.asyncIterator(NEW_QUESTION),
        (payload, variables) => {
          // Check if status matches the requested.
          if (payload.newQuestion.status !== variables.statusType) {
            return false;
          }

          // Check if consultant matches the requested.
          if (typeof variables.consultantId !== 'undefined') {
            if (payload.newQuestion.consultant !== variables.consultantId) {
              return false;
            }
          }

          return true;
        },
      ),
    },
    newMessage: {
      subscribe: withFilter(
        (_, __, { pubsub }) => pubsub.asyncIterator(NEW_MESSAGE),
        (payload, variables) =>
          payload.newMessage.question.toString() === variables.questionId,
      ),
    },
    questionAssignedToConsultant: {
      subscribe: withFilter(
        (_, __, { pubsub }) =>
          pubsub.asyncIterator(QUESTION_ASSIGNED_TO_CONSULTANT),
        (payload, variables) => {
          // Check if consultant matches the requested.
          if (typeof variables.consultantId !== 'undefined') {
            if (
              payload.questionAssignedToConsultant.consultant !==
              variables.consultantId
            ) {
              return false;
            }
          }

          return true;
        },
      ),
    },
    questionAssigned: {
      subscribe: withFilter(
        (_, __, { pubsub }) => pubsub.asyncIterator(QUESTION_ASSIGNED),
        (payload, variables) =>
          payload.questionAssigned.id === variables.questionId,
      ),
    },
    assignedQuestionClosed: {
      subscribe: withFilter(
        (_, __, { pubsub }) => pubsub.asyncIterator(ASSIGNED_QUESTION_CLOSED),
        (payload, variables) => {
          // Check if consultant matches the requested.
          if (typeof variables.consultantId !== 'undefined') {
            if (
              payload.assignedQuestionClosed.consultant !==
              variables.consultantId
            ) {
              return false;
            }
          }

          return true;
        },
      ),
    },
    questionClosed: {
      subscribe: withFilter(
        (_, __, { pubsub }) => pubsub.asyncIterator(QUESTION_CLOSED),
        (payload, variables) =>
          payload.questionClosed.id === variables.questionId,
      ),
    },
    questionReopened: {
      subscribe: withFilter(
        (_, __, { pubsub }) => pubsub.asyncIterator(QUESTION_REOPENED),
        (payload, variables) => {
          // Check if question matches the requested.
          if (typeof variables.questionId !== 'undefined') {
            if (payload.questionReopened.id !== variables.questionId) {
              return false;
            }
          }

          return true;
        },
      ),
    },
    questionHeartbeat: {
      subscribe: withFilter(
        (_, __, { pubsub }) => pubsub.asyncIterator(QUESTION_HEARTBEAT),
        (payload, variables) => {
          // Check if question matches the requested.
          if (typeof variables.questionId !== 'undefined') {
            if (payload.questionHeartbeat.id !== variables.questionId) {
              return false;
            }
          }

          return true;
        },
      ),
    },
  },
};

module.exports = resolver;
