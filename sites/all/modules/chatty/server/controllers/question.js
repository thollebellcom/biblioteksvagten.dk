const qs = require('qs');

const axios = require('../custom-axios');

// Create item.
const create = async data => {
  const response = await axios.post('create-question', qs.stringify(data));

  return response.data;
};

// Get item.
const read = async questionId => {
  const response = await axios.get('question', {
    params: {
      questionId,
    },
  });

  return response.data;
};

// Get collection of items.
const index = async (statusType, consultantId = null) => {
  const response = await axios.get('questions', {
    params: {
      consultantId,
      statusType,
    },
  });

  return response.data;
};

// Relationships.
const getMessages = async questionId => {
  const response = await axios.get('messages', {
    params: {
      questionId,
    },
  });

  return response.data;
};

const assignQuestion = async (questionId, consultantId) => {
  const response = await axios.post(
    'assign-question',
    qs.stringify({
      questionId,
      consultantId,
    })
  );

  return response.data;
};

const closeQuestion = async (questionId, reason, keepConsultant, title) => {
  const response = await axios.post(
    'close-question',
    qs.stringify({
      questionId,
      reason,
      keepConsultant,
      title,
    })
  );

  return response.data;
};

const reopenQuestion = async questionId => {
  const response = await axios.post(
    'reopen-question',
    qs.stringify({
      questionId,
    })
  );

  return response.data;
};

const makeHeartbeat = async questionId => {
  const response = await axios.post(
    'question-heartbeat',
    qs.stringify({
      questionId,
    })
  );

  return response.data;
};

module.exports = {
  create,
  read,
  index,
  getMessages,
  assignQuestion,
  closeQuestion,
  reopenQuestion,
  makeHeartbeat,
};
