import React from 'react';

import { ApolloProvider } from 'react-apollo';
import ApolloClient from 'apollo-client';
import { InMemoryCache } from 'apollo-cache-inmemory';
import { split } from 'apollo-link';
import { HttpLink } from 'apollo-link-http';
import { WebSocketLink } from 'apollo-link-ws';
import { getMainDefinition } from 'apollo-utilities';
import fetch from 'unfetch';

// HTTP link.
const httpLink = new HttpLink({
  uri: process.env.REACT_APP_APOLLO_HTTP_URI,
  fetch: fetch,
});

// WebSocket link.
const wsLink = new WebSocketLink({
  uri: process.env.REACT_APP_APOLLO_WS_URI,
  fetch: fetch,
  lazy: true,
  options: {
    reconnect: true,
  },
});

const link = split(
  ({ query }) => {
    const definition = getMainDefinition(query);
    return (
      definition.kind === 'OperationDefinition' &&
      definition.operation === 'subscription'
    );
  },
  wsLink,
  httpLink,
);

const cache = new InMemoryCache();

const client = new ApolloClient({
  link,
  cache,
});

const Apollo = ({ children }) => (
  <ApolloProvider client={client}>
    {children}
  </ApolloProvider>
);

export default Apollo;
