import gql from 'graphql-tag';

const QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION = gql`
  subscription QuestionAssignedToConsultantSubscription($consultantId: ID) {
    questionAssignedToConsultant(consultantId: $consultantId) {
      id
      subject
      authorName
      createdAt
    }
  }
`;

export default QUESTION_ASSIGNED_TO_CONSULTANT_SUBSCRIPTION;
