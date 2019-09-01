#ifndef ROOM_H
#define ROOM_H
#include <map>
#include <memory>
#include "wall.h"
#include "door.h"
namespace core {
namespace dungeon {

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
private:
    bool checkDirection(char& direction)
    {
        if(direction >= 'a' && direction <= 'z')
            direction -= 'a'-'A';
        return (direction == 'N' || direction == 'S' || direction == 'W' || direction == 'E');
    }
    int _id;
    std::map<char, std::shared_ptr<Wall>> _walls; // the walls of this room
    std::map<char, std::shared_ptr<Door>> _doors;
    std::map<char, std::string> _entranceOrExit; // save the direction of entrance or exit in this room
};

} // namespace dungeon
} // namespace core


#endif // ROOM_H
