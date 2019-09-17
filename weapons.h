#ifndef WEAPONS_H
#define WEAPONS_H
#include <string>
#include <memory>
#include "weapons.h"
namespace core {
namespace weapons {
/**
 * @brief TODO The Weapon class
 */
class Weapon
{
public:
	Weapon() {}
	Weapon(std::string &name, std::string &description) : _name(name), _description(description) {}
	Weapon(std::string &name, std::string &description, std::string &longDescription) : _name(name), _description(description), _longDescription(longDescription) {}
	Weapon(std::string &name, std::string &description, std::string &longDescription, int minDamage, int maxDamage)
		: _name(name), _description(description), _longDescription(longDescription), _minDamage(minDamage), _maxDamage(maxDamage) {}
	/**
		* @brief getName 获得名字
		* @return
		*/
	std::string getName()
	{
		return _name;
	}
	/**
		* @brief setName 设定名字
		* @param name
		*/
	void setName(std::string name)
	{
		_name = name;
	}
	/**
		* @brief getDescription
		* @return
		*/
	std::string getDescription()
	{
		return _description;
	}
	/**
		* @brief setDescription
		* @param description
		*/
	void setDescription(std::string description)
	{
		_description = description;
	}
	/**
		* @brief getLongDescription
		* @return
		*/
	std::string getLongDescription()
	{
		return _longDescription;
	}
	/**
		* @brief setLongDescription
		* @param longDescription
		*/
	void setLongDescription(std::string longDescription)
	{
		_longDescription = longDescription;
	}
	/**
		* @brief getDamageRange 获得武器的最小攻击力和最大攻击力
		* @return
		*/
	int* getDamageRange()
	{
		int* range = new int[2];
		int enchantmentDamage = getEnchantmentDamage();
		range[0] = _minDamage + enchantmentDamage;
		range[1] = _maxDamage + enchantmentDamage;
		return range;
	}
	/**
		* @brief setDamageRange 设置武器的最小攻击力和最大攻击力
		* @param minDamage
		* @param maxDamage
		*/
	void setDamageRange(int minDamage, int maxDamage)
	{
		_minDamage = minDamage;
		_maxDamage = maxDamage;
	}
	/**
		* @brief getSpecialAbilityDescription
		* @return
		*/
	std::string getSpecialAbilityDescription()
	{
		return _specialAbilityDescription;
	}
	/**
		* @brief setSpecialAbilityDescription
		* @param specialAbilityDescription
		*/
	void setSpecialAbilityDescription(std::string specialAbilityDescription)
	{
		_specialAbilityDescription = specialAbilityDescription;
	}
	auto getPrefixEnchantment()
	{
		return _prefixEnchantment;
	}
	auto getSuffixEnchantment()
	{
		return _suffixEnchantment;
	}
private:
	int getEnchantmentDamage()
	{
		if (_prefixEnchantment != nullptr)
		{
			if (_prefixEnchantment->getEnchantmentType() == "FlameEnchantment")
			{
				auto flameEnchantment = std::static_pointer_cast<FlameEnchantment>(_prefixEnchantment);
				return flameEnchantment->getExtraDamage();
			}
			else if (_prefixEnchantment->getEnchantmentType() == "ElectricityEnchantment")
			{
				auto electricityEnchantment = std::static_pointer_cast<ElectricityEnchantment>(_prefixEnchantment);
				return electricityEnchantment->getExtraDamage();
			}
		}
	}
	std::string _name = "";
	std::string _description = "";
	std::string _longDescription = "";
	int _minDamage = -1;
	int _maxDamage = -1;
	std::string _specialAbilityDescription = "";
	std::shared_ptr<Enchantment> _prefixEnchantment;
	std::shared_ptr<Enchantment> _suffixEnchantment;
};

/**
 * @brief TODO The Enchantment class
 */
class Enchantment
{
public:
	Enchantment()
	{
	}

	std::string getEnchantmentType()
	{
		return _enchantmentType;
	}
protected:
	std::string _enchantmentType;
};

/**
 * @brief TODO The Fists class
 */
class Fists : public Weapon
{
public:
	Fists()
	{
		setName("Fists");
		setDescription("you look down at your fists and shrug, \"these will do\"");
		setLongDescription("Fists are the weapon of choice for someone who has nothing else.");
		setDamageRange(4, 4);
	}
};

/**
 * @brief TODO The Boomerang class
 */
class Boomerang : public Weapon
{
public:
	Boomerang()
	{
		setName("Boomerang");
		setDescription("an effective ranged weapon that returns to your hand when used");
		setLongDescription("You scratch your head struggling to understand how this weapon can return even *after* it hits its target?");
		setDamageRange(6, 8);
	}
};

/**
 * @brief TODO The ShortSword class
 */
class ShortSword : public Weapon
{
public:
	ShortSword()
	{
		setName("Short Sword");
		setDescription("a sharp and pointy instrument, good for stabbing");
		setLongDescription("Not very large, but with a sharp point. Short swords are designed more for stabbing than for slicing. The hilt is surprisingly ornate for such an inconspicuous weapon.");
		setDamageRange(5, 10);
	}
};

/**
 * @brief TODO The BattleAxe class
 */
class BattleAxe : public Weapon
{
public:
	BattleAxe()
	{
		setName("Battle Axe");
		setDescription("heavy, but effective");
		setLongDescription("A large and heavy weapon. The battle axe must be wielded with two hands but even then you are almost as likely to cut off your own limbs as those of an enemy.");
		setDamageRange(10, 15);
	}
};

/**
 * @brief TODO The WizardsStaff class
 */
class WizardsStaff : public Weapon
{
public:
	WizardsStaff()
	{
		setName("Wizard's Staff");
		setDescription("it would break if you leant on it, but it shoots fireballs so that’s something");
		setLongDescription("Not a very sturdy staff, but the swirl of magical fire around its top belies a magical secret: it shoots fireballs!");
		setDamageRange(1, 2);
		setSpecialAbilityDescription("Fireball: deals 10 - 20 damage to the opponent (plus the bonus from the creature or character’s Wisdom stat). Always hits, regardless of dodge chance.");
	}
};

/**
 * @brief TODO The MagicWand class
 */
class MagicWand : public Weapon
{
public:
	MagicWand()
	{
		setName("Magic Wand");
		setDescription("birch with angel’s feather core and rubberised leather grip");
		setLongDescription("Apparently, there is no other wand like this one in existence. The angel’s feather at its core allows the bearer to perform unbelievable feats of healing.");
		setDamageRange(5, 10);
		setSpecialAbilityDescription("Healing: returns character to full health.");
	}
};

/**
 * @brief TODO The FlameEnchantment class
 */
class FlameEnchantment : public Enchantment
{
public:
    FlameEnchantment()
	{
		_enchantmentType = "FlameEnchantment";
	}

	int getExtraDamage()
	{
		return 5;
	}
};

/**
 * @brief TODO The ElectricityEnchantment class
 */
class ElectricityEnchantment : public Enchantment
{
public:
    ElectricityEnchantment()
	{
		_enchantmentType = "ElectricityEnchantment";
	}

	int getExtraDamage()
	{
		return 5;
	}
};

/**
 * @brief TODO The HealingEnchantment class
 */
class HealingEnchantment : public Enchantment
{
public:
    HealingEnchantment()
	{
		_enchantmentType = "HealingEnchantment";
	}
    void doHeal(std::shared_ptr<core::Character::Creature> creature)
	{
		creature->setHealthPoint(creature->getHealthPoint() + 5);
	}
};

/**
 * @brief TODO The VampirismEnchantment class
 */
class VampirismEnchantment : public Enchantment
{
public:
    VampirismEnchantment()
	{
		_enchantmentType = "VampirismEnchantment";
	}
    void doHeal(std::shared_ptr<core::Character::Creature> creature, int damagedThisRound)
	{
		creature->setHealthPoint(creature->getHealthPoint() + damagedThisRound / 2);
	}
};
} // namespace items
} // namespace core


#endif // WEAPONS_H
