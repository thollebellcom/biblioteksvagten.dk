const { gql } = require('apollo-server-express');

const typeDef = gql`
  type Mutation {
    createQuestion(data: QuestionCreateInput!): Question!
    createMessage(questionId: ID!, data: MessageCreateInput!): Message!
    assignQuestion(questionId: ID!, consultantId: ID!): Question!
    closeQuestion(questionId: ID!, reason: String!): Question!
    reopenQuestion(questionId: ID!): Question!
  }
`;

module.exports = typeDef;
