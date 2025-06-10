#pragma once

#include <vector>
#include <string>

// Draws a vertical menu of "items", highlighting index "select".
void drawMenu(int select, const std::vector<std::string>& items);

// Runs the Arrow key + Enter loop and returns the zero based chosen index.
int getMenuChoice(const std::vector<std::string>& items);