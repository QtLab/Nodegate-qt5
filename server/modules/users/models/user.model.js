'use strict';


/**
 * User Model
 */
module.exports = function(sequelize, dataTypes) {
  var User = sequelize.define('User', {

    username: dataTypes.STRING,
    password: dataTypes.STRING

  });

  return User;
};
