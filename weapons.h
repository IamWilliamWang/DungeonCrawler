#ifndef WEAPONS_H
#define WEAPONS_H

namespace core {
namespace weapons {

/**
 * @brief TODO The Weapon class
 */
class Weapon
{
public:
    Weapon(){}
	Weapon(std::string &name, std::string &description) : _name(name),_description(description){}
	Weapon(std::string &name, std::string &description, std::string &longDescription) : _name(name), _description(description), _longDescription(longDescription) {}
	Weapon(std::string &name, std::string &description, std::string &longDescription, int minDamage, int maxDamage)
		: _name(name), _description(description), _longDescription(longDescription), _minDamage(minDamage), _maxDamage(maxDamage){}
	std::string getName()
	{
		return _name;
	}
	void setName(std::string name)
	{
		_name = name;
	}
	std::string getDescription()
	{
		return _description;
	}
	void setDescription(std::string description)
	{
		_description = description;
	}
	std::string getLongDescription()
	{
		return _longDescription;
	}
	void setLongDescription(std::string longDescription)
	{
		_longDescription = longDescription;
	}
	int* getDamageRange()
	{
		int range[2];
		range[0] = _minDamage;
		range[1] = _maxDamage;
		return range;
	}
	void setDamageRange(int minDamage, int maxDamage)
	{
		_minDamage = minDamage;
		_maxDamage = maxDamage;
	}
	std::string getSpecialAbilityDescription()
	{
		return _specialAbilityDescription;
	}
	void setSpecialAbilityDescription(std::string specialAbilityDescription)
	{
		_specialAbilityDescription = specialAbilityDescription;
	}
private:
	std::string _name;
	std::string _description;
	std::string _longDescription;
	int _minDamage;
	int _maxDamage;
	std::string _specialAbilityDescription;
};

/**
 * @brief TODO The Fists class
 */
class Fists : public Weapon
{
public:
    Fists(){}
};

/**
 * @brief TODO The Boomerang class
 */
class Boomerang : public Weapon
{
public:
    Boomerang(){}
};

/**
 * @brief TODO The ShortSword class
 */
class ShortSword : public Weapon
{
public:
    ShortSword(){}
};

/**
 * @brief TODO The BattleAxe class
 */
class BattleAxe : public Weapon
{
public:
    BattleAxe(){}
};

/**
 * @brief TODO The WizardsStaff class
 */
class WizardsStaff : public Weapon
{
public:
    WizardsStaff(){}
};

/**
 * @brief TODO The MagicWand class
 */
class MagicWand : public Weapon
{
public:
    MagicWand(){}
};

/**
 * @brief TODO The Enchantment class
 */
class Enchantment
{
public:
    Enchantment(){}
};

/**
 * @brief TODO The FlameEnchantment class
 */
class FlameEnchantment : public Enchantment
{
public:
    FlameEnchantment(){}
};

/**
 * @brief TODO The ElectricityEnchantment class
 */
class ElectricityEnchantment : public Enchantment
{
public:
    ElectricityEnchantment(){}
};

/**
 * @brief TODO The HealingEnchantment class
 */
class HealingEnchantment : public Enchantment
{
public:
    HealingEnchantment(){}
};

/**
 * @brief TODO The VampirismEnchantment class
 */
class VampirismEnchantment : public Enchantment
{
public:
    VampirismEnchantment(){}
};

} // namespace items
} // namespace core


#endif // WEAPONS_H
