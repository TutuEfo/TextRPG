#include "Combat.h"
#include "Console.h"
#include "Mage.h"
#include <iostream>
#include <limits>

Combat::Combat(Character& player, Enemy& enemy) : cPlayer(player), cEnemy(enemy){
}

bool Combat::runCombat()
{
	cPlayer.setEscapeBattle(false);

	while (cPlayer.getHealth() > 0 && cEnemy.isAlive() && !cPlayer.getEscapeBattle())
	{
		displayStats();

		int choice = chooseAction();

		performAction(choice);

		if (cPlayer.getHealth() > 0 && cEnemy.isAlive() && !cPlayer.getEscapeBattle())
		{
			enemyTurn();
		}

		endOfRoundCleanup();
	}

	return (cPlayer.getHealth() > 0);
}

void Combat::displayStats() const
{
	Mage* magePtr = dynamic_cast<Mage*>(&cPlayer);

	if (magePtr != nullptr)
	{
		magePtr->displayCharacter();
	}
	else
	{
		cPlayer.displayCharacter();
	}

	cEnemy.displayStatus();
}

int Combat::chooseAction() const
{
	Mage* magePtr = dynamic_cast<Mage*>(&cPlayer);
	
	int choice = 0;

	while (true)
	{
		coloredPrint(Color::Yellow, "\n>> Choose action:\n");
		
		if (magePtr)
		{
			std::cout << "1) Cast Spell" << endl;
			std::cout << "2) Defend" << endl;
			std::cout << "3) Use Item" << endl;
			std::cout << "4) Escape" << endl;
		}
		else
		{
			std::cout << "1) Attack" << endl;
			std::cout << "2) Defend" << endl;
			std::cout << "3) Use Item" << endl;
			std::cout << "4) Escape" << endl;
		}

		std::cout << "Enter your choice: ";

		if (cin >> choice)
		{
			bool validChoice = (choice >= 1 && choice <= 4);

			if (validChoice)
			{
				break;
			}

			coloredPrint(Color::Red, "Invalid choice.\n");
			std::cout << "Enter your choice: " << endl;
		}
	}

	return choice;
}

void Combat::performAction(int choice)
{
	Mage* magePtr = dynamic_cast<Mage*>(&cPlayer);

	switch (choice)
	{
	case 1:
	{
		if (magePtr)
		{
			int spellChoice = 0;

			playerDisplaySpells();

			cin >> spellChoice;

			playerCastSpell(spellChoice);
			
			break;
		}

		playerAttack();

		break;
	}
	case 2:
		playerDefend();

		break;

	case 3:
		playerUseItem();

		break;

	case 4:
	{
		playerEscape();

		break;
	}
	default:

		break;
	}
}

void Combat::endOfRoundCleanup() {

	if (cPlayer.getStrengthPotionDuration() > 0)
	{
		int duration = cPlayer.getStrengthPotionDuration() - 1;

		cPlayer.setStrengthPotionDuration(duration);

		if (duration == 0 && cPlayer.isStrengthEffectActive())
		{
			cPlayer.setStrength(cPlayer.getStrength() - 5);
			cPlayer.setStrengthEffectActive(false);
			coloredPrint(Color::Green, "Strength buff wore off.\n");
		}
	}

	if (cPlayer.getDefencePotionDuration() > 0)
	{
		int duration = cPlayer.getDefencePotionDuration() - 1;

		cPlayer.setDefencePotionDuration(duration);

		if (duration == 0 && cPlayer.isDefenceEffectActive())
		{
			cPlayer.setDefence(cPlayer.getDefence() - 3);
			cPlayer.setDefenceEffectActive(false);
			coloredPrint(Color::Green, "Defence buff wore off.\n");
		}
	}

	cout << ">> Press Enter to continue...";
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.get();
}

void Combat::playerAttack()
{
	int damage = cPlayer.attack();

	bool crit = (rand() % 100) < cPlayer.getCritChance();

	if (crit)
	{
		damage = 2 * damage;

		coloredPrint(Color::Red, ">> CRITICAL HIT!!!\n");
	}

	int takeDamage = std::max(0, damage - cEnemy.getEnemyDefence());

	cEnemy.takeDamage(takeDamage);
	
	cout << ">> " << cPlayer.getNickName() << " deals " << takeDamage << " damage!\n";
}

void Combat::playerUseItem()
{
	int choice = promptPotionMenu();

	switch (choice)
	{
	case 1:
		cPlayer.usePotion(1);

		break;
	case 2:
		if (!cPlayer.isStrengthEffectActive())
		{
			cPlayer.usePotion(2);
			cPlayer.setStrengthPotionDuration(4);
			cPlayer.setStrengthEffectActive(true);
		}
		else
		{
			coloredPrint(Color::Yellow, "Strength buff active.\n");
		}

		break;
	case 3:
		if (!cPlayer.isDefenceEffectActive())
		{
			cPlayer.usePotion(3);
			cPlayer.setDefencePotionDuration(4);
			cPlayer.setDefenceEffectActive(true);
		}
		else
		{
			coloredPrint(Color::Yellow, "Defence buff active.\n");
		}

		break;
	case 4:
	{
		Mage* magePtr = dynamic_cast<Mage*>(&cPlayer);
		if (magePtr)
		{
			magePtr->useManaPotion();

			break;
		}

		break;
	}
	case 5:
	{
		int backMenu = chooseAction();
		performAction(backMenu);

		break;
	}
	default: 
		break;
	}
}

void Combat::playerDisplaySpells()
{
	Mage* magePtr = dynamic_cast<Mage*>(&cPlayer);

	cout << "========== Spell List ==========" << endl;

	cout << "1) Fireball  (10 MP)" << endl;
	cout << "2) Lightning (25 MP)" << endl;
	cout << "3) Ice Bolts (50 MP)" << endl;
	cout << ">> Remaining mana: " << magePtr->getMana() << endl;
	cout << ">> Enter your choice: ";
}

void Combat::playerCastSpell(int choice)
{
	Mage* magePtr = dynamic_cast<Mage*>(&cPlayer);

	int damage = 0;

	if (magePtr && magePtr->getMana() >= 10)
	{
		cout << ">> " << cPlayer.getNickName() << " casts a spell\n";

		damage = magePtr->castSpell(choice);

		bool crit = (rand() % 100) < cPlayer.getCritChance();

		if (crit)
		{
			damage = 2 * damage;

			coloredPrint(Color::Red, ">> CRITICAL HIT!!!\n");
		}

		damage = max(0, damage - cEnemy.getEnemyDefence());

		cEnemy.takeDamage(damage);

		cout << ">> Spell deals " << damage << " damage.\n";
	}
	else
	{
		coloredPrint(Color::Yellow, "Not enough mana.\n");
	}
}

void Combat::playerEscape()
{
	cPlayer.escapeFromBattle();

	if (cPlayer.getEscapeBattle())
	{
		coloredPrint(Color::Green, "You escaped!\n");
	}
	else
	{
		coloredPrint(Color::Red, "Escape failed!\n");
	}
}

void Combat::enemyTurn()
{
	std::cout << ">> Enemy attacks!\n";

	int damage = 0;

	if (damageReduction != 0)
	{
		damage = max(0, cEnemy.attackCharacter() - cPlayer.getDefence() - damageReduction);
	}
	else
	{
		damage = max(0, cEnemy.attackCharacter() - cPlayer.getDefence());
	}

	bool crit = (rand() % 100) < (cEnemy.getEnemyLevel() + 1);

	if (crit)
	{
		damage = 2 * damage;

		coloredPrint(Color::Red, ">> CRITICAL HIT!!!\n");
	}

	cPlayer.takeDamage(damage);
	
	std::cout << ">> " << cPlayer.getNickName() <<  " takes " << damage << " damage.\n";
}

int Combat::promptPotionMenu() const
{
	Mage* magePtr = dynamic_cast<Mage*>(&cPlayer);

	int choice = 0;

	while (true)
	{
		coloredPrint(Color::Cyan, "\n-- Items --\n");
		std::cout << "1) Health (" << cPlayer.getHealthPotions() << ")" << endl;
		std::cout << "2) Strength (" << cPlayer.getStrengthPotions() << ")" << endl;
		std::cout << "3) Defence (" << cPlayer.getDefencePotions() << ")" << endl;

		if (magePtr)
		{
			std::cout << "4) Mana (" << magePtr->getManaPotions() << ")" << endl;
			std::cout << "5) Back" << endl;
		}
		else
		{
			std::cout << "4) Back" << endl;
		}

		std::cout << "Choose: ";

		if (cin >> choice)
		{
			bool valid = magePtr ? (choice >= 1 && choice <= 5) : (choice >= 1 && choice <= 4);

			if (valid)
			{
				break;
			}
		}

		cin.clear();
		coloredPrint(Color::Red, "Invalid choice.\n");
	}
	return choice;
}

void Combat::playerDefend()
{
	damageReduction = ((rand() % cPlayer.getDefence()) + cPlayer.getLevel());

	cout << cPlayer.getNickName() << " reduces the damage by " << damageReduction << "!" << endl;
}