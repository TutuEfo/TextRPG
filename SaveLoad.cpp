#include "SaveLoad.h"
#include "Quest.h"
#include <fstream>
#include <iostream>
#include <limits>

using namespace std;

namespace SaveLoad
{

    void saveGame(const Character& player, const string& filename) {

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

        // Write how many quests we have so that the loader knows how many to read back
        const auto& quests = player.getActiveQuests();

        out << quests.size() << '\n';

        for (const Quest& q : quests)
        {
            out << q.description.length() << ' ' << q.description << '\n';
            out << q.targetName.length() << ' ' << q.targetName << '\n';
            out << q.targetCount << '\n';
            out << q.progress << '\n';
            out << q.rewardXP << '\n';
            out << q.rewardGold << '\n';
        }
    }

    bool loadGame(Character& player, const std::string& filename)
    {
        player.clearQuests();

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

        
        // Read the number of quests that were saved; if this fails, throw an error
        size_t questCount;
        if (!(in >> questCount))
        {
            throw runtime_error("Failed to read quest count");
        }
            
        // Skip the newline after the questCount
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        for (size_t i = 0; i < questCount; ++i) {
            Quest q;

            size_t len;
            in >> len;

            // Consume the space
            in.get();

            // Resize the string buffer to hold exactly len characters
            q.description.resize(len);

            // Read exactly len characters into the description
            in.read(&q.description[0], len);

            // Consume the newline
            in.get();

            in >> len;

            // Consume the space
            in.get();

            q.targetName.resize(len);

            in.read(&q.targetName[0], len);

            // Consume the newline
            in.get();

            in >> q.targetCount
                >> q.progress
                >> q.rewardXP
                >> q.rewardGold;


            // Skip to the next line before the next quest
            in.ignore(numeric_limits<streamsize>::max(), '\n');

            // Add quest to the back of the list.
            player.addQuest(q);
        }

        if (questCount > 0) player.setHasQuests(true);

        return true;
    }

} // namespace SaveLoad
