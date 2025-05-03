#include <iostream>
#include <string>
#include "Mage.h"

Mage::Mage(const string& name) : Character(name), mana(100){
	
}

int Mage::castSpell(){
	
	int damage = getStrength() + (rand() % (getStrength() - 2));

	if (mana >= 10)
	{
		mana -= 10;
		cout << getNickName() << " attacks, and deals: " << damage << " damage to the enemy" << endl;
	}

	return damage;
}