#ifndef WEAPONS_H
#define WEAPONS_H
#include <string>
#include <memory>
namespace core {
namespace weapons {
/**
 * @brief TODO The Enchantment class
 */
class Enchantment
{
public:
	Enchantment();
	std::string getEnchantmentType();
protected:
	std::string _enchantmentType;
};

/**
 * @brief TODO The FlameEnchantment class
 */
class FlameEnchantment : public Enchantment
{
public:
	FlameEnchantment();
	int getExtraDamage();
};

/**
 * @brief TODO The ElectricityEnchantment class
 */
class ElectricityEnchantment : public Enchantment
{
public:
	ElectricityEnchantment();
	int getExtraDamage();
};

/**
 * @brief TODO The HealingEnchantment class
 */
class HealingEnchantment : public Enchantment
{
public:
	HealingEnchantment();
	//void doHeal(std::shared_ptr<core::creatures::Creature> creature);
	int getHealHealthPoints();
};

/**
 * @brief TODO The VampirismEnchantment class
 */
class VampirismEnchantment : public Enchantment
{
public:
	VampirismEnchantment();
	//void doHeal(std::shared_ptr<core::Character::Creature> creature, int damagedThisRound);
	int getHealHealthPoints();
};

/**
 * @brief TODO The Weapon class
 */
class Weapon
{
public:
	Weapon();
	Weapon(std::string &name, std::string &description);
	Weapon(std::string &name, std::string &description, std::string &longDescription);
	Weapon(std::string &name, std::string &description, std::string &longDescription, int minDamage, int maxDamage);
  /**
	* @brief getName 获得名字
	* @return
	*/
	std::string getName();

	/**
		* @brief setName 设定名字
		* @param name
		*/
	void setName(std::string name);

	/**
		* @brief getDescription
		* @return
		*/
	std::string getDescription();

	/**
		* @brief setDescription
		* @param description
		*/
	void setDescription(std::string description);

	/**
		* @brief getLongDescription
		* @return
		*/
	std::string getLongDescription();

	/**
		* @brief setLongDescription
		* @param longDescription
		*/
	void setLongDescription(std::string longDescription);

	/**
		* @brief getDamageRange 获得武器的最小攻击力和最大攻击力
		* @return
		*/
	int* getDamageRange();

	/**
		* @brief setDamageRange 设置武器的最小攻击力和最大攻击力
		* @param minDamage
		* @param maxDamage
		*/
	void setDamageRange(int minDamage, int maxDamage);

	/**
		* @brief getSpecialAbilityDescription
		* @return
		*/
	std::string getSpecialAbilityDescription();

	/**
		* @brief setSpecialAbilityDescription
		* @param specialAbilityDescription
		*/
    void setSpecialAbilityDescription(std::string specialAbilityDescription);

	auto getPrefixEnchantment();

	auto getSuffixEnchantment();

private:
	int getEnchantmentDamage();

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
 * @brief TODO The Fists class
 */
class Fists : public Weapon
{
public:
	Fists();
};

/**
 * @brief TODO The Boomerang class
 */
class Boomerang : public Weapon
{
public:
	Boomerang();
};

/**
 * @brief TODO The ShortSword class
 */
class ShortSword : public Weapon
{
public:
	ShortSword();
};

/**
 * @brief TODO The BattleAxe class
 */
class BattleAxe : public Weapon
{
public:
	BattleAxe();
};

/**
 * @brief TODO The WizardsStaff class
 */
class WizardsStaff : public Weapon
{
public:
	WizardsStaff();
};

/**
 * @brief TODO The MagicWand class
 */
class MagicWand : public Weapon
{
public:
	MagicWand();
};

} // namespace items
} // namespace core


#endif // WEAPONS_H
