import React, {useEffect} from 'react';
import { Mutation } from 'react-apollo';

import SIGN_IN_MUTATION from '../../shared/Apollo/mutation/signIn';

const SignIn = ({ children }) => (
  <Mutation mutation={SIGN_IN_MUTATION}>
    {(signIn, { data, loading }) => {
      if (!data || loading) return <SignInComponent signIn={signIn} />;

      return (
        <>
          {children}
        </>
      );
    }}
  </Mutation>
);

const SignInComponent = ({signIn}) => {
  useEffect(() => {
    signIn();
  }, [signIn])


  return 'Logger ind...';
}

export default SignIn;
