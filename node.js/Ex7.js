var http = require('http')

var url = process.argv[2]

http.get(url, function (res) {
    console.log(url)
    console.log("got response: " + res.statusCode)
}).on('error', console.error)
