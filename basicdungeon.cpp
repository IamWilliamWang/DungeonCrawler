#include "basicdungeon.h"

using namespace core::dungeon;

/* ------------------------------------------------------------------------------
 * BasicDungeon member implementations
 * -----------------------------------------------------------------------------*/

BasicDungeon::BasicDungeon()
{

}

std::shared_ptr<Room> BasicDungeon::getEntranceRoom()
{
	for (auto &pair : _rooms)
	{
		if (pair.second->getEntranceDirection() != '\0')
			return pair.second;
	}
	return nullptr;
}

auto BasicDungeon::getNowRoom()
{
	return _nowRoom;
}

void BasicDungeon::setNowRoom(std::shared_ptr<Room> nowRoom)
{
	_nowRoom = nowRoom;
	_path.emplace_back(nowRoom);
}

std::shared_ptr<Room> BasicDungeon::path(int index)
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

/* ------------------------------------------------------------------------------
 * RockChamber member implementations
 * -----------------------------------------------------------------------------*/

RockChamber::RockChamber()
{

}

/* ------------------------------------------------------------------------------
 * QuartzChamber member implementations
 * -----------------------------------------------------------------------------*/

QuartzChamber::QuartzChamber()
{

}

/* ------------------------------------------------------------------------------
 * BasicWall member implementations
 * -----------------------------------------------------------------------------*/

RockWall::RockWall()
{

}
