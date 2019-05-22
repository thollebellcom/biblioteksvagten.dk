const questionResolver = require('./question');
const messageResolver = require('./message');

const mutationResolver = require('./mutation');
const queryResolver = require('./query');
const subscriptionResolver = require('./subscription');

const resolvers = {
  ...mutationResolver,
  ...queryResolver,
  ...subscriptionResolver,
  ...questionResolver,
  ...messageResolver,
};

module.exports = resolvers;
