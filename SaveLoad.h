#ifndef SAVELOAD_H
#define SAVELOAD_H

#include "Character.h"

#include <string>
#include <optional>
#include <vector>

struct SaveMetadata {
    std::string timestamp;
    std::string className;
    std::string nickName;
    int level;
    int health;
    int gold;
};

namespace SaveLoad {

    void saveGame(const Character& player, const std::string& filename);
    bool loadGame(Character& player, const std::string& filename);
    bool deleteSave(const std::string& filename);
    std::vector<std::string> listSaveFiles();
    std::optional<SaveMetadata> readMetadata(const std::string& filename);
    void ensureSaveDirExists();
}

#endif SAVELOAD_H