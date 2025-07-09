#pragma once
#ifndef QUEST_H
#define QUEST_H

#include <iostream>
#include <string>
#include "Item.h"

using namespace std;

enum class QuestStatus {NotStarted, InProgress, Completed};
enum class QuestType { Main, Side };

struct Quest {

    string id;
    QuestStatus status;
    QuestType type;

    string giveID;
    string description;
    string targetName;

    int targetCount = 0;
    int progress = 0;
    int rewardXP = 0;
    int rewardGold = 0;

    // In progress: vector<Item> rewardItems;

    void start();
    void updateProgress(const string& name);
    bool isComplete() const;
};

#endif // QUEST_H