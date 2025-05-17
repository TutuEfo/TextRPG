#include <iostream>
#include <string>
#include "Quest.h"

using namespace std;

bool Quest::isComplete() const
{
	return (progress > targetCount);
}

string Quest::getDescription()
{
	return description;
}

string Quest::getTargetName()
{
	return targetName;
}

int Quest::getTargetCount()
{
	return targetCount;
}

int Quest::getProgress()
{
	return progress;
}