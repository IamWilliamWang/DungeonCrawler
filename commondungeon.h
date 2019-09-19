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
 * @brief The OpenDoorway class
 */
class OpenDoorway : public Door
{
public:
    /**
     * @brief OpenDoorway 连接两个房间的门
     * @param room1
     * @param room2
     */
	OpenDoorway(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2);
};

class Chamber
{

};
} // namespace dungeon
} // namespace core

#endif // COMMONDUNGEON_H
