'use strict';


/**
 * Users routes
 */
module.exports = function (app) {
  var users = require('../controllers/users.controller');

  // Users collection routes
  app.route('/api/users').get(users.list);
  app.route('/api/users').post(users.create);

  // Single user collection routes
  app.route('/api/users/:userId').get(users.read);
  app.route('/api/users/:userId').delete(users.delete);

  // Finish by binding the user middleware
  app.param('userId', users.userByID);

  // Users collection websockets
  app.ws('/ws/users/echo', users.echo);
};
