#ifndef BASICDUNGEON_H
#define BASICDUNGEON_H
#include "dungeon.h"
#include "commondungeon.h"
namespace core {
namespace dungeon {

// TODO: define component classes spcific to the BasicDungeon type

/**
 * @brief The BasicDungeon class
 */
class BasicDungeon : public Dungeon
{
public:
    BasicDungeon();
private:
    std::string typeName = "BasicDungeon";
};

/**
 * @brief TODO The RockChamber class
 */
class RockChamber : public Chamber
{
public:
    /**
     * @brief RockChamber
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
     * @brief QuartzChamber
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
     * @brief RockWall
     */
	RockWall();
};

} // namespace dungeon
} // namespace core

#endif // BASICDUNGEON_H
