const { gql } = require('apollo-server-express');

const typeDef = gql`
  type Question {
    id: ID!
    authorName: String!
    authorEmail: String!
    subject: String!
    consultant: String
    messages: [Message]!
    status: String!
    lastHeartbeatAt: String!
    createdAt: String!
    updatedAt: String!
  }

  input QuestionCreateInput {
    authorName: String!
    authorEmail: String!
    subject: String!
  }
`;

module.exports = typeDef;
