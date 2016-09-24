var fs = require('fs')
var path = require('path')

module.exports = function (pathname, ext, callback) {
    fs.readdir (pathname, function doReading(err, list) {
        if (err) {
            return callback(err);
        }
        var filelist = []
        list.forEach(function(file) {
            if(path.extname(file) === '.' + ext) {
                filelist.push(file)
            }
        })
        return callback(null, filelist)
    })
}
