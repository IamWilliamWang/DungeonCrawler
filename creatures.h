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
  Creature(const std::string &name);

  const std::string& name() const;
  int getStrength() { return _strength; }
  int getDexterity() { return _dexterity; }
  int getWisdom() { return _wisdom; }
  int getHealthPoint() { return _health; }
  bool setAttribute(int strength, int dexterity, int wisdom);
  int damage();
  int dodgeChance();

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
