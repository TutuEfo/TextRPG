#include <iostream>
#include <string>
#include "Character.h"
#include "Mage.h"
#include "UI.h"

using namespace std;

Mage::Mage(const string& name) : Character(name){}

int Mage::castSpell()
{
	
	int damage = 0;

	if (mana >= 10)
	{
		damage = getStrength() + (rand() % getStrength());

		mana -= 10;
	}

	return damage;
}

Mage::Mage(const string& name, int hp, int str, int def, int critCh) : Character(name, hp, str, def, critCh){}

void Mage::displayCharacter() const
{
	Character::displayCharacter();

	cout << "Mana:   ";
	printBar(mana, 100, 20);
	cout << endl;
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