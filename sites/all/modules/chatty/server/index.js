require('dotenv').config();
require('events').EventEmitter.prototype._maxListeners = 10000;

const http = require('http');
const https = require('https');
const fs = require('fs');
const express = require('express');
const {
  ApolloServer,
  makeExecutableSchema,
  PubSub,
} = require('apollo-server-express');
const { applyMiddleware } = require('graphql-middleware');
const cors = require('cors');
const bodyParser = require('body-parser');
const cookieParser = require('cookie-parser');

const permissions = require('./permissions');
const { typeDefs, resolvers } = require('./schema');

const { PORT } = process.env;
const allowedDomains = process.env.CORS_ALLOWED_DOMAINS;

const corsOptionsDelegate = function(req, callback) {
  const corsOptions = {
    origin: false,
    credentials: true,
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
  schema: applyMiddleware(
    makeExecutableSchema({ typeDefs, resolvers }),
    permissions
  ),
  introspection: false,
  playground: false,
  context: ({ req, res, connection }) => {
    let token;

    if (connection) {
      token = process.env.SECRET_KEY; // Allow subscriptions.
    } else {
      token = req.headers.authorization || null;

      if (token) {
        token = token.split('Bearer ')[1];
      }
    }

    return {
      req,
      res,
      token,
      pubsub,
    };
  },
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
