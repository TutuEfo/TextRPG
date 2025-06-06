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

void Mage::levelUp()
{
	level++;

	health = maxHealth;

	xpToLevelUp = 100 + (level * 100);

	maxHealth = health + level * (10);

	health = maxHealth;

	int skillPoints = 2;
	int levelChoice = 0;

	coloredPrint(Color::Cyan, "\n========== Level Up Menu ==========\n");


	while (skillPoints != 0)
	{
		cout << "1) Spell Power (+5)" << endl;
		cout << "2) Defence (+3)" << endl;
		cout << "3) Spell Crit Chance (+1)" << endl;
		cout << ">> Remaining skillpoint(s): " << skillPoints << endl;
		cout << ">> Choose one: ";
		cin >> levelChoice;

		switch (levelChoice)
		{
		case 1:
		{
			spellPower = spellPower + 5;

			cout << "# Spell Power is increased by 5!" << endl;
			cout << "\n";

			break;
		}
		case 2:
		{
			defence = defence + 3;

			cout << "# Defence is increased by 3!" << endl;
			cout << "\n";

			break;
		}
		case 3:
		{
			critChance = critChance + 1;

			cout << "# Crit chance is increased by 1!" << endl;
			cout << "\n";

			break;
		}
		}

		skillPoints--;
	}

	if (healthPotions == 0)
	{
		healthPotions = healthPotions + 3;
		cout << "# Potions are refilled!" << endl;
		cout << "\n";
	}

	cout << "# Max Health is increased by 10!" << endl;
	cout << "\n";

	cout << ">> " << nickName << " leveled up to Level " << level << "!" << endl;
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