const fs = require('fs');
const FILE = "log.txt";

function log(text)
{
    fs.appendFileSync(FILE, text);
}

module.exports.write = log;