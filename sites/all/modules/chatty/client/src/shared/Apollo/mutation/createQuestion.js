import gql from 'graphql-tag';

const CREATE_QUESTION_MUTATION = gql`
  mutation CreateQuestionMutation(
    $agencyId: String!
    $authorName: String!
    $authorEmail: String!
    $subject: String!
    $url: String!
  ) {
    createQuestion(
      data: {
        authorName: $authorName
        authorEmail: $authorEmail
        agencyId: $agencyId
        subject: $subject
        url: $url
      }
    ) {
      id
      subject
      authorName
      status
    }
  }
`;

export default CREATE_QUESTION_MUTATION;
