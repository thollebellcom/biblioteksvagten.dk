import gql from 'graphql-tag';

const MAKE_HEARTBEAT_MUTATION = gql`
  mutation MakeHeartbeatMutation($questionId: ID!) {
    makeHeartbeat(questionId: $questionId) {
      id
    }
  }
`;

export default MAKE_HEARTBEAT_MUTATION;
