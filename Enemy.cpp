#include <iostream>
#include <string>
#include "Enemy.h"

using namespace std;

Enemy::Enemy(const string& name, int health, int defence, int strength) : enemyName(name), health(health), defence(defence), strength(strength) {}

string Enemy::getEnemyName()
{
	return enemyName;
}

void Enemy::displayStatus() const
{
	cout << "\n=== Enemy Stats ===\n";
	cout << "Name:     " << enemyName << endl;
	cout << "Health:   " << health << endl;
	cout << "Strength: " << strength << endl;
	cout << "Defence:  " << defence << endl;
}

bool Enemy::isAlive() const
{
	if (health > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Enemy::getEnemyHealth()
{
	return health;
}

int Enemy::getEnemyDefence()
{
	return defence;
}

int Enemy::getEnemyStrength()
{
	return strength;
}

void Enemy::takeDamage(int damage)
{
	this->health = this->health - damage;

	if (this->health < 0)
	{
		this->health = 0;
	}
}