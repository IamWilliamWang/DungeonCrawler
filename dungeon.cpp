#include "dungeon.h"
#include "room.h"
using namespace core::dungeon;

Dungeon::Dungeon()
  : _rooms{}
{

}

Dungeon::Dungeon(const Dungeon& oldDungeon)
{
	memcpy(&this->_rooms, &oldDungeon._rooms, sizeof(oldDungeon._rooms));
	memcpy(&this->_path, &oldDungeon._path, sizeof(oldDungeon._path));
	memcpy(&this->_nowRoom, &oldDungeon._nowRoom, sizeof(oldDungeon._nowRoom));
}

std::shared_ptr<Room> Dungeon::getEntranceRoom()
{
	for (auto &pair : _rooms)
	{
		if (pair.second->getEntranceDirection() != '\0')
			return pair.second;
	}
	return nullptr;
}

std::shared_ptr<Room> Dungeon::getNowRoom()
{
	return _nowRoom;
}

void Dungeon::setNowRoom(std::shared_ptr<Room> nowRoom)
{
	_nowRoom = nowRoom;
	_path.emplace_back(nowRoom);
}

std::shared_ptr<Room> Dungeon::path(int index)
{
	if (index < 0)
	{
		auto it = _path.rbegin();
		for (; index < -1 && it != _path.rend(); index++)
			it++;
		if (it == _path.rend())
			return nullptr;
		return *it;
	}
	else
	{
		auto it = _path.begin();
		for (; index > 0 && it != _path.end(); index--)
			it++;
		if (it == _path.end())
			return nullptr;
		return *it;
	}
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
