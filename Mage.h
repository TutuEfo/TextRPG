#ifndef MAGE_H
#define MAGE_H

#include <string>
#include <iostream>
#include "Character.h"

using namespace std;

class Mage : public Character {
private:
	int mana = 100;
	int manaPotions = 3;
public:
	Mage(const string& name);
	int getMana();
	int castSpell();
	void addManaPotion(int amount);
	int getManaPotions();
	void displayCharacter() const override;
	void useManaPotion();
	string getClassName() const override { return "Mage"; }
};


#endif // MAGE_H