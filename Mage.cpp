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
		cout << getNickName() << " casts spell, and deals: " << damage << " damage to the enemy!" << endl;
	}
	else if (mana < 10)
	{
		cout << "Don't have enough mana to cast a spell!" << endl;
	}

	return damage;
}

void Mage::displayCharacter() const {
	Character::displayCharacter();
	cout << "Mana:     " << mana << endl;
}