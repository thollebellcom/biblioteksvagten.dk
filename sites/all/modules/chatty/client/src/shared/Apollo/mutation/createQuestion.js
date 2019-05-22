import gql from 'graphql-tag';

const CREATE_QUESTION_MUTATION = gql`
  mutation CreateQuestionMutation($subject: String!, $authorName: String!, $authorEmail: String!) {
    createQuestion(data: { 
      subject: $subject
      authorName: $authorName
      authorEmail: $authorEmail
    }) {
      id
      subject
      authorName
      status
    }
  }
`;

export default CREATE_QUESTION_MUTATION;
