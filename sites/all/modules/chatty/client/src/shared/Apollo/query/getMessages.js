import gql from 'graphql-tag';

const GET_MESSAGES_QUERY = gql`
  query MessagesQuery($questionId: ID!) {
    messages(questionId: $questionId) {
      id
      text
      sentFrom
      createdAt
    }
  }
`;

export default GET_MESSAGES_QUERY;
