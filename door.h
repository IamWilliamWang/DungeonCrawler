#ifndef DOOR_H
#define DOOR_H
#include <memory>
#include "room.h"

namespace core {
namespace dungeon {

class Room; //predeclaration

/**
 * @brief The Door class
 */
class Door
{
public:
    /**
     * @brief Door 门
     * @param room1
     * @param room2
     */
	Door(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2);

    /**
     * @brief getNeighbourRoom 获得邻居Room
     * @param thisRoom
     * @return
     */
	std::shared_ptr<Room> getNeighbourRoom(std::shared_ptr<Room> thisRoom);

private:
	std::shared_ptr<Room> _room1;
	std::shared_ptr<Room> _room2;
};

} // namespace dungeon
} // namespace core

#endif // DOOR_H
