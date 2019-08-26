import gql from 'graphql-tag';

const CREATE_MESSAGE_MUTATION = gql`
  mutation CreateMessageMutation($questionId: ID!, $sentFrom: String!, $text: String!) {
    createMessage(questionId: $questionId, data: { text: $text, sentFrom: $sentFrom }) {
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

export default CREATE_MESSAGE_MUTATION;
