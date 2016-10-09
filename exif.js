//  node exif.js <a.jpg
var jpeg = require('jpeg-marker-stream')
process.stdin.pipe(jpeg())
  .on('data', console.log)
