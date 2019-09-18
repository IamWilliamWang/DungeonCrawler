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
    /**
     * @brief Enchantment
     */
	Enchantment();
    /**
     * @brief getEnchantmentType
     * @return
     */
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
    /**
     * @brief FlameEnchantment
     */
	FlameEnchantment();
    /**
     * @brief getExtraDamage
     * @return
     */
	int getExtraDamage();
};

/**
 * @brief TODO The ElectricityEnchantment class
 */
class ElectricityEnchantment : public Enchantment
{
public:
    /**
     * @brief ElectricityEnchantment
     */
	ElectricityEnchantment();
    /**
     * @brief getExtraDamage
     * @return
     */
	int getExtraDamage();
};

/**
 * @brief TODO The HealingEnchantment class
 */
class HealingEnchantment : public Enchantment
{
public:
    /**
     * @brief HealingEnchantment
     */
	HealingEnchantment();
	//void doHeal(std::shared_ptr<core::creatures::Creature> creature);
    /**
     * @brief getHealHealthPoints
     * @return
     */
	int getHealHealthPoints();
};

/**
 * @brief TODO The VampirismEnchantment class
 */
class VampirismEnchantment : public Enchantment
{
public:
    /**
     * @brief VampirismEnchantment
     */
	VampirismEnchantment();
	//void doHeal(std::shared_ptr<core::Character::Creature> creature, int damagedThisRound);
    /**
     * @brief getHealHealthPoints
     * @param damagedThisRound
     * @return
     */
    int getHealHealthPoints(int damagedThisRound);
};

/**
 * @brief TODO The Weapon class
 */
class Weapon
{
public:
    /**
     * @brief Weapon
     */
	Weapon();

    /**
     * @brief Weapon
     * @param name
     * @param description
     */
	Weapon(std::string &name, std::string &description);

    /**
     * @brief Weapon
     * @param name
     * @param description
     * @param longDescription
     */
	Weapon(std::string &name, std::string &description, std::string &longDescription);

    /**
     * @brief Weapon
     * @param name
     * @param description
     * @param longDescription
     * @param minDamage
     * @param maxDamage
     */
	Weapon(std::string &name, std::string &description, std::string &longDescription, int minDamage, int maxDamage);

    /**
     * @brief getName
     * @return
     */
	std::string getName();

    /**
     * @brief setName
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

    /**
     * @brief getPrefixEnchantment
     * @return
     */
    std::shared_ptr<Enchantment> getPrefixEnchantment();

    /**
     * @brief getSuffixEnchantment
     * @return
     */
    std::shared_ptr<Enchantment> getSuffixEnchantment();

private:
    /**
     * @brief getEnchantmentDamage
     * @return
     */
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
    /**
     * @brief Fists
     */
	Fists();
};

/**
 * @brief TODO The Boomerang class
 */
class Boomerang : public Weapon
{
public:
    /**
     * @brief Boomerang
     */
	Boomerang();
};

/**
 * @brief TODO The ShortSword class
 */
class ShortSword : public Weapon
{
public:
    /**
     * @brief ShortSword
     */
	ShortSword();
};

/**
 * @brief TODO The BattleAxe class
 */
class BattleAxe : public Weapon
{
public:
    /**
     * @brief BattleAxe
     */
	BattleAxe();
};

/**
 * @brief TODO The WizardsStaff class
 */
class WizardsStaff : public Weapon
{
public:
    /**
     * @brief WizardsStaff
     */
	WizardsStaff();
};

/**
 * @brief TODO The MagicWand class
 */
class MagicWand : public Weapon
{
public:
    /**
     * @brief MagicWand
     */
	MagicWand();
};

} // namespace items
} // namespace core

std::ostream& operator<<(std::ostream &stream, core::weapons::Weapon &weapon);

#endif // WEAPONS_H
