#include "Character.h"
#include "Enemy.h"
#include "Mage.h"
#include "Console.h"
#include "SaveLoad.h"
#include "Combat.h"
#include "Menu.h"
#include "Map.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <optional>
#include <limits>
#include <iomanip>

using namespace std;

bool showLoadMenu(Character*& player, MapSnapshot& outSnap)
{
    auto files = SaveLoad::listSaveFiles();

    if (files.empty())
    {
        cout << "\n>> No save files found.\n";

        coloredPrint(Color::Cyan, ">> Press Enter to return main menu.");
        cin.get();

        return false;
    }

    cout << "\n========== Load Game Menu ==========\n";

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
                << files[i] << " (Save file corrupted)\n";
        }
    }

    int choice;
    cout << "\n>> Enter a number to load (0 to cancel): ";

    while (!(cin >> choice) || choice < 0 || choice > (int)files.size())
    {
        cin.clear();
        // Throw everyhting in the buffer, to enter an input again.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << ">> Please enter 0 to " << files.size() << ": ";
    }

    if (choice == 0)
    {
        return false;
    }

    const string& sel = files[choice - 1];

    cout << ">> Load \"" << sel << "\"? (Y/N): ";
    char c; cin >> c;

    if (c == 'y' || c == 'Y')
    {
        auto mdOpt = SaveLoad::readMetadata(sel);

        if (!mdOpt)
        {
            cout << ">> Error: Could not read save metadata.\n";
            return false;
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

        if (SaveLoad::loadGame(*player, outSnap, sel))
        {
            cout << ">> Loaded \"" << sel << "\" successfully.\n";

            return true;
        }
        else
        {
            cout << ">> Failed to load \"" << sel << "\".\n";
            
            return false;
        }
    }

    coloredPrint(Color::Cyan, ">> Press Enter to return main menu.");
    cin.ignore();
    cin.get();
}

void doDelete()
{
    auto files = SaveLoad::listSaveFiles();

    if (files.empty())
    {
        cout << "\n>> No save files found.\n";

        coloredPrint(Color::Cyan, ">> Press Enter to return main menu.");
        cin.get();

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
            cout << setw(2) << (i + 1) << ") " << files[i] << " (Save file corrupted)\n";
        }
    }

    cout << ">> Enter filename to remove (0 to cancel): ";

    string fname;
    cin >> fname;

    if (fname == "0")
    {
        coloredPrint(Color::Cyan, ">> Press Enter to return main menu.");
        cin.get();

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

    coloredPrint(Color::Cyan, ">> Press Enter to return main menu.");
    cin.ignore();
    cin.get();
}

void chooseClass()
{
    cout << "\n\nChoose your class:" << endl;
    cout << "1) Default" << endl;
    cout << "2) Mage" << endl;
    // cout << "3) Necromancer" << endl;
    cout << ">> Enter you choice: ";
}

static const char* slotName(EquipSlot s)
{
    switch (s)
    {
    case EquipSlot::Weapon:
        return "Weapon";
    case EquipSlot::Helmet:
        return "Helmet";
    case EquipSlot::Chestplate:
        return "Chestplate";
    case EquipSlot::Leggings:
        return "Leggings";
    case EquipSlot::Boots:
        return "Boots";
    case EquipSlot::Accessory:
        return "Accessory";
    }
}

optional<EquipSlot> toSlot(ItemType t)
{
    switch (t)
    {
    case ItemType::Sword:
        return EquipSlot::Weapon;
    case ItemType::Wand:
        return EquipSlot::Weapon;
    case ItemType::Helmet:
        return EquipSlot::Helmet;
    case ItemType::Chestplate:
        return EquipSlot::Chestplate;
    case ItemType::Leggings:
        return EquipSlot::Leggings;
    case ItemType::Boots:
        return EquipSlot::Boots;
    case ItemType::Shield:
        return EquipSlot::Accessory;
    case ItemType::Cloak:
        return EquipSlot::Accessory;
    default:
        return nullopt;
    }
}

void showInventoryMenu(Inventory& inv, Equipment& eq, Character *player)
{
    while (true)
    {
        cout << "\n=== Inventory ===" << endl;
        auto& items = inv.getItems();

        if (items.empty())
        {
            cout << "(Empty)\n";
        }
        else
        {
            for (size_t i = 0; i < items.size(); i++)
            {
                cout << " " << (i + 1) << ") " << items[i].name << " " << items[i].description << endl;
            }
        }

        cout << "\nEquipped:\n";
        if (eq.getEquipped().empty())
        {
            cout << "(Nothing)\n";
        }
        else
        {
            for (auto& p : eq.getEquipped())
            {
                cout << " - " << slotName(p.first) << ": " << p.second.name << " " << p.second.description << endl;
            }
        }

        cout << "\nOptions:\n" << " 1) Equip item\n" << " 2) Unequip slot\n" << " 3) Exit" << endl;
        cout << "Choice: ";
        int choice; cin >> choice;

        if (choice == 3)
        {
            break;
        }

        if (choice == 1)
        {
            cout << "Enter inventory number to equip: ";

            size_t idx;
            cin >> idx;

            if (idx == 0 || idx > items.size())
            {
                cout << "Invalid." << endl;
                continue;
            }
            Item it = items[idx - 1];

            auto oslot = toSlot(it.type);

            if (!oslot)
            {
                cout << "Cannot equip that." << endl;
                continue;
            }

            inv.removeItem(idx - 1);
            auto old = eq.equip(*oslot, it);

            if (old)
            {
                inv.addItem(*old);
                cout << "Swapped out " << old->name << "." << endl;
            }

            player->applyItemBonus(it);
        }
        else if (choice == 2)
        {
            auto& emap = eq.getEquipped();

            if (emap.empty())
            {
                cout << "Nothing to unequip." << endl;
                continue;
            }

            vector<EquipSlot> slots;
            int n = 1;

            for (auto& p : emap)
            {
                cout << " " << n << ") " << slotName(p.first) << endl;
                slots.push_back(p.first);
                n++;
            }
            cout << "Choose slot to unequip: ";
            int s;
            cin >> s;
            
            if (s < 1 || s >(int)slots.size())
            {
                cout << "Invalid." << endl;
                continue;
            }

            auto old = eq.unequip(slots[s - 1]);
            if (old)
            {
                player->removeItemBonus(*old);
                inv.addItem(*old);
                cout << "Unequipped " << old->name << "." << endl;
            }
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }
}

int main()
{
    initConsole();

    // static_cast: converting the value to the expected type.
    srand(static_cast<unsigned int>(time(0)));

    Character* player = nullptr;

    MapSnapshot loadedSnap;
    bool mapWasLoaded = false;

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

            cout << ">> Enter your name: ";
            cin >> name;

            if (classChoice == 1)
            {
                int strengthCounter = 0;
                int defenceCounter = 0;
                int critCounter = 0;
                int healthCounter = 0;

                while ((strengthCounter + defenceCounter + critCounter + healthCounter) != 25)
                {
                    cout << endl;
                    cout << "You have 25 skill points to create your character!" << endl;
                    cout << "1) Strength" << endl;
                    cout << "2) Defence" << endl;
                    cout << "3) Crit Chance" << endl;
                    cout << "4) Health" << endl;
                    cout << ">> Base stats: Health: 100, Strength: 0, Defence: 0, Crit Chance: 0" << endl;
                    cout << ">> Enter the skill point distribution (20 5 0 0): ";
                    cin >> strengthCounter >> defenceCounter >> critCounter >> healthCounter;

                    if (strengthCounter == 250 && defenceCounter == 250 && critCounter == 250 && healthCounter == 250)
                    {
                        // OP Character Secret!
                        break;
                    }

                    if ((strengthCounter + defenceCounter + critCounter + healthCounter) != 25)
                    {
                        cout << ">> Make the sum of the point distribution 25!" << endl;
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

                while ((spellPowerCounter + defenceCounter + critCounter + healthCounter) != 25)
                {
                    cout << endl;
                    cout << "You have 25 skill points to create your character!" << endl;
                    cout << "1) Spell Power" << endl;
                    cout << "2) Defence" << endl;
                    cout << "3) Spell Crit Chance" << endl;
                    cout << "4) Health/Mana" << endl;
                    cout << ">> Base stats: Health/Mana: 100, Spell Power: 0, Defence: 0, Spell Crit Chance: 0" << endl;
                    cout << "Enter the skill point distribution (20 5 0 0): ";
                    cin >> spellPowerCounter >> defenceCounter >> critCounter >> healthCounter;

                    if (spellPowerCounter == 250 && defenceCounter == 250 && critCounter == 250 && healthCounter == 250)
                    {
                        // OP Mage Secret!
                        break;
                    }

                    if ((spellPowerCounter + defenceCounter + critCounter + healthCounter) != 25)
                    {
                        cout << "Make the sum of the point distribution 15!" << endl;
                    }
                }

                player = new Mage(name, healthCounter, spellPowerCounter, defenceCounter, critCounter);

                cout << ">> " << name << " has been created!\n" << endl;
            }

            cout << ">> Press Enter to start the game...";
            cin.ignore();
            cin.get();

            break;
        }
        case 2:
        {
            mapWasLoaded = showLoadMenu(player, loadedSnap);

            if (player)
            {
                menuChoice = 1;
            }

            if (mapWasLoaded)
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
            cout << "\n>> Enemies lurk in the shadows. We need you back ASAP!\n";
            return 0;
        }
        default:
            cout << "\n>> Please choose again" << endl;
            break;
        }
    }

    Map map(player);

    if (mapWasLoaded)
    {
        map.loadSnapshot(loadedSnap);
    }

    while (player && player->getHealth() > 0)
    {
        system("cls");
        map.display();

        coloredPrint(Color::Red, "Enter your inputs one by one\n");
        coloredPrint(Color::Red, "# -> Wall, T -> Trap, S -> Shop, B -> Boss, D -> Dungeon, N -> Next Room\n");

        cout << "\nMove (W/A/S/D), Save (F), Quit (Q), Inventory (I): ";

        char in;
        cin >> in;

        if (in == 'f')
        {
            MapSnapshot snap = map.makeSnapshot();

            cout << "\nSave filename: ";

            string fname;
            cin >> fname;
            
            try
            {
                SaveLoad::saveGame(*player, snap, fname);
                cout << "Saved!\n";

                system("pause");
            }
            catch (const std::exception& e)
            {
                cerr << e.what() << "\n";

                system("pause");
            }

            continue;
        }
        else if (in == 'i')
        {
            showInventoryMenu(player->getInventory(), player->getEquipment(), player);
        }
        else if (in == 'q')
        {
            cout << "\n>> Quitting the game!\n";
            cout << "\n>> Enemies lurk in the shadows. We need you back ASAP!\n";

            break;
        }
        map.movePlayer(in);
    }

    return 0;
}
