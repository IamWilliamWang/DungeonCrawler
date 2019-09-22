#ifndef WEAPONS_H
#define WEAPONS_H
#include <string>
#include <memory>
namespace core {
namespace weapons {
/**
 * @brief The Interface virtual class used as a decorator
 */
class Interface
{
    /**
     * @brief get Gets the data you want
     * @param args Any parameters that need to be passed in
     * @return Desired integer data
     */
    virtual int get(void* args = nullptr) = 0;
};

/**
 * @brief The Enchantment class represents enchantment
 */
class Enchantment : public Interface
{
public:
    /**
     * @brief Enchantment default constructor
     */
    Enchantment();

    /**
     * @brief instanceOf Determines if enchantment is an instance of type "typeName"
     * @param typeName type name
     * @return
     */
    bool instanceOf(std::string typeName)
    {
        return _enchantmentType == typeName;
    }

protected:
    /**
     * @brief getEnchantmentType Gets the enchantment type name
     * @return
     */
    std::string getEnchantmentType();

    std::string _enchantmentType; // save the class name
};

/**
 * @brief The FlameEnchantment class represents flame enchantment
 */
class FlameEnchantment : public Enchantment
{
public:
    /**
     * @brief FlameEnchantment default constructor
     */
    FlameEnchantment();

    /**
     * @brief getExtraDamage Gets extra damage from this enchantment
     * @return
     */
    int getExtraDamage();

    /**
     * @brief get Gets extra damage from this enchantment (equal to getExtraDamage())
     * @param args No need to pass any args
     * @return
     */
    int get(void* args = nullptr);
};

/**
 * @brief The ElectricityEnchantment class represents electricity enchantment
 */
class ElectricityEnchantment : public Enchantment
{
public:
    /**
     * @brief ElectricityEnchantment default constructor
     */
    ElectricityEnchantment();
    /**
     * @brief getExtraDamage Gets extra damage from this enchantment
     * @return
     */
    int getExtraDamage();

    /**
     * @brief get Gets extra damage from this enchantmentz (equal to getExtraDamage())
     * @param args No need to pass any args
     * @return
     */
    int get(void* args = nullptr);
};

/**
 * @brief The HealingEnchantment class represents healing enchantment
 */
class HealingEnchantment : public Enchantment
{
public:
    /**
     * @brief HealingEnchantment default constructor
     */
    HealingEnchantment();

    /**
     * @brief getHealHealthPoints Gets a healing value that can be healed
     * @return
     */
    int getHealHealthPoints();

    /**
     * @brief get Gets a healing value that can be healed (equal to getHealHealthPoints())
     * @param args No need to pass any args
     * @return
     */
    int get(void* args = nullptr);
};

/**
 * @brief The VampirismEnchantment class represents vampirism enchantment
 */
class VampirismEnchantment : public Enchantment
{
public:
    /**
     * @brief VampirismEnchantment default constructor
     */
    VampirismEnchantment();

    /**
     * @brief getHealHealthPoints Gets a healing value that can be healed in this round
     * @param damagedThisRound Damages taken this turn
     * @return
     */
    int getHealHealthPoints(int damagedThisRound);

    /**
     * @brief get Gets a healing value that can be healed in this round (equal to getHealHealthPoints(int))
     * @param args An integer pointer that represents the damage taken this turn
     * @return
     */
    int get(void* args = nullptr);
};

/**
 * @brief The Weapon class represents weapon
 */
class Weapon : public Interface
{
public:
    /**
     * @brief Weapon default constructor
     * @param name
     */
    Weapon(std::string name);

    /**
     * @brief getName Gets the weapon's name
     * @return
     */
	std::string getName();

    /**
     * @brief getFullName Gets the full name with prefix and suffix
     * @return
     */
	std::string getFullName();

    /**
     * @brief setName Sets the weapon's name
     * @param name weapon's name
     */
	void setName(std::string name);

    /**
     * @brief getDescription Gets the short description of weapon
     * @return
     */
    std::string getDescription();

    /**
     * @brief setDescription Sets the short description of weapon
     * @param description description
     */
    void setDescription(std::string description);

    /**
     * @brief getLongDescription Gets the long description of weapon
     * @return
     */
    std::string getLongDescription();

    /**
     * @brief setLongDescription Sets the long description of weapon
     * @param longDescription long description of weapon
     */
    void setLongDescription(std::string longDescription);

    /**
     * @brief getDamageRange Gets minimum damage and maximum damage of weapon (including enchant bonuses)
     * @return
     */
    int* getDamageRange();

    /**
     * @brief setDamageRange Sets minimum damage and maximum damage of weapon (not considering enchant bonuses)
     * @param minDamage minDamage of weapon
     * @param maxDamage maxDamage of weapon
     */
	void setDamageRange(int minDamage, int maxDamage);

    /**
     * @brief getSpecialAbilityDescription Gets special ability description
     * @return
     */
	std::string getSpecialAbilityDescription();

    /**
     * @brief setSpecialAbilityDescription Sets special ability description
     * @param specialAbilityDescription special ability description
     */
    void setSpecialAbilityDescription(std::string specialAbilityDescription);

    /**
     * @brief getPrefixEnchantment Gets prefix enchantment
     * @return
     */
    std::shared_ptr<Enchantment> getPrefixEnchantment();

    /**
     * @brief setPrefixEnchantment Forces to set prefix enchantment
     * @param prefixEnchantment prefix enchantment
     */
    void setPrefixEnchantment(std::shared_ptr<Enchantment> prefixEnchantment);

    /**
     * @brief getSuffixEnchantment Gets suffix enchantment
     * @return
     */
    std::shared_ptr<Enchantment> getSuffixEnchantment();

    /**
     * @brief setSuffixEnchantment Forces to set suffix enchantment
     * @param suffixEnchantment suffix enchantment
     */
    void setSuffixEnchantment(std::shared_ptr<Enchantment> suffixEnchantment);

    /**
     * @brief get Use the result of getDamageRange() to randomly pick a damage value
     * @param args No need to pass any args
     * @return
     */
    int get(void* args = nullptr);
private:

    /**
     * @brief createEnchantmentOrNot Decides whether to add enchantment or not, and automatically does so
     * @return
     */
    bool createEnchantmentOrNot();

    /**
     * @brief hasEnchantmentCount The number of enchantments you need to have
     * @return
     */
    int hasEnchantmentCount();

    /**
     * @brief createEnchantment Create enchantmentCount enchantments for this weapon
     * @param enchantmentCount enchantment count
     * @return
     */
    bool createEnchantment(int enchantmentCount);

    /**
     * @brief getEnchantmentDamage Gets additional damage from enchantment
     * @return
     */
	int getEnchantmentDamage();

    std::string _name = ""; // weapon's name
    std::string _description = ""; // weapon's description
    std::string _longDescription = ""; // weapon's long description
    int _minDamage = -1; // weapon's minimum damage
    int _maxDamage = -1; // weapon's maximum damage
    std::string _specialAbilityDescription = ""; // weapon's special ability description
    std::shared_ptr<Enchantment> _prefixEnchantment; // weapon's prefix enchantment
    std::shared_ptr<Enchantment> _suffixEnchantment; // weapon's suffix enchantment
};

/**
 * @brief The Fists class represents fists
 */
class Fists : public Weapon
{
public:
    /**
     * @brief Fists default constructor
     */
	Fists();
};

/**
 * @brief The Boomerang class represents boomerang
 */
class Boomerang : public Weapon
{
public:
    /**
     * @brief Boomerang default constructor
     */
	Boomerang();
};

/**
 * @brief The ShortSword class represents short sword
 */
class ShortSword : public Weapon
{
public:
    /**
     * @brief ShortSword default constructor
     */
	ShortSword();
};

/**
 * @brief The BattleAxe class represents battle axe
 */
class BattleAxe : public Weapon
{
public:
    /**
     * @brief BattleAxe default constructor
     */
	BattleAxe();
};

/**
 * @brief The WizardsStaff class represents wizard's staff
 */
class WizardsStaff : public Weapon
{
public:
    /**
     * @brief WizardsStaff default constructor
     */
	WizardsStaff();
};

/**
 * @brief The MagicWand class represents magic wand
 */
class MagicWand : public Weapon
{
public:
    /**
     * @brief MagicWand default constructor
     */
	MagicWand();
};

} // namespace items
} // namespace core

std::ostream& operator<<(std::ostream &stream, core::weapons::Weapon &weapon);

#endif // WEAPONS_H
