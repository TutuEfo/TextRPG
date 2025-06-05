#include <iostream>
#include <string>
#include "Character.h"
#include "Mage.h"
#include "UI.h"
#include "Console.h"

using namespace std;

Mage::Mage(const string& name) : Character(name), mana(50), maxMana(100), manaPotions(3), spellPower(12)
{
	strength = 0;
	defence = 3;
	critChance = 5;
	maxHealth = 100;
	health = maxHealth;
}

int Mage::castSpell()
{
	int damage = 0;

	if (mana >= 10)
	{
		damage = spellPower + (rand() % spellPower);

		mana -= 10;
	}

	return damage;
}

Mage::Mage(const string& name, int hp, int sp, int def, int critCh) : Character(name, hp, 0, def, critCh), maxMana(100 + (hp * 10)), mana(maxMana), manaPotions(3), spellPower(sp)
{
	strength = 0;
}

void Mage::displayCharacter() const
{
	coloredPrint(Color::Cyan, "\n========== MAGE STATS ==========\n\n");
	cout << "Name:        " << nickName << "\n";

	cout << "Health:      ";
	printBar(health, maxHealth, 20);
	cout << endl;

	cout << "Mana:        ";
	printBar(mana, maxMana, 20);
	cout << endl;

	cout << "XP:          ";
	printBar(xp, xpToLevelUp, 20);
	cout << endl;

	cout << "Level:       " << level << "\n";
	cout << "Spell Power: " << spellPower << "\n";
	cout << "Crit Chance: " << critChance << "\n";
	cout << "Defence:     " << defence << "\n";
	cout << "Gold:        " << gold << "\n";
}

void Mage::addManaPotion(int amount)
{
	manaPotions = manaPotions + amount;
}

int Mage::getMana() const
{
	return mana;
}

int Mage::getManaPotions() const
{
	return manaPotions;
}

void Mage::useManaPotion()
{
	manaPotions--;

	mana = mana + 25;

	cout << ">> " << getNickName() << " used a mana potion and gains 25 Mana!" << endl;
}

void Mage::setMana(int amount)
{
	mana = amount;
}

void Mage::setManaPotions(int amount)
{
	manaPotions = amount;
}