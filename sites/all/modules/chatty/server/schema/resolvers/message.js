const MessageController = require('../../controllers/message');

const resolver = {
  Message: {
    question: ({ question }) => MessageController.getQuestion(question),
  },
};

module.exports = resolver;
