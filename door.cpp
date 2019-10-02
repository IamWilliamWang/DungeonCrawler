#include "door.h"

using namespace core::dungeon;

Door::Door(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2) {
    _room1 = room1;
    _room2 = room2;
}

std::shared_ptr<Room> Door::getNeighbourRoom(std::shared_ptr<Room> thisRoom) {
    if (thisRoom == _room1) {
        return _room2;
    }
    else {
        return _room1;
    }
}
