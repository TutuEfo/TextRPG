#include <iostream>
#include <string>
#include "Quest.h"

using namespace std;

bool Quest::isComplete() const
{
	return (progress >= targetCount);
}