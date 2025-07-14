#pragma once
#include <vector>
#include <string>
#include "NPC.h"

using namespace std;

class Character;
class Enemy;
class Combat;

struct MapSnapshot
{
    int rows, cols;
    int playerX, playerY;

    vector<string> rowsData;
};

class Map{
private:
	vector<vector<char>> grid;
	int playerX;
	int playerY;
    vector<NPC> npcs;

    Character* player = nullptr;
public:
    Map(Character *player);

    void setPlayer(Character* p);

    void generateRandomMap(int x, int y);
    void display() const;
    void movePlayer(char direction);

    int getPlayerX() const;
    int getPlayerY() const;
    char getTile(int x, int y) const;
    void triggerTile(char tile);
    void shopMenu(Character *p);

    MapSnapshot makeSnapshot() const;
    void loadSnapshot(const MapSnapshot&);
    void addNPC(const NPC& n);
};