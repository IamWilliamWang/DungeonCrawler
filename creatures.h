#ifndef CREATURE_H
#define CREATURE_H
#include <string>
#include <memory>
#include "weapons.h"
namespace core {
namespace creatures {
// TODO: define Creature class and the its concrete subclasses.
// There is some example code in here, but it can be modified if desired.

/**
 * @brief The Creature class represents all creatures in this game
 */
class Creature
{
public:
    /**
     * @brief Creature default constructor with creature's name
     * @param name creature's name
     */
    Creature(const std::string &name);

    /**
     * @brief name Gets the name of creature
     * @return name of creature
     */
    std::string& name();

    /**
     * @brief getStrength Gets the strength of creature
     * @return strength of creature
     */
    int getStrength();

    /**
     * @brief getDexterity Gets the dexterity of creature
     * @return dexterity of creature
     */
    int getDexterity();

    /**
     * @brief getWisdom Gets the wisdom of creature
     * @return wisdom of creature
     */
    int getWisdom();

    /**
     * @brief getHealthPoint Gets the health points of creature
     * @return health points of creature
     */
    int getHealthPoint();
    
    /**
     * @brief setHealthPoint Sets the health points of creature
     * @param healthPoint health points of creature
     */
    void setHealthPoint(int healthPoint);

    /**
     * @brief getMaxHealthPoint Gets health points' max value
     * @return health points' max value
     */
    int getMaxHealthPoint();

    /**
     * @brief isAlive Determines whether an creature is alive
     * @return Whether an creature is alive
     */
    bool isAlive();

    /**
     * @brief setAttribute Sets basic properties (including strength, dexterity, wisdom) of creature
     * @param strength Sets strength of creature
     * @param dexterity Sets dexterity of creature
     * @param wisdom Sets wisdom of creature
     * @param checkVaild Decides whether to judge the validity of values
     * @return
     */
    bool setAttribute(int strength, int dexterity, int wisdom, bool checkVaild=true);

    /**
     * @brief damage Gets the damage from not using a weapon
     * @return damage without weapon
     */
    int damage();

    /**
     * @brief damageWeaponed Gets the damage of a enchanted weapon
     * @return Random value within the damage range
     */
    int damageWeaponed();

    /**
     * @brief damageWeaponedRange Gets the damage range of a enchanted weapon
     * @return An int[2], contains [minimum damage, maximum damage]
     */
    int* damageWeaponedRange();

    /**
     * @brief dodgeChance Gets the probability of avoiding, 0 is impossible to avoid, 100 is certain to avoid
     * @return dodge change
     */
    int dodgeChance();

    /**
     * @brief setDescription Sets the description of creature
     * @param description Description of creature
     */
    void setDescription(std::string description);

    /**
     * @brief getDescription Gets the description of creature
     * @return description
     */
    std::string getDescription();

    /**
     * @brief getWeapon Gets the weapon of creature
     * @return weapon
     */
    std::shared_ptr<core::weapons::Weapon> getWeapon();

    /**
     * @brief setWeapon Sets the weapon of creature
     * @param weapon weapon of creature
     */
    void setWeapon(std::shared_ptr<core::weapons::Weapon> weapon);

private:
    std::string _name; // creature's name
    std::string _description; // creature's description
    int _strength; // creature's strength
    int _dexterity; // creature's dexterity
    int _wisdom; // creature's wisdom
    int _health; // creature's health
    int _maxHealth = -1; // creature's maximum health
    std::shared_ptr<core::weapons::Weapon> _weapon; // creature's weapon
};

} // namespace creatures
} // namespace core

/**
 * @brief operator << output the creature's information to the output stream
 * @param stream output stream
 * @param creature the creature
 * @return output stream
 */
std::ostream& operator<<(std::ostream &stream, core::creatures::Creature &creature);

#endif // CREATURE_H
