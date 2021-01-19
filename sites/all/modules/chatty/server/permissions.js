const { not, rule, shield, allow } = require('graphql-shield');

const isAuthenticated = rule({ cache: 'contextual' })(
  (parent, args, { token }) =>
    token !== null && token === process.env.SECRET_TOKEN
);

module.exports = shield(
  {
    Query: {
      questions: isAuthenticated,
      question: allow,
      messages: allow,
      settings: allow,
    },
    Mutation: {
      createQuestion: allow,
      createMessage: allow,
      assignQuestion: isAuthenticated,
      closeQuestion: isAuthenticated,
      reopenQuestion: isAuthenticated,
      makeHeartbeat: allow,
    },
  },
  {
    debug: true,
  }
);
