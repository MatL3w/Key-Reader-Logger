// import KeyReaderLogger from "./KeyReaderLogger.js";
import  {KeyReaderLogger} from "key-reader-logger";

const k = new KeyReaderLogger();
const kLog = new KeyReaderLogger();
kLog.startAll();
kLog.on('mouseData',(data)=>{
  console.log(data);
});
kLog.on("keyData", (data) => {
  console.log(data);
});