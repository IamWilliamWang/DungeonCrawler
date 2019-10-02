#include "creatures.h"
#include <iostream>
using namespace core::creatures;

/* ------------------------------------------------------------------------------
 * Creature member implementations
 * -----------------------------------------------------------------------------*/

Creature::Creature(const std::string &name)
    : _name(name) {
	_weapon = std::make_shared<core::weapons::Fists>();
}

std::string& Creature::name() {
	return _name;
}

int Creature::getStrength() {
	return _strength;
}

int Creature::getDexterity() {
	return _dexterity;
}

int Creature::getWisdom() {
	return _wisdom;
}

int Creature::getHealthPoint() {
	return _health;
}

void Creature::setHealthPoint(int healthPoint) {
    if (_maxHealth == -1) {
		_maxHealth = healthPoint;
    }
    // prevent health point higher than the max value.
    _health = healthPoint > _maxHealth ? _maxHealth : healthPoint;
}

int Creature::getMaxHealthPoint() {
	return _maxHealth;
}

bool Creature::isAlive() {
	return _health > 0;
}

bool Creature::setAttribute(int strength, int dexterity, int wisdom, bool checkVaild) {
	if (checkVaild) {
		if (strength < 1 || strength > 6)
			return false;
		if (dexterity < 1 || dexterity > 6)
			return false;
		if (wisdom < 1 || wisdom > 6)
			return false;
	}
	_strength = strength;
	_dexterity = dexterity;
	_wisdom = wisdom;
	setHealthPoint(50);
	return true;
}

int Creature::damage() {
	return 2 * (_strength - 1);
}

int Creature::damageWeaponed() {
	return damage() + _weapon->get();
}

int* Creature::damageWeaponedRange() {
	int* result = _weapon->getDamageRange();
	result[0] += damage();
	result[1] += damage();
	return result;
}

int Creature::dodgeChance() {
	return _dexterity > 0 ? 20 * (_dexterity - 1) : 0;
}

void Creature::setDescription(std::string description) {
	_description = description;
}

std::string Creature::getDescription() {
	return _description;
}

std::shared_ptr<core::weapons::Weapon> Creature::getWeapon() {
	return _weapon;
}

void Creature::setWeapon(std::shared_ptr<core::weapons::Weapon> weapon) {
	_weapon = weapon;
}

std::ostream& operator<<(std::ostream &stream, core::creatures::Creature &creature) {
	// I use c-style formatted output, can't come up with a c++ solution.
	stream << creature.name() << std::endl;
	printf("Strength:%10d\n", creature.getStrength());
	printf("Dexterity:%9d\n", creature.getDexterity());
	printf("Wisdom:%12d\n", creature.getWisdom());
	printf("Health:%7d / %2d\n", creature.getHealthPoint(), creature.getMaxHealthPoint());
	int* characterDamageWeaponed = creature.damageWeaponedRange();
	printf("Damage:%7d - %2d\n", characterDamageWeaponed[0], characterDamageWeaponed[1]);
	delete characterDamageWeaponed; // release the memory.
	printf("Dodge:%12d%%\n", creature.dodgeChance());
	stream << "Weapon:    " << creature.getWeapon()->getDescription() << std::endl;
	return stream;
}
