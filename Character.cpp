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
}

string Character::getNickName(){
	return nickName;
}

int Character::getStrength() {
	return strength;
}

void Character::displayCharacter(){

	cout << "\n=== Character Stats ===\n";
	cout << "Name:     " << nickName << endl;
	cout << "Health:   " << health << endl;
	cout << "Strength: " << strength << endl;
	cout << "Defence:  " << defence << endl;
	cout << "Level:    " << level << endl;
}

int Character::attack(){
	int damage = strength + (rand() % strength);

	cout << nickName << " attacks, and deals: " << damage << " damage to the enemy" << endl;
	return damage;
}