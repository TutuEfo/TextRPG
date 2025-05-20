#include "Console.h"
#include <iostream>

#if defined(_WIN32)
#include <windows.h>
#endif

using namespace std;

// ANSI escape codes for colors
static const string ANSI_CODES[] = {
    "\033[0m",      // Default
    "\033[31m",     // Color Red
    "\033[32m",     // Color Green
    "\033[33m",     // Color Yellow
    "\033[34m",     // Color Blue
    "\033[35m",     // Color Magenta
    "\033[36m",     // Color Cyan
    "\033[37m"      // Color White
};

void initConsole()
{

#if defined(_WIN32)
    // Gets a handle to the standard output device.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // Declares a variable "dwMode" to store the current console mode.
    DWORD dwMode = 0;
    // Gets the current mode of the console associated with the "hOut" and stores it in "dwMode"
    GetConsoleMode(hOut, &dwMode);
    // Sets the ENABLE_VIRTUAL_TERMINAL_PROCESSING flag in "dwMode" This enables ANSI escape code processing.
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    // Applies the updated mode back to the console so that we can use ANSI codes.
    SetConsoleMode(hOut, dwMode);

#endif

}

void setColor(Color c)
{
    cout << ANSI_CODES[static_cast<int>(c)];
}

void resetColor()
{
    cout << ANSI_CODES[static_cast<int>(Color::Default)];
}

void coloredPrint(Color c, const string& message)
{
    setColor(c);

    cout << message;

    resetColor();
}
