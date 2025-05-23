#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <vector>
#include "Quest.h"

using namespace std;

class Character {
private:
    string nickName;

    int health;
    int strength;
    int defence;

    int xp;
    int xpToLevelUp;
    int level;

    int healthPotions;
    int strengthPotions;
    int defencePotions;
    int strengthPotionDuration;
    int defencePotionDuration;
    bool strengthEffectActive;
    bool defenceEffectActive;

    int gold;

    bool escapeBattle;

    vector<Quest> activeQuests;
    bool hasQuests;
public:
    Character(const string& nickname);  // Constructor

    void addGold(int amuntOfGold);

    void gainXP(int amount);
    void levelUp();
    int getXPToLevelUp() const;

    void usePotion(int choice);
    void addHealthPotion(int amount);
    void addStrengthPotion(int amount);
    void addDefencePotion(int amount);

    void takeDamage(int damage);
    int attack();
    
    virtual void displayCharacter() const;
    
    void escapeFromBattle();

    void addQuest(const Quest& q);
    void checkQuestCompletion(const string& enemyName);
    void displayQuests() const;

    string getNickName();
    int getHealth();
    int getStrength();
    int getDefence();
    int getLevel();
    int getGold();
    int getXP() const;

    int getHealthPotions() const;
    int getStrengthPotions() const;
    int getDefencePotions() const;

    int getStrengthPotionDuration() const;
    void setStrengthPotionDuration(int duration);
    int getDefencePotionDuration() const;
    void setDefencePotionDuration(int duration);

    bool isStrengthEffectActive() const;
    void setStrengthEffectActive(bool active);
    bool isDefenceEffectActive() const;
    void setDefenceEffectActive(bool active);

    bool getEscapeBattle();
    bool getHasQuests();
    void setHasQuests(bool hasQuest);
    void setEscapeBattle(bool escape);
    void setStrength(int amount);
    void setDefence(int amount);
    void setHealthPotions(int amount);
    void setStrengthPotions(int amount);
    void setDefencePotions(int amount);
    void setNickName(string name);
    void setLevel(int lvl);
    void setXP(int xp);
    void setGold(int amount);
    const vector<Quest>& getActiveQuests() const;
};

#endif // CHARACTER_H
