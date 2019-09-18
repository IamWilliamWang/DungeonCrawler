#ifndef BASICDUNGEON_H
#define BASICDUNGEON_H
#include <memory>
#include <list>
#include "commondungeon.h"
namespace core {
namespace dungeon {

class Dungeon;
class Room; // predeclaration.
//class Chamber;

// TODO: define component classes spcific to the BasicDungeon type

/**
 * @brief TODO The BasicDungeon class
 */
class BasicDungeon : public Dungeon
{
public:
    /**
     * @brief BasicDungeon
     */
    BasicDungeon();

	/**
	 * @brief 
	 * @param nowRoom
	 */
	BasicDungeon(const BasicDungeon& oldDungeon);

    /**
     * @brief getEntranceRoom 获得牢笼的开始Room
     * @return
     */
    std::shared_ptr<Room> getEntranceRoom();

    /**
     * @brief getNowRoom 获得当前的Room
     */
    std::shared_ptr<Room> getNowRoom();

    /**
     * @brief setNowRoom 设置当前的Room
     * @param nowRoom
     */
    void setNowRoom(std::shared_ptr<Room> nowRoom);

    /**
     * @brief path 获得走过路径上第几个Room，index可正可负
     * @param index
     * @return
     */
    std::shared_ptr<Room> path(int index);

private:
	std::list<std::shared_ptr<Room>> _path;
	std::shared_ptr<Room> _nowRoom;
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
