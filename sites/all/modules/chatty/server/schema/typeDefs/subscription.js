const { gql } = require('apollo-server-express');

const typeDef = gql`
  type Subscription {
    newQuestion(consultantId: ID, statusType: String!): Question!
    newMessage(questionId: ID!): Message!
    questionAssignedToConsultant(consultantId: ID): Question!
    questionAssigned(questionId: ID): Question!
    assignedQuestionClosed(consultantId: ID): Question!
    questionClosed(questionId: ID!): Question!
    questionReopened(questionId: ID): Question!
    questionHeartbeat(questionId: ID): Question!
  }
`;

module.exports = typeDef;
