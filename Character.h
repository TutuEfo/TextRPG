#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <vector>
#include "Quest.h"

using namespace std;

class Character {
private:
    string nickName;
    int health;
    int strength;
    int defence;
    int xp;
    int xpToLevelUp;
    int level;
    int potions;
    int gold;
    bool escapeBattle;
    vector<Quest> activeQuests;
public:
    Character(const string& nickname);  // Constructor

    void addGold(int amuntOfGold);

    void gainXP(int amount);
    void levelUp();
    int getXPToLevelUp() const;

    void usePotion();
    void addPotion(int amount);

    void takeDamage(int damage);
    int attack();
    
    virtual void displayCharacter() const;
    
    void escapeFromBattle();

    void addQuest(Quest& q);
    void checkQuestCompletion(const string& enemyName, Character& player);
    void displayQuests() const;

    string getNickName();
    int getHealth();
    int getStrength();
    int getDefence();
    int getLevel();
    int getGold();
    int getXP() const;
    int getPotions() const;
    bool getEscapeBattle();
    void setEscapeBattle(bool escape);
};

#endif // CHARACTER_H
