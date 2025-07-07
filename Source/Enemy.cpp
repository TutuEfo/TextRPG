#include <iostream>
#include <cstdlib>
#include <string>
#include "Enemy.h"
#include "Console.h"
#include "Item.h"
#include "UI.h"

using namespace std;

Enemy::Enemy()
{
	enemyName = "Undefined";
	enemyLevel = 0;
	enemyHealth = 0;
	enemyMaxHealth = enemyHealth;
	enemyDefence = 0;
	enemyStrength = 0;
}

Enemy::Enemy(const string& name, int health, int defence, int strength, int level)
{
	enemyName = name;
	enemyLevel = level;
	enemyHealth = health;
	enemyDefence = defence;
	enemyStrength = strength;
	enemyMaxHealth = enemyHealth;
}

void Enemy::displayStatus() const
{
	coloredPrint(Color::Red, "\n========== ENEMY STATS ==========\n");
	cout << "Name: " << enemyName << endl;
	cout << "Health: ";
	printBar(enemyHealth, enemyMaxHealth, 25);
	cout << endl;
	cout << "Strength:    " << enemyStrength << endl;
	cout << "Defence:     " << enemyDefence << endl;
	cout << "Level:       " << enemyLevel << endl;
}

Enemy Enemy::generateEnemy(int level)
{
	const string types[] = { "Goblin", "Orc", "Bandit", "Troll" };
	int typeIndex = rand() % 4;

	string name = types[typeIndex];

	int baseHealth = 50 + (level * 10);
	int baseStrength = 3 + (level * 2);
	int baseDefence = 2 + (level * 1);

	int enemyLevel = max(1, level + (rand() % 3 - 1));

	int health = baseHealth + (enemyLevel * 50);
	int strength = baseStrength + enemyLevel;
	int defence = baseDefence + enemyLevel;

	return Enemy(name, health, defence, strength, enemyLevel);
}

Enemy Enemy::generateBoss(int level)
{
	const string bossAdjectives[] = { "Ancient", "Savage", "Unholy", "Wrathful", "Doombringer", "Infernal" };
	const string bossNames[] = { "Goblin Boss", "Orc Boss", "Bandit Boss", "Troll Boss" };

	int bossAdjIndex = rand() % 5;
	int bossNamesIndex = rand() % 4;

	string name = bossAdjectives[bossAdjIndex] + " " + bossNames[bossNamesIndex];

	int enemyLevel = level + 1;
	int health = 150 + (level * 20);
	int strength = 15 + (level * 3);
	int defence = 10 + (level * 2);

	return Enemy(name, health, defence, strength, enemyLevel);
}

bool Enemy::isAlive() const
{
	if (enemyHealth > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Enemy::attackCharacter()
{
	return (enemyStrength + (rand() % enemyStrength));
}

void Enemy::takeDamage(int damage)
{
	this->enemyHealth = this->enemyHealth - max(0, damage - enemyDefence);

	if (this->enemyHealth < 0)
	{
		this->enemyHealth = 0;
	}
}

// Getters
int Enemy::getGoldReward() const
{
	return (enemyLevel * (10 + (rand() % 5 + 1)));
}

int Enemy::getXPReward()
{
	return (20 + ((rand() % 10) + 1));
}

int Enemy::getGoldRewardBoss() const
{
	return (enemyLevel * (30 + (rand() % 10 + 1)));
}

int Enemy::getXPRewardBoss()
{
	return (60 + ((rand() % 20) + 1));
}

Item Enemy::getItemReward()
{
	Item it;
	int itemType;

	itemType = (rand() % 10);
	
	if (itemType == 0)
	{
		it.type = ItemType::HealthPotion;
		it.name = "Health Potion";

		it.bonusStat = 20;
		it.description = "+20 HP";
	}
	else if (itemType == 1)
	{
		it.type = ItemType::ManaPotion;
		it.name = "Mana Potion";

		it.bonusStat = 50;
		it.description = "+50 MP";
	}
	else if (itemType == 2)
	{
		it.type = ItemType::Sword;

		int swordStat;
		swordStat = rand() % 5 + (enemyLevel + 2);

		const string swordAdjectives[] = { "Rusty", "Sharp", "Holly", "Vicious" };
		int swordAdj;
		swordAdj = rand() % 4;

		it.name = swordAdjectives[swordAdj] + " Sword";
		it.bonusStat = swordStat;
		it.description = "+" + to_string(swordStat) + " Strength";
	}
	else if (itemType == 3)
	{
		it.type = ItemType::Shield;

		int shieldStat;
		shieldStat = rand() % 5 + (enemyLevel + 2);

		const string shieldAdjectives[] = { "Round", "Large", "Protective", "Annoying Wooden" };
		int shieldAdj;
		shieldAdj = rand() % 4;

		it.name = shieldAdjectives[shieldAdj] + " Shield";
		it.bonusStat = shieldStat;
		it.description = "+" + to_string(shieldStat) + " Defence";
	}
	else if (itemType == 4)
	{
		it.type = ItemType::Wand;

		int wandStat;
		wandStat = rand() % 5 + (enemyLevel + 2);

		const string wandAdjectives[] = { "Miserable", "Fairy", "Crystal", "Scarlet" };
		int wandAdj;
		wandAdj = rand() % 4;

		it.name = wandAdjectives[wandAdj] + " Wand";
		it.bonusStat = wandStat;
		it.description = "+" + to_string(wandStat) + " Spell Power";
	}
	else if (itemType == 5)
	{
		it.type = ItemType::Cloak;

		int cloakStat;
		cloakStat = rand() % 5 + (enemyLevel + 2);

		const string cloakAdjectives[] = { "Dry", "Shiny", "fur-lined Crimson", "Dusky Yellow" };
		int cloakAdj;
		cloakAdj = rand() % 4;

		it.name = cloakAdjectives[cloakAdj] + " Wand";
		it.bonusStat = cloakStat;
		it.description = "+" + to_string(cloakStat) + " MP";
	}
	else if (itemType == 6)
	{
		it.type = ItemType::Helmet;

		int helmetStat;
		helmetStat = rand() % 5 + (enemyLevel + 2);

		const string helmetAdjectives[] = { "White", "Armored", "Marvelously Protective", "Dusky Yellow" };
		int helmetAdj;
		helmetAdj = rand() % 4;

		it.name = helmetAdjectives[helmetAdj] + " Helmet";
		it.bonusStat = helmetStat;
		it.description = "+" + to_string(helmetStat) + " Defence";
	}
	else if (itemType == 7)
	{
		it.type = ItemType::Chestplate;

		int chestPlateStat;
		chestPlateStat = rand() % 5 + (enemyLevel + 2);

		const string chestPlateAdjectives[] = { "Cumbersome", "Armored", "Molten", "Massive" };
		int chestPlateAdj;
		chestPlateAdj = rand() % 4;

		it.name = chestPlateAdjectives[chestPlateAdj] + " Chestplate";
		it.bonusStat = chestPlateStat;
		it.description = "+" + to_string(chestPlateStat) + " Defence";
	}
	else if (itemType == 8)
	{
		it.type = ItemType::Leggings;

		int leggingsStat;
		leggingsStat = rand() % 5 + (enemyLevel + 2);

		const string leggingsAdjectives[] = { "Well-Worn", "Armored", "Gaudy Blue", "Clean" };
		int leggingsAdj;
		leggingsAdj = rand() % 4;

		it.name = leggingsAdjectives[leggingsAdj] + " Leggings";
		it.bonusStat = leggingsStat;
		it.description = "+" + to_string(leggingsStat) + " Defence";
	}
	else if (itemType == 9)
	{
		it.type = ItemType::Boots;

		int BootsStat;
		BootsStat = rand() % 5 + (enemyLevel + 2);

		const string BootsAdjectives[] = { "Traditional Cheap", "Armored", "Weighted Lunar", "Harmless" };
		int BootsAdj;
		BootsAdj = rand() % 4;

		it.name = BootsAdjectives[BootsAdj] + " Boots";
		it.bonusStat = BootsStat;
		it.description = "+" + to_string(BootsStat) + " Defence";
	}

	return it;
}

Item Enemy::getItemRewardBoss()
{
	Item it;
	int itemType;

	itemType = (rand() % 10);

	if (itemType == 0)
	{
		it.type = ItemType::HealthPotion;
		it.name = "Health Potion";

		it.bonusStat = 20;
		it.description = "+20 HP";
	}
	else if (itemType == 1)
	{
		it.type = ItemType::ManaPotion;
		it.name = "Mana Potion";

		it.bonusStat = 50;
		it.description = "+50 MP";
	}
	else if (itemType == 2)
	{
		it.type = ItemType::Sword;

		int swordStat;
		swordStat = rand() % 5 + (enemyLevel + 2) + 5;

		const string swordAdjectives[] = { "Rusty", "Sharp", "Holly", "Vicious" };
		int swordAdj;
		swordAdj = rand() % 4;

		it.name = swordAdjectives[swordAdj] + " Sword";
		it.bonusStat = swordStat;
		it.description = "+" + to_string(swordStat) + " Strength";
	}
	else if (itemType == 3)
	{
		it.type = ItemType::Shield;

		int shieldStat;
		shieldStat = rand() % 5 + (enemyLevel + 2) + 5;

		const string shieldAdjectives[] = { "Round", "Large", "Protective", "Annoying Wooden" };
		int shieldAdj;
		shieldAdj = rand() % 4;

		it.name = shieldAdjectives[shieldAdj] + " Shield";
		it.bonusStat = shieldStat;
		it.description = "+" + to_string(shieldStat) + " Defence";
	}
	else if (itemType == 4)
	{
		it.type = ItemType::Wand;

		int wandStat;
		wandStat = rand() % 5 + (enemyLevel + 2) + 5;

		const string wandAdjectives[] = { "Miserable", "Fairy", "Crystal", "Scarlet" };
		int wandAdj;
		wandAdj = rand() % 4;

		it.name = wandAdjectives[wandAdj] + " Wand";
		it.bonusStat = wandStat;
		it.description = "+" + to_string(wandStat) + " Spell Power";
	}
	else if (itemType == 5)
	{
		it.type = ItemType::Cloak;

		int cloakStat;
		cloakStat = rand() % 5 + (enemyLevel + 2) + 5;

		const string cloakAdjectives[] = { "Dry", "Shiny", "fur-lined Crimson", "Dusky Yellow" };
		int cloakAdj;
		cloakAdj = rand() % 4;

		it.name = cloakAdjectives[cloakAdj] + " Wand";
		it.bonusStat = cloakStat;
		it.description = "+" + to_string(cloakStat) + " MP";
	}
	else if (itemType == 6)
	{
		it.type = ItemType::Helmet;

		int helmetStat;
		helmetStat = rand() % 5 + (enemyLevel + 2) + 5;

		const string helmetAdjectives[] = { "White", "Armored", "Marvelously Protective", "Dusky Yellow" };
		int helmetAdj;
		helmetAdj = rand() % 4;

		it.name = helmetAdjectives[helmetAdj] + " Helmet";
		it.bonusStat = helmetStat;
		it.description = "+" + to_string(helmetStat) + " Defence";
	}
	else if (itemType == 7)
	{
		it.type = ItemType::Chestplate;

		int chestPlateStat;
		chestPlateStat = rand() % 5 + (enemyLevel + 2) + 5;

		const string chestPlateAdjectives[] = { "Cumbersome", "Armored", "Molten", "Massive" };
		int chestPlateAdj;
		chestPlateAdj = rand() % 4;

		it.name = chestPlateAdjectives[chestPlateAdj] + " Chestplate";
		it.bonusStat = chestPlateStat;
		it.description = "+" + to_string(chestPlateStat) + " Defence";
	}
	else if (itemType == 8)
	{
		it.type = ItemType::Leggings;

		int leggingsStat;
		leggingsStat = rand() % 5 + (enemyLevel + 2) + 5;

		const string leggingsAdjectives[] = { "Well-Worn", "Armored", "Gaudy Blue", "Clean" };
		int leggingsAdj;
		leggingsAdj = rand() % 4;

		it.name = leggingsAdjectives[leggingsAdj] + " Leggings";
		it.bonusStat = leggingsStat;
		it.description = "+" + to_string(leggingsStat) + " Defence";
	}
	else if (itemType == 9)
	{
		it.type = ItemType::Boots;

		int BootsStat;
		BootsStat = rand() % 5 + (enemyLevel + 2) + 5;

		const string BootsAdjectives[] = { "Traditional Cheap", "Armored", "Weighted Lunar", "Harmless" };
		int BootsAdj;
		BootsAdj = rand() % 4;

		it.name = BootsAdjectives[BootsAdj] + " Boots";
		it.bonusStat = BootsStat;
		it.description = "+" + to_string(BootsStat) + " Defence";
	}

	return it;
}

string Enemy::getEnemyName()
{
	return enemyName;
}

int Enemy::getEnemyHealth()
{
	return enemyHealth;
}

int Enemy::getEnemyDefence()
{
	return enemyDefence;
}

int Enemy::getEnemyStrength()
{
	return enemyStrength;
}

int Enemy::getEnemyLevel()
{
	return enemyLevel;
}
