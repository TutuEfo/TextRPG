#include <iostream>
#include <string>
#include "Character.h"
#include "Mage.h"

using namespace std;

Mage::Mage(const string& name) : Character(name), mana(100){
	
}

int Mage::castSpell(){
	
	int damage = 0;

	if (mana >= 10)
	{
		damage = getStrength() + (rand() % (getStrength() - 2));

		mana -= 10;
	}

	return damage;
}

void Mage::displayCharacter() const {
	Character::displayCharacter();
	cout << "Mana:     " << mana << endl;
}

int Mage::getMana()
{
	return mana;
}