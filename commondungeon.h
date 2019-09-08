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
 * @brief TODO The OpenDoorway class
 */
class OpenDoorway : public Door
{
public:
    OpenDoorway(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2) : Door(room1,room2) { }
};

} // namespace dungeon
} // namespace core

#endif // COMMONDUNGEON_H
