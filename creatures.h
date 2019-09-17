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
 * @brief TODO The Creature class
 */
class Creature
{
public:
	Creature(const std::string &name);

    /**
     * @brief name 获得生物的名字
     * @return
     */
	const std::string& name();

    /**
     * @brief getStrength 获得力量值
     * @return
     */
	int getStrength();

    /**
     * @brief getDexterity 获得敏捷值
     * @return
     */
	int getDexterity();

    /**
     * @brief getWisdom 获得智力值
     * @return
     */
	int getWisdom();

    /**
     * @brief getHealthPoint 获得生命点数
     * @return
     */
	int getHealthPoint();
    
	void setHealthPoint(int healthPoint);

	int getMaxHealthPoint();

	/**
	 * @brief isAlive 判断是否存活
	 * @return
	 */
	bool isAlive();

    /**
     * @brief setAttribute 设置生物的基本属性
     * @param strength
     * @param dexterity
     * @param wisdom
     * @return
     */
	bool setAttribute(int strength, int dexterity, int wisdom);

    /**
     * @brief damage 获得基础伤害值
     * @return
     */
	int damage();

	/**
	 * @brief damageWeaponed 带有武器的伤害值
	 * @return 返回int[2]，包含[最低伤害,最高伤害]
	 */
	int* damageWeaponed();

    /**
     * @brief dodgeChance 获得躲避概率，0为不可能躲避，100为一定躲避
     * @return
     */
	int dodgeChance();

	void setDescription(std::string description);

	std::string getDescription();

	/**
	 * @brief getWeapon 获得武器
	 */
    std::shared_ptr<core::weapons::Weapon> getWeapon();

	/**
	 * @brief setWeapon 设置武器
	 * @param weapon
	 */
	void setWeapon(std::shared_ptr<core::weapons::Weapon> weapon);

private:
  std::string _name;
  std::string _description;
  int _strength;
  int _dexterity;
  int _wisdom;
  int _health;
  int _maxHealth = -1;
  std::shared_ptr<core::weapons::Weapon> _weapon;
};

} // namespace creatures
} // namespace core

#endif // CREATURE_H
