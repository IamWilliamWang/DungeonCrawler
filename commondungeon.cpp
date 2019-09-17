#include "commondungeon.h"

using namespace core::dungeon;

OpenDoorway::OpenDoorway(std::shared_ptr<Room> room1, std::shared_ptr<Room> room2) 
	: Door(room1, room2) 
{ 

}
