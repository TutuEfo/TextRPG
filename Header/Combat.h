#ifndef COMBAT_H
#define COMBAT_H

#include "Character.h"
#include "Enemy.h"
#include "Mage.h"

#include <iostream>
#include <string>

using namespace std;

class Mage;

class Combat{
private:
    Character& cPlayer;
    Enemy& cEnemy;

    void displayStats() const;
    int  chooseAction() const;
    void performAction(int choice);
    void endOfRoundCleanup();

    void playerAttack();
    void playerUseItem();
    void playerCastSpell();
    void playerEscape();
    void enemyTurn();

    int promptPotionMenu() const;

public:
	Combat(Character& player, Enemy& enemy);
	bool runCombat();
};

#endif // COMBAT_H