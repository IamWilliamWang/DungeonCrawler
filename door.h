#ifndef DOOR_H
#define DOOR_H
#include <memory>
#include "room.h"

namespace core {
namespace dungeon {

class Room; //predeclaration

/**
 * @brief TODO The Door class
 */
class Door
{
public:
    Door(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2)
    {
        _room1 = room1;
        _room2 = room2;
    }
    /**
     * @brief getNeighbourRoom 获得邻居Room
     * @param thisRoom
     * @return
     */
	std::shared_ptr<Room> getNeighbourRoom(std::shared_ptr<Room> thisRoom)
	{
		if (thisRoom == _room1)
			return _room2;
		else return _room1;
	}
private:
	std::shared_ptr<Room> _room1;
	std::shared_ptr<Room> _room2;
};

} // namespace dungeon
} // namespace core

#endif // DOOR_H
