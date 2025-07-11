#include "SaveLoad.h"
#include "Quest.h"
#include "Mage.h"
#include "Map.h"
#include "Inventory.h"
#include "Equipment.h"

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
    void saveGame(const Character& player, const MapSnapshot& mapSnap, const std::string& filename)
    {
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

        const auto& abs = player.getAbilities();
        out << abs.size() << '\n';

        for (auto& a : abs)
        {
            out << a.name.length() << ' ' << a.name << '\n';
            out << a.description.length() << ' ' << a.description << '\n';
            out << a.requiredLevel << '\n';
        }

        const auto& inv = player.getInventory().getItems();
        out << inv.size() << '\n';

        for (auto& it : inv)
        {
            out << static_cast<int>(it.type) << ' ';

            out << it.name.length() << ' ' << it.name << ' ';
            out << it.description.length() << ' ' << it.description << ' ';
            out << it.bonusStat << '\n';
        }

        const auto& eq = player.getEquipment().getEquipped();
        out << eq.size() << '\n';

        for (auto& [slot, it] : eq)
        {
            out << static_cast<int>(slot) << ' ';
            out << static_cast<int>(it.type) << ' ';

            out << it.name.length() << ' ' << it.name << ' ';
            out << it.description.length() << ' ' << it.description << ' ';
            out << it.bonusStat << '\n';
        }

        // Write map dimensions and player position in one line: rows cols playerX playerY
        out << mapSnap.rows << ' ' << mapSnap.cols << ' ' << mapSnap.playerX << ' ' << mapSnap.playerY << '\n';

        // Write each row of the saved map as its own line
        for (auto& row : mapSnap.rowsData)
        {
            out << row << '\n';
        }
    }

    bool loadGame(Character& player, MapSnapshot& mapSnap, const string& filename)
    {
        ensureSaveDirExists();

        player.clearQuests();
        player.clearAbilities();

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

        size_t aCount;

        in >> aCount;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        for (size_t i = 0; i < aCount; ++i)
        {
            size_t len; string name, desc; int lvl;
            in >> len; in.ignore(1);

            name.resize(len); in.read(&name[0], len); in.ignore(1);
            in >> len; in.ignore(1);

            desc.resize(len); in.read(&desc[0], len); in.ignore(1);
            in >> lvl; in.ignore(1);

            player.addAbility({ name, desc, lvl });
        }

        size_t invCount;
        in >> invCount;

        for (size_t i = 0; i < invCount; i++)
        {
            int typeInt, bonus;
            size_t nlen, dlen;
            string name, desc;

            in >> typeInt >> nlen;
            in.ignore(1);
            name.resize(nlen);
            in.read(&name[0], nlen);
            in.ignore(1);

            in >> dlen;
            in.ignore(1);
            desc.resize(dlen);
            in.read(&desc[0], dlen);
            in.ignore(1);

            in >> bonus;
            in.ignore(1);

            Item it;
            it.type = static_cast<ItemType>(typeInt);
            it.name = move(name);
            it.description = move(desc);
            it.bonusStat = bonus;

            player.addItem(it);
        }

        size_t eqCount;
        in >> eqCount;

        for (size_t i = 0; i < eqCount; i++)
        {
            int slotInt, typeInt, bonus;
            size_t nlen, dlen;
            string name, desc;

            in >> slotInt >> typeInt >> nlen; in.ignore(1);
            name.resize(nlen);
            in.read(&name[0], nlen);
            in.ignore(1);

            in >> dlen; in.ignore(1);
            desc.resize(dlen);
            in.read(&desc[0], dlen);
            in.ignore(1);

            in >> bonus;
            in.ignore(1);

            Item it;
            it.type = static_cast<ItemType>(typeInt);
            it.name = move(name);
            it.description = move(desc);
            it.bonusStat = bonus;

            auto slot = static_cast<EquipSlot>(slotInt);
            player.getEquipment().equip(slot, it);
            player.applyItemBonus(it);
        }

        in >> mapSnap.rows >> mapSnap.cols >> mapSnap.playerX >> mapSnap.playerY;
        // Discard the trailing newline before reading row data
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        mapSnap.rowsData.resize(mapSnap.rows);

        for (int i = 0; i < mapSnap.rows; ++i)
        {
            getline(in, mapSnap.rowsData[i]);

            if (!mapSnap.rowsData[i].empty() && mapSnap.rowsData[i].back() == '\r')
            {
                mapSnap.rowsData[i].pop_back();
            }
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
