#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Map.h"

Map::Map()
{
    int x = rand() % 15 + 1;
    int y = rand() % 15 + 1;

    generateRandomMap(x, y);
}

void Map::generateRandomMap(int x, int y)
{
    grid.resize(x, vector<char>(y, '.'));

    for (int i = 0; i < x; ++i)
    {
        grid[i][0] = grid[i][y - 1] = 'W';
    }

    for (int j = 0; j < y; ++j)
    {
        grid[0][j] = grid[x - 1][j] = 'W';
    }

    for (int i = 1; i < x - 1; ++i)
    {
        for (int j = 1; j < y - 1; ++j)
        {
            int r = rand() % 100;

            if (r < 10)
            {
                grid[i][j] = 'D';
            }
            else if (r < 25)
            {
                grid[i][j] = 'T';
            }
            else
            {
                grid[i][j] = '.';
            }
        }
    }

    grid[x / 2][y / 2] = 'S';
    grid[1][(y - 2) + 1] = 'B';
    grid[1][y - 2] = 'N';

    grid[x - 2][y - 2] = 'P';
    playerX = x - 2;
    playerY = y - 2;
}

void Map::display() const
{
    for (const auto& row : grid)
    {
        for (char tile : row)
        {
            cout << tile << ' ';
        }

        cout << '\n';
    }
}

void Map::movePlayer(char direction)
{
    int newX = playerX;
    int newY = playerY;

    switch (tolower(direction))
    {
    case 'w':
    {
        newX--;

        break;
    }
    case 's':
    {
        newX++;

        break;
    }
    case 'a':
    {
        newY--;
        
        break;
    }
    case 'd':
    {
        newY++;
        
        break;
    }
    }

    if (grid[newX][newY] == '.')
    {
        grid[playerX][playerY] = '.';
        playerX = newX;
        playerY = newY;
        grid[playerX][playerY] = 'P';
    }
    else if (grid[newX][newY] == 'W')
    {
        grid[playerX][playerY] = 'P';

        cout << ">> Can't move there! It is a wall." << endl;
    }
    else if (grid[newX][newY] == 'S')
    {
        cout << "Welcome to the Shop!" << endl;
    }
    else if (grid[newX][newY] == 'D')
    {
        cout << ">> Entering the dungeon!" << endl;
    }
    else if (grid[newX][newY] == 'B')
    {
        cout << ">> A powerful BOSS is approaching!" << endl;
    }
    else if (grid[newX][newY] == 'N')
    {
        cout << "Moving on to the next room!" << endl;
    }
    else if (grid[newX][newY] == 'T')
    {
        cout << ">> It is a trap!" << endl;
    }
    else 
    {
        cout << "How did you get here!" << endl;
    }
}