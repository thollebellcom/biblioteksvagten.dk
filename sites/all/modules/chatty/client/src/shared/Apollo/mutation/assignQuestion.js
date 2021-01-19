import gql from 'graphql-tag';

const ASSIGN_QUESTION_MUTATION = gql`
  mutation AssignQuestionMutation($questionId: ID!, $consultantId: ID!) {
    assignQuestion(questionId: $questionId, consultantId: $consultantId) {
      id
      subject
      authorName
      createdAt
    }
  }
`;

export default ASSIGN_QUESTION_MUTATION;
