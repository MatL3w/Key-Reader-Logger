import { spawn } from "child_process";
import { EventEmitter } from "node:events";
export class KeyReaderLogger extends EventEmitter {
    childProcess;
    constructor() {
        super();
        this.start();
        this.init();
    }
    start() {
        this.childProcess = spawn("kHook.exe");
    }
    init() {
        this.childProcess.on("close", (code) => {
            console.log(`child process exited with code ${code}`);
        });
        this.childProcess.stdout.on("data", (data) => {
            this.emit("data", data.toString());
        });
    }
}
