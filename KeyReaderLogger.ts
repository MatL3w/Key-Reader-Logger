import {ChildProcess, ChildProcessWithoutNullStreams, spawn} from "child_process";
import {EventEmitter} from "node:events";

export class KeyReaderLogger extends EventEmitter {
  private childProcess!: ChildProcessWithoutNullStreams;
  constructor() {
    super();
    this.start()
    this.init();
  }
  private start() {
    this.childProcess = spawn("kHook.exe");
  }
  private init() {
    this.childProcess.on("close", (code: any) => {
      console.log(`child process exited with code ${code}`);
    });
    this.childProcess.stdout.on("data", (data: any) => {
      this.emit("data", data.toString());
    });
  }
}
