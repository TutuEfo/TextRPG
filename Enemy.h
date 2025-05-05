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
	Enemy(string name, int health, int defence, int strength);
	void takeDamage(int damage);
	void displayStatus() const;
	bool isAlive() const;
};

#endif ENEMY_H