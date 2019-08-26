import gql from 'graphql-tag';

const QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION = gql`
  subscription QuestionAssignedToConsultantSubscription($consultantId: ID) {
    questionAssignedToConsultant(consultantId: $consultantId) {
      id
      status
      subject
      authorName
      authorEmail
      consultant
      source
      createdAt
      lastHeartbeatAt
    }
  }
`;

export default QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION;
