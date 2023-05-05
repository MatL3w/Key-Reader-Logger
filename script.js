import fs from "fs";

// console.log("lol");
// const lol = require("./build/Release/my_addon.node");
// console.log(lol.pass_number());
let i=0;
fs.watch("myfile.txt", (eventType, filename) => {
  fs.stat('myfile.txt',(err,stats)=>{
    if(stats.size>0){
      console.log(`event type is: ${eventType}`);
      i++;
      console.log(i);
      fs.readFile("myfile.txt",'utf8',(err,data)=>{
        console.log(data);
      });
      fs.writeFile("myfile.txt", "",err=>{
        console.log(err);
      });
    }
  })

});
// const user32 = ffi.Library("user32", {
//   MessageBoxA: ["int", ["int", "string", "string", "int"]],
// });

// const MB_OKCANCEL = 1;
// const IDOK = 1;
// const IDCANCEL = 2;

// const ret = user32.MessageBoxA(null, "Hello World!", "Node.js", MB_OKCANCEL);
// if (ret === IDOK) {
//   console.log("User clicked OK");
// } else if (ret === IDCANCEL) {
//   console.log("User clicked Cancel");
// } else {
//   console.log("User closed the message box");
// }
