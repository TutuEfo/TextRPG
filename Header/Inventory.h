#pragma once
#include <vector>
#include "Item.h"

class Inventory {
private:
	vector<Item> items;
	size_t capacity;
public:
	Inventory(size_t cap = 20) : capacity(cap) {}
	
	bool addItem(const Item& it)
	{
		if (items.size() >= capacity)
		{
			return false;
		}
		else
		{
			items.push_back(it);
			return true;
		}
	}

	bool removeItem(size_t index)
	{
		if (index >= items.size())
		{
			return false;
		}
		else
		{
			items.erase(items.begin() + index);
			return true;
		}
	}

	const vector<Item>& getItems() const
	{
		return items;
	}
};