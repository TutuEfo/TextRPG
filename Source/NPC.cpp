#include "NPC.h"
#include <iostream>
#include <cstdlib>

using namespace std;

NPC::NPC(string ID, string npcName, int startX, int startY) : id(ID), name(npcName), xCord(startX), yCord(startY) {}

void NPC::addDialogLine(const string& line)
{
    dialog.push_back(line);
}

void NPC::setQuest(const Quest& q)
{
    assignedQuest = q;
}

void NPC::interact(Character& player)
{

    for (auto& line : dialog)
    {
        cout << name << ": " << line << "\n";
    }

    if (assignedQuest && assignedQuest->status == QuestStatus::NotStarted)
    {
        player.addQuest(*assignedQuest);
        assignedQuest->start();
        cout << "> You have new quest: " << assignedQuest->description << "\n";
    }
    else if (assignedQuest && !assignedQuest->isComplete())
    {
        cout << "> Quest in progress: " << player.getQuestProgress(assignedQuest->id) << " / " << assignedQuest->targetCount << "\n";
    }
    else if (assignedQuest && assignedQuest->isComplete())
    {
        player.gainXP(assignedQuest->rewardXP);
        player.addGold(assignedQuest->rewardGold);
        cout << "> Quest complete! You earned " << assignedQuest->rewardXP << " XP and " << assignedQuest->rewardGold << " gold.\n";
        assignedQuest->status = QuestStatus::Completed;
    }
}

void NPC::moveRandomly(int width, int height)
{
    int rx = (rand() % 3) - 1;
    int ry = (rand() % 3) - 1;
    xCord = (xCord + rx);
    yCord = (yCord + ry);
}

int NPC::getX() const
{
    return xCord;
}

int NPC::getY() const
{
    return yCord;
}

char NPC::getSymbol() const
{
    return 'N';
}