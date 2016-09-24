var module = require('./mymodule.js')

var pathname = process.argv[2]
var ext = process.argv[3]

module(pathname, ext, function(err, list) {
    if (err)
        return console.error('Err:', err)

    list.forEach(function (file) {
        console.log(file)
    })
})
