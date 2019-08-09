import gql from 'graphql-tag';

const ASSIGNED_QUESTION_CLOSED_SUBSCRIPTION = gql`
  subscription AssignedQuestionClosedSubscription($consultantId: ID) {
    assignedQuestionClosed(consultantId: $consultantId) {
      id
      subject
      authorName
      createdAt
      consultant
      lastHeartbeatAt
    }
  }
`;

export default ASSIGNED_QUESTION_CLOSED_SUBSCRIPTION;
