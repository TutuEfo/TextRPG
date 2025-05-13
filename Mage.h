#ifndef MAGE_H
#define MAGE_H

#include <string>
#include <iostream>
#include "Character.h"

using namespace std;

class Mage : public Character {
private:
	int mana;
	int manaPotions;
public:
	Mage(const string& name);
	int getMana();
	int castSpell();
	void addManaPotion(int amount);
	void displayCharacter() const override;
};


#endif // MAGE_H