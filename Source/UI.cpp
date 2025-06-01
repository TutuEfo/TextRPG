#include "UI.h"
#include <iostream>

using namespace std;

void printBar(int current, int maximum, int barWidth, char fillChar, char emptyChar)
{
    if (maximum <= 0 || barWidth <= 0)
    {
        cout << "[Invalid bar parameters]";
        return;
    }

    if (current < 0)
    {
        current = 0;
    }

    if (current > maximum)
    {
        current = maximum;
    }

    // Calculate how many “columns” of the bar should be filled: round((current/maximum) * barWidth)
    int filledWidth = static_cast<int>((static_cast<double>(current) / maximum) * barWidth + 0.5);

    // If filledWidth exceeds barWidth, clamp it to barWidth
    if (filledWidth > barWidth)
    {
        filledWidth = barWidth;
    }

    // If filledWidth is below 0, clamp it to 0
    if (filledWidth < 0)
    {
        filledWidth = 0;
    }


    cout << "|";

    for (int i = 0; i < filledWidth; ++i)
    {
        cout << fillChar;
    }

    for (int i = filledWidth; i < barWidth; ++i)
    {
        cout << emptyChar;
    }

    cout << "| " << current << "/" << maximum;
}