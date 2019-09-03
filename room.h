#ifndef ROOM_H
#define ROOM_H
#include <map>
#include <memory>
#include <list>
#include "wall.h"
#include "door.h"
namespace core {
namespace dungeon {
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
    int id() {return _id; }
    bool addWall(char direction, std::shared_ptr<Wall> wall)
    {
        if(!checkDirection(direction))
            return false;

        _walls[direction] = wall;
        return true;
    }
    bool addDoor(char direction, std::shared_ptr<Door> door)
    {
        if(!checkDirection(direction))
            return false;

        _doors[direction] = door;
        return true;
    }
	std::shared_ptr<dungeon::Door> getDoor(char direction)
	{
		if (!checkDirection(direction))
			return nullptr;
		if (_doors.count(direction) == 0)
			return nullptr;
		return _doors[direction];
	}
    bool setEntrance(char direction)
    {
        if(!checkDirection(direction))
            return false;

        _entranceOrExit[direction] = "entrance";
        return true;
    }
    bool setExit(char direction)
    {
        if(!checkDirection(direction))
            return false;

        _entranceOrExit[direction] = "exit";
        return true;
    }
	std::list<char> findDoorDirections()
	{
		std::list<char> directionList;
		for (auto& pair : _doors)
		{
			directionList.emplace_back(pair.first);
		}
		return directionList;
	}
	bool existEntranceOrExit()
	{
		return getEntranceDirection() != '\0' || getExitDirection() != '\0';
	}
    char getEntranceDirection()
    {
        for(auto& pair : _entranceOrExit)
        {
            if(pair.second == "entrance")
                return pair.first;
        }
        return '\0';
    }
    char getExitDirection()
    {
        for(auto& pair : _entranceOrExit)
        {
            if(pair.second == "exit")
                return pair.first;
        }
        return '\0';
    }
	bool checkDirection(char& direction)
	{
		if (direction >= 'a' && direction <= 'z')
			direction -= 'a' - 'A';
		return (direction == NORTH || direction == SOUTH || direction == WEST || direction == EAST);
	}
private:
    
    int _id;
    std::map<char, std::shared_ptr<Wall>> _walls; // the walls of this room
    std::map<char, std::shared_ptr<Door>> _doors;
    std::map<char, std::string> _entranceOrExit; // save the direction of entrance or exit in this room
};

} // namespace dungeon
} // namespace core


#endif // ROOM_H
