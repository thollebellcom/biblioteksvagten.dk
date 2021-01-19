import gql from 'graphql-tag';

const GET_SETTINGS = gql`
  query {
    settings {
      messages
      standardAnswers
    }
  }
`;

export default GET_SETTINGS;
