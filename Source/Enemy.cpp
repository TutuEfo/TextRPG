#include <iostream>
#include <cstdlib>
#include <string>
#include "Enemy.h"
#include "Console.h"

using namespace std;

Enemy::Enemy()
{
	enemyName = "Undefined";
	enemyLevel = 0;
	enemyHealth = 0;
	enemyDefence = 0;
	enemyStrength = 0;
}

Enemy::Enemy(const string& name, int health, int defence, int strength, int level)
{
	enemyName = name;
	enemyLevel = max(1, level + (rand() % 3));
	enemyHealth = health + (level - 1) * 10;
	enemyDefence = defence + level;
	enemyStrength = strength + level;
}

void Enemy::displayStatus() const
{
	coloredPrint(Color::Red, "\n========== ENEMY STATS ==========\n");
	cout << "Name:        " << enemyName << endl;
	cout << "Health:      " << enemyHealth << endl;
	cout << "Strength:    " << enemyStrength << endl;
	cout << "Defence:     " << enemyDefence << endl;
	cout << "Level:       " << enemyLevel << endl;
}

Enemy Enemy::generateEnemy(int level)
{
	const string types[] = { "Goblin", "Orc", "Bandit", "Troll" };
	int typeIndex = rand() % 4;

	string name = types[typeIndex];

	int baseHealth = 50 + ((rand() % level) + 10);
	int baseStrength = 3 + ((rand() % level) + 2);
	int baseDefence = 2 + ((rand() % level) + 1);

	int enemyLevel = max(1, level + (rand() % 3 - 1));

	int health = baseHealth + (enemyLevel - 1) * 5;
	int strength = baseStrength + (enemyLevel - 1) * 2;
	int defence = baseDefence + (enemyLevel - 1);

	return Enemy(name, health, defence, strength, enemyLevel);
}

Enemy Enemy::generateBoss(int level)
{
	const string bossAdjectives[] = { "Ancient", "Savage", "Unholy", "Wrathful", "Doombringer", "Infernal" };
	const string bossNames[] = { "Goblin", "Orc", "Bandit", "Troll" };

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
	this->enemyHealth = this->enemyHealth - damage;

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
