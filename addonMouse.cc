#include <node.h>
#include <Windows.h>
#include <iostream>
#include <string>

  using namespace std;
  using namespace Nan;
  using namespace v8;
HHOOK g_hMouseHook;
HANDLE g_hPipe;

// Mouse hook procedure
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        MSLLHOOKSTRUCT* pMouseHookStruct = reinterpret_cast<MSLLHOOKSTRUCT*>(lParam);
        if (wParam == WM_MOUSEMOVE) {
            // Send the mouse position to the named pipe
            if (g_hPipe != INVALID_HANDLE_VALUE) {
                std::string message = std::to_string(pMouseHookStruct->pt.x) + "," + std::to_string(pMouseHookStruct->pt.y);
                DWORD bytesWritten;
                WriteFile(g_hPipe, message.c_str(), message.length(), &bytesWritten, NULL);
            }
        }
    }
    // Call the next hook procedure in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void InstallMouseHook(const v8::FunctionCallbackInfo<v8::Value>& args) {
    // Get the name of the named pipe from the arguments
    v8::String::Utf8Value pipeName(args[0]->ToString());
    std::string pipeNameStr(*pipeName);

    // Create the named pipe
    g_hPipe = CreateNamedPipe(pipeNameStr.c_str(), PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);
    if (g_hPipe == INVALID_HANDLE_VALUE) {
        return;
    }

    // Wait for the client to connect to the named pipe
    if (!ConnectNamedPipe(g_hPipe, NULL)) {
        return;
    }

    // Install the mouse hook
    g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    if (g_hMouseHook == NULL) {
        return;
    }
}