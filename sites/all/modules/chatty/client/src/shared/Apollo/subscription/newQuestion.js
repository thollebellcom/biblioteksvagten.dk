import gql from 'graphql-tag';

const NEW_QUESTION = gql`
  subscription NewQuestionSubscription($statusType: String!) {
    newQuestion(statusType: $statusType) {
      id
      subject
      authorName
      authorEmail
      source
      consultant
      createdAt
      lastHeartbeatAt
    }
  }
`;

export default NEW_QUESTION;
