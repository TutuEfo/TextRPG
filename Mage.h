#ifndef MAGE_H
#define MAGE_H

#include <string>
#include <iostream>
#include "Character.h"

using namespace std;

class Mage : public Character {
private:
	int mana;
public:
	Mage(const string& name);
	int castSpell();
	void displayCharacter() const override;
};


#endif // MAGE_H