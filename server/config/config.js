'use strict';

var _   = require('lodash'),
  chalk = require('chalk'),
  glob  = require('glob'),
  fs    = require('fs'),
  path  = require('path');


/**
 * Get files by glob patterns
 */
var getGlobbedPaths = function (globPatterns, excludes) {
  // URL paths regex
  var urlRegex = new RegExp('^(?:[a-z]+:)?\/\/', 'i');

  // The output array
  var output = [];

  // If glob pattern is array then we use each pattern in a recursive way, otherwise we use glob
  if (_.isArray(globPatterns)) {
    globPatterns.forEach(function (globPattern) {
      output = _.union(output, getGlobbedPaths(globPattern, excludes));
    });
  } else if (_.isString(globPatterns)) {
    if (urlRegex.test(globPatterns)) {
      output.push(globPatterns);
    } else {
      var files = glob.sync(globPatterns);
      if (excludes) {
        files = files.map(function (file) {
          if (_.isArray(excludes)) {
            for (var i in excludes) {
              if (excludes.hasOwnProperty(i)) {
                file = file.replace(excludes[i], '');
              }
            }
          } else {
            file = file.replace(excludes, '');
          }
          return file;
        });
      }
      output = _.union(output, files);
    }
  }

  return output;
};


/**
 * Initialize global configuration files
 */
var initGlobalConfigFiles = function (config, assets) {
  config.files = {};

  config.files.routes   = getGlobbedPaths(assets.server.routes);
  config.files.models   = getGlobbedPaths(assets.server.models);
  config.files.configs  = getGlobbedPaths(assets.server.config);
  config.files.policies = getGlobbedPaths(assets.server.policies);
};


/**
 * Initialize global configuration
 */
var initGlobalConfig = function () {
  var assets = require(path.join(process.cwd(), 'config/assets/default'));
  var config = require(path.join(process.cwd(), 'config/env/default'));

  // read package.json for project information
  config.pkg = require(path.resolve('./package.json'));

  // Extend the config object with the local-NODE_ENV.js custom/local environment. This will override any settings present in the local configuration.
  config = _.merge(config, (fs.existsSync(path.join(process.cwd(), 'config/env/local-' + process.env.NODE_ENV + '.js')) && require(path.join(process.cwd(), 'config/env/local-' + process.env.NODE_ENV + '.js'))) || {});

  // Initialize global globbed files
  initGlobalConfigFiles(config, assets);

  return config;
};

/**
 * Set configuration object
 */
module.exports = initGlobalConfig();
