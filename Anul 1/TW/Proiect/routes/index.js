var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res, next) {
  console.log("Aici");
  res.end("Buuuna");
});

module.exports = router;
