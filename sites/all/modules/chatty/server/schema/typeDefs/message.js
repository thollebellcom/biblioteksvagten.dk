const { gql } = require('apollo-server-express');

const typeDef = gql`
  type Message {
    id: ID!
    question: Question!
    text: String!
    sentFrom: String!
    createdAt: String!
    updatedAt: String!
  }

  input MessageCreateInput {
    text: String!
    sentFrom: String!
  }
`;

module.exports = typeDef;
