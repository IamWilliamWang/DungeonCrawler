#include "character.h"
using core::Character;

Character::Character(const std::string &name)
  : core::creatures::Creature (name)
{

}

//std::ostream& operator<<(std::ostream &stream, const Character &character) {
//  stream << character.name();
//  return stream;
//}
