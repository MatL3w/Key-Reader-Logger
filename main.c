#include <Windows.h>
#include <iostream>

int main()
{
    while (true)
    {
        // Check the state of the 'A' key
        short keyState = GetAsyncKeyState('A');

        // Check if the key is currently pressed
        bool isKeyPressed = (keyState & 0x8000) != 0;

        // Check if the key was pressed since the last time the function was called
        bool wasKeyPressed = (keyState & 0x0001) != 0;

        // Print the results to the console
        std::cout << "Is 'A' key pressed: " << isKeyPressed << std::endl;
        std::cout << "Was 'A' key pressed: " << wasKeyPressed << std::endl;

        // Wait for a short period of time
        Sleep(100);
    }

    return 0;
}