#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>

using namespace std;

class Enemy {
private:
	string enemyName;
	int health;
	int defence;
	int strength;
public:
	Enemy(const string& name, int health, int defence, int strength);
	string getEnemyName();
	int getEnemyHealth();
	int getEnemyDefence();
	int getEnemyStrength();
	void takeDamage(int damage);
	void displayStatus() const;
	bool isAlive() const;
};

#endif ENEMY_H