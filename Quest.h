#ifndef QUEST_H
#define QUEST_H

#include <iostream>
#include <string>

using namespace std;

struct Quest {
private:
    string description;
    string targetName;
    int targetCount;
    int progress = 0;
    int rewardXP;
    int rewardGold;
public:
    bool isComplete() const;
    string getDescription();
    string getTargetName();
    int getTargetCount();
    int getProgress();
};

#endif // QUEST_H