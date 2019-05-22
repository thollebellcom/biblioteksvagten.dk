import gql from 'graphql-tag';

const REOPEN_QUESTION_MUTATION = gql`
  mutation ReopenQuestionMutation($questionId: ID!) {
    reopenQuestion(questionId: $questionId) {
      id
    }
  }
`;

export default REOPEN_QUESTION_MUTATION;
