#include "SaveLoad.h"
#include "Quest.h"
#include "Mage.h"

#include <fstream>
#include <filesystem>
#include <iostream>
#include <limits>
#include <chrono>
#include <iomanip>
#include <optional>

using namespace std;

namespace fs = std::filesystem;

static const string SAVE_DIR = "saves/";

namespace SaveLoad
{
    void saveGame(const Character& player, const std::string& filename) {
        ensureSaveDirExists();

        // Normalize slot name to always have .sav
        filesystem::path slot(filename);

        if (slot.extension().empty())
        {
            slot += ".sav";
        }

        std::ofstream out(SAVE_DIR + slot.string(), std::ios::trunc);

        if (!out)
        {
            throw std::runtime_error("Failed to open save file for writing");
        }

        // Get the current point in time from the system clock
        auto now = chrono::system_clock::now();
        time_t t = chrono::system_clock::to_time_t(now);

        // Convert safely into a std::tm
        std::tm tm;
        #if defined(_MSC_VER)
        // MSVC’s “secure” localtime
        localtime_s(&tm, &t);
        #else
        // POSIX localtime is not thread-safe on its own, so copy immediately
        std::tm* tmPtr = std::localtime(&t);
        if (!tmPtr) throw std::runtime_error("localtime failed");
        tm = *tmPtr;
        #endif

        // Format the time as "Year-Month-Day Hour:Minute:Second" in local time
        out << put_time(&tm, "%Y-%m-%d %H:%M:%S") << '\n';

        // player name
        out << player.getNickName() << '\n';

        // player class
        out << player.getClassName() << '\n';

        // Player level, Health, Gold
        out << player.getLevel() << ' '
            << player.getHealth() << ' '
            << player.getGold() << '\n';

        // blank line to separate header from body
        out << '\n';

        out << player.getHealth() << '\n'
            << player.getStrength() << '\n'
            << player.getDefence() << '\n'
            << player.getLevel() << '\n'
            << player.getXP() << '\n'
            << player.getGold() << '\n'
            << player.getHealthPotions() << '\n'
            << player.getStrengthPotions() << '\n'
            << player.getDefencePotions() << '\n';

        if (player.getClassName() == "Mage")
        {
            const Mage& m = static_cast<const Mage&>(player);
            out << m.getMana() << '\n';
            out << m.getManaPotions() << '\n';
        }

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

    bool loadGame(Character& player, const string& filename)
    {
        ensureSaveDirExists();

        player.clearQuests();

        // Normalize slot name
        string slot = filename;
        if (filesystem::path(slot).extension().empty()) {
            slot += ".sav";
        }

        ifstream in(SAVE_DIR + slot);

        if (!in)
        {
            return false;
        }

        string line;

        while (getline(in, line))
        {
            if (line.empty()) break;
        }

        int health, strength, defence;
        int level, xp, gold;
        int healthPotions, strengthPotions, defencePotions;

        if (!(in
            >> health
            >> strength
            >> defence
            >> level
            >> xp
            >> gold
            >> healthPotions
            >> strengthPotions
            >> defencePotions))
        {
            return false;
        }

        player.setHealth(health);
        player.setStrength(strength);
        player.setDefence(defence);
        player.setLevel(level);
        player.setXP(xp);
        player.setGold(gold);
        player.setHealthPotions(healthPotions);
        player.setStrengthPotions(strengthPotions);
        player.setDefencePotions(defencePotions);

        if (player.getClassName() == "Mage")
        {
            Mage* m = static_cast<Mage*>(&player);

            int savedMana, savedManaPotions;
            in >> savedMana >> savedManaPotions;

            m->setMana(savedMana);
            m->setManaPotions(savedManaPotions);
        }

        // Read the number of quests that were saved; if this fails, throw an error
        size_t questCount;

        if (!(in >> questCount))
        {
            throw std::runtime_error("Failed to read quest count");
        }

        // Skip the newline after the questCount
        in.ignore(numeric_limits<std::streamsize>::max(), '\n');

        for (size_t i = 0; i < questCount; ++i)
        {
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
            in.ignore(std::numeric_limits<streamsize>::max(), '\n');

            // Add quest to the back of the list.
            player.addQuest(q);
        }

        if (questCount > 0)
        {
            player.setHasQuests(true);
        }

        return true;
    }

    bool deleteSave(const string& filename)
    {
        ensureSaveDirExists();

        string fullPath = SAVE_DIR + filename;

        // variable that the non-throwing overload of fs::remove, ec.meesage() / ec.value()
        error_code ec;
        bool removed = fs::remove(fullPath, ec);

        return removed;
    }

    // Either contains a value or it is empty
    optional<SaveMetadata> readMetadata(const string& filename)
    {
        ensureSaveDirExists();

        ifstream in(SAVE_DIR + filename);
        if (!in)
        {
            return nullopt;
        }

        SaveMetadata md;

        if (!getline(in, md.timestamp) || md.timestamp.empty())
        {
            return nullopt;
        }

        if (!getline(in, md.nickName) || md.nickName.empty())
        {
            return nullopt;
        }

        if (!getline(in, md.className) || md.className.empty())
        {
            return nullopt;
        }

        if (!(in >> md.level >> md.health >> md.gold))
        {
            return nullopt;
        }

        return md;
    }

    vector<string> listSaveFiles()
    {
        ensureSaveDirExists();

        vector<string> files;

        for (auto& p : fs::directory_iterator(SAVE_DIR))
        {
            if (p.path().extension() == ".sav" || p.path().extension() == ".txt")
            {
                // Extracting the file nam only, from the path and extensions.
                files.push_back(p.path().filename().string());
            }

        }
        return files;
    }

    void ensureSaveDirExists()
    {
        if (!fs::exists(SAVE_DIR))
        {
            fs::create_directory(SAVE_DIR);
        }
    }

} // namespace SaveLoad
