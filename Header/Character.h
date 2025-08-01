#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <vector>
#include "Quest.h"
#include "Ability.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Equipment.h"

using namespace std;

class Character {
protected:
    string nickName;

    int health;
    int maxHealth;
    int strength;
    int defence;
    int critChance;

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

    vector<Ability> unlockedAbilities;
    int lastDamageTaken;
    bool damageReduction;

    int questCount;
    vector<Quest> activeQuests;

    Inventory inventory;
    Equipment equipment;
public:
    Character(const string& nickname);  // Constructor
    Character(const string& name, int hp, int str, int def, int critCh);

    void addGold(int amuntOfGold);

    void gainXP(int amount);
    virtual void levelUp();
    int getXPToLevelUp() const;

    bool abilities();
    virtual void unlockAbilitiesByLevel();
    void useAbility(int input, Enemy& target);
    void clearAbilities();
    void addAbility(const Ability& a);
    const vector<Ability>& getAbilities() const;

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
    void requestQuest();
    Quest generateRandomQuest(const string& name);
    int getQuestCount();

    string getNickName() const;
    int getHealth() const;
    int getStrength() const;
    int getDefence() const;
    int getCritChance() const;
    int getLevel() const;
    int getGold() const;
    int getXP() const;
    virtual string getClassName() const { return "Default"; }

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
    void setEscapeBattle(bool escape);
    void setStrength(int amount);
    void setDefence(int amount);
    void setHealth(int amount);
    void setCritChance(int amount);
    void setHealthPotions(int amount);
    void setStrengthPotions(int amount);
    void setDefencePotions(int amount);
    void setNickName(string name);
    void setLevel(int lvl);
    void setXP(int xp);
    void setGold(int amount);
    const vector<Quest>& getActiveQuests() const;
    void clearQuests();

    Inventory& getInventory();
    Equipment& getEquipment();
    const Inventory& getInventory() const;
    const Equipment& getEquipment() const;

    virtual void addItem(Item it);

    virtual void applyItemBonus(const Item& it);
    virtual void removeItemBonus(const Item& it);

    int getQuestProgress(const string& questID) const;
};

#endif // CHARACTER_H
