#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>
#include "Item.h"

using namespace std;

class Enemy {
private:
	string enemyName;
	int enemyHealth;
	int enemyMaxHealth;
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
	Item getItemReward();
	Item getItemRewardBoss();
};

#endif ENEMY_H