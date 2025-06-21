#include "Menu.h"
#include "Console.h"
#if defined(_WIN32)
    #include <conio.h>
#endif
#include <iostream>

using namespace std;

void drawMenu(int sel, const vector<string>& items)
{
    // Alternative but not good looking version:
    // \033[2J = clear entire screen; \033[H = move cursor to top-left
    // cout << "\033[2J\033[H";

    system("cls");

    cout << R"(
   _____         _    ____________ _____ 
  |_   _|       | |   | ___ \ ___ \  __ \
    | | _____  _| |_  | |_/ / |_/ / |  \/
    | |/ _ \ \/ / __| |    /|  __/| | __ 
    | |  __/>  <| |_  | |\ \| |   | |_\ \
    \_/\___/_/\_\\__| \_| \_\_|    \____/
    )" << endl;

    for (int i = 0; i < (int)items.size(); ++i)
    {
        if (i == sel)
        {
            // Turn on reverse-video: swap foreground and background
            cout << "\033[7m";
            // Print the selected item in white text
            coloredPrint(Color::White, " " + items[i] + "\n");
            // Reset colors and attributes to defaults
            cout << "\033[0m";
        }
        else
        {
            // Non-selected items in cyan
            coloredPrint(Color::Cyan, " " + items[i] + "\n");
        }
    }

    cout << "(Use Up and Down Arrow keys to change option and select with Enter)";
}

int getMenuChoice(const vector<string>& items)
{
    int sel = 0;

    drawMenu(sel, items);

    while (true)
    {
        // read one character from console
        int c = _getch();

        // special key prefix on Windows
        if (c == 224)
        {
            // actual code for arrow key
            int arrow = _getch();

            // Up arrow: move sel up, wrap to last if at 0
            if (arrow == 72)
            {
                sel = (sel + items.size() - 1) % items.size();
            }
            // Down arrow: move sel down, wrap to 0 if at last
            else if (arrow == 80)
            {
                sel = (sel + 1) % items.size();
            }

            // redraw with new highlight
            drawMenu(sel, items);
        }
        // Enter key ASCII code
        else if (c == 13)
        {
            // selection confirmed
            return sel;
        }
    }
}