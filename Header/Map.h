#pragma once
#include <vector>
#include <string>

using namespace std;

class Map{
private:
	vector<vector<char>> grid;
	int playerX;
	int playerY;
public:
    Map();

    void generateRandomMap(int x, int y);
    void display() const;
    void movePlayer(char direction);

    int getPlayerX() const;
    int getPlayerY() const;
    char getTile(int x, int y) const;
};