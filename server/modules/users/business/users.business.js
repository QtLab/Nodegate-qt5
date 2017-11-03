'use strict';


var path = require('path'),
    db = require(path.resolve('./config/lib/sequelize')).db;


/**
 * Create a new Game
 */
exports.create = function (username, password) {
  db.User.create({
    username: username,
    password: password
  });
};


/**
 * List of Users
 */
exports.list = function () {
  return db.User.findAll();
};


/**
 * User delete
 */
exports.delete = function (idUser) {
  return db.User.destroy({
    where: { id: idUser }
  });
};


/**
 * User by id
 */
exports.userById = function (idUser) {
  return db.User.findById(idUser);
};