#include <iostream>
#include <Windows.h>
#include <fstream>

std::ofstream fileStream;
HHOOK hKeyboardHook;
// Keyboard hook procedure
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboardHookStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        if (wParam == WM_KEYDOWN) {
            std::cout << "type: " << "KeyPressed" << std::endl
                      << "vkCode: " << pKeyboardHookStruct->vkCode << std::endl
                      << "scanCode: " << pKeyboardHookStruct->scanCode << std::endl
                      << "time: " << pKeyboardHookStruct->time << std::endl;
        }
        else if (wParam == WM_KEYUP) {
            std::cout << "type: " << "KeyReleased" << std::endl
                      << "vkCode: " << pKeyboardHookStruct->vkCode << std::endl
                      << "scanCode: " << pKeyboardHookStruct->scanCode << std::endl
                      << "time: " << pKeyboardHookStruct->time << std::endl;
        }
    }
    // Call the next hook procedure in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void cleanup() {
    UnhookWindowsHookEx(hKeyboardHook);
}

int main() {
    // Install the keyboard hook
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hKeyboardHook == NULL) {
        std::cerr << "Failed to install keyboard hook" << std::endl;
        return 1;
    }
    std::atexit(cleanup);

    // Run the message loop to process events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    // Uninstall the keyboard hook
    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}