var express = require('./express'),
    sequelize = require('./sequelize'),
    config = require('../env/default.js');
    


/**
 * Initialize application
 */
module.exports.init = function init(callback) {

  var db = sequelize.init(function() {
    var app = express.init();

    if (callback)
    {
      callback(app, db, config);
    }
  });
};


/**
 * Start application
 */
module.exports.start = function start(callback) {
  var _this = this;

  _this.init(function (app, db, config) {
    app.listen(config.port, config.host, function () {
      if (callback) {
        callback(app, db, config);
      }
    });
  });
};
