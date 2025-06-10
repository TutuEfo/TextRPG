#include "Character.h"
#include "Enemy.h"
#include "Mage.h"
#include "Console.h"
#include "SaveLoad.h"
#include "Combat.h"
#include "Menu.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <optional>
#include <limits>
#include <iomanip>

using namespace std;

void showLoadMenu(Character*& player)
{
    auto files = SaveLoad::listSaveFiles();

    if (files.empty())
    {
        cout << ">> No save files found.\n";

        return;
    }

    cout << "\n========== Load Game ==========\n";

    for (size_t i = 0; i < files.size(); ++i)
    {
        auto mdOpt = SaveLoad::readMetadata(files[i]);

        if (mdOpt)
        {
            auto& md = *mdOpt;

            cout << setw(2) << (i + 1) << ") "
                << "[" << md.className << "] "
                << md.nickName << " "
                << "(Lvl " << md.level
                << ", HP " << md.health
                << ", Gold " << md.gold
                << ")  [" << md.timestamp
                << "]\n";
        }
        else
        {
            cout << setw(2) << (i + 1) << ") "
                << files[i] << "  (Save file corrupted)\n";
        }
    }

    int choice;
    cout << "\n>> Enter number to load (0 to cancel): ";

    while (!(cin >> choice) || choice < 0 || choice > (int)files.size())
    {
        cin.clear();
        // Throw everyhting in the buffer, to enter an input again.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ">> Please enter 0 to " << files.size() << ": ";
    }

    if (choice == 0)
    {
        return;
    }

    const string& sel = files[choice - 1];

    cout << ">> Load \"" << sel << "\"? (y/n): ";
    char c; cin >> c;

    if (c == 'y' || c == 'Y')
    {
        auto mdOpt = SaveLoad::readMetadata(sel);

        if (!mdOpt)
        {
            cout << ">> Error: could not read save metadata.\n";
            return;
        }

        auto& md = *mdOpt;
        // Delete any old player
        delete player;

        // Instantiate the right subclass using the saved nickname
        if (md.className == "Mage")
        {
            player = new Mage(md.nickName);
        }
        else
        {
            player = new Character(md.nickName);
        }

        if (SaveLoad::loadGame(*player, sel))
        {
            cout << ">> Loaded \"" << sel << "\" successfully.\n";
        }
        else
        {
            cout << ">> Failed to load \"" << sel << "\".\n";
        }
    }
}

void doSave(const Character& player)
{
    // 1) Ask the user for a filename
    cout << ">> Enter save filename: ";
    string fname;
    cin >> fname;

    // 2) Try to write the player's data to that file
    try
    {
        SaveLoad::saveGame(player, fname);
        cout << ">> Game saved to " << fname << "\n";
    }
    catch (exception& e){
        // 3) If something goes wrong (e.g. disk error), report it
        cerr << ">> Save failed: " << e.what() << "\n";
    }
}

void doLoad(Character& player)
{
    // 1) Ask the user for the savefile name
    cout << ">> Enter filename to load: ";
    string fname;
    cin >> fname;

    // 2) Call loadGame, which returns true on success
    if (SaveLoad::loadGame(player, fname))
    {
        cout << ">> Loaded " << fname << "\n";
    }
    else
    {
        // 3) If open or parsing failed, let the user know
        cerr << ">> Load failed: could not open!" << fname << "\n";
    }
}

void doDelete()
{
    auto files = SaveLoad::listSaveFiles();

    if (files.empty())
    {
        cout << ">> No save files found.\n";

        return;
    }

    cout << "\n========== Saved Games ==========\n";

    for (size_t i = 0; i < files.size(); ++i)
    {
        auto mdOpt = SaveLoad::readMetadata(files[i]);

        if (mdOpt)
        {
            cout << "File name: " << files[i] << endl;

            auto& md = *mdOpt;

            cout << setw(2) << (i + 1) << ") "
                << "[" << md.className << "] "
                << md.nickName << " "
                << "(Lvl " << md.level
                << ", HP " << md.health
                << ", Gold " << md.gold
                << ")  [" << md.timestamp
                << "]\n\n";
        }
        else
        {
            cout << setw(2) << (i + 1) << ") " << files[i] << "  (Save file corrupted)\n";
        }
    }

    cout << ">> Enter filename to remove (0 to cancel): ";

    string fname;
    cin >> fname;

    if (fname == "0")
    {
        return;
    }

    bool removed = SaveLoad::deleteSave(fname);

    if (removed)
    {
        cout << ">> " << fname + " " + "removed!" << endl;
    }
    else
    {
        cout << ">> " << fname + " " + "remove failed!" << endl;
    }
}

void shopMenu(Character& player)
{
    int choice = 0;

    while (choice != 3)
    {
        coloredPrint(Color::Yellow, "\n===== SHOP =====");
        cout << endl;
        cout << ">> Gold: " << player.getGold() << endl;
        cout << "1) Buy Health Potion (20 gold)" << endl;
        cout << "2) Buy Mana Potion (25 gold)" << endl; // For Mage Class
        cout << "3) Exit Shop" << endl;
        cout << ">> Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (player.getGold() >= 20)
            {
                player.addHealthPotion(1);
                player.addGold(-20);
                coloredPrint(Color::Green, ">> You bought 1 Health Potion!");
            }
            else
            {
                coloredPrint(Color::Red, ">> Not enough gold!");
            }

            break;

        case 2:
            if (Mage* mage = dynamic_cast<Mage*>(&player))
            {
                if (player.getGold() >= 25)
                {
                    mage->addManaPotion(1);
                    player.addGold(-25);
                    coloredPrint(Color::Cyan, ">> You bought 1 Mana Potion!");
                }
                else
                {
                    coloredPrint(Color::Red, ">> Not enough gold!");
                }
            }
            else
            {
                coloredPrint(Color::Red, ">> Only Mages can buy mana potions!");
            }

            break;

        case 3:
            cout << ">> Leaving the shop..." << endl;

            break;

        default:
            coloredPrint(Color::Red, ">> Invalid choice!");
        }
    }
}

void chooseClass()
{
    cout << "Choose your hero" << endl;
    cout << "1) Default" << endl;
    cout << "2) Mage" << endl;
    // cout << "3) Necromancer" << endl;
    cout << ">> Enter you choice: ";
}

int gameMenu(Character &player)
{
    Quest quest;
    // Quest Panel:
    if (!player.getHasQuests())
    {
        const string types[] = { "Goblin", "Orc", "Bandit", "Troll" };
        int typeIndex = rand() % 4;

        string name = types[typeIndex];

        int count;
        count = rand() % 3 + 5;

        int randomXP;
        randomXP = rand() % 26 + 25;

        int randomGold;
        randomGold = rand() % 41 + 10;

        quest = { "Defeat " + to_string(count) + " " + name, name, count, 0, randomXP, randomGold };

        player.addQuest(quest);

        player.setHasQuests(true);
    }

    // Normal Enemy & Boss:
    Enemy randomEnemy;
    if (player.getLevel() % 5 == 0)
    {
        coloredPrint(Color::Red, "\n>> A powerful enemy is approaching...\n");
        randomEnemy = Enemy::generateBoss(player.getLevel());
    }
    else
    {
        randomEnemy = Enemy::generateEnemy(player.getLevel());
    }

    // Combat loop:
    Combat battle(player, randomEnemy);
    bool survived = battle.runCombat();


    // Reward Panel: 
    if (survived && !player.getEscapeBattle())
    {
        player.checkQuestCompletion(randomEnemy.getEnemyName());

        if (player.getLevel() % 5 == 0)
        {
            player.gainXP(randomEnemy.getXPRewardBoss());
            player.addGold(randomEnemy.getGoldRewardBoss());

        }
        else
        {
            player.gainXP(randomEnemy.getXPReward());
            player.addGold(randomEnemy.getGoldReward());
        }

        cout << ">> " << player.getNickName() << " defeated the " << randomEnemy.getEnemyName() << "!" << endl;

    }
    
    if (!survived)
    {
        cout << "\n======================================" << endl;
        cout << ">> " << player.getNickName() << " has been defeated!" << endl;
        cout << ">> GAME OVER!!" << endl;
        cout << "======================================" << endl;

        return 0;
    }

    // Post Combat Panel:
    int choice = 0;
    while (choice < 1 || choice > 3)
    {
        coloredPrint(Color::Green, "\n========== Post Combat Menu ==========");
        cout << endl;
        cout << endl;
        coloredPrint(Color::Cyan, "1) Move to the Next Battle");
        cout << endl;
        coloredPrint(Color::Yellow, "2) Open Shop");
        cout << endl;
        coloredPrint(Color::Magenta, "3) View Quest(s) ");
        cout << endl;
        cout << "4) Save Game" << endl;
        cout << ">> Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            break;
        }
        case 2:
        {
            shopMenu(player);

            break;
        }
        case 3:
        {
            player.displayQuests();

            break;
        }
        case 4:
        {
            doSave(player);

            break;
        }
        default:
        {
            coloredPrint(Color::Red, ">> Invalid choice! Choice again: ");
        }
        }

        if (choice == 1)
        {
            continue;
        }
    }

    cout << endl;
    player.setEscapeBattle(false);

    coloredPrint(Color::Cyan, ">> Press Enter to face the next enemy...");
    cin.ignore();
    cin.get();
}

int main()
{
    initConsole();

    // static_cast: converting the value to the expected type.
    srand(static_cast<unsigned int>(time(0)));

    Character* player = nullptr;

    int menuChoice = 0;

    while (menuChoice != 1 && menuChoice != 4)
    {
        initConsole();
        vector<string> mainItems = { "-|====>  New Game", "-|====>  Load Save", "-|====>  Delete Save", "-|====>  Quit" };
        menuChoice = getMenuChoice(mainItems) + 1;

        switch (menuChoice)
        {
        case 1:
        {
            int classChoice;
            chooseClass();
            cin >> classChoice;

            string name;
            cout << "\n>> Enter your name: ";
            cin >> name;

            if (classChoice == 1)
            {
                int strengthCounter = 0;
                int defenceCounter = 0;
                int critCounter = 0;
                int healthCounter = 0;

                while ((strengthCounter + defenceCounter + critCounter + healthCounter) != 15)
                {
                    cout << endl;
                    cout << "You have 15 skill points to create your character!" << endl;
                    cout << "1) Strength (base strength is 0)" << endl;
                    cout << "2) Defence (base defence is 0)" << endl;
                    cout << "3) Crit Chance (base crit chance is 0)" << endl;
                    cout << "4) Health (base health is 100)" << endl;
                    cout << ">> Enter the skill point distribution (10 5 0 0): ";
                    cin >> strengthCounter >> defenceCounter >> critCounter >> healthCounter;

                    if ((strengthCounter + defenceCounter + critCounter + healthCounter) != 15)
                    {
                        cout << ">> Make the sum of the point distribution 15!" << endl;
                    }
                }

                player = new Character(name, healthCounter, strengthCounter, defenceCounter, critCounter);

                cout << ">> " << name << " has been created!\n" << endl;
            }
            else
            {
                int spellPowerCounter = 0;
                int defenceCounter = 0;
                int critCounter = 0;
                int healthCounter = 0;

                while ((spellPowerCounter + defenceCounter + critCounter + healthCounter) != 15)
                {
                    cout << endl;
                    cout << "You have 15 skill points to create your character!" << endl;
                    cout << "1) Spell Power (base spell power is 0)" << endl;
                    cout << "2) Defence (base defence is 0)" << endl;
                    cout << "3) Spell Crit Chance (base spell crit chance is 0)" << endl;
                    cout << "4) Health/Mana (base health/mana is 100)" << endl;
                    cout << "Enter the skill point distribution (10 5 0 0): ";
                    cin >> spellPowerCounter >> defenceCounter >> critCounter >> healthCounter;

                    if ((spellPowerCounter + defenceCounter + critCounter + healthCounter) != 15)
                    {
                        cout << "Make the sum of the point distribution 15!" << endl;
                    }
                }

                player = new Mage(name, healthCounter, spellPowerCounter, defenceCounter, critCounter);

                cout << ">> " << name << " has been created!\n" << endl;
            }

            break;
        }
        case 2:
        {
            showLoadMenu(player);

            if (player)
            {
                menuChoice = 1;
            }

            break;
        }
        case 3:
        {
            doDelete();

            break;
        }
        case 4:
        {
            cout << "\n>> Quitting the game!\n";
            return 0;
        }
        default:
            cout << "\n>> Please choose correct!" << endl;
            break;
        }
    }

    if (player != nullptr)
    {
        while (gameMenu(*player));
    }

    return 0;
}
