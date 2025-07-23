#include <iostream>
#include <string>
#include "Necromancer.h"
#include "UI.h"
#include "Console.h"

Necromancer::Necromancer(const string& name) : Character(name), mana(50), maxMana(100), manaPotions(3), minionPower(12)
{
	strength = 0;
	defence = 3;
	critChance = 5;
	maxHealth = 100;
	health = maxHealth;
	maxMinion = 3;
	minionCounter = 0;
	summonPotions = 3;
}

Necromancer::Necromancer(const string& name, int hp, int mp, int def, int critCh) : Character(name, hp, 0, def, critCh), maxMana(100 + (hp * 10)), mana(maxMana), manaPotions(3), minionPower(mp)
{
	strength = 0;
	maxMinion = 3;
	minionCounter = 0;
	summonPotions = 3;
}

void Necromancer::addManaPotion(int amount)
{
	manaPotions = manaPotions + mana;
}

void Necromancer::displayCharacter() const
{
	coloredPrint(Color::Cyan, "\n========== MAGE STATS ==========\n\n");
	cout << "Name:           " << nickName << "\n";

	cout << "Health:         ";
	printBar(health, maxHealth, 25);
	cout << endl;

	cout << "Mana:           ";
	printBar(mana, maxMana, 25);
	cout << endl;

	cout << "XP:             ";
	printBar(xp, xpToLevelUp, 25);
	cout << endl;

	cout << endl;
	cout << "Level:          " << level << "\n";
	cout << "Minion Power:   " << minionPower << "\n";
	cout << "Minion Counter: " << minionCounter << "\n";
	cout << "Defence:        " << defence << "\n";
	cout << "Gold:           " << gold << "\n";
}

void Necromancer::levelUp()
{
	level++;

	xpToLevelUp = 100 + (level * 100);

	maxHealth = maxHealth + (level - 1) * (10);

	maxMana = maxMana + (level - 1) * 50;

	health = maxHealth;

	int levelUpChoice1 = 0;
	int levelUpChoice2 = 0;

	coloredPrint(Color::Cyan, "\n========== Level Up Menu ==========\n");

	cout << "1) Minion Power (+2)" << endl;
	cout << "2) Defence (+2)" << endl;
	cout << "3) Spell Crit Chance (+1)" << endl;
	cout << ">> Choose your upgrades (1 3):";
	cin >> levelUpChoice1 >> levelUpChoice2;

	if (levelUpChoice1 == 1)
	{
		minionPower = minionPower + 2;

		cout << "# Minion Power is increased by 2!" << endl;
	}
	else if (levelUpChoice1 == 2)
	{
		defence = defence + 2;

		cout << "# Defence is increased by 2!" << endl;
	}
	else if (levelUpChoice1 == 3)
	{
		critChance = critChance + 1;

		cout << "# Spell Crit Chance is increased by 1!" << endl;
	}

	if (levelUpChoice2 == 1)
	{
		minionPower = minionPower + 2;

		cout << "# Minion Power is increased by 2!" << endl;
	}
	else if (levelUpChoice2 == 2)
	{
		defence = defence + 2;

		cout << "# Defence is increased by 2!" << endl;
	}
	else if (levelUpChoice2 == 3)
	{
		critChance = critChance + 1;

		cout << "# Spell Crit Chance is increased by 1!" << endl;
	}

	if (healthPotions == 0)
	{
		healthPotions = 3;
		cout << "# Health potions are refilled!" << endl;
	}

	if (manaPotions == 0)
	{
		manaPotions = 3;
		cout << "# Mana potions are refilled!" << endl;
	}

	cout << "# Max Health is increased by 10!" << endl;

	cout << ">> " << nickName << " leveled up to Level " << level << "!" << endl;
}

void Necromancer::useManaPotion()
{
	manaPotions--;

	if (mana >= maxMana)
	{
		mana = maxMana;
	}
	else
	{
		mana = mana + 50;
	}

	cout << ">> " << getNickName() << " used a mana potion and gained 50 Mana!" << endl;
}

void Necromancer::useMinionPotion()
{
	summonPotions--;

	minionCounter++;

	cout << ">> " << getNickName() << " used a mana potion and gained 50 Mana!" << endl;
}

//void Necromancer::unlockAbilitiesByLevel()
//{
//	
//}

//void Necromancer::applyItemBonus(const Item& it)
//{
//
//}
//

//void Necromancer::removeItemBonus(const Item& it)
//{
//
//}

//void Necromancer::addItem(Item it)
//{
//
//}

void Necromancer::setMana(int amount)
{
	mana = amount;
}

void Necromancer::setManaPotions(int amount)
{
	manaPotions = amount;
}

int Necromancer::getMaxMinion() const
{
	return maxMinion;
}

int Necromancer::getSummonPotions() const
{
	return summonPotions;
}

int Necromancer::getMana() const
{
	return mana;
}

void Necromancer::summonMinion(const Minion& m)
{
	if (minionCounter >= maxMinion || mana < 25)
	{
		return;
	}

	minions.push_back(m);
	mana -= 10;
	++minionCounter;

	cout << ">> Summoned " << m.name << "!\n";
}

void Necromancer::clearDeadMinions()
{
	minions.erase(remove_if(minions.begin(), minions.end(), [&](const Minion& m) { return m.health <= 0 || --(const_cast<Minion&>(m).remainingTurns) < 0; }), minions.end());
	minionCounter = (int)minions.size();
}

const vector<Minion>& Necromancer::getMinions() const
{
	return minions;
}