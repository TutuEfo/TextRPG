#include <iostream>
#include <string>
#include "Quest.h"

using namespace std;

bool Quest::isComplete() const
{
	return status == QuestStatus::Completed;
}

void Quest::start()
{
	status = QuestStatus::InProgress;
	progress = 0;
}

void Quest::updateProgress(const string& name)
{
	if (status != QuestStatus::InProgress)
	{
		return;
	}

	if (name == targetName)
	{
		progress++;

		if (progress >= targetCount)
		{
			status = QuestStatus::Completed;
		}
	}
}