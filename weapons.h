#ifndef WEAPONS_H
#define WEAPONS_H

namespace core {
namespace weapons {
class Enchantment; //predeclaration

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
	std::string _specialAbilityDescription = nullptr;
	std::shared_ptr<Enchantment> _prefixEnchantment = nullptr;
	std::shared_ptr<Enchantment> _suffixEnchantment = nullptr;
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
		setDescription("it would break if you leant on it, but it shoots fireballs so that¡¯s something");
		setLongDescription("Not a very sturdy staff, but the swirl of magical fire around its top belies a magical secret: it shoots fireballs!");
		setDamageRange(1, 2);
		setSpecialAbilityDescription("Fireball: deals 10 - 20 damage to the opponent (plus the bonus from the creature or character¡¯s Wisdom stat). Always hits, regardless of dodge chance.");
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
		setDescription("birch with angel¡¯s feather core and rubberised leather grip");
		setLongDescription("Apparently, there is no other wand like this one in existence. The angel¡¯s feather at its core allows the bearer to perform unbelievable feats of healing.");
		setDamageRange(5, 10);
		setSpecialAbilityDescription("Healing: returns character to full health.");
	}
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
