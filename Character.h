#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>

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
    
    bool escapeFromBattle();

    string getNickName();
    int getHealth();
    int getStrength();
    int getDefence();
    int getLevel();
    int getGold();
    int getXP() const;
    int getPotions() const;
};

#endif // CHARACTER_H
