#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Map.h"
#include "Combat.h"
#include "Enemy.h"
#include "Console.h"
#include "Necromancer.h"

static void printTile(char tile)
{
    switch (tile)
    {
    case '#':
    {
        coloredPrint(Color::Blue, "# ");
        break;
    }
    case '.':
    {
        cout << ". ";
        break;
    }
    case 'D':
    {
        coloredPrint(Color::BrightBlue, "D ");
        break;
    }
    case 'T':
    {
        coloredPrint(Color::BrightRed, "T ");
        break;
    }
    case 'S':
    {
        coloredPrint(Color::Yellow, "S ");
        break;
    }
    case 'B':
    {
        coloredPrint(Color::Red, "B ");
        break;
    }
    case 'N':
    {
        coloredPrint(Color::Yellow, "N ");
        break;
    }
    case 'P':
    {
        coloredPrint(Color::Cyan, "P ");
        break;
    }
    case 'R':
    {
        coloredPrint(Color::BrightCyan, "R ");
        break;
    }
    default:
    {
        cout << tile << ' ';
        break;
    }
    }
}

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
    grid.assign(x, vector<char>(y, '.'));

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
    grid[1][(y - 2) + 1] = 'R';
    grid[1][y - 2] = 'B';

    grid[x - 2][y - 2] = 'P';
    playerX = x - 2;
    playerY = y - 2;

    //const char* roles[] = { "Elder","Blacksmith","Healer","Guard","Merchant" };
    //const char* dialogs[] = {
    //    ">> Hello there, traveler!",
    //    ">> Our village needs your help!",
    //    ">> Beware the wolves in the woods.",
    //    ">> Please find my lost amulet."
    //};
    //const int  ROLENUM = sizeof(roles) / sizeof(roles[0]);
    //const int  DLGNUM = sizeof(dialogs) / sizeof(dialogs[0]);

    //int rRole = rand() % ROLENUM;
    //int rDialog = rand() % DLGNUM;
    //int x = std::rand() % columns();
    //int y = std::rand() % ();

    //std::string id = std::string(roles[rRole]) + "_" + std::to_string(rRole);

    //NPC npc(id, roles[rRole], x, y);
    //npc.addDialogLine(dialogs[rDialog]);
    //npc.setQuest(player->generateRandomQuest(roles[rRole]));
    //addNPC(npc);
}

void Map::display() const
{
    for (int i = 0; i < (int)grid.size(); ++i)
    {
        for (int j = 0; j < (int)grid[i].size(); ++j)
        {
            bool drawn = false;
            for (auto const& npc : npcs)
            {
                if (npc.getX() == i && npc.getY() == j)
                {
                    printTile(npc.getSymbol());
                    drawn = true;
                    break;
                }
            }

            if (!drawn)
            {
                printTile(grid[i][j]);
            }
        }
        std::cout << '\n';
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

    for (auto& npc : npcs)
    {
        if (npc.getX() == newX && npc.getY() == newY)
        {
            npc.interact(*player);

            std::cout << ">> Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            return;
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
    case 'B':
    {
        Enemy boss = Enemy::generateBoss(player->getLevel());
        Combat battle(*player, boss);

        if (!battle.runCombat())
        {
            exit(0);
        }

        player->addGold(boss.getGoldRewardBoss() + 5);
        player->setXP(boss.getXPRewardBoss() + 5);

        int itemChance;
        itemChance = rand() % 5;

        if (itemChance == 2)
        {
            coloredPrint(Color::Yellow, "\n>> ITEM DROP!\n");

            player->addItem(boss.getItemRewardBoss());
        }

        cout << ">> Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        break;
    }
    case 'T':
    {
        cout << ">> Trap! -10 HP";

        player->takeDamage(10);

        cout << "\n>> Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        break;
    }
    case 'S':
    {
        cout << ">> Shop time!\n";
        
        shopMenu(player);

        break;
    }
    case 'R':
    {
        cout << ">> Descending to next level...\n";

        int newWidth = rand() % 15 + 15;
        int newHeight = rand() % 15 + 15;

        generateRandomMap(newWidth, newHeight);

        playerX = newWidth - 2;
        playerY = newHeight - 2;

        grid[playerX][playerY] = 'P';

        cout << ">> Press Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

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

            player->addGold(e.getGoldReward() + 5);
            player->gainXP(e.getXPReward() + 5);

            int itemChance;
            itemChance = rand() % 5;

            if (itemChance == 2)
            {
                coloredPrint(Color::Yellow, "\n>> ITEM DROP!\n");

                player->addItem(e.getItemReward());
            }

            cout << ">> Press Enter to continue to the next enemy...";

            cin.get();

            count--;
        }

        cout << ">> Press Enter to exit dungeon...";
        cin.get();

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
    if (player == nullptr)
    {
        return;
    }

    int choice = 0;

    string name = player->getNickName();

    while (choice != 3)
    {
        coloredPrint(Color::Yellow, "\n===== SHOP =====");
        cout << endl;

        int option, amount;
        cout << ">> Gold: " << player->getGold() << endl;
        cout << "1) Health Potion (" + to_string(20 * player->getLevel()) + " gold)" << endl;
        cout << "2) Mana Potion (" + to_string(20 * player->getLevel()) + " gold)" << endl; // For Mage Class
        cout << "3) Strength Potion (" + to_string(30 * player->getLevel()) + " gold)" << endl;
        cout << "4) Defence Potion (" + to_string(30 * player->getLevel()) + " gold)" << endl;
        cout << "5) Summon Potion (" + to_string(30 * player->getLevel()) + " gold)" << endl;
        cout << "6) Exit" << endl;
        cout << ">> Choose an option: ";
        cin >> option;

        switch (option)
        {
        case 1:

            cout << "Enter amount: ";
            cin >> amount;

            if (player->getGold() >= 20 * amount)
            {
                player->addHealthPotion(amount);
                player->addGold(-20 * amount);
                coloredPrint(Color::Green, ">> " + name + " bought " + to_string(amount) + " Health Potion(s)!\n");
            }
            else
            {
                coloredPrint(Color::Red, ">> Not enough gold!\n");
            }

            break;

        case 2:
            if (Mage* mage = dynamic_cast<Mage*>(player))
            {
                cout << "Enter amount: ";
                cin >> amount;

                if (player->getGold() >= 25 * amount)
                {
                    mage->addManaPotion(amount);
                    player->addGold(-25 * amount);
                    coloredPrint(Color::Cyan, ">> " + name + " bought " + to_string(amount) + " Mana Potion(s)!\n");
                }
                else
                {
                    coloredPrint(Color::Red, ">> Not enough gold!\n");
                }
            }
            else if (Necromancer* necro = dynamic_cast<Necromancer*>(player))
            {
                cout << "Enter amount: ";
                cin >> amount;

                if (player->getGold() >= 25 * amount)
                {
                    necro->addManaPotion(amount);
                    player->addGold(-25 * amount);
                    coloredPrint(Color::Cyan, ">> " + name + " bought " + to_string(amount) + " Mana Potion(s)!\n");
                }
                else
                {
                    coloredPrint(Color::Red, ">> Not enough gold!\n");
                }
            }
            else
            {
                coloredPrint(Color::Red, ">> Only Mages/Necromancer can buy a mana potions!\n");
            }

            break;
        case 3:

            cout << "Enter amount: ";
            cin >> amount;

            if (player->getGold() >= 30 * amount)
            {
                player->addStrengthPotion(amount);
                player->addGold(-30 * amount);
                coloredPrint(Color::Green, ">> " + name + " bought " + to_string(amount) + " Strength Potion(s)!\n");
            }
            else
            {
                coloredPrint(Color::Red, ">> Not enough gold!\n");
            }

            break;
        case 4:

            cout << "Enter amount: ";
            cin >> amount;

            if (player->getGold() >= 30 * amount)
            {
                player->addDefencePotion(amount);
                player->addGold(-30 * amount);
                coloredPrint(Color::Green, ">> " + name + " bought " + to_string(amount) + " Defence Potion(s)!\n");
            }
            else
            {
                coloredPrint(Color::Red, ">> Not enough gold!\n");
            }

            break;
        case 5:
            if (Necromancer* necro = dynamic_cast<Necromancer*>(player))
            {
                cout << "Enter amount: ";
                cin >> amount;

                if (player->getGold() >= 25 * amount)
                {
                    necro->addSummonPotions(amount);
                    player->addGold(-25 * amount);
                    coloredPrint(Color::Cyan, ">> " + name + " bought " + to_string(amount) + " Mana Potion(s)!\n");
                }
                else
                {
                    coloredPrint(Color::Red, ">> Not enough gold!\n");
                }
            }
            else
            {
                coloredPrint(Color::Red, ">> Only Necromancer can buy a mana potions!\n");
            }

            break;
        case 6:
            cout << ">> Leaving the shop..." << endl;

            return;

        default:
            coloredPrint(Color::Red, ">> Invalid choice!\n");
        }
    }

    cout << ">> Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

MapSnapshot Map::makeSnapshot() const
{
    MapSnapshot snap;

    snap.rows = grid.size();
    snap.cols = grid[0].size();
    snap.playerX = playerX;
    snap.playerY = playerY;

    // Allocate space for each row�s string
    snap.rowsData.resize(snap.rows);
    
    for (int i = 0; i < snap.rows; ++i)
    {
        // Convert the row�s vector<char> into a single string
        snap.rowsData[i].assign(grid[i].begin(), grid[i].end());
    }
        
    return snap;
}

void Map::loadSnapshot(const MapSnapshot& s)
{
    grid.assign(s.rows, vector<char>(s.cols));

    // Copy every saved character into the newly-sized grid
    for (int i = 0; i < s.rows; ++i) {
        for (int j = 0; j < s.cols; ++j) {
            grid[i][j] = s.rowsData[i][j];
        }
    }
        
    playerX = s.playerX;
    playerY = s.playerY;
}

void Map::addNPC(const NPC &n)
{
    npcs.push_back(n);
}

// I introduced a MapSnapshot struct to capture the dungeon�s size, the player�s X / Y, and each row of tiles as a string via makeSnapshot().
// When you hit Save, I write your character data first, then dump those snapshot fields�rows, cols, playerX, playerY�and each row string into the file.
// On load, I read everything back into a new MapSnapshot, then call map.loadSnapshot(), which does grid.assign(rows, vector<char>(cols)) to rebuild an
// exact size grid and copies each saved character into it, restoring the exact map layout and player position you had.