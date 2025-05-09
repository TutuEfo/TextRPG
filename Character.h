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
public:
    Character(const string& nickname);  // Constructor
    string getNickName();
    int getHealth();
    int getStrength();
    int getDefence();
    int getLevel();
    int getPotions() const;
    void gainXP(int amount);
    void levelUp();
    int getXP() const;
    int getXPToLevelUp() const;
    void usePotion();
    void takeDamage(int damage);
    virtual void displayCharacter() const;
    int attack();
};

#endif // CHARACTER_H
