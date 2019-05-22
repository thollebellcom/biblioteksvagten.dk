const { gql } = require('apollo-server-express');

const typeDef = gql`
  type Settings {
    messages: String!
    standardAnswers: String!
  }
`;

module.exports = typeDef;
