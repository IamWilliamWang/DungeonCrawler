#ifndef BASICDUNGEON_H
#define BASICDUNGEON_H
#include "commondungeon.h"

namespace core {
namespace dungeon {

// TODO: define component classes spcific to the BasicDungeon type

/**
 * @brief TODO The BasicDungeon class
 */
class BasicDungeon : public Dungeon
{
public:
    BasicDungeon(){}
    std::shared_ptr<Room> getEntranceRoom()
    {
        for(auto &pair : _rooms)
        {
            if(pair.second->getEntranceDirection() != '\0')
                return pair.second;
        }
        return nullptr;
    }
	auto getNowRoom()
	{
		return _nowRoom;
	}
	void setNowRoom(std::shared_ptr<dungeon::Room> nowRoom)
	{
		_nowRoom = nowRoom;
	}
private:
	std::shared_ptr<dungeon::Room> _nowRoom;
};

/**
 * @brief TODO The RockChamber class
 */
class RockChamber
{
public:
    RockChamber(){}
};

/**
 * @brief TODO The QuartzChamber class
 */
class QuartzChamber
{
public:
    QuartzChamber(){}
};

/**
 * @brief TODO The BasicWall class
 */
class RockWall
{
public:
    RockWall(){}
};

} // namespace dungeon
} // namespace core

#endif // BASICDUNGEON_H
