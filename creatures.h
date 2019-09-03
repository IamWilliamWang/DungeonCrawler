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

    const std::string& name() {return _name; }
    int getStrength() { return _strength; }
    int getDexterity() { return _dexterity; }
    int getWisdom() { return _wisdom; }
    int getHealthPoint() { return _health; }
    bool isAlive(){ return _health > 0; }

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

    int damage()
    {
      return 2*(_strength-1);
    }

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
