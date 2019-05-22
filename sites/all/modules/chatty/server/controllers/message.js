const qs = require('qs');

const axios = require('../custom-axios');

// Create item.
const create = async (questionId, data) => {
  const params = {
    ...data,
    questionId,
  };

  const response = await axios.post('create-message', qs.stringify(params));

  return response.data;
};

// Get collection of items.
const index = async questionId => {
  const response = await axios.get('messages', {
    params: {
      questionId,
    },
  });

  return response.data;
};

// Relationship.
const getQuestion = async questionId => {
  const response = await axios.get('question', {
    params: {
      questionId,
    },
  });

  return response.data;
};

module.exports = {
  create,
  index,
  getQuestion,
};
