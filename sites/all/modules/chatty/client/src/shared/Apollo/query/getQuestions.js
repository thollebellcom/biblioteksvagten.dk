import gql from 'graphql-tag';

const GET_QUESTIONS = gql`
  query QuestionsQuery($statusType: String!, $consultantId: ID) {
    questions(statusType: $statusType, consultantId: $consultantId) {
      id
      subject
      authorName
      createdAt
      lastHeartbeatAt
    }
  }
`;

export default GET_QUESTIONS;
