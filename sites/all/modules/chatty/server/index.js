require('dotenv').config();

const http = require('http');
const express = require('express');
const { ApolloServer, PubSub } = require('apollo-server-express');
const bodyParser = require('body-parser');

const { typeDefs, resolvers } = require('./schema');

const { PORT } = process.env;

// Server.
const app = express();
const pubsub = new PubSub();

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

const httpServer = http.createServer(app);

const apolloServer = new ApolloServer({
  typeDefs,
  resolvers,
  context: { pubsub },
});

apolloServer.applyMiddleware({ app });
apolloServer.installSubscriptionHandlers(httpServer);

httpServer.listen(PORT, () => {
  console.log(
    `🚀 Server ready at http://localhost:${PORT}${apolloServer.graphqlPath}`,
  );
  console.log(
    `🚀 Subscriptions ready at ws://localhost:${PORT}${
      apolloServer.subscriptionsPath
    }`,
  );
});
