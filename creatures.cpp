#include "creatures.h"

using namespace core::creatures;

/* ------------------------------------------------------------------------------
 * Creature member implementations
 * -----------------------------------------------------------------------------*/

Creature::Creature(const std::string &name)
  : _name{name}
{

}

const std::string& Creature::name() const {
  return _name;
}

bool Creature::setAttribute(int strength, int dexterity, int wisdom)
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

int Creature::damage()
{
    return 2*(_strength-1);
}

int Creature::dodgeChance()
{
    return 20*(_dexterity-1);
}
