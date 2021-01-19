const questionType = require('./question');
const messageType = require('./message');
const settingsType = require('./settings');

const mutationType = require('./mutation');
const queryType = require('./query');
const subscriptionType = require('./subscription');

module.exports = [
  mutationType,
  queryType,
  subscriptionType,
  settingsType,
  questionType,
  messageType,
];
