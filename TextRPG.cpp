#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Mage.h"

using namespace std;

int main()
{
    // static_cast: converting the value to the expected type.
    srand(static_cast<unsigned int>(time(0)));

    // Testing the Classes:
    Mage myCharMage("Gandalf");
    myCharMage.displayCharacter();
    myCharMage.castSpell();

    Character myCharDefault("TutuEfo");
    myCharDefault.displayCharacter();
    myCharDefault.attack();
        
    return 0;
}
