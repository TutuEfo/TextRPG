#include <iostream>
#include "Character.h"
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

Character::Character(const string& name) /* : nickName(name), health(0), strength(5), defence(1), level(1) */ {
	nickName = name;
	health = 100;
	strength = 5;
	defence = 1;
	level = 1;
	potions = 3;
}

void Character::displayCharacter() const
{

	cout << "\n=== Character Stats ===\n";
	cout << "Name:     " << nickName << endl;
	cout << "Health:   " << health << endl;
	cout << "Strength: " << strength << endl;
	cout << "Defence:  " << defence << endl;
	cout << "Level:    " << level << endl;
}

int Character::attack()
{
	int damage = strength + (rand() % strength);

	return damage;
}

void Character::usePotion()
{
	int maxHealth = 100 + (10 * (level - 1));

	if (potions > 0)
	{
		health += 20;
		potions--;

		if (health >= maxHealth)
		{
			health = maxHealth;
		}

		cout << nickName << " used a potion and recovered 20 HP!" << endl;
	}
	else
	{
		cout << "No potions left!" << endl;
	}
	
}

string Character::getNickName()
{
	return nickName;
}

int Character::getHealth()
{
	return health;
}

int Character::getStrength()
{
	return strength;
}

int Character::getDefence()
{
	return defence;
}

int Character::getLevel()
{
	return level;
}

int Character::getPotions() const
{
	return potions;
}

void Character::takeDamage(int damage)
{
	this->health = this->health - damage;

	if (this->health < 0)
	{
		this->health = 0;
	}
}