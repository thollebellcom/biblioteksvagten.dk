import gql from 'graphql-tag';

const SIGN_IN_MUTATION = gql`
  mutation SignInMutation {
    signIn
  }
`;

export default SIGN_IN_MUTATION;
