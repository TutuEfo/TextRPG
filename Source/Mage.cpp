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

int Mage::castSpell(int choice)
{
	int damage = 0;

	if (choice == 1 && mana >= 10)
	{
		coloredPrint(Color::Red, nickName + " casts a FIREBALL!\n");

		damage = spellPower + ((rand() % spellPower) * level);

		mana -= 10;
	}
	else if (choice == 2 && mana >= 25)
	{
		coloredPrint(Color::Yellow, nickName + " casts a LIGHTNING!\n");

		damage = (2 * spellPower) + ((rand() % spellPower) * level);

		mana -= 25;
	}
	else if (choice == 3 && mana >= 50)
	{
		coloredPrint(Color::Blue, nickName + " casts ICE BOLTS!\n");

		damage = (3 * spellPower) + ((rand() % spellPower) * level);

		mana -= 50;
	}
	else
	{
		cout << "Not enough mana" << endl;
	}

	return damage;
}

Mage::Mage(const string& name, int hp, int sp, int def, int critCh) : Character(name, hp, 0, def, critCh), maxMana(100 + (hp * 10)), mana(maxMana), manaPotions(3), spellPower(sp)
{
	strength = 0;
}

void Mage::levelUp()
{
	level++;

	health = maxHealth;

	xpToLevelUp = 100 + (level * 100);

	maxHealth = health + level * (10);

	health = maxHealth;

	int levelUpChoice1 = 0;
	int levelUpChoice2 = 0;

	coloredPrint(Color::Cyan, "\n========== Level Up Menu ==========\n");

	cout << "1) Strength (+2)" << endl;
	cout << "2) Defence (+2)" << endl;
	cout << "3) Crit Chance (+1)" << endl;
	cout << ">> Choose your upgrades: ";
	cin >> levelUpChoice1 >> levelUpChoice2;

	if (levelUpChoice1 == 1)
	{
		spellPower = spellPower + 2;

		cout << "# Spell Power is increased by 2!" << endl;
		cout << "\n";
	}
	else if (levelUpChoice1 == 2)
	{
		defence = defence + 2;

		cout << "# Defence is increased by 2!" << endl;
		cout << "\n";
	}
	else if (levelUpChoice1 == 3)
	{
		critChance = critChance + 1;

		cout << "# Spell Crit Chance is increased by 1!" << endl;
		cout << "\n";
	}

	if (levelUpChoice2 == 1)
	{
		spellPower = spellPower + 2;

		cout << "# Spell Power is increased by 2!" << endl;
		cout << "\n";
	}
	else if (levelUpChoice2 == 2)
	{
		defence = defence + 2;

		cout << "# Defence is increased by 2!" << endl;
		cout << "\n";
	}
	else if (levelUpChoice2 == 3)
	{
		critChance = critChance + 1;

		cout << "# Spell Crit Chance is increased by 1!" << endl;
		cout << "\n";
	}

	if (healthPotions == 0)
	{
		healthPotions = healthPotions + 3;
		cout << "# Potions are refilled!" << endl;
	}

	cout << "# Max Health is increased by 10!" << endl;

	cout << ">> " << nickName << " leveled up to Level " << level << "!" << endl;
}

void Mage::displayCharacter() const
{
	coloredPrint(Color::Cyan, "\n========== MAGE STATS ==========\n\n");
	cout << "Name:        " << nickName << "\n";

	cout << "Health:      ";
	printBar(health, maxHealth, 25);
	cout << endl;

	cout << "Mana:        ";
	printBar(mana, maxMana, 25);
	cout << endl;

	cout << "XP:          ";
	printBar(xp, xpToLevelUp, 25);
	cout << endl;

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

	mana = mana + 50;

	cout << ">> " << getNickName() << " used a mana potion and gains 50 Mana!" << endl;
}

void Mage::setMana(int amount)
{
	mana = amount;
}

void Mage::setManaPotions(int amount)
{
	manaPotions = amount;
}