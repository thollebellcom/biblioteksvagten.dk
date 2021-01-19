import gql from 'graphql-tag';

const QUESTION_HEARTBEAT_SUBSCRIPTION = gql`
  subscription QuestionHeartbeatSubscription($questionId: ID) {
    questionHeartbeat(questionId: $questionId) {
      id
      lastHeartbeatAt
    }
  }
`;

export default QUESTION_HEARTBEAT_SUBSCRIPTION;
