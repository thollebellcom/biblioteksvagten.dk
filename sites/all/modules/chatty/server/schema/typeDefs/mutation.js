const { gql } = require('apollo-server-express');

const typeDef = gql`
  type Mutation {
    createQuestion(data: QuestionCreateInput!): Question!
    createMessage(questionId: ID!, data: MessageCreateInput!): Message!
    assignQuestion(questionId: ID!, consultantId: ID!): Question!
    closeQuestion(
      questionId: ID!
      reason: String!
      keepConsultant: Boolean
      title: String
    ): Question!
    reopenQuestion(questionId: ID!): Question!
    makeHeartbeat(questionId: ID!): Question!
    signIn(token: String): String
    signOut(token: String): Boolean
  }
`;

module.exports = typeDef;
