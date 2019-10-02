#ifndef DUNGEONBUILDER_H
#define DUNGEONBUILDER_H
#include <fstream>
#include <stdlib.h>
#include "dungeon.h"
#include "basicdungeon.h"
#include "magicaldungeon.h"
#include "csvfile.h"
namespace core {
namespace dungeon {

class Dungeon;

/**
 * @brief The DungeonBuilder virtual class represents the dungeon builder, need subclasses to implement.
 */
class DungeonBuilder
{
public:
    /**
     * @brief buildDungeon Builds a dungeon
     * @return a new dungeon
     */
    virtual std::shared_ptr<Dungeon> buildDungeon() = 0;
    /**
     * @brief clone Clones a dungeon
     * @param dungeon old dungeon
     * @return a new cloned dungeon
     */
    virtual std::shared_ptr<Dungeon> clone(std::shared_ptr<Dungeon> dungeon) = 0;
    virtual ~DungeonBuilder() = default;
};

/**
 * @brief The BasicDungeonBuilder class represents basic dungeon builder
 */
class BasicDungeonBuilder : public DungeonBuilder
{
public:
    /**
     * @brief buildDungeon Builds basic dungeon
     * @return a new basic dungeon
     */
    std::shared_ptr<Dungeon> buildDungeon();

    /**
     * @brief clone Clones a basic dungeon
     * @param dungeon old basic dungeon
     * @return a new cloned basic dungeon
     */
    std::shared_ptr<Dungeon> clone(std::shared_ptr<Dungeon> dungeon);

private:
    /**
     * @brief parseInt Converts string to int
     * @param intStr A string representing an integer
     * @return parsed int
     */
    int parseInt(std::string intStr);

    /**
     * @brief loadCreatures Loads all basic dungeon creatures
     * @return
     */
    bool loadCreatures();

    /**
     * @brief loadWeapons Loads all basic dungeon weapons
     * @return
     */
    bool loadWeapons();

    std::vector<std::shared_ptr<core::creatures::Creature>> _creatureList; // all basic dungeon creatures' list
    std::vector<std::shared_ptr<core::weapons::Weapon>> _weaponList; // all basic dungeon weapons' list
};

/**
 * @brief The MagicalDungeonBuilder class represents magical dungeon builder
 */
class MagicalDungeonBuilder : public DungeonBuilder
{
public:
    /**
     * @brief buildDungeon Builds magical dungeon
     * @return a new magical dungeon
     */
    std::shared_ptr<Dungeon> buildDungeon();

    /**
     * @brief clone Clones a magical dungeon
     * @param dungeon old magical dungeon
     * @return a new cloned magical dungeon
     */
    std::shared_ptr<Dungeon> clone(std::shared_ptr<Dungeon> dungeon);

private:
    /**
     * @brief parseInt Converts string to int
     * @param intStr a string representing an integer
     * @return parsed int
     */
    int parseInt(std::string intStr);

    /**
     * @brief loadCreatures Loads all magical dungeon creatures
     * @return
     */
    bool loadCreatures();

    /**
     * @brief loadCreatures Loads all magical dungeon weapons
     * @return
     */
    bool loadWeapons();

    std::vector<std::shared_ptr<core::creatures::Creature>> _creatureList; // all magical dungeon creatures' list
    std::vector<std::shared_ptr<core::weapons::Weapon>> _weaponList; // all magical dungeon weapons' list
};
}
}
#endif // DUNGEONBUILDER_H
