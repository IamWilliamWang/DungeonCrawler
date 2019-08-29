#include "room.h"

using namespace core::dungeon;

Room::Room(int id)
  : _id{id}
{

}

int Room::id() {
  return _id;
}
