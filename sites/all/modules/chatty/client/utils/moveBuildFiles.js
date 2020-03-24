var fs = require('fs');
var glob = require('glob');
var ncp = require('ncp').ncp;

var removeFolder = require('./removeFolder');

var srcDir = process.cwd() + '/build/static';
var destDir = process.cwd() + '/../static';
var jsDestDirectory = destDir + '/js';
var cssDestDirectory = destDir + '/css';

var renameFiles = [
  {
    from: jsDestDirectory + '/main.*.js',
    to: jsDestDirectory + '/main.js',
  },
  {
    from: jsDestDirectory + '/2.*.js',
    to: jsDestDirectory + '/2.js',
  },
  {
    from: cssDestDirectory + '/main.*.css',
    to: cssDestDirectory + '/main.css',
  },
];

// Remove static directory.
fs.access(destDir, fs.constants.F_OK, (err) => {
  
  // Directory exists.
  if (!err) {
    removeFolder(destDir + '/');
  }
});

// Copy directory.
ncp(srcDir, destDir, err => {
  if (err) {
    console.error(err);

    throw err;
  }

  // Rename files.
  renameFiles.forEach(renameFile => {

    glob(renameFile.from, {}, (err, files) => {
      if (err) {
        console.error(err);

        throw err;
      }
      console.log('files', files);

      files.forEach(file => {
        fs.rename(file, renameFile.to, () => {});
      })
    });
  });
});
