require('dotenv').config();
require('events').EventEmitter.prototype._maxListeners = 5000;

const http = require('http');
const https = require('https');
const fs = require('fs');
const express = require('express');
const { ApolloServer, PubSub } = require('apollo-server-express');
const cors = require('cors');
const bodyParser = require('body-parser');

const { typeDefs, resolvers } = require('./schema');

const { PORT } = process.env;
const allowedDomains = process.env.CORS_ALLOWED_DOMAINS;

const corsOptionsDelegate = function(req, callback) {
  const corsOptions = {
    origin: false,
  };

  if (allowedDomains.indexOf(req.header('Origin')) !== -1) {
    corsOptions.origin = true;
  }

  callback(null, corsOptions);
};

// Server.
let server;
const app = express();
const pubsub = new PubSub();

app.use(cors(corsOptionsDelegate));

if (process.env.SSL === 'true') {
  const sslOptions = {
    key: fs.readFileSync(process.env.SSL_KEY_PATH),
    cert: fs.readFileSync(process.env.SSL_CERT_PATH),
  };

  if (process.env.SSL_PASSPHRASE && process.env.SSL_PASSPHRASE !== '') {
    sslOptions.passphrase = process.env.SSL_PASSPHRASE;
  }

  server = https.createServer(sslOptions, app);
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
    }://localhost:${PORT}${apolloServer.graphqlPath}`
  );
  console.log(
    `🚀 Subscriptions ready at ws${
      process.env.SSL === 'true' ? 's' : ''
    }://localhost:${PORT}${apolloServer.subscriptionsPath}`
  );
});
