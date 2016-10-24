var fs = require('fs')
var path = require('path')
var pathname = process.argv[2]
var ext = '.' + process.argv[3]
function filter_ls(callback) {
    fs.readdir(pathname, function doReading(err, list) {
        for (var i in list) {
            if (path.extname(list[i]) === ext) {
                console.log(list[i])
            }
        }
        callback()
    })
}

function filter() {
}

filter_ls(filter)
