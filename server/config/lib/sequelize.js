'use strict';

var config = require('../env/default.js'),
    path = require('path'),
    Sequelize = require('sequelize'),
    db = {};


/**
 * Load all models & associate them if needed
 */
module.exports.initModuleModels = function (sequelize, db) {
  config.files.models.forEach(function (modelPath) {
    var model = sequelize.import(path.resolve('./' + modelPath));
    db[model.name] = model;
  });

  Object.keys(db).forEach(function(modelName) {
    if ("associate" in db[modelName]) {
      db[modelName].associate(db);
    }
  });
};


/**
 * Initialize database
 */
module.exports.init = function (callback) {
  var sequelize = new Sequelize(config.db.database, config.db.user, config.db.password ? config.db.password : null, {
    host: config.db.host,
    dialect: 'mysql',
    logging: console.log,
    define: {
      timestamps: false
    }
  });

  sequelize.authenticate().then(() => {
    console.log('Connection has been established successfully.');

    this.initModuleModels(sequelize, db);

    db.sequelize = sequelize;
    db.Sequelize = Sequelize;

    if (callback) callback(db);
  })
  .catch(err => {
    console.error('Unable to connect to the database:', err);
  });

  return db;
};

module.exports.db = db;
