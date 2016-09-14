var fs = require('fs')

var b = new Buffer(1024);

b = fs.readFileSync(process.argv[2])
var string = b.toString('ascii');

var arr = string.split("\n");

console.log(arr.length - 1)
