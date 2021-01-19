import gql from 'graphql-tag';

const CLOSE_QUESTION_MUTATION = gql`
  mutation CloseQuestionMutation(
    $questionId: ID!
    $reason: String!
    $keepConsultant: Boolean
    $title: String
  ) {
    closeQuestion(
      questionId: $questionId
      reason: $reason
      keepConsultant: $keepConsultant
      title: $title
    ) {
      id
      subject
      authorName
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

export default CLOSE_QUESTION_MUTATION;
