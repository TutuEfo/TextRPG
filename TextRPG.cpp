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
    cout << "Your stats: " << endl;
    cout << "Name:     " << player.getNickName() << endl;
    cout << "Health:   " << player.getHealth() << endl;

    // dynamic_cast checks if 'player' is actually a Mage.
    // If so, it safely casts to Mage* and stores it in magePtr.
    // Then we call getMana() on magePtr to get the mana value.
    Mage* magePtr = dynamic_cast<Mage*>(&player);
    if (magePtr != nullptr)
    {
        cout << "Mana:     " << magePtr->getMana() << endl;
    }

    cout << "Strength: " << player.getStrength() << endl;
    cout << "Defence:  " << player.getDefence() << endl;
    cout << "Level:    " << player.getLevel() << endl;
    cout << "XP:       " << player.getXP() << "/" << player.getXPToLevelUp() << endl;

    cout << "\n" << endl;

    cout << "===================================================" << endl;
    cout << "Enemy stats: " << endl;
    cout << "Name:     " << enemy.getEnemyName() << endl;
    cout << "Health:   " << enemy.getEnemyHealth() << endl;
    cout << "Strength: " << enemy.getEnemyStrength() << endl;
    cout << "Defence:  " << enemy.getEnemyDefence() << endl;
    cout << "Level:    " << enemy.getEnemyLevel() << endl;

    cout << "\n" << endl;

    
    cout << "1) Attack" << endl;

    if (magePtr != nullptr)
    {
        cout << "2) Defend" << endl;
        cout << "3) Items" << endl;
        cout << "4) Cast Spell" << endl;
        // cout << "5) Escape" << endl;
    }
    else
    {
        cout << "2) Defend" << endl;
        cout << "3) Items" << endl;
        // cout << "4) Escape" << endl;

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

int main()
{
    // static_cast: converting the value to the expected type.
    srand(static_cast<unsigned int>(time(0)));

    // Testing the Mage Class:
    Mage myCharMage("Gandalf");
    //myCharMage.displayCharacter();
    //myCharMage.castSpell();

    Character myCharDefault("TutuEfo");
    Enemy enemyGoblin("Goblin", 100, 3, 3, myCharMage.getLevel());

    while (enemyGoblin.isAlive())
    {
        combatRound(myCharMage, enemyGoblin);
    }

    if (!enemyGoblin.isAlive())
    {
        myCharMage.gainXP(enemyGoblin.getXPReward());
    }

    cout << ">> " << myCharMage.getNickName() << " defeats the " << enemyGoblin.getEnemyName() << "!" << endl;

    myCharMage.displayCharacter();
        
    return 0;
}