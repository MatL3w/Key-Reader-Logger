import fs from "fs";

setInterval(() => {
    fs.appendFile(
      "lol.txt",
      "This text will be appended to the file.",
      function (err) {
        if (err) throw err;
        console.log("Text appended to file.");
      }
    );
}, 10);
