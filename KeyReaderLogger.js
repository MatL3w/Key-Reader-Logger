import { spawn } from "child_process";
import { EventEmitter } from "node:events";
import path from "path";
import { fileURLToPath } from "url";
export class KeyReaderLogger extends EventEmitter {
  childProcessKeyboard;
  childProcessMouse;
  currentDirectory;
  constructor() {
    super();
    this.currentDirectory = path.dirname(new URL(import.meta.url).pathname);
  }
  startKeyboard() {
    const __filename = fileURLToPath(import.meta.url);
    const __dirname = path.dirname(__filename);
    const absolutePath = path.join(__dirname, "kHook.exe");
    this.childProcessKeyboard = spawn(absolutePath);
    this.initKeyboard();
  }
  initKeyboard() {
    this.childProcessKeyboard.on("close", (code) => {
      console.log(`child process exited with code ${code}`);
    });
    this.childProcessKeyboard.stdout.on("data", (data) => {
      this.emit("keyData", data.toString());
    });
  }
  startMouse() {
    const __filename = fileURLToPath(import.meta.url);
    const __dirname = path.dirname(__filename);
    const absolutePath = path.join(__dirname, "mHook.exe");
    this.childProcessMouse = spawn(absolutePath);
    this.initMouse();
  }
  initMouse() {
    this.childProcessMouse.on("close", (code) => {
      console.log(`child process exited with code ${code}`);
    });
    this.childProcessMouse.stdout.on("data", (data) => {
      this.emit("mouseData", data.toString());
    });
  }
  stopKeyboard() {
    return this.childProcessKeyboard.kill();
  }
  stopMouse() {
    return this.childProcessMouse.kill();
  }
  stopAll() {
    return this.childProcessKeyboard.kill() && this.childProcessMouse.kill();
  }
  startAll() {
    this.startKeyboard();
    this.startMouse();
  }
}
