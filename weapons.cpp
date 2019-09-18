#include "game.h"
#include "weapons.h"
#include <sstream>
#include <iomanip>

using namespace core::weapons;


/* ------------------------------------------------------------------------------
 * Weapon member implementations
 * -----------------------------------------------------------------------------*/

Weapon::Weapon() 
{

}

Weapon::Weapon(std::string &name, std::string &description)
    : _name(name), _description(description)
{

}

Weapon::Weapon(std::string &name, std::string &description, std::string &longDescription)
    : _name(name), _description(description), _longDescription(longDescription)
{

}

Weapon::Weapon(std::string &name, std::string &description, std::string &longDescription, int minDamage, int maxDamage)
    : _name(name), _description(description), _longDescription(longDescription), _minDamage(minDamage), _maxDamage(maxDamage)
{

}

std::string Weapon::getName()
{
	return _name;
}

void Weapon::setName(std::string name)
{
	_name = name;
}

std::string Weapon::getFullName()
{
	std::string result = "";
	if (_prefixEnchantment != nullptr)
	{
		if (_prefixEnchantment->getEnchantmentType() == "FlameEnchantment")
			result += "Flaming ";
		else if (_prefixEnchantment->getEnchantmentType() == "ElectricityEnchantment")
			result += "Electrified ";
	}
	result += _name;
	if (_suffixEnchantment != nullptr)
	{
		if (_suffixEnchantment->getEnchantmentType() == "HealingEnchantment")
			result += " of Healing";
		else if (_suffixEnchantment->getEnchantmentType() == "VampirismEnchantment")
			result += " of Vampirism";
	}
	return result;
}

std::string Weapon::getDescription()
{
	return _description;
}

void Weapon::setDescription(std::string description)
{
	_description = description;
}

std::string Weapon::getLongDescription()
{
	return _longDescription;
}

void Weapon::setLongDescription(std::string longDescription)
{
	_longDescription = longDescription;
}

int* Weapon::getDamageRange()
{
	int* range = new int[2];
	int enchantmentDamage = getEnchantmentDamage();
	range[0] = _minDamage + enchantmentDamage;
	range[1] = _maxDamage + enchantmentDamage;
	return range;
}

void Weapon::setDamageRange(int minDamage, int maxDamage)
{
	_minDamage = minDamage;
	_maxDamage = maxDamage;
}

std::string Weapon::getSpecialAbilityDescription()
{
	return _specialAbilityDescription;
}

void Weapon::setSpecialAbilityDescription(std::string specialAbilityDescription)
{
	_specialAbilityDescription = specialAbilityDescription;
}
std::shared_ptr<Enchantment> Weapon::getPrefixEnchantment()
{
	return _prefixEnchantment;
}
std::shared_ptr<Enchantment> Weapon::getSuffixEnchantment()
{
	return _suffixEnchantment;
}

int Weapon::getEnchantmentDamage()
{
	if (_prefixEnchantment != nullptr)
	{
		if (_prefixEnchantment->getEnchantmentType() == "FlameEnchantment")
		{
			auto flameEnchantment = std::static_pointer_cast<FlameEnchantment>(_prefixEnchantment);
			return flameEnchantment->get();
		}
		else if (_prefixEnchantment->getEnchantmentType() == "ElectricityEnchantment")
		{
			auto electricityEnchantment = std::static_pointer_cast<ElectricityEnchantment>(_prefixEnchantment);
			return electricityEnchantment->get();
		}
	}
    return 0;
}

int Weapon::get(void* args)
{
    auto range = getDamageRange();
    return Game::instance()->randomIntBetweenInc(range[0], range[1]);
}

Fists::Fists()
{
	setName("Fists");
	setDescription("you look down at your fists and shrug, \"these will do\"");
	setLongDescription("Fists are the weapon of choice for someone who has nothing else.");
	setDamageRange(4, 4);
}

Boomerang::Boomerang()
{
	setName("Boomerang");
	setDescription("an effective ranged weapon that returns to your hand when used");
	setLongDescription("You scratch your head struggling to understand how this weapon can return even *after* it hits its target?");
	setDamageRange(6, 8);
}

ShortSword::ShortSword()
{
	setName("Short Sword");
	setDescription("a sharp and pointy instrument, good for stabbing");
	setLongDescription("Not very large, but with a sharp point. Short swords are designed more for stabbing than for slicing. The hilt is surprisingly ornate for such an inconspicuous weapon.");
	setDamageRange(5, 10);
}

BattleAxe::BattleAxe()
{
	setName("Battle Axe");
	setDescription("heavy, but effective");
	setLongDescription("A large and heavy weapon. The battle axe must be wielded with two hands but even then you are almost as likely to cut off your own limbs as those of an enemy.");
	setDamageRange(10, 15);
}

WizardsStaff::WizardsStaff()
{
	setName("Wizard's Staff");
	setDescription("it would break if you leant on it, but it shoots fireballs so that’s something");
	setLongDescription("Not a very sturdy staff, but the swirl of magical fire around its top belies a magical secret: it shoots fireballs!");
	setDamageRange(1, 2);
	setSpecialAbilityDescription("Fireball: deals 10 - 20 damage to the opponent (plus the bonus from the creature or character’s Wisdom stat). Always hits, regardless of dodge chance.");
}

MagicWand::MagicWand()
{
	setName("Magic Wand");
	setDescription("birch with angel’s feather core and rubberised leather grip");
	setLongDescription("Apparently, there is no other wand like this one in existence. The angel’s feather at its core allows the bearer to perform unbelievable feats of healing.");
	setDamageRange(5, 10);
	setSpecialAbilityDescription("Healing: returns character to full health.");
}


/* ------------------------------------------------------------------------------
 * Enchantment member implementations
 * -----------------------------------------------------------------------------*/

Enchantment::Enchantment()
{

}

std::string Enchantment::getEnchantmentType()
{
	return _enchantmentType;
}

FlameEnchantment::FlameEnchantment()
{
	_enchantmentType = "FlameEnchantment";
}

int FlameEnchantment::getExtraDamage()
{
	return 5;
}

int FlameEnchantment::get(void* args)
{
    return getExtraDamage();
}

ElectricityEnchantment::ElectricityEnchantment()
{
	_enchantmentType = "ElectricityEnchantment";
}

int ElectricityEnchantment::getExtraDamage()
{
	return 5;
}

int ElectricityEnchantment::get(void* args)
{
    return getExtraDamage();
}

HealingEnchantment::HealingEnchantment()
{
	_enchantmentType = "HealingEnchantment";
}

int HealingEnchantment::getHealHealthPoints()
{
	return 5;
}

int HealingEnchantment::get(void* args)
{
    return getHealHealthPoints();
}

VampirismEnchantment::VampirismEnchantment()
{
	_enchantmentType = "VampirismEnchantment";
}

int VampirismEnchantment::getHealHealthPoints(int damagedThisRound)
{
	return damagedThisRound / 2;
}

int VampirismEnchantment::get(void* args)
{
    return getHealHealthPoints(*static_cast<int*>(args));
}

std::ostream& operator<<(std::ostream &stream, core::weapons::Weapon &weapon)
{
	// I use c-style formatted output, can't come up with a c++ solution.
    stream << "\"" << weapon.getFullName() << "\"" << std::endl;
    int* damages = weapon.getDamageRange();
    printf("Min. Damage:%7d\n", damages[0]);
    printf("Max. Damage:%7d\n", damages[1]);
	delete damages;
    stream << weapon.getLongDescription() << std::endl;
    return stream;
}
