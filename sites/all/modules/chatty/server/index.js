require('dotenv').config();
require('events').EventEmitter.prototype._maxListeners = 100;

const http = require('http');
const https = require('https');
const fs = require('fs');
const express = require('express');
const { ApolloServer, PubSub } = require('apollo-server-express');
const bodyParser = require('body-parser');

const { typeDefs, resolvers } = require('./schema');

const { PORT } = process.env;

// Server.
let server;
const app = express();
const pubsub = new PubSub();

if (process.env.SSL === 'true') {
  server = https.createServer(
    {
      key: fs.readFileSync(process.env.SSL_KEY_PATH),
      cert: fs.readFileSync(process.env.SSL_CERT_PATH),
    },
    app,
  );
} else {
  server = http.createServer(app);
}

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

const apolloServer = new ApolloServer({
  typeDefs,
  resolvers,
  context: { pubsub },
});

apolloServer.applyMiddleware({ app });
apolloServer.installSubscriptionHandlers(server);

server.listen(PORT, () => {
  console.log(
    `🚀 Server ready at http${
      process.env.SSL === 'true' ? 's' : ''
    }://localhost:${PORT}${apolloServer.graphqlPath}`,
  );
  console.log(
    `🚀 Subscriptions ready at ws${
      process.env.SSL === 'true' ? 's' : ''
    }://localhost:${PORT}${apolloServer.subscriptionsPath}`,
  );
});
