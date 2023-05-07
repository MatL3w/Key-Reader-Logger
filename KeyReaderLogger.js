import { spawn } from "child_process";
import { EventEmitter } from "node:events";
export class KeyReaderLogger extends EventEmitter {
    childProcessKeyboard;
    childProcessMouse;
    constructor() {
        super();
    }
    startKeyboard() {
        this.childProcessKeyboard = spawn("kHook.exe");
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
        this.childProcessMouse = spawn("mHook.exe");
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
