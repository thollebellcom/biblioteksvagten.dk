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
    source: String!
    lastHeartbeatAt: String!
    createdAt: String!
    updatedAt: String!
  }

  input QuestionCreateInput {
    agencyId: String!
    agencyMail: String!
    authorName: String!
    authorEmail: String!
    subject: String!
    url: String!
  }
`;

module.exports = typeDef;
