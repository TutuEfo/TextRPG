#include "SaveLoad.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace SaveLoad
{

    void saveGame(const Character& player, const std::string& filename) {
        
        ofstream out(filename, ios::trunc);

        if (!out)
        {
            throw std::runtime_error("Failed to open save file for writing");
        }

        out << player.getNickName() << '\n'
            << player.getLevel() << '\n'
            << player.getXP() << '\n'
            << player.getGold() << '\n'
            << player.getHealthPotions() << '\n';
            << player.getStrengthPotions() << '\n';
            << player.getDefencePotions() << '\n';

    }

    bool loadGame(Character& player, const std::string& filename)
    {
        ifstream in(filename);
        if (!in)
        {
            return false;
        }

        string name;
        int level, xp, gold, healthPotions, strengthPotions, defencePotions;

        getline(in, name);
        in >> level >> xp >> gold >> healthPotions >> strengthPotions, defencePotions;

        in.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!in)
        {
            return false;
        }

        player.setNickName(name);
        player.setLevel(level);
        player.setXP(xp);
        player.setGold(gold);
        player.setHealthPotions(healthPotions);
        player.strengthPotions(strengthPotions);
        player.setDefencePotions(defencePotions);

        return true;
    }

}