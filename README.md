# Key-Reader-Logger
ENABLE ONLY ON WINDOWS
Package provide utility to capture input data from keyboard and mouse. Consist of two separete process wrote in cpp(source file included).Those process create windows hooks to capture data;

Work of  class KeyReaderLogger base on two events: "keyData" and "mouseData";

kLog.on('mouseData',(data)=>{
  console.log(data);
});

kLog.on("keyData", (data) => {
  console.log(data);
});

Remember to use function start() to initialize subprocess.
See example in example.js.