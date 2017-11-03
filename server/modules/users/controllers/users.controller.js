'use strict';


var path = require('path'),
    db = require(path.resolve('./config/lib/sequelize')).db,
    wsEvents = require('ws-events'),
    users = require("../business/users.business");


/**
 * User create
 */
exports.create = function (req, res) {
  users.create(req.body.username, req.body.password);
};


/**
 * List of Users
 */
exports.list = function (req, res) {
  users.list().then(users => {
    res.json(users);
  });
};


/**
 * User read
 */
exports.read = function (req, res) {
  res.json(req.user);
};


/**
 * User delete
 */
exports.delete = function (req, res) {
  users.delete(req.user.id).then(() => {
    res.json(req.user);
  });
};


/**
 * User middleware
 */
exports.userByID = function (req, res, next, id) {
  if (isNaN(id)) {
    return res.status(400).send({
      message: 'User is invalid'
    });
  }

  users.userById(id).then(user => {
    if (!user) {
      return next(new Error('Failed to load user ' + id));
    }

    req.user = user;
    next();
  });
};


/**
 * User socket service echo
 */
exports.echo = function(ws, req) {
  var events = wsEvents(ws);

  events.emit('login', {
    any: 'json'
  });
 
//  events.on('login', (arg) => {
//    console.log(arg)
//  });

};

/**
 * Game websocket session
 */
/*
exports.session = function(ws, req) {
  var events = wsEvents(ws);
  var wss = req.app.websocket.getWss();

  events.on('play', (move) => {
    wss.clients.forEach(function each(client) {
      if (client !== ws && client.readyState === WebSocket.OPEN) {
        wsEvents(client).emit('play', move);
      }
    });
  });
};
*/