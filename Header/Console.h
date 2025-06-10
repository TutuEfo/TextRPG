#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

using namespace std;

enum class Color {
    Default,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
};

// Initialize console for ANSI
void initConsole();

void setColor(Color c);

void resetColor();

void coloredPrint(Color c, const string& message);

#endif // CONSOLE_H