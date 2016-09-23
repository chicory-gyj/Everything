var fs = require('fs')
function get_lines_number() {
    fs.readFile(process.argv[2], function doReading(err, fileContents) {
        var string = fileContents.toString('ascii')
        var arr = string.split("\n")
        console.log(arr.length - 1)
    })
}

get_lines_number()
