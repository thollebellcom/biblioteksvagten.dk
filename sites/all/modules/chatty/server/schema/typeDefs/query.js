const { gql } = require('apollo-server-express');

const typeDef = gql`
  type Query {
    questions(statusType: String!, consultantId: ID): [Question]!
    question(questionId: ID!): Question!
    messages(questionId: ID!): [Message]!
    settings: Settings!
  }
`;

module.exports = typeDef;
