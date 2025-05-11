#include <iostream>
#include <cstdlib>
#include <string>
#include "Enemy.h"

using namespace std;

Enemy::Enemy(const string& name, int health, int defence, int strength, int level)
{
	enemyName = name;
	enemyLevel = max(1, level + (rand() % 3 - 1));
	enemyHealth = health + (level - 1) * 10;
	enemyDefence = defence + (level - 1) * 1;
	enemyStrength = strength + (level - 1) * 2;
}

Enemy Enemy::generateEnemy(int level)
{
	const string types[] = { "Goblin", "Orc", "Bandit", "Troll" };
	int typeIndex = rand() % 4;

	string name = types[typeIndex];

	int baseHealth = 50 + (rand() % 15 + 1);
	int baseStrength = 5 + (rand() % 3 + 1);
	int baseDefence = 2 + (rand() % 3 + 1);

	int enemyLevel = max(1, level + (rand() % 3 - 1));

	int health = baseHealth + (enemyLevel - 1) * 10;
	int strength = baseStrength + (enemyLevel - 1) * 2;
	int defence = baseDefence + (enemyLevel - 1) * 1;

	return Enemy(name, health, defence, strength, enemyLevel);
}

string Enemy::getEnemyName()
{
	return enemyName;
}

void Enemy::displayStatus() const
{
	cout << "\n=== Enemy Stats ===\n";
	cout << "Name:     " << enemyName << endl;
	cout << "Health:   " << enemyHealth << endl;
	cout << "Strength: " << enemyStrength << endl;
	cout << "Defence:  " << enemyDefence << endl;
	cout << "Level:    " << enemyLevel << endl;
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

int Enemy::getXPReward()
{
	return (10 + ((rand() % 10) + 1));
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

void Enemy::takeDamage(int damage)
{
	this->enemyHealth = this->enemyHealth - damage;

	if (this->enemyHealth < 0)
	{
		this->enemyHealth = 0;
	}
}