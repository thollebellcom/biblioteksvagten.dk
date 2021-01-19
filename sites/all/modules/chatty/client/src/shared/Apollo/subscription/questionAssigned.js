import gql from 'graphql-tag';

const QUESTION_ASSIGNED_SUBSCRIPTION = gql`
  subscription QuestionAssignedSubscription($questionId: ID) {
    questionAssigned(questionId: $questionId) {
      status
    }
  }
`;

export default QUESTION_ASSIGNED_SUBSCRIPTION;
