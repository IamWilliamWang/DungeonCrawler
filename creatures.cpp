#include "creatures.h"

using namespace core::creatures;

/* ------------------------------------------------------------------------------
 * Creature member implementations
 * -----------------------------------------------------------------------------*/

Creature::Creature(const std::string &name) 
	: _name(name)
{
	_weapon = std::make_shared<core::weapons::Fists>();
}

const std::string& Creature::name() 
{ 
	return _name; 
}

int Creature::getStrength() 
{ 
	return _strength; 
}

int Creature::getDexterity() 
{ 
	return _dexterity; 
}

int Creature::getWisdom() 
{ 
	return _wisdom; 
}

int Creature::getHealthPoint() 
{ 
	return _health; 
}

void Creature::setHealthPoint(int healthPoint)
{
	if (_maxHealth == -1)
		_maxHealth = healthPoint;
	_health = healthPoint > _maxHealth ? _maxHealth : healthPoint; // can not higher than the max value.
}

int Creature::getMaxHealthPoint()
{
	return _maxHealth;
}

bool Creature::isAlive() 
{ 
	return _health > 0; 
}

bool Creature::setAttribute(int strength, int dexterity, int wisdom)
{
	if (strength < 1 || strength > 6)
		return false;
	if (dexterity < 1 || dexterity > 6)
		return false;
	if (wisdom < 1 || wisdom > 6)
		return false;
	_strength = strength;
	_dexterity = dexterity;
	_wisdom = wisdom;
	if (_maxHealth == -1)
		_maxHealth = 50;
	_health = 50;
	return true;
}

int Creature::damage()
{
	return 2 * (_strength - 1);
}

int* Creature::damageWeaponed()
{
	int* result = _weapon->getDamageRange();
	result[0] += damage();
	result[1] += damage();
	return result;
}

int Creature::dodgeChance()
{
	return _dexterity > 0 ? 20 * (_dexterity - 1) : 0;
}

void Creature::setDescription(std::string description)
{
	_description = description;
}

std::string Creature::getDescription()
{
	return _description;
}

auto Creature::getWeapon()
{
	return _weapon;
}

void Creature::setWeapon(std::shared_ptr<core::weapons::Weapon> weapon)
{
	_weapon = weapon;
}

//const std::string& Creature::name() const {
//  return _name;
//}


