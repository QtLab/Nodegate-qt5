var config = require('../config'),
    express = require('express'),
    expressWs = require('express-ws'),
    path = require('path'),
    bodyParser = require('body-parser');


/**
 * Initialize application middleware
 */
module.exports.initMiddleware = function (app) {
  app.use(bodyParser());
};


/**
 * Configure the modules server routes
 */
module.exports.initModulesRoutes = function (app) {
  config.files.routes.forEach(function (routePath) {
    require(path.resolve(routePath))(app);
  });
};


/**
 * Configure view engine
 */
module.exports.initViewEngine = function (app) {
  app.set('view engine', 'pug')
  app.set('views', path.resolve('./'));
};


/**
 * Initialize the Express application
 */
module.exports.init = function () {
  var app = express();

  app.websocket = expressWs(app);

  this.initMiddleware(app);

  this.initViewEngine(app);

  this.initModulesRoutes(app);

  return app;
};