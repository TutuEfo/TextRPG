#pragma once
#ifndef NECROMANCER_H
#define NECROMANCER_H

#include <string>
#include <iostream>
#include "Character.h"

using namespace std;

class Necromancer : public Character {
private:
	int maxMana;
	int maxMinion;
	int mana;
	int manaPotions;
	int summonPotions;
	int minionPower;
	int minionCounter;

	vector<Ability> unlockedAbilities;
public:
	Necromancer(const string& name);
	Necromancer(const string& name, int hp, int sp, int def, int critCh);
	int summonMinion(int choice);
	void addManaPotion(int amount);
	void displayCharacter() const override;
	void levelUp() override;
	void useManaPotion();
	void useMinionPotion();
	void unlockAbilitiesByLevel() override;

	void applyItemBonus(const Item& it);
	void removeItemBonus(const Item& it);
	void addItem(Item it) override;

	void setMana(int amount);
	void setManaPotions(int amount);

	string getClassName() const override { return "Necromancer"; }
	int getManaPotions() const;
	int getMinionCounter() const;
	int getMaxMinion() const;
	int getSummonPotions() const;
	int getMana() const;
};


#endif // NECROMANCER_H