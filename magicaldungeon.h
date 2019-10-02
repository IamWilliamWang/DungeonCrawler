#ifndef MAGICALDUNGEON_H
#define MAGICALDUNGEON_H
#include "commondungeon.h"
#include "dungeon.h"
namespace core {
namespace dungeon {

// TODO: define component classes spcific to the MagicalDungeon type
class EnchantedLibrary;

/**
 * @brief The MagicalDungeon class represents magical dungeon
 */
class MagicalDungeon : public Dungeon
{
public:
    /**
     * @brief MagicalDungeon default constructor of magical dungeon
     */
    MagicalDungeon();
private:

};

/**
 * @brief The EnchantedLibrary class represents enchanted library
 */
class EnchantedLibrary
{
public:
    /**
     * @brief EnchantedLibrary default constructor
     */
    EnchantedLibrary();
};

/**
 * @brief The AlchemistsLaboratory class represents alchemists laboratory
 */
class AlchemistsLaboratory
{
public:
    /**
     * @brief AlchemistsLaboratory default constructor
     */
    AlchemistsLaboratory();
};

/**
 * @brief The MagicWall class represents magic wall
 */
class MagicWall
{
public:
    /**
     * @brief MagicWall default constructor
     */
    MagicWall();
};

} // namespace dungeon
} // namespace core

#endif // MAGICALDUNGEON_H
