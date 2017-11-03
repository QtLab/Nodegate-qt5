'use strict';

module.exports = {
  app: {
    title: 'PILAF.JS',
    description: 'Webservice with Sequelize, Express, and Node.js'
  },
  db: {
    host: process.env.HOST || 'localhost',
    driver: "mysql",
    user: "root",
    database: "dev_db",
    password: "root"
  },
  port: process.env.PORT || 3000,
  host: process.env.HOST || '0.0.0.0',
  domain: process.env.DOMAIN,
  sessionCookie: {
    maxAge: 24 * (60 * 60 * 1000),
    httpOnly: true,
    secure: false
  }
};
