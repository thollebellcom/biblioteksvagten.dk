const axios = require('../custom-axios');

// Get.
const get = async () => {
  const response = await axios.get('settings');
  const { messages, standardAnswers } = response.data;

  return {
    messages: JSON.stringify(messages),
    standardAnswers: JSON.stringify(standardAnswers),
  };
};

const getDecodedMessage = async key => {
  const response = await axios.get('settings');
  const { messages } = response.data;

  return messages[key];
};

const getConsultantName = async consultantId => {
  const response = await axios.get('consultant-name', {
    params: {
      consultantId,
    },
  });

  return response.data;
};

module.exports = {
  get,
  getDecodedMessage,
  getConsultantName,
};
