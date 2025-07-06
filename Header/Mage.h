#pragma once
#ifndef MAGE_H
#define MAGE_H

#include <string>
#include <iostream>
#include "Character.h"

using namespace std;

class Mage : public Character{
private:
	int maxMana;
	int mana;
	int manaPotions;
	int spellPower;
public:
	Mage(const string& name);
	Mage(const string& name, int hp, int sp, int def, int critCh);
	int getMana() const;
	int castSpell(int choice);
	void addManaPotion(int amount);
	int getManaPotions() const;
	void displayCharacter() const override;
	void levelUp() override;
	void useManaPotion();
	string getClassName() const override { return "Mage"; }

	void setMana(int amount);
	void setManaPotions(int amount);

	void applyItemBonus(const Item& it);
	void removeItemBonus(const Item& it);
};


#endif // MAGE_H