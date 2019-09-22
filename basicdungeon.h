#ifndef BASICDUNGEON_H
#define BASICDUNGEON_H
#include "dungeon.h"
#include "commondungeon.h"
namespace core {
namespace dungeon {

// TODO: define component classes spcific to the BasicDungeon type

/**
 * @brief The BasicDungeon class represents the basic dungeon
 */
class BasicDungeon : public Dungeon
{
public:
    /**
     * @brief BasicDungeon default constructor
     */
    BasicDungeon();
private:
};

/**
 * @brief The RockChamber class represents the rock chamber
 */
class RockChamber : public Chamber
{
public:
    /**
     * @brief RockChamber default constructor
     */
	RockChamber();
};

/**
 * @brief TODO The QuartzChamber class
 */
class QuartzChamber : public Chamber
{
public:
    /**
     * @brief QuartzChamber default constructor
     */
	QuartzChamber();
};

/**
 * @brief TODO The BasicWall class
 */
class RockWall
{
public:
    /**
     * @brief RockWall default constructor
     */
	RockWall();
};

} // namespace dungeon
} // namespace core

#endif // BASICDUNGEON_H
