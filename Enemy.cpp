#include <iostream>
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