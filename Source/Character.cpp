#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "Character.h"
#include "Quest.h"
#include "Console.h"
#include "UI.h"
#include "Ability.h"
#include "Enemy.h"

using namespace std;

static const std::string QUEST_TYPES[] = { "Goblin", "Orc", "Bandit", "Troll" };

Character::Character(const string& name) /* : nickName(name), health(0), strength(5), defence(1), level(1) */ {
	nickName = name;

	health = 100;
	strength = 10;
	defence = 7;
	critChance = 5;

	level = 1;
	xp = 0;
	xpToLevelUp = 100;

	gold = 0;

	maxHealth = 100 + ((level - 1) * 10);
	healthPotions = 3;
	strengthPotions = 2;
	defencePotions = 2;
	strengthPotionDuration = 0;
	defencePotionDuration = 0;
	strengthEffectActive = false;
	defenceEffectActive = false;

	escapeBattle = false;

	questCount = 0;
	activeQuests;

	lastDamageTaken = 0;
	damageReduction = false;
}

Character::Character(const string& name, int hp, int str, int def, int critCh)
{
	nickName = name;

	health = 100 + (10 * hp);
	strength = str;
	defence = def;
	critChance = critCh;

	level = 1;
	xp = 0;
	xpToLevelUp = 100;

	gold = 0;

	maxHealth = health + ((level - 1) * 10);
	healthPotions = 3;
	strengthPotions = 2;
	defencePotions = 2;
	strengthPotionDuration = 0;
	defencePotionDuration = 0;
	strengthEffectActive = false;
	defenceEffectActive = false;

	escapeBattle = false;

	questCount = 0;
	activeQuests;

	lastDamageTaken = 0;
	damageReduction = false;
}

void Character::displayCharacter() const
{
	coloredPrint(Color::Blue, "\n========== CHARACTER STATS ==========\n");
	cout << endl;

	cout << "Name: " << nickName << endl;

	cout << "Health: ";
	printBar(health, maxHealth, 25);
	cout << endl;

	cout << "XP:     ";
	printBar(xp, xpToLevelUp, 25);
	cout << endl;

	cout << endl;
	cout << "Level:         " << level << endl;
	cout << "Strength:      " << strength << endl;
	cout << "Crit Chance:   " << critChance << endl;
	cout << "Defence:       " << defence << endl;
	cout << "Gold:          " << gold << endl;
}

void Character::escapeFromBattle()
{
	int escape;

	escape = rand() % 4;

	if (escape == 1)
	{
		escapeBattle = true;
	}
	else
	{
		escapeBattle = false;
	}
}

int Character::attack()
{
	int damage = strength + (rand() % strength);

	return damage;
}

void Character::unlockAbilitiesByLevel()
{
	if (level == 5)
	{
		unlockedAbilities.push_back({ "Deadly Scatter", "Deals +10 bonus damage", 5 });
	}
	else if (level == 10)
	{
		unlockedAbilities.push_back({ "Vengeful Punishment", "Reflects damage from last turn", 10 });
	}
	else if (level == 15)
	{
		unlockedAbilities.push_back({ "Warrior's Surge", "Fully restores health", 15 });
	}
	else if (level == 20)
	{
		unlockedAbilities.push_back({ "Defensive Stance", "Negates all damage this turn", 20 });
	}
}

void Character::abilities()
{
	if (unlockedAbilities.empty())
	{
		cout << ">> No abilities unlocked yet." << endl;

		return;
	}

	coloredPrint(Color::Yellow, "\n=== Abilities ===\n");

	for (size_t i = 0; i < unlockedAbilities.size(); ++i)
	{
		cout << (i + 1) << ") " << unlockedAbilities[i].name << " - " << unlockedAbilities[i].description << endl;
	}
}

void Character::useAbility(int index, Enemy& target)
{
	const Ability& ab = unlockedAbilities[index];
	cout << ">> " << nickName << " used " << ab.name << "!\n";

	if (ab.name == "Deadly Scatter")
	{
		int damage = strength + 15;
		cout << ">> " << nickName << "uses Deadly Scatter ability and deals " << damage << " damage!\n";

		target.takeDamage(damage);
	}
	else if (ab.name == "Vengeful Punishment")
	{
		cout << ">> " << nickName << "uses Vengeful Punishment ability and reflects " << lastDamageTaken << " damage!\n";

		target.takeDamage(lastDamageTaken);
	}
	else if (ab.name == "Warrior's Surge")
	{
		health = maxHealth;
		cout << ">> Fully healed to " << maxHealth << " HP!\n";
	}
	else if (ab.name == "Defensive Stance")
	{
		damageReduction = true;
		cout << ">> All damage will be blocked this turn.\n";
	}
}

void Character::clearAbilities()
{
	unlockedAbilities.clear();
}

void Character::addAbility(const Ability& a)
{
	unlockedAbilities.push_back(a);
}

const vector<Ability>& Character::getAbilities() const
{
	return unlockedAbilities;
}

void Character::usePotion(int choice)
{
	int maxHealth = 100 + (10 * (level - 1));

	if (healthPotions > 0 && choice == 1)
	{
		health += 20;
		healthPotions--;

		if (health >= maxHealth)
		{
			health = maxHealth;
		}

		cout << ">> " << nickName << " used a health potion and recovered 20 HP!" << endl;
	}
	else if (strengthPotions > 0 && choice == 2)
	{
		strengthPotions--;

		strength = strength + 5;

		cout << ">> " << nickName << " used a strength potion and gain +5 strength for 3 rounds!" << endl;
	}
	else if (defencePotions > 0 && choice == 3)
	{
		defencePotions--;

		defence = defence + 3;

		cout << ">> " << nickName << " used a defence potion and gain +3 defence for 3 rounds!" << endl;
	}
	else
	{
		cout << ">> No potions left, buy some more from shop!" << endl;
	}
}

void Character::gainXP(int amount)
{
	xp = xp + amount;

	cout << ">> " << nickName << " gained " << amount << " XP!" << endl;

	if (xp >= xpToLevelUp)
	{
		xp = xp - xpToLevelUp;

		levelUp();
	}
}

void Character::levelUp()
{
	level++;

	health = maxHealth;

	xpToLevelUp = (level * 100);

	maxHealth = health + level * (10);

	health = maxHealth;

	int levelUpChoice1 = 0;
	int levelUpChoice2 = 0;

	coloredPrint(Color::Cyan, "\n========== Level Up Menu ==========\n");

	cout << "1) Strength (+2)" << endl;
	cout << "2) Defence (+2)" << endl;
	cout << "3) Crit Chance (+1)" << endl;
	cout << ">> Choose your upgrades (1 3): ";
	cin >> levelUpChoice1 >> levelUpChoice2;

	if (levelUpChoice1 == 1)
	{
		strength = strength + 2;

		cout << "# Strength is increased by 2!" << endl;
	}
	else if(levelUpChoice1 == 2)
	{
		defence = defence + 2;

		cout << "# Defence is increased by 2!" << endl;
	}
	else if (levelUpChoice1 == 3)
	{
		critChance = critChance + 1;

		cout << "# Crit chance is increased by 1!" << endl;
	}

	if (levelUpChoice2 == 1)
	{
		strength = strength + 2;

		cout << "# Strength is increased by 2!" << endl;
	}
	else if (levelUpChoice2 == 2)
	{
		defence = defence + 2;

		cout << "# Defence is increased by 2!" << endl;
	}
	else if (levelUpChoice2 == 3)
	{
		critChance = critChance + 1;

		cout << "# Crit chance is increased by 1!" << endl;
	}

	if (healthPotions == 0)
	{
		healthPotions = healthPotions + 3;
		cout << "# Health potions are refilled!" << endl;
	}

	cout << "# Max Health is increased by 10!" << endl;

	cout << ">> " << nickName << " leveled up to Level " << level << "!" << endl;

	unlockAbilitiesByLevel();
}

void Character::addGold(int amount)
{
	gold = gold + amount;

	cout << ">> " << nickName << " received " << amount << " gold!" << endl;
}

Inventory& Character::getInventory()
{
	return inventory;
}

Equipment& Character::getEquipment()
{
	return equipment;
}

void Character::applyItemBonus(const Item& it)
{
	switch(it.type)
	{
	case ItemType::Sword:
	{
		strength += it.bonusStat;

		break;
	}
	case ItemType::Shield:
	{
		defence += it.bonusStat;

		break;
	}
	case ItemType::Helmet:
	{
		defence += it.bonusStat;

		break;
	}
	case ItemType::Chestplate:
	{
		defence += it.bonusStat;

		break;
	}
	case ItemType::Leggings:
	{
		defence += it.bonusStat;

		break;
	}
	case ItemType::Boots:
	{
		defence += it.bonusStat;

		break;
	}
	default:
		break;
	}
}

void Character::removeItemBonus(const Item& it)
{
	switch (it.type)
	{
	case ItemType::Sword:
	{
		strength -= it.bonusStat;

		break;
	}
	case ItemType::Shield:
	{
		defence -= it.bonusStat;

		break;
	}
	case ItemType::Helmet:
	{
		defence -= it.bonusStat;

		break;
	}
	case ItemType::Chestplate:
	{
		defence -= it.bonusStat;

		break;
	}
	case ItemType::Leggings:
	{
		defence -= it.bonusStat;

		break;
	}
	case ItemType::Boots:
	{
		defence -= it.bonusStat;

		break;
	}
	default:
		break;
	}
}

void Character::addHealthPotion(int amount)
{
	healthPotions = healthPotions + amount;
}

void Character::addStrengthPotion(int amount)
{
	strengthPotions = strengthPotions + amount;
}

void Character::addDefencePotion(int amount)
{
	defencePotions = defencePotions + amount;
}

void Character::addQuest(const Quest& q)
{
	activeQuests.push_back(q);
}

void Character::checkQuestCompletion(const string& enemyName)
{
	// bind it by reference, deduce the type
	for (auto& q : activeQuests)
	{
		if (!q.isComplete() && q.targetName == enemyName)
		{
			q.progress++;

			cout << ">> Quest updated: " << q.description << " (" << q.progress << "/" << q.targetCount << ")\n";

			if (q.isComplete())
			{
				cout << ">> Quest complete! +" << q.rewardXP << " XP, +" << q.rewardGold << " gold\n";

				gainXP(q.rewardXP);
				addGold(q.rewardGold);
			
				questCount--;
			}
		}
	}
}

int Character::getQuestCount()
{
	return questCount;
}

void Character::generateRandomQuest()
{
	int typeIndex = rand() % (sizeof(QUEST_TYPES) / sizeof(*QUEST_TYPES));
	int count = rand() % 3 + 5;
	int randomXP = rand() % 26 + 25;
	int randomGold = rand() % 41 + 10;

	std::string name = QUEST_TYPES[typeIndex];
	Quest q
	{
		"Defeat " + std::to_string(count) + " " + name,
		name,
		count,
		0,
		randomXP,
		randomGold
	};

	activeQuests.push_back(q);

	std::cout << ">> New quest added: " << q.description << " (Reward: " << q.rewardXP << " XP, " << q.rewardGold << " gold)\n";
}

void Character::requestQuest()
{
	const int maxQuest = 3;

	if (activeQuests.size() >= maxQuest)
	{
		cout << ">> You already have " << maxQuest << " quests in progress!\n";
	}
	else
	{
		generateRandomQuest();

		questCount++;
	}
}

void Character::displayQuests() const
{
	coloredPrint(Color::Magenta, "\n=== Active Quests ===\n");
	cout << endl;

	int i = 1;

	for (const auto& q : activeQuests)
	{
		cout << to_string(i) + ": " << q.description << " (" << q.progress << "/" << q.targetCount << ")";

		if (q.isComplete())
		{
			coloredPrint(Color::Green, " [Completed]");
		}

		cout << "\n";

		i++;
	}

	cout << endl;
}

int Character::getStrengthPotionDuration() const
{
	return strengthPotionDuration;
}

int Character::getDefencePotionDuration() const
{ 
	return defencePotionDuration;
}

bool Character::isStrengthEffectActive() const 
{ 
	return strengthEffectActive; 
}

bool Character::isDefenceEffectActive() const
{ 
	return defenceEffectActive; 
}

void Character::takeDamage(int damage)
{
	if (damageReduction)
	{
		cout << ">> " << nickName << " blocked all damage with Defensive Stance!\n";
		damageReduction = false;
		return;
	}

	lastDamageTaken = damage;
	health = health - damage;

	if (health < 0) 
	{
		health = 0;
	}
}

void Character::clearQuests()
{
	activeQuests.clear();
}


// Getters
const vector<Quest>& Character::getActiveQuests() const
{
	return activeQuests;
}

int Character::getXPToLevelUp() const
{
	return xpToLevelUp;
}

int Character::getXP() const
{
	return xp;
}

string Character::getNickName() const
{
	return nickName;
}

int Character::getHealth() const
{
	return health;
}

int Character::getStrength() const
{
	return strength;
}

int Character::getDefence() const
{
	return defence;
}

int Character::getCritChance() const
{
	return critChance;
}

int Character::getLevel() const
{
	return level;
}

int Character::getHealthPotions() const
{
	return healthPotions;
}

int Character::getStrengthPotions() const
{
	return strengthPotions;
}

int Character::getDefencePotions() const
{
	return defencePotions;
}

int Character::getGold() const
{
	return gold;
}

bool Character::getEscapeBattle()
{
	return escapeBattle;
}


// Setters
void Character::setEscapeBattle(bool escape)
{
	escapeBattle = escape;
}

void Character::setStrength(int strength)
{
	this->strength = strength;
}

void Character::setDefence(int defence)
{
	this->defence = defence;
}\

void Character::setCritChance(int crit)
{
	critChance = critChance + crit;
}

void Character::setStrengthEffectActive(bool active)
{
	strengthEffectActive = active;
}

void Character::setDefenceEffectActive(bool active)
{
	defenceEffectActive = active;
}

void Character::setStrengthPotionDuration(int duration)
{
	strengthPotionDuration = duration;
}

void Character::setDefencePotionDuration(int duration)
{
	defencePotionDuration = duration;
}

void Character::setHealthPotions(int amount)
{
	healthPotions = amount;
}

void Character::setStrengthPotions(int amount)
{
	strengthPotions = amount;
}

void Character::setDefencePotions(int amount)
{
	defencePotions = amount;
}

void Character::setNickName(string name)
{
	nickName = name;
}

void Character::setLevel(int lvl)
{
	level = lvl;
}

void Character::setXP(int xp)
{
	this->xp = xp;
}

void Character::setGold(int amount)
{
	gold = amount;
}

void Character::setHealth(int amount)
{
	health = amount;
}