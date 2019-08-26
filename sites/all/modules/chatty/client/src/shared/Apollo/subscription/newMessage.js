import gql from 'graphql-tag';

const NEW_MESSAGE = gql`
  subscription NewMessageSubscription($questionId: ID!) {
    newMessage(questionId: $questionId) {
      id
      text
      sentFrom
      createdAt
      question {
        id
        authorName
      }
    }
  }
`;

export default NEW_MESSAGE;
