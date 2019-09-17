#include "room.h"
using namespace core::dungeon;

#define NORTH 'N'
#define SOUTH 'S'
#define WEST 'W'
#define EAST 'E'

Room::Room(int id) 
	: _id(id) 
{

}

int Room::id() 
{ 
	return _id; 
}

bool Room::addWall(char direction, std::shared_ptr<Wall> wall = std::make_shared<Wall>())
{
	if (!checkDirectionVaild(direction))
		return false;

	_walls[direction] = wall;
	return true;
}

bool Room::addDoor(char direction, std::shared_ptr<Door> door)
{
	if (!checkDirectionVaild(direction))
		return false;

	_doors[direction] = door;
	return true;
}

std::shared_ptr<dungeon::Door> Room::getDoor(char direction)
{
	if (!checkDirectionVaild(direction))
		return nullptr;
	if (_doors.count(direction) == 0)
		return nullptr;
	return _doors[direction];
}

std::list<char> Room::findDoorDirections()
{
	std::list<char> directionList;
	for (auto& pair : _doors)
	{
		directionList.emplace_back(pair.first);
	}
	return directionList;
}

std::list<char> Room::getDoorDirections()
{
	return findDoorDirections();
}

bool Room::existEntranceOrExit()
{
	return getEntranceDirection() != '\0' || getExitDirection() != '\0';
}

void Room::addEntranceOrExit(char direction, bool addEntrance)
{
	if (addEntrance)
		this->setEntrance(direction);
	else
		this->setExit(direction);
}

char Room::getEntranceDirection()
{
	for (auto& pair : _entranceOrExit)
	{
		if (pair.second == "entrance")
			return pair.first;
	}
	return '\0';
}

char Room::getExitDirection()
{
	for (auto& pair : _entranceOrExit)
	{
		if (pair.second == "exit")
			return pair.first;
	}
	return '\0';
}

bool Room::checkDirectionVaild(char& direction)
{
	if (direction >= 'a' && direction <= 'z')
		direction -= 'a' - 'A';
	return (direction == NORTH || direction == SOUTH || direction == WEST || direction == EAST);
}

bool Room::createCreature(std::vector<std::shared_ptr<core::creatures::Creature>> possibleCreatures)
{
    _creature = possibleCreatures.at(Game::instance()->randomIntBetweenEx(0, possibleCreatures.size()));
	return true;
}

bool Room::createWeapon(std::vector<std::shared_ptr<core::weapons::Weapon>> possibleWeapons)
{
    _weapon = possibleWeapons.at(Game::instance()->randomIntBetweenEx(0, possibleWeapons.size()));
	return true;
}

std::shared_ptr<core::creatures::Creature> Room::getCreature()
{
	return _creature;
}

void Room::setCreature(std::shared_ptr<core::creatures::Creature> creature)
{
	_creature = creature;
}

std::shared_ptr<core::weapons::Weapon> Room::getWeapon()
{
	if (_creature == nullptr) // weapon only
		return _weapon;
	else return _creature->getWeapon(); // creature takes a weapon
}

void Room::setWeapon(std::shared_ptr<core::weapons::Weapon> weapon)
{
	_weapon = weapon;
}

bool Room::setEntrance(char direction)
{
	if (!checkDirectionVaild(direction))
		return false;

	_entranceOrExit[direction] = "entrance";
	return true;
}

bool Room::setExit(char direction)
{
	if (!checkDirectionVaild(direction))
		return false;

	_entranceOrExit[direction] = "exit";
	return true;
}
