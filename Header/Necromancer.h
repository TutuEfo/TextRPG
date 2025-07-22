#pragma once
#ifndef NECROMANCER_H
#define NECROMANCER_H

#include <string>
#include <iostream>
#include <vector>
#include "Character.h"
#include "Ability.h"
#include "Item.h"

using namespace std;

struct Minion {
	string name;
	int health;
	int damage;
	int remainingTurns;
};

class Necromancer : public Character {
private:
	int maxMana;
	int maxMinion;
	int mana;
	int manaPotions;
	int summonPotions;
	int minionPower;
	int minionCounter;
	vector<Minion> minions;

	vector<Ability> unlockedAbilities;
public:
	Necromancer(const string& name);
	Necromancer(const string& name, int hp, int sp, int def, int critCh);
	void addManaPotion(int amount);
	void displayCharacter() const override;
	void levelUp() override;
	void useManaPotion();
	void useMinionPotion();
	void unlockAbilitiesByLevel() override;

	void applyItemBonus(const Item& it);
	void removeItemBonus(const Item& it);
	void addItem(Item it) override;

	void summonMinion(const Minion& m);
	void clearDeadMinions();

	void setMana(int amount);
	void setManaPotions(int amount);

	string getClassName() const override { return "Necromancer"; }
	int getManaPotions() const;
	int getMaxMinion() const;
	int getSummonPotions() const;
	int getMana() const;
};


#endif // NECROMANCER_H