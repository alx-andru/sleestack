var Clay = require('pebble-clay');
var clayConfig = require('./config');
var clay = new Clay(clayConfig);

Pebble.addEventListener('webviewclosed', function(e) {
  //console.log(JSON.stringify(e));

});