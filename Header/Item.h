#pragma once
#include <string>

using namespace std;

enum class ItemType {
	HealthPotion,
	ManaPotion,
	Sword,
	Shield,
	Wand,
	Cloak,
	Helmet,
	Chestplate,
	Leggings,
	Boots
};

struct Item {
	ItemType type;
	string name;
	string description;
	int bonusStat;
};