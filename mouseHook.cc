#include <iostream>
#include <Windows.h>

// Mouse hook procedure
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {

            std::cout << "nCode: " <<  nCode << std::endl;
            std::cout << "wParam: " <<  wParam << std::endl;
            std::cout << "lParam: " <<  lParam << std::endl;
             MOUSEHOOKSTRUCT* pMouseHookStruct = reinterpret_cast<MOUSEHOOKSTRUCT*>(lParam);
        std::cout << "Mouse position: " << pMouseHookStruct->pt.x << ", " << pMouseHookStruct->pt.y << std::endl;
    }
    // Call the next hook procedure in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    // Install the mouse hook
    HHOOK hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    if (hMouseHook == NULL) {
        std::cerr << "Failed to install mouse hook" << std::endl;
        return 1;
    }
    // Run the message loop to process events
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        std::cout << "lol" << std::endl;
    }
    // Uninstall the mouse hook
    UnhookWindowsHookEx(hMouseHook);
    return 0;
}