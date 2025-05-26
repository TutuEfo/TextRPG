#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Enemy.h"
#include "Mage.h"
#include "Console.h"
#include "SaveLoad.h"

using namespace std;

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

void combatRound(Character& player, Enemy& enemy)
{
    int choice = 0;
    int goBackMenu = 0;
    int escapeChoice = 0;

    if (player.getStrengthPotionDuration() > 0)
    {
        int sDuration = player.getStrengthPotionDuration() - 1;

        player.setStrengthPotionDuration(sDuration);

        if (player.getStrengthPotionDuration() == 0 && player.isStrengthEffectActive())
        {
            player.setStrength(player.getStrength() - 5);
            player.setStrengthEffectActive(false);
            cout << ">> Strength potion wore off!" << endl;
        }
    }

    if (player.getDefencePotionDuration() > 0)
    {
        int dDuration = player.getDefencePotionDuration() - 1;

        player.setDefencePotionDuration(dDuration);

        if (player.getDefencePotionDuration() == 0 && player.isDefenceEffectActive())
        {
            player.setDefence(player.getDefence() - 3);
            player.setDefenceEffectActive(false);
            cout << ">> Defence potion wore off!" << endl;
        }
    }

    cout << endl;

    cout << "===================================================" << endl;
    // dynamic_cast checks if 'player' is actually a Mage.
    // If so, it safely casts to Mage* and stores it in magePtr.
    // Then we call getMana() on magePtr to get the mana value.
    Mage* magePtr = dynamic_cast<Mage*>(&player);

    // Check for Mage Class:
    if (magePtr != nullptr)
    {
        magePtr->displayCharacter();
    }
    else
    {
        player.displayCharacter();
    }

    cout << endl;

    cout << "===================================================" << endl;

    enemy.displayStatus();

    cout << endl;

    cout << "1) Attack" << endl;

    // Combat Panel:
    if (magePtr != nullptr)
    {
        cout << "2) Defend" << endl;
        cout << "3) Items" << endl;
        cout << "4) Escape" << endl;
        cout << "5) Cast Spell" << endl;
    }
    else
    {
        cout << "2) Defend" << endl;
        cout << "3) Items" << endl;
        cout << "4) Escape" << endl;
    }

    cout << "What do you want to do: ";

    cin >> choice;

    cout << endl;

    if (choice == 3)
    {
        int itemChoice = 0;

        while (itemChoice != 4)
        {
            cout << "===================================================" << endl;

            // Items Panel:
            cout << ">> Items: " << endl;
            cout << ">> 1) Potions" << endl;
            cout << ">> 2) Go back to the main menu" << endl;
            cout << ">> Choose an option: ";

            cin >> itemChoice;

            if (itemChoice == 1)
            {
                int potionChoiceDefault = 0;
                int potionChoiceMage = 0;

                if (magePtr == nullptr)
                {
                    cout << endl;
                    cout << ">> Which potion do you want to use: " << endl;
                    cout << ">> 1) Health: " << player.getHealthPotions() << endl;
                    cout << ">> 2) Strength: " << player.getStrengthPotions() << endl;
                    cout << ">> 3) Defence: " << player.getDefencePotions() << endl;
                    cout << ">> 4) Don't use potion: " << endl;
                    cout << ">> Choose a potion: ";

                    cin >> potionChoiceDefault;
                }
                else
                {
                    cout << endl;
                    cout << ">> Which potion do you want to use: " << endl;
                    cout << ">> 1) Health: " << player.getHealthPotions() << endl;
                    cout << ">> 2) Strength: " << player.getStrengthPotions() << endl;
                    cout << ">> 3) Defence: " << player.getDefencePotions() << endl;
                    cout << ">> 4) Mana: " << magePtr->getManaPotions() << endl;
                    cout << ">> 5) Don't use potion: " << endl;
                    cout << ">> Choose a potion: ";

                    cin >> potionChoiceMage;
                }

                if (potionChoiceDefault == 1 || potionChoiceMage == 1)
                {
                    player.usePotion(potionChoiceDefault);

                    goBackMenu = 1;
                }
                else if ((potionChoiceDefault == 2 || potionChoiceMage == 2) && !player.isStrengthEffectActive())
                {
                    player.usePotion(potionChoiceDefault);

                    player.setStrengthPotionDuration(3);

                    player.setStrengthEffectActive(true);

                    goBackMenu = 1;
                }
                else if ((potionChoiceDefault == 3 || potionChoiceMage == 3) && !player.isDefenceEffectActive())
                {
                    player.usePotion(potionChoiceDefault);

                    player.setDefencePotionDuration(3);

                    player.setDefenceEffectActive(true);

                    goBackMenu = 1;
                }
                else if (potionChoiceMage == 4)
                {
                    magePtr->useManaPotion();
                }
                else if (potionChoiceDefault == 4 || potionChoiceMage == 5)
                {
                    goBackMenu = 1;
                }
                else
                {
                    cout << ">> You can't use that potion right now." << endl;
                }
            }

            if (itemChoice == 2 || goBackMenu == 1)
            {
                cout << endl;
                cout << "1) Attack" << endl;
                cout << "2) Defend" << endl;
                cout << "3) Escape" << endl;

                if (magePtr != nullptr)
                {
                    cout << "4) Cast Spell" << endl;
                }

                cout << "What do you want to do: ";

                cin >> choice;

                if (choice == 3)
                {
                    escapeChoice = 1;
                }
                else if (choice == 4)
                {
                    choice = 5;
                }

                break;
            }
        }
    }

    if (choice == 1)
    {
        cout << "===================================================" << endl;

        cout << ">> " << player.getNickName() << " chooses to attack the " << enemy.getEnemyName() << endl;

        int damagePlayer1 = max(0, player.attack() - enemy.getEnemyDefence());
        enemy.takeDamage(damagePlayer1);

        cout << ">> " << player.getNickName() << " attacks the " << enemy.getEnemyName() << " and deals " << damagePlayer1 << " damage!" << endl;

        cout << "===================================================" << endl;

        cout << ">> " << enemy.getEnemyName() << " attacks the " << player.getNickName() << endl;

        int damageEnemy1 = max(0, enemy.attackCharacter() - player.getDefence());
        player.takeDamage(damageEnemy1);

        cout << ">> " << enemy.getEnemyName() << " hits the " << player.getNickName() << " and deals " << damageEnemy1 << " damage!" << endl;

        cout << endl;

    }
    else if (choice == 2)
    {
        cout << "===================================================" << endl;

        cout << ">> " << player.getNickName() << " chooses to defend aginst the " << enemy.getEnemyName() << endl;

        int damageEnemy2 = max(0, enemy.attackCharacter() - (2 * player.getDefence()));
        player.takeDamage(damageEnemy2);

        cout << ">> " << player.getNickName() << " defends and reduces " << damageEnemy2 << " damage!" << endl;

        cout << "===================================================" << endl;

        cout << ">> " << player.getNickName() << " attacks the " << enemy.getEnemyName() << endl;

        int damagePlayer2 = max(0, (player.attack()) - (2 * enemy.getEnemyDefence()));
        enemy.takeDamage(damagePlayer2);

        cout << ">> " << player.getNickName() << " hits the " << enemy.getEnemyName() << " and deals " << damagePlayer2 << " damage!" << endl;

        cout << endl;

    }
    else if (choice == 4 || escapeChoice == 1)
    {
        player.escapeFromBattle();

        if (player.getEscapeBattle())
        {
            cout << endl;

            coloredPrint(Color::Green, "You escaped successfully from the battle!");

            cout << endl;

            return;
        }
        else
        {
            coloredPrint(Color::Red, "Escape failed! The enemy strikes you as you run!");

            int escapeDamage = enemy.attackCharacter() - player.getDefence();
            player.takeDamage(max(0, escapeDamage));

            cout << endl;
        }
    }
    else if (choice == 5 && magePtr != nullptr)
    {
        if (magePtr->getMana() > 0)
        {
            cout << "===================================================" << endl;

            cout << ">> " << magePtr->getNickName() << " casts a spell at " << enemy.getEnemyName() << "!" << endl;

            int spellDamage = max(0, magePtr->castSpell() - enemy.getEnemyDefence());
            enemy.takeDamage(spellDamage);

            cout << ">> The spell deals " << spellDamage << " damage!" << endl;

            cout << "===================================================" << endl;
        }
        else
        {
            coloredPrint(Color::Yellow, "Don't have enough mana to cast a spell!");
        }

        cout << ">> " << enemy.getEnemyName() << " attacks the " << player.getNickName() << endl;

        int damageEnemy3 = max(0, enemy.attackCharacter() - player.getDefence());
        player.takeDamage(damageEnemy3);

        cout << ">> " << enemy.getEnemyName() << " hits the " << player.getNickName() << " and deals " << damageEnemy3 << " damage!" << endl;
        cout << endl;
    }
    else
    {
        if (choice != 3)
        {
            cout << ">> " << "Please choose 1, 2 or 3" << endl;
        }

        cout << endl;
    }

    // Press Enter to continue program to slow things down.
    cout << ">> Press Enter to continue to the battle:";
    // cin.ignore() skips the leftover '\n' character in the input buffer.
    // This is usually needed after using cin >> something, because cin leaves a '\n' behind.
    cin.ignore();
    // cin.get() waits for the user to press Enter.
    // It reads the next character (which will be '\n' after Enter) and pauses the program.
    cin.get();
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

void mainMenu()
{
    cout << "Welcome to the TextRPG!" << endl;
    cout << "1) New Game" << endl;
    cout << "2) Load Game" << endl;
    cout << "3) Quit" << endl;
    cout << ">> Enter you choice: ";
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
    Enemy randomEnemy;

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

        Quest quest{ "Defeat " + to_string(count) + " " + name, name, count, 0, randomXP, randomGold };

        player.addQuest(quest);

        player.setHasQuests(true);
    }

    // Normal Enemy & Boss:
    if (player.getLevel() % 5 == 0)
    {
        coloredPrint(Color::Red, "\n!! A powerful enemy is approaching...\n");
        randomEnemy = Enemy::generateBoss(player.getLevel());
    }
    else
    {
        randomEnemy = Enemy::generateEnemy(player.getLevel());
    }

    // Combat loop:
    while (randomEnemy.isAlive() && player.getHealth() > 0 && !player.getEscapeBattle())
    {
        combatRound(player, randomEnemy);

        if (!randomEnemy.isAlive())
        {
            player.checkQuestCompletion(randomEnemy.getEnemyName());
        }
    }

    // Reward Panel: 
    if (!randomEnemy.isAlive())
    {
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

    // Game Over:
    if (player.getHealth() <= 0)
    {
        cout << "\n======================================" << endl;
        cout << ">> " << player.getNickName() << " has been defeated!" << endl;
        cout << ">> GAME OVER!!" << endl;
        cout << "======================================" << endl;

        return 0;
    }

    int choice = 0;

    // Post Combat Panel:
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

    // Testing the Mage Class:
    // Mage myCharMage("Gandalf");
    //myCharMage.displayCharacter();
    //myCharMage.castSpell();

    Character* player = nullptr;

    int menuChoice;

    mainMenu();
    cin >> menuChoice;

    if (menuChoice == 1)
    {
        int classChoice;

        chooseClass();

        cin >> classChoice;

        string name;

        cout << ">> Enter your name: ";

        cin >> name;

        if (classChoice == 1)
        {
            player = new Character(name);
        }
        else if (classChoice == 2)
        {
            player = new Mage(name);
        }
    }
    else if (menuChoice == 2)
    {
        cout << ">> Which Class would you like the load:" << endl;
        cout << "1) Default" << endl;
        cout << "2) Mage" << endl;
        cout << "Enter your choice: ";

        int loadClass;
        cin >> loadClass;

        if (loadClass == 1)
        {
            player = new Character("temp");
        }
        else
        {
            player = new Mage("temp");
        }

        doLoad(*player);
    }
    else
    {
        cout << "Quitting the game!" << endl;

        return 0;
    }

    while (gameMenu(*player))
    {
        gameMenu(*player);
    }
        
    return 0;
}