
import {spawn} from"child_process";

const childProcess = spawn("kHook.exe");

childProcess.on("close", (code) => {
  console.log(`child process exited with code ${code}`);
});

childProcess.stdout.on("data", (data) => {
  console.log(`stdout: ${data}`);
});