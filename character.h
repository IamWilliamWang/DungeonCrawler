#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <memory>
#include "creatures.h"
#include "room.h"
#include "basicdungeon.h"
#include "weapons.h"
namespace core {

// TODO: define Character class.
// There is some example code in here, but it can be modified if desired.

/**
 * @brief TODO The Complete the Character class, following is just a small example
 */
class Character : public creatures::Creature
{
public:
    Character(const std::string &name) : creatures::Creature(name) 
	{
		_weapon = std::make_shared<weapons::Fists>();
	}
    /**
     * @brief damageWeaponed 带有武器的伤害值
     * @return 返回int[2]，包含[最低伤害,最高伤害]
     */
	int* damageWeaponed()
	{
		int* result = _weapon->getDamageRange();
		result[0] += damage();
		result[1] += damage();
		return result;
	}
    /**
     * @brief getWeapon 获得武器
     */
	auto getWeapon()
	{
		return _weapon;
	}
    /**
     * @brief setWeapon 设置武器
     * @param weapon
     */
	void setWeapon(std::shared_ptr<weapons::Weapon> weapon)
	{
		_weapon = weapon;
	}
private:
	std::shared_ptr<weapons::Weapon> _weapon;
};

} // namespace core

//std::ostream& operator<<(std::ostream &stream, core::Character &character) {
//  stream << character.name();
//  return stream;
//}
#endif // CHARACTER_H
