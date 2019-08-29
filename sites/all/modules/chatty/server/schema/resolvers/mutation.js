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

const tokenReplacer = require('../../shared/tokenReplacer');
const MessageController = require('../../controllers/message');
const SettingsController = require('../../controllers/settings');
const QuestionController = require('../../controllers/question');

const resolver = {
  Mutation: {
    createQuestion: async (_, { data }, { pubsub }) => {
      const question = await QuestionController.create(data);

      pubsub.publish(NEW_QUESTION, {
        newQuestion: question,
      });

      return question;
    },
    createMessage: async (_, { questionId, data }, { pubsub }) => {
      const message = await MessageController.create(questionId, data);

      pubsub.publish(NEW_MESSAGE, {
        newMessage: message,
      });

      return message;
    },
    assignQuestion: async (_, { questionId, consultantId }, { pubsub }) => {
      const consultantName = await SettingsController.getConsultantName(
        consultantId,
      );
      const question = await QuestionController.assignQuestion(
        questionId,
        consultantId,
      );
      const message = await MessageController.create(questionId, {
        text: tokenReplacer(
          await SettingsController.getDecodedMessage('chatAssigned'),
          {
            token: '%consultant_name',
            replaceBy: consultantName,
          },
        ),
        sentFrom: 'system',
      });

      pubsub.publish(NEW_MESSAGE, {
        newMessage: message,
      });
      pubsub.publish(QUESTION_ASSIGNED_TO_CONSULTANT, {
        questionAssignedToConsultant: question,
      });
      pubsub.publish(QUESTION_ASSIGNED, {
        questionAssigned: question,
      });

      return question;
    },
    closeQuestion: async (
      _,
      { questionId, reason, keepConsultant, title },
      { pubsub },
    ) => {
      const question = await QuestionController.closeQuestion(
        questionId,
        reason,
        keepConsultant,
        title,
      );
      const consultantName = await SettingsController.getConsultantName(
        question.consultant,
      );
      const message = await MessageController.create(questionId, {
        text: tokenReplacer(
          await SettingsController.getDecodedMessage('chatClosedByAdmin'),
          {
            token: '%consultant_name',
            replaceBy: consultantName,
          },
        ),
        sentFrom: 'system',
      });

      pubsub.publish(NEW_MESSAGE, {
        newMessage: message,
      });
      pubsub.publish(QUESTION_CLOSED, {
        questionClosed: question,
      });
      pubsub.publish(ASSIGNED_QUESTION_CLOSED, {
        assignedQuestionClosed: question,
      });

      return question;
    },
    reopenQuestion: async (_, { questionId }, { pubsub }) => {
      const question = await QuestionController.reopenQuestion(questionId);
      const message = await MessageController.create(questionId, {
        text: await SettingsController.getDecodedMessage('chatReopened'),
        sentFrom: 'system',
      });

      pubsub.publish(NEW_MESSAGE, {
        newMessage: message,
      });
      pubsub.publish(QUESTION_REOPENED, {
        questionReopened: question,
      });

      return question;
    },
    makeHeartbeat: async (_, { questionId }, { pubsub }) => {
      const question = await QuestionController.makeHeartbeat(questionId);

      pubsub.publish(QUESTION_HEARTBEAT, {
        questionHeartbeat: question,
      });

      return question;
    },
  },
};

module.exports = resolver;
