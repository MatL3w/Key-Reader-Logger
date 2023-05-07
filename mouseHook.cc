#include <Windows.h>
#include <iostream>

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        // MOUSEHOOKSTRUCTEX* pMouseHookStruct = reinterpret_cast<MOUSEHOOKSTRUCTEX*>(lParam);
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
        std::cout << "x: " << pMouseStruct->pt.x << std::endl
                  << "y: " << pMouseStruct->pt.y  << std::endl
                  << "time: " << pMouseStruct->time << std::endl;
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
        if (wParam == WM_MOUSEWHEEL) 
        {
            int delta = GET_WHEEL_DELTA_WPARAM(pMouseStruct->mouseData);
            int direction = (delta > 0) ? 1 : -1;
            std::cout << "scrollDirection: "  << direction <<std::endl;
        }
        if (wParam == WM_MBUTTONDOWN ) {
            std::cout << "scroll:" << "down"<< std::endl;
        }
        if (wParam == WM_MBUTTONUP ) {
            std::cout << "scroll:" << "up"<< std::endl;
        }
    }
    // Call the next hook procedure in the chain
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    // Install the mouse hook
    std::cout << _WIN32_WINNT<< std::endl;
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