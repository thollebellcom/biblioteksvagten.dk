const MessageController = require('../../controllers/message');
const QuestionController = require('../../controllers/question');
const SettingsController = require('../../controllers/settings');

const resolver = {
  Query: {
    questions: (_, { statusType, consultantId }) =>
      QuestionController.index(statusType, consultantId),
    question: (_, { questionId }) => QuestionController.read(questionId),
    messages: (_, { questionId }) => MessageController.index(questionId),
    settings: () => SettingsController.get(),
  },
};

module.exports = resolver;
