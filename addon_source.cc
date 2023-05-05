
  #include <nan.h>
  #include <Windows.h>
  #include <iostream>
  using namespace std;
  using namespace Nan;
  using namespace v8;

  // Accepts 1 number from JavaScript, adds 42 and returns the result.
  NAN_METHOD(PassNumber) {

        POINT cursorPos;
        GetCursorPos(&cursorPos);
        std::cout << "Mouse position: x = " << cursorPos.x << ", y = " << cursorPos.y << std::endl;
        short keyState = GetAsyncKeyState('A');
        std::cout << "Is 'A' key pressed: " << keyState<< std::endl;
        Local<Number> retval = Nan::New(keyState);

        info.GetReturnValue().Set(retval);

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