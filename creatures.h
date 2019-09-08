#ifndef CREATURE_H
#define CREATURE_H
#include <string>

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
    Creature(const std::string &name) : _name(name){}
    /**
     * @brief name 获得生物的名字
     * @return
     */
    const std::string& name() {return _name; }
    /**
     * @brief getStrength 获得力量值
     * @return
     */
    int getStrength() { return _strength; }
    /**
     * @brief getDexterity 获得敏捷值
     * @return
     */
    int getDexterity() { return _dexterity; }
    /**
     * @brief getWisdom 获得智力值
     * @return
     */
    int getWisdom() { return _wisdom; }
    /**
     * @brief getHealthPoint 获得生命点数
     * @return
     */
    int getHealthPoint() { return _health; }
    /**
     * @brief isAlive 判断是否存活
     * @return
     */
    bool isAlive(){ return _health > 0; }
    /**
     * @brief setAttribute 设置生物的基本属性
     * @param strength
     * @param dexterity
     * @param wisdom
     * @return
     */
    bool setAttribute(int strength, int dexterity, int wisdom)
    {
      if(strength < 1 || strength > 6)
          return false;
      if(dexterity < 1 || dexterity > 6)
          return false;
      if(wisdom < 1 || wisdom > 6)
          return false;
      _strength = strength;
      _dexterity = dexterity;
      _wisdom = wisdom;
      _health = 50;
      return true;
    }
    /**
     * @brief damage 获得基础伤害值
     * @return
     */
    int damage()
    {
      return 2*(_strength-1);
    }
    /**
     * @brief dodgeChance 获得躲避概率，0为不可能躲避，100为一定躲避
     * @return
     */
    int dodgeChance()
    {
		return _dexterity > 0 ? 20 * (_dexterity - 1) : 0;
    }

private:
  std::string _name;
  int _strength;
  int _dexterity;
  int _wisdom;
  int _health = -1;
};

} // namespace creatures
} // namespace core

#endif // CREATURE_H
