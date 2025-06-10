#pragma once
#ifndef UI_H
#define UI_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h> 

// This is a true compile-time constant.
constexpr char BAR_CHAR = static_cast<char>(219);

void printBar(int current, int maximum, int barWidth, char fillChar = BAR_CHAR, char emptyChar = ' ');

#endif UI_H