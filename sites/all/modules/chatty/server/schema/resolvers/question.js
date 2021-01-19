const QuestionController = require('../../controllers/question');

const resolver = {
  Question: {
    messages: question => QuestionController.getMessages(question.id),
  },
};

module.exports = resolver;
