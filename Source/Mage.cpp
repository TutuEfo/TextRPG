#include <iostream>
#include <string>
#include "Character.h"
#include "Mage.h"

using namespace std;

Mage::Mage(const string& name) : Character(name){}

int Mage::castSpell()
{
	
	int damage = 0;

	if (mana >= 10)
	{
		damage = getStrength() + (rand() % (getStrength() - 2));

		mana -= 10;
	}

	return damage;
}

Mage::Mage(const string& name, int hp, int str, int def, int critCh) : Character(name, hp, str, def, critCh){}

void Mage::displayCharacter() const
{
	Character::displayCharacter();
	cout << "Mana:        " << mana << endl;
}

void Mage::addManaPotion(int amount)
{
	manaPotions = manaPotions + amount;
}

int Mage::getMana()
{
	return mana;
}

int Mage::getManaPotions()
{
	return manaPotions;
}

void Mage::useManaPotion()
{
	manaPotions--;

	mana = mana + 25;

	cout << ">> " << getNickName() << " used a mana potion and gains 25 Mana!" << endl;
}