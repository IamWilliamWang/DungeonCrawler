#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <memory>
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
    Character(const std::string &name) : creatures::Creature(name) { }
private:
	
};

} // namespace core

//std::ostream& operator<<(std::ostream &stream, core::Character &character) {
//  stream << character.name();
//  return stream;
//}
#endif // CHARACTER_H
