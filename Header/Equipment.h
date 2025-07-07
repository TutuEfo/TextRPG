#pragma once
#include "Item.h"
#include <optional>
#include <map>

using namespace std;

enum class EquipSlot {
	Weapon,
	Helmet,
	Chestplate,
	Leggings,
	Boots,
	Accessory
};

class Equipment {
private:
    std::map<EquipSlot, Item> equipped;
public:
    optional<Item> equip(EquipSlot slot, const Item& it)
    {
        auto old = equipped.count(slot) ? optional<Item>{equipped[slot]} : nullopt;
        equipped[slot] = it;

        return old;
    }

    optional<Item> unequip(EquipSlot slot)
    {
        if (!equipped.count(slot))
        {
            return nullopt;
        }

        auto old = equipped[slot];
        equipped.erase(slot);
        
        return old;
    }

    const map<EquipSlot, Item>& getEquipped() const
    {
        return equipped;
    }
};