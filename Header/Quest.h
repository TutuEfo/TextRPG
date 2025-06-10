#pragma once
#ifndef QUEST_H
#define QUEST_H

#include <iostream>
#include <string>

using namespace std;

struct Quest {

    string description;
    string targetName;
    int targetCount = 0;
    int progress = 0;
    int rewardXP = 0;
    int rewardGold = 0;

    bool isComplete() const;
};

#endif // QUEST_H