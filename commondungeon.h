#ifndef COMMONDUNGEON_H
#define COMMONDUNGEON_H
#include "dungeon.h"
#include "room.h"
#include "wall.h"
#include "door.h"

namespace core {
namespace dungeon {

// TODO: define concrete components classes common to all dungeon types

/**
 * @brief The OpenDoorway class represents open doorway
 */
class OpenDoorway : public Door
{
public:
    /**
     * @brief OpenDoorway default constructor
     * @param room1 Left side of the open door
     * @param room2 Right side of the open door
     */
	OpenDoorway(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2);
};

class Chamber
{

};
} // namespace dungeon
} // namespace core

#endif // COMMONDUNGEON_H
