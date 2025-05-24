#include "SaveLoad.h"
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

namespace SaveLoad
{

    void saveGame(const Character& player, const std::string& filename) {

        ofstream out(filename, ios::trunc);

        if (!out)
        {
            throw runtime_error("Failed to open save file for writing");
        }

        out
            << player.getNickName() << '\n'
            << player.getHealth() << '\n'
            << player.getStrength() << '\n'
            << player.getDefence() << '\n'
            << player.getLevel() << '\n'
            << player.getXP() << '\n'
            << player.getGold() << '\n'
            << player.getHealthPotions() << '\n'
            << player.getStrengthPotions() << '\n'
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
        int level, xp, gold, health, strength, defence;
        int healthPotions, strengthPotions, defencePotions;

        if (!getline(in, name))
        {
            return false;
        }

        if (!(in >> health >> strength >> defence >> level >> xp >> gold >> healthPotions >> strengthPotions >> defencePotions))
        {
            return false;
        }

        player.setNickName(name);
        player.setHealth(health);
        player.setStrength(strength);
        player.setDefence(defence);
        player.setLevel(level);
        player.setXP(xp);
        player.setGold(gold);
        player.setHealthPotions(healthPotions);
        player.setStrengthPotions(strengthPotions);
        player.setDefencePotions(defencePotions);

        return true;
    }

} // namespace SaveLoad
