#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "Quest.h"
#include "Console.h"
#include "UI.h"

using namespace std;

Character::Character(const string& name) /* : nickName(name), health(0), strength(5), defence(1), level(1) */ {
	nickName = name;

	health = 100;
	strength = 10;
	defence = 7;
	critChance = 5;

	level = 1;
	xp = 0;
	xpToLevelUp = 100;

	gold = 0;

	maxHealth = 100 + ((level - 1) * 10);
	healthPotions = 3;
	strengthPotions = 2;
	defencePotions = 2;
	strengthPotionDuration = 0;
	defencePotionDuration = 0;
	strengthEffectActive = false;
	defenceEffectActive = false;

	escapeBattle = false;

	activeQuests;
	hasQuests = false;
}

Character::Character(const string& name, int hp, int str, int def, int critCh)
{
	nickName = name;

	health = 100 + (10 * hp);
	strength = str;
	defence = def;
	critChance = critCh;

	level = 1;
	xp = 0;
	xpToLevelUp = 100;

	gold = 0;

	maxHealth = health + ((level - 1) * 10);
	healthPotions = 3;
	strengthPotions = 2;
	defencePotions = 2;
	strengthPotionDuration = 0;
	defencePotionDuration = 0;
	strengthEffectActive = false;
	defenceEffectActive = false;

	escapeBattle = false;

	// *skillList;

	activeQuests;
	hasQuests = false;
}

void Character::displayCharacter() const
{
	coloredPrint(Color::Blue, "\n========== CHARACTER STATS ==========\n");
	cout << endl;

	cout << "Name: " << nickName << endl;

	cout << "Health: ";
	printBar(health, maxHealth, 25);
	cout << endl;

	cout << "XP:     ";
	printBar(xp, xpToLevelUp, 25);
	cout << endl;

	cout << endl;
	cout << "Level:         " << level << endl;
	cout << "Strength:      " << strength << endl;
	cout << "Crit Chance:   " << critChance << endl;
	cout << "Defence:       " << defence << endl;
	cout << "Gold:          " << gold << endl;
}

void Character::escapeFromBattle()
{
	int escape;

	escape = rand() % 4;

	if (escape == 1)
	{
		escapeBattle = true;
	}
	else
	{
		escapeBattle = false;
	}
}

int Character::attack()
{
	int damage = strength + (rand() % strength);

	return damage;
}

void Character::abilities()
{
	// Ability Ideas based on level progression:

	cout << "Heavy Blow" << endl;			// + 10 damage, level 5
	cout << "Vengeance" << endl;			// Same damage as the enemy from last turn, level 10
	cout << "Berserker Stance" << endl;		// Maybe a potion (?), level 15
	cout << "Defensive Stance" << endl;		// Buff the defense by 10 or no incoming damage this turn, level 20;
}

void Character::usePotion(int choice)
{
	int maxHealth = 100 + (10 * (level - 1));

	if (healthPotions > 0 && choice == 1)
	{
		health += 20;
		healthPotions--;

		if (health >= maxHealth)
		{
			health = maxHealth;
		}

		cout << ">> " << nickName << " used a health potion and recovered 20 HP!" << endl;
	}
	else if (strengthPotions > 0 && choice == 2)
	{
		strengthPotions--;

		strength = strength + 5;

		cout << ">> " << nickName << " used a strength potion and gain +5 strength for 3 rounds!" << endl;
	}
	else if (defencePotions > 0 && choice == 3)
	{
		defencePotions--;

		defence = defence + 3;

		cout << ">> " << nickName << " used a defence potion and gain +3 defence for 3 rounds!" << endl;
	}
	else
	{
		cout << ">> No potions left!" << endl;
	}
}

void Character::gainXP(int amount)
{
	xp = xp + amount;

	cout << ">> " << nickName << " gained " << amount << " XP!" << endl;

	if (xp >= xpToLevelUp)
	{
		xp = xp - xpToLevelUp;

		levelUp();
	}
}

void Character::levelUp()
{
	level++;

	health = maxHealth;

	xpToLevelUp = 100 + (level * 100);

	maxHealth = health + level * (10);

	health = maxHealth;

	int skillPoints = 2;
	int levelChoice = 0;

	coloredPrint(Color::Cyan, "\n========== Level Up Menu ==========\n");


	while (skillPoints != 0)
	{
		cout << "1) Strength (+2)" << endl;
		cout << "2) Defence (+2)" << endl;
		cout << "3) Crit Chance (+1)" << endl;
		cout << ">> Remaining skillpoint(s): " << skillPoints << endl;
		cout << ">> Choose one: ";
		cin >> levelChoice;

		switch (levelChoice)
		{
		case 1:
		{
			strength = strength + 2;

			cout << "# Strength is increased by 2!" << endl;
			cout << "\n";

			break;
		}
		case 2:
		{
			defence = defence + 2;

			cout << "# Defence is increased by 2!" << endl;
			cout << "\n";

			break;
		}
		case 3:
		{
			critChance = critChance + 1;

			cout << "# Crit chance is increased by 1!" << endl;
			cout << "\n";

			break;
		}
		}

		skillPoints--;
	}

	if (healthPotions == 0)
	{
		healthPotions = healthPotions + 3;
		cout << "# Potions are refilled!" << endl;
		cout << "\n";
	}

	cout << "# Max Health is increased by 10!" << endl;
	cout << "\n";

	cout << ">> " << nickName << " leveled up to Level " << level << "!" << endl;
 }

void Character::addGold(int amount)
{
	gold = gold + amount;

	cout << ">> " << nickName << " received " << amount << " gold!" << endl;
}

void Character::addHealthPotion(int amount)
{
	healthPotions = healthPotions + amount;
}

void Character::addStrengthPotion(int amount)
{
	strengthPotions = strengthPotions + amount;
}

void Character::addDefencePotion(int amount)
{
	defencePotions = defencePotions + amount;
}

void Character::addQuest(const Quest& q)
{
	activeQuests.push_back(q);
}

void Character::checkQuestCompletion(const string& enemyName)
{
	// bind it by reference, deduce the type
	for (auto& q : activeQuests)
	{
		if (!q.isComplete() && q.targetName == enemyName)
		{
			q.progress++;

			cout << ">> Quest updated: " << q.description << " (" << q.progress << "/" << q.targetCount << ")\n";

			if (q.isComplete())
			{
				cout << ">> Quest complete! +" << q.rewardXP << " XP, +" << q.rewardGold << " gold\n";

				gainXP(q.rewardXP);
				addGold(q.rewardGold);

				hasQuests = false;
			}
		}
	}
}

void Character::displayQuests() const
{
	coloredPrint(Color::Magenta, "\n=== Active Quests ===\n");
	cout << endl;

	for (const auto& q : activeQuests)
	{
		cout << q.description << " (" << q.progress << "/" << q.targetCount << ")";

		if (q.isComplete())
		{
			coloredPrint(Color::Green, " [Completed]");
		}

		cout << "\n";
	}

	cout << endl;
}

int Character::getStrengthPotionDuration() const
{
	return strengthPotionDuration;
}

int Character::getDefencePotionDuration() const
{ 
	return defencePotionDuration;
}

bool Character::isStrengthEffectActive() const 
{ 
	return strengthEffectActive; 
}

bool Character::isDefenceEffectActive() const
{ 
	return defenceEffectActive; 
}

void Character::takeDamage(int damage)
{
	this->health = this->health - damage;

	if (this->health < 0)
	{
		this->health = 0;
	}
}

void Character::clearQuests() {
	activeQuests.clear();
	hasQuests = false;
}

// Getters
const vector<Quest>& Character::getActiveQuests() const
{
	return activeQuests;
}

int Character::getXPToLevelUp() const
{
	return xpToLevelUp;
}

int Character::getXP() const
{
	return xp;
}

string Character::getNickName() const
{
	return nickName;
}

int Character::getHealth() const
{
	return health;
}

int Character::getStrength() const
{
	return strength;
}

int Character::getDefence() const
{
	return defence;
}

int Character::getCritChance() const
{
	return critChance;
}

int Character::getLevel() const
{
	return level;
}

int Character::getHealthPotions() const
{
	return healthPotions;
}

int Character::getStrengthPotions() const
{
	return strengthPotions;
}

int Character::getDefencePotions() const
{
	return defencePotions;
}

int Character::getGold() const
{
	return gold;
}

bool Character::getEscapeBattle()
{
	return escapeBattle;
}

bool Character::getHasQuests()
{
	return hasQuests;
}

// Setters
void Character::setEscapeBattle(bool escape)
{
	escapeBattle = escape;
}

void Character::setHasQuests(bool hasQuest)
{
	hasQuests = hasQuest;
}

void Character::setStrength(int strength)
{
	this->strength = strength;
}

void Character::setDefence(int defence)
{
	this->defence = defence;
}\

void Character::setCritChance(int crit)
{
	critChance = critChance + crit;
}

void Character::setStrengthEffectActive(bool active)
{
	strengthEffectActive = active;
}

void Character::setDefenceEffectActive(bool active)
{
	defenceEffectActive = active;
}

void Character::setStrengthPotionDuration(int duration)
{
	strengthPotionDuration = duration;
}

void Character::setDefencePotionDuration(int duration)
{
	defencePotionDuration = duration;
}

void Character::setHealthPotions(int amount)
{
	healthPotions = amount;
}

void Character::setStrengthPotions(int amount)
{
	strengthPotions = amount;
}

void Character::setDefencePotions(int amount)
{
	defencePotions = amount;
}

void Character::setNickName(string name)
{
	nickName = name;
}

void Character::setLevel(int lvl)
{
	level = lvl;
}

void Character::setXP(int xp)
{
	this->xp = xp;
}

void Character::setGold(int amount)
{
	gold = amount;
}

void Character::setHealth(int amount)
{
	health = amount;
}