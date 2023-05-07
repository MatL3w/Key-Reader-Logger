import {ChildProcess, ChildProcessWithoutNullStreams, spawn} from "child_process";
import {EventEmitter} from "node:events";

export class KeyReaderLogger extends EventEmitter {
  private childProcessKeyboard!: ChildProcessWithoutNullStreams;
  private childProcessMouse!: ChildProcessWithoutNullStreams;
  constructor() {
    super();
  }
  public startKeyboard() {
    this.childProcessKeyboard = spawn("kHook.exe");
    this.initKeyboard();
  }
  private initKeyboard() {
    this.childProcessKeyboard.on("close", (code: any) => {
      console.log(`child process exited with code ${code}`);
    });
    this.childProcessKeyboard.stdout.on("data", (data: any) => {
      this.emit("keyData", data.toString());
    });
  }
  public startMouse() {
    this.childProcessMouse = spawn("mHook.exe");
    this.initMouse();
  }
  private initMouse() {
    this.childProcessMouse.on("close", (code: any) => {
      console.log(`child process exited with code ${code}`);
    });
    this.childProcessMouse.stdout.on("data", (data: any) => {
      this.emit("mouseData", data.toString());
    });
  }
  public stopKeyboard() {
    return this.childProcessKeyboard.kill();
  }
  public stopMouse() {
    return this.childProcessMouse.kill();
  }
  public stopAll() {
    return this.childProcessKeyboard.kill() && this.childProcessMouse.kill();
  }
  public startAll(){
    this.startKeyboard();
    this.startMouse();
  }
}
