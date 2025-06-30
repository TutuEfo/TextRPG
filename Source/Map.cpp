#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Map.h"
#include "Combat.h"
#include "Enemy.h"

Map::Map()
{
    srand(static_cast<unsigned>(time(nullptr)));

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

    char tile = grid[newX][newY];

    if (grid[newX][newY] == 'W')
    {
        grid[playerX][playerY] = 'P';

        cout << ">> Can't move there! It is a wall." << endl;

        return;
    }

    grid[playerX][playerY] = '.';
    playerX = newX;
    playerY = newY;
    grid[playerX][playerY] = 'P';
    
    triggerTile(tile);
}

int Map::getPlayerX() const
{
    return playerX;
}

int Map::getPlayerY() const
{
    return playerY;
}

char Map::getTile(int x, int y) const
{
    return grid[x][y];
}

void Map::triggerTile(char tile)
{
    switch (tile)
    {
    case 'E':
    {
        
        break;
    }
    case 'B':
    {
        
        break;
    }
    case 'T':
    {
        cout << ">> Trap! –10 HP\n";

        break;
    }
    case 'S':
    {
        cout << ">> Shop time!\n";

        break;
    }
    case 'N':
    {

        cout << ">> Descending to next level...\n";

        generateRandomMap(rand() % 10 + 10, rand() % 10 + 10);

        break;
    }
    case 'D':
    {
        cout << ">> You step into the dungeon depths.\n";

        break;
    }
    default:
    {
        break;
    }
    }
}