#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Map.h"
#include "Combat.h"
#include "Enemy.h"
#include "Console.h"

Map::Map(Character *p) : player(p)
{
    srand(static_cast<unsigned>(time(nullptr)));

    int x = rand() % 15 + 15;
    int y = rand() % 15 + 15;

    generateRandomMap(x, y);
}

void Map::setPlayer(Character* p)
{
    player = p;
}

void Map::generateRandomMap(int x, int y)
{
    grid.resize(x, vector<char>(y, '.'));

    for (int i = 0; i < x; ++i)
    {
        grid[i][0] = grid[i][y - 1] = '#';
    }

    for (int j = 0; j < y; ++j)
    {
        grid[0][j] = grid[x - 1][j] = '#';
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
    grid[1][(y - 2) + 1] = 'N';
    grid[1][y - 2] = 'B';

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

    if (grid[newX][newY] == '#')
    {
        grid[playerX][playerY] = 'P';

        cout << ">> Can't move there! It is a wall." << endl;

        cout << ">> Press Enter to continue...";
        cin.ignore();
        cin.get();

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
        Enemy e = Enemy::generateEnemy(player->getLevel());
        Combat battle(*player, e);

        if (!battle.runCombat())
        {
            exit (0);
        }

        break;
    }
    case 'B':
    {
        Enemy boss = Enemy::generateBoss(player->getLevel());
        Combat battle(*player, boss);

        if (!battle.runCombat())
        {
            exit(0);
        }

        break;
    }
    case 'T':
    {
        cout << ">> Trap! -10 HP\n";

        player->takeDamage(10);

        cout << ">> Press Enter to continue...";
        cin.ignore();
        cin.get();

        break;
    }
    case 'S':
    {
        cout << ">> Shop time!\n";
        
        shopMenu(player);

        cout << ">> Press Enter to continue...";
        cin.ignore();
        cin.get();

        break;
    }
    case 'N':
    {
        cout << ">> Descending to next level...\n";

        int newWidth = rand() % 10 + 10;
        int newHeight = rand() % 10 + 10;

        generateRandomMap(newWidth, newHeight);

        playerX = newWidth - 2;
        playerY = newHeight - 2;

        grid[playerX][playerY] = 'P';

        break;
    }
    case 'D':
    {
        cout << ">> You step into the dungeon depths.\n";

        int count = 5;

        while (count > 0)
        {
            Enemy e = Enemy::generateEnemy(player->getLevel());
            Combat battle(*player, e);

            if (!battle.runCombat())
            {
                exit(0);
            }

            count--;
        }

        break;
    }
    default:
    {
        break;
    }
    }
}

void Map::shopMenu(Character *player)
{
    int choice = 0;

    string name = player->getNickName();

    while (choice != 3)
    {
        coloredPrint(Color::Yellow, "\n===== SHOP =====");
        cout << endl;
        cout << ">> Gold: " << player->getGold() << endl;
        cout << "1) Health Potion (20 gold)" << endl;
        cout << "2) Mana Potion (25 gold)" << endl; // For Mage Class
        cout << "3) Exit" << endl;
        cout << ">> Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (player->getGold() >= 20)
            {
                player->addHealthPotion(1);
                player->addGold(-20);
                coloredPrint(Color::Green, ">> " + name + " bought Health Potion!\n");
            }
            else
            {
                coloredPrint(Color::Red, ">> Not enough gold!\n");
            }

            break;

        case 2:
            if (Mage* mage = dynamic_cast<Mage*>(player))
            {
                if (player->getGold() >= 25)
                {
                    mage->addManaPotion(1);
                    player->addGold(-25);
                    coloredPrint(Color::Cyan, ">> " + name + " bought Mana Potion!\n");
                }
                else
                {
                    coloredPrint(Color::Red, ">> Not enough gold!\n");
                }
            }
            else
            {
                coloredPrint(Color::Red, ">> Only Mages can buy mana potions!\n");
            }

            break;

        case 3:
            cout << ">> Leaving the shop..." << endl;

            break;

        default:
            coloredPrint(Color::Red, ">> Invalid choice!\n");
        }
    }
}