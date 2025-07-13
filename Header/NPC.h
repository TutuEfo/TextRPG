#pragma once
#include <string>
#include <vector>
#include "Quest.h"
#include "Character.h"

using namespace std;

class NPC {
private:
	string id;
	string name;
	int xCord;
	int yCord;
	vector<string> dialog;
	optional<Quest> assignedQuest;
public:
	NPC(string id, string name, int startX, int startY);
	
	void addDialogLine(const string& line);
	void setQuest(const Quest& q);
	void interact(Character& player);

	void moveRandomly(int width, int height);

	int  getX() const;
	int  getY() const;
	char getSymbol() const;
};