#ifndef DOOR_H
#define DOOR_H
#include <memory>
#include "room.h"

namespace core {
namespace dungeon {

class Room; //predeclaration

/**
 * @brief The Door class represents the door
 */
class Door
{
public:
    /**
     * @brief Door default constructor with two rooms
     * @param room1 Left side of the door
     * @param room2 Right side of the door
     */
	Door(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2);

    /**
     * @brief getNeighbourRoom Gets neighbour room of thisRoom
     * @param thisRoom this room
     * @return
     */
	std::shared_ptr<Room> getNeighbourRoom(std::shared_ptr<Room> thisRoom);

private:
    std::shared_ptr<Room> _room1; // left room of the door
    std::shared_ptr<Room> _room2; // right room of the door
};

} // namespace dungeon
} // namespace core

#endif // DOOR_H
