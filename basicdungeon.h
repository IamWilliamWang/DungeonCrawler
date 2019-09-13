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
    /**
     * @brief getEntranceRoom 获得牢笼的开始Room
     * @return
     */
    std::shared_ptr<Room> getEntranceRoom()
    {
        for(auto &pair : _rooms)
        {
            if(pair.second->getEntranceDirection() != '\0')
                return pair.second;
        }
        return nullptr;
    }
    /**
     * @brief getNowRoom 获得当前的Room
     */
	auto getNowRoom()
	{
		return _nowRoom;
	}
    /**
     * @brief setNowRoom 设置当前的Room
     * @param nowRoom
     */
	void setNowRoom(std::shared_ptr<dungeon::Room> nowRoom)
	{
		_nowRoom = nowRoom;
		_path.emplace_back(nowRoom);
	}
    /**
     * @brief path 获得走过路径上第几个Room，index可正可负
     * @param index
     * @return
     */
	std::shared_ptr<dungeon::Room> path(int index)
	{
		if (index < 0)
		{
			auto it = _path.rbegin();
			for (; index < -1 && it!=_path.rend(); index++)
				it++;
			if (it == _path.rend())
				return nullptr;
			return *it;
		}
		else
		{
			auto it = _path.begin();
			for (; index > 0 && it != _path.end(); index--)
				it++;
			if (it == _path.end())
				return nullptr;
			return *it;
        }
	}
private:
	std::list<std::shared_ptr<dungeon::Room>> _path;
	std::shared_ptr<dungeon::Room> _nowRoom;
};

/**
 * @brief TODO The RockChamber class
 */
class RockChamber : public Chamber
{
public:
    RockChamber(){}
};

/**
 * @brief TODO The QuartzChamber class
 */
class QuartzChamber : public Chamber
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
