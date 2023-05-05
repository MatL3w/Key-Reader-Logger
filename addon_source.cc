
  #include <nan.h>
  #include <Windows.h>
  #include <iostream>
  using namespace std;
  using namespace Nan;
  using namespace v8;

  // Accepts 1 number from JavaScript, adds 42 and returns the result.
  NAN_METHOD(PassNumber) {

        short keyState = GetAsyncKeyState('A');

        // Check if the key is currently pressed
        bool isKeyPressed = (keyState & 0x8000) != 0;

        // Check if the key was pressed since the last time the function was called
        bool wasKeyPressed = (keyState & 0x0001) != 0;

        if(wasKeyPressed){
            std::cout << "Was 'A' key pressed: " << wasKeyPressed << std::endl;
            info.GetReturnValue().Set(wasKeyPressed);
        }
        else{
          return;
        }    
  }

  // Called by the NODE_MODULE macro below, 
  // exposes a pass_number method to JavaScript, which maps to PassNumber 
  // above.
  NAN_MODULE_INIT(Init) {
     Nan::Set(target, New<String>("pass_number").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(PassNumber)).ToLocalChecked());
  }

  // macro to load the module when require'd
  NODE_MODULE(my_addon, Init)