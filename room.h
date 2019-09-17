#ifndef ROOM_H
#define ROOM_H
#include <map>
#include <memory>
#include <list>
#include <random>
#include <ctime>
#include <vector>
#include "wall.h"
#include "door.h"
#include "weapons.h"
#include "creatures.h"

namespace core {
namespace dungeon {

class Wall;
class Door; //predeclaration

#define NORTH 'N'
#define SOUTH 'S'
#define WEST 'W'
#define EAST 'E'
/**
 * @brief TODO The Room class
 */
class Room
{
public:
    Room(int id) : _id(id){}

	/**
	* @brief id Returns the unique integer id of the Room.
	* @return the unique id
	*/
	int id() { return _id; }

    /**
     * @brief addWall 给Room的某个方向增加一堵墙
     * @param direction
     * @param wall
     * @return
     */
	bool addWall(char direction, std::shared_ptr<Wall> wall = std::make_shared<Wall>())
    {
        if(!checkDirectionVaild(direction))
            return false;

        _walls[direction] = wall;
        return true;
    }

    /**
     * @brief addDoor 给Room的某个方向增加一扇门
     * @param direction
     * @param door
     * @return
     */
    bool addDoor(char direction, std::shared_ptr<Door> door)
    {
        if(!checkDirectionVaild(direction))
            return false;

        _doors[direction] = door;
        return true;
    }

    /**
     * @brief getDoor 获得Room特定位置上的门
     * @param direction
     * @return
     */
	std::shared_ptr<dungeon::Door> getDoor(char direction)
	{
		if (!checkDirectionVaild(direction))
			return nullptr;
		if (_doors.count(direction) == 0)
			return nullptr;
		return _doors[direction];
	}
    
    /**
     * @brief findDoorDirections 找门所在的方向，返回char list
     * @return
     */
	std::list<char> findDoorDirections()
	{
		std::list<char> directionList;
		for (auto& pair : _doors)
		{
			directionList.emplace_back(pair.first);
		}
		return directionList;
	}

	/**
	 * @brief getDoorDirections findDoorDirections便捷函数，开发结束时会删除
	 * @return
	 */
	auto getDoorDirections()
	{
		return findDoorDirections();
	}

    /**
     * @brief existEntranceOrExit 如果存在入口或者出口
     * @return
     */
	bool existEntranceOrExit()
	{
		return getEntranceDirection() != '\0' || getExitDirection() != '\0';
	}

	void addEntranceOrExit(char direction, bool addEntrance)
	{
        if (addEntrance)
			this->setEntrance(direction);
		else
			this->setExit(direction);
	}

    /**
     * @brief getEntranceDirection 获得入口所在的方向
     * @return
     */
    char getEntranceDirection()
    {
        for(auto& pair : _entranceOrExit)
        {
            if(pair.second == "entrance")
                return pair.first;
        }
        return '\0';
    }
    /**
     * @brief getExitDirection 获得出口所在的方向
     * @return
     */
    char getExitDirection()
    {
        for(auto& pair : _entranceOrExit)
        {
            if(pair.second == "exit")
                return pair.first;
        }
        return '\0';
    }
    /**
     * @brief checkDirection 检查方向char是否合法
     * @param direction
     * @return
     */
	bool checkDirectionVaild(char& direction)
	{
		if (direction >= 'a' && direction <= 'z')
			direction -= 'a' - 'A';
		return (direction == NORTH || direction == SOUTH || direction == WEST || direction == EAST);
	}
    /**
     * @brief createCreature 使用可能的生物列表随机创建生物
     * @param possibleCreatures
     * @return
     */
	bool createCreature(std::vector<std::shared_ptr<core::creatures::Creature>> possibleCreatures)
	{
        _creature = possibleCreatures.at(Game::randomIntBetweenEx(0, possibleCreatures.size()));
		return true;
	}
	/*bool createWeapon(std::vector<std::shared_ptr<core::weapons::Weapon>> possibleWeapons)
	{
		std::default_random_engine randomEngine(static_cast<unsigned>(time(nullptr)));
		std::uniform_int_distribution<unsigned> rand(0, possibleWeapons.size() - 1);
		_weapon = possibleWeapons.at(rand(randomEngine));
		_creature->setWeapon(_weapon);
		return true;
	}*/
	auto getCreature()
	{
		return _creature;
	}
	void setCreature(std::shared_ptr<core::creatures::Creature> creature)
	{
		_creature = creature;
	}
	auto getWeapon()
	{
		if (_creature == nullptr) // weapon only
			return _weapon;
		else return _creature->getWeapon(); // creature takes a weapon
	}
	void setWeapon(std::shared_ptr<core::weapons::Weapon> weapon)
	{
		_weapon = weapon;
	}
private:
	/**
	 * @brief setEntrance 设置Room的特定方向为牢笼入口
	 * @param direction
	 * @return
	 */
	bool setEntrance(char direction)
	{
		if (!checkDirectionVaild(direction))
			return false;

		_entranceOrExit[direction] = "entrance";
		return true;
	}

	/**
	 * @brief setExit 设置Room的特定方向为牢笼出口
	 * @param direction
	 * @return
	 */
	bool setExit(char direction)
	{
		if (!checkDirectionVaild(direction))
			return false;

		_entranceOrExit[direction] = "exit";
		return true;
	}

    int _id;
    std::map<char, std::shared_ptr<Wall>> _walls; // the walls of this room
    std::map<char, std::shared_ptr<Door>> _doors;
    std::map<char, std::string> _entranceOrExit; // save the direction of entrance or exit in this room
	std::shared_ptr<core::creatures::Creature> _creature; 
    std::shared_ptr<core::weapons::Weapon> _weapon;
};

} // namespace dungeon
} // namespace core


#endif // ROOM_H
