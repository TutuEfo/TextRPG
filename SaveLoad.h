#ifndef SAVELOAD_H
#define SAVELOAD_H

#include <string>
#include "Character.h"

using namespace std;

namespace SaveLoad {

    void saveGame(const Character& player, const std::string& filename);
    bool loadGame(Character& player, const std::string& filename);
}

#endif SAVELOAD_H