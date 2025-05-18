#ifndef QUEST_H
#define QUEST_H

#include <iostream>
#include <string>

using namespace std;

struct Quest {

    string description;
    string targetName;
    int targetCount;
    int progress = 0;
    int rewardXP;
    int rewardGold;

    bool isComplete() const;
};

#endif // QUEST_H