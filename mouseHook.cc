#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501 // Target Windows XP or later
#include <Windows.h>
#include <Winuser.h>
#include <iostream>
// Mouse hook procedure
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MOUSEHOOKSTRUCT* pMouseHookStruct = reinterpret_cast<MOUSEHOOKSTRUCT*>(lParam);
        //  = reinterpret_cast<MOUSEHOOKSTRUCTEX*>(lParam);
        std::cout << "x: " << pMouseHookStruct->pt.x << std::endl
                  << "y: " << pMouseHookStruct->pt.y  << std::endl
                  << "dwExtraInfo: " << pMouseHookStruct->dwExtraInfo << std::endl;

        if (wParam == WM_LBUTTONDBLCLK) 
        {
            std::cout << "leftKey: click" << std::endl;
        }
        else if (wParam == WM_LBUTTONDOWN) 
        {
             std::cout << "leftKey: down" << std::endl;
        }
        else if (wParam == WM_LBUTTONUP) 
        {
             std::cout << "leftKey: up" << std::endl;
        }
        else if (wParam == WM_RBUTTONDOWN) 
        {
            std::cout << "rightKey: down" << std::endl;
        }
        else if (wParam == WM_RBUTTONDBLCLK) 
        {
            std::cout << "rightKey: click" << std::endl;
        }
        else if (wParam == WM_RBUTTONUP) 
        {
            std::cout << "rightKey: up" << std::endl;
        }
        else if (wParam == WM_MOUSEWHEEL) 
        {
            std::cout << "scroll: WM_MOUSEWHEEL"<< std::endl;
            std::cout << "HIWORD"<< HIWORD(wParam) <<std::endl;
            std::cout << "HIWORD"<< (wParam) <<std::endl;
            std::cout << WM_XBUTTONDOWN<< std::endl;
        }
        // int fwKeys = GET_KEYSTATE_WPARAM(wParam);
        // int wheelDelta = HIWORD(wParam);
        // std::cout << "scroll: " << wheelDelta << std::endl;
        // std::cout << "_WIN32_WINNT: " << _WIN32_WINNT<< std::endl;
        // std::cout << "scroll: " << fwKeys << std::endl;
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