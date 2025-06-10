#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>

using namespace std;

class Enemy {
private:
	string enemyName;
	int enemyHealth;
	int enemyDefence;
	int enemyStrength;
	int enemyLevel;
public:
	Enemy();
	Enemy(const string& name, int health, int defence, int strength, int level);
	static Enemy generateEnemy(int level);
	static Enemy generateBoss(int level);
	string getEnemyName();
	int getEnemyHealth();
	int getEnemyDefence();
	int getEnemyStrength();
	int getEnemyLevel();
	int getXPReward();
	int getGoldReward() const;
	int getGoldRewardBoss() const;
	int getXPRewardBoss();
	int attackCharacter();
	void takeDamage(int damage);
	void displayStatus() const;
	bool isAlive() const;
};

#endif ENEMY_H