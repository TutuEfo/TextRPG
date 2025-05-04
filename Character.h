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
    int level;
public:
    Character(const string& nickname);  // Constructor
    string getNickName();
    int getHealth();
    int getStrength();
    int getDefence();
    int getLevel();
    virtual void displayCharacter() const;
    int attack();
};

#endif // CHARACTER_H
