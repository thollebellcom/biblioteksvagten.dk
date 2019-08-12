import gql from 'graphql-tag';

const GET_QUESTION = gql`
  query QuestionQuery($questionId: ID!) {
    question(questionId: $questionId) {
      id
      subject
      authorName
      authorEmail
      consultant
      status
      source
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
