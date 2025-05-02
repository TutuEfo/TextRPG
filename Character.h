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
    void displayCharacter();
};

#endif // CHARACTER_H
