#include "dungeon.h"

using namespace core::dungeon;

Dungeon::Dungeon()
  : _rooms{}
{

}


// DO NOT modify implementation below this comment

std::shared_ptr<Room> Dungeon::retrieveRoom(int id) {
  auto roomIterator = _rooms.find(id);
  if (roomIterator != _rooms.end()) {
    return roomIterator->second;
  }
  return std::shared_ptr<Room>{nullptr};
}

bool Dungeon::addRoom(std::shared_ptr<Room> newRoom) {
  if (!_rooms.count(newRoom->id())) {
    _rooms[newRoom->id()] = newRoom;
    return true;
  }
  return false;
}
