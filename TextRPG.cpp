#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Enemy.h"
#include "Mage.h"

using namespace std;

void combatRound(Character &player, Enemy &enemy)
{
    int choice = 0;

    cout << "\n" << endl;

    cout << "===================================================" << endl;
    // dynamic_cast checks if 'player' is actually a Mage.
    // If so, it safely casts to Mage* and stores it in magePtr.
    // Then we call getMana() on magePtr to get the mana value.
    Mage* magePtr = dynamic_cast<Mage*>(&player);

    if (magePtr != nullptr)
    {
        magePtr->displayCharacter();
    }
    else
    {
        player.displayCharacter();
    }

    cout << "\n" << endl;

    cout << "===================================================" << endl;

    enemy.displayStatus();

    cout << "\n" << endl;

    
    cout << "1) Attack" << endl;

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

    cout << "\n" << endl;

    if (choice == 3)
    {
        int itemChoice = 0;

        while (itemChoice != 4)
        {
            cout << "===================================================" << endl;

            cout << ">> Items: " << endl;
            cout << ">> 1) Health Potions:      " << player.getPotions() << endl;
            // cout << ">> 2) Strength Potions: " << player.getStrengthPotions() << endl;
            // cout << ">> 3) Defense Potions:  " << player.getDefensePotions() << endl;
            cout << ">> 4) Go back to the main menu" << endl;

            cin >> itemChoice;

            if (itemChoice == 1)
            {
                player.usePotion();
                break;
            }
            if (itemChoice == 4)
            {
                cout << "1) Attack" << endl;
                cout << "2) Defend" << endl;
                // cout << "3) Escape" << endl;
                cout << "What do you want to do: ";

                cin >> choice;
                cin.ignore();
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

        cout << "\n" << endl;

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

        int damagePlayer2 = max(0, (player.attack()) - enemy.getEnemyDefence());
        enemy.takeDamage(damagePlayer2);

        cout << ">> " << player.getNickName() << " hits the " << enemy.getEnemyName() << " and deals " << damagePlayer2 << " damage!" << endl;

        cout << "\n" << endl;

    }
    else if (choice == 4)
    {
        player.escapeFromBattle();
        
        if (player.getEscapeBattle())
        {
            cout << "You escaped successfully from the battle!" << endl;
            return;
        }
        else
        {
            cout << "Escape failed! The enemy strikes you as you run!" << endl;

            int escapeDamage = enemy.attackCharacter() - player.getDefence();
            player.takeDamage(max(0, escapeDamage));

            cout << "\n" << endl;
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
            cout << "Don't have enough mana to cast a spell!" << endl;
        }

        cout << ">> " << enemy.getEnemyName() << " attacks the " << player.getNickName() << endl;

        int damageEnemy3 = max(0, enemy.attackCharacter() - player.getDefence());
        player.takeDamage(damageEnemy3);

        cout << ">> " << enemy.getEnemyName() << " hits the " << player.getNickName() << " and deals " << damageEnemy3 << " damage!" << endl;
        cout << "\n" << endl;
    }
    else
    {
        if (choice != 3)
        {
            cout << ">> " << "Please choose 1, 2 or 3" << endl;
        }

        cout << "\n" << endl;
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
        cout << "\n===== SHOP =====" << endl;
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
                player.addPotion(1);
                player.addGold(-20);
                cout << ">> You bought 1 Health Potion!" << endl;
            }
            else
            {
                cout << ">> Not enough gold!" << endl;
            }
            break;

        case 2:
            if (Mage* mage = dynamic_cast<Mage*>(&player))
            {
                if (player.getGold() >= 25)
                {
                    mage->addManaPotion(1);
                    player.addGold(-25);
                    cout << ">> You bought 1 Mana Potion!" << endl;
                }
                else
                {
                    cout << ">> Not enough gold!" << endl;
                }
            }
            else
            {
                cout << ">> Only Mages can buy mana potions!" << endl;
            }
            break;

        case 3:
            cout << ">> Leaving the shop..." << endl;
            break;

        default:
            cout << ">> Invalid choice!" << endl;
        }
    }
}

int main()
{
    // static_cast: converting the value to the expected type.
    srand(static_cast<unsigned int>(time(0)));

    // Testing the Mage Class:
    // Mage myCharMage("Gandalf");
    //myCharMage.displayCharacter();
    //myCharMage.castSpell();

    Character player("TutuEfo");

    while (true)
    {
        Enemy randomEnemy;

        if(!player.getHasQuests())
        {
            const string types[] = { "Goblin", "Orc", "Bandit", "Troll" };
            int typeIndex = rand() % 4;

            string name = types[0];

            int count;
            count = rand() % 3 + 5;

            int randomXP;
            randomXP = rand() % 26 + 25;

            int randomGold;
            randomGold = rand() % 41 + 10;

            Quest quest{ "Defeat 5 " + name, name, count, 0, randomXP, randomGold };

            player.addQuest(quest);

            player.setHasQuests(true);
        }

        if (player.getLevel() % 5 == 0)
        {
            cout << "\nA powerful enemy is approaching...\n";
            randomEnemy = Enemy::generateBoss(player.getLevel());
        }
        else
        {
            randomEnemy = Enemy::generateEnemy(player.getLevel());
        }

        while (randomEnemy.isAlive() && player.getHealth() > 0 && !player.getEscapeBattle())
        {
            combatRound(player, randomEnemy);

            if (!randomEnemy.isAlive())
            {
                player.checkQuestCompletion(randomEnemy.getEnemyName());
            }
        }

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

        if (player.getHealth() <= 0)
        {
            cout << "\n======================================" << endl;
            cout << ">> "<< player.getNickName() << " has been defeated!" << endl;
            cout << ">> GAME OVER!!" << endl;
            cout << "======================================" << endl;
            break;
        }

        int choice = 0;

        while (choice < 1 || choice > 3)
        {
            cout << "\n========== Post Combat Menu ==========" << endl;
            cout << "1) Move to the Next Battle" << endl;
            cout << "2) Open Shop" << endl;
            cout << "3) View Quest(s) " << endl;
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
            default:
            {
                cout << "Invalid choice, choose again";
            }
            }

            if (choice == 1)
            {
                continue;
            }
        }

        cout << "\n";
        player.setEscapeBattle(false);

        cout << ">> Press Enter to face the next enemy...";
        cin.ignore();
        cin.get();
    }
        
    return 0;
}