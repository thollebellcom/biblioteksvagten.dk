import gql from 'graphql-tag';

const GET_QUESTION = gql`
  query QuestionQuery($questionId: ID!) {
    question(questionId: $questionId) {
      id
      authorName
      subject
      consultant
      status
      lastHeartbeatAt
      createdAt
      messages {
        id
        text
        sentFrom
        createdAt
      }
    }
  }
`;

export default GET_QUESTION;
