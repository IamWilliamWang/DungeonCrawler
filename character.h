#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "creatures.h"
namespace core {

// TODO: define Character class.
// There is some example code in here, but it can be modified if desired.

/**
 * @brief TODO The Complete the Character class, following is just a small example
 */
class Character : public core::creatures::Creature
{
public:
  Character(const std::string &name);

private:

};

} // namespace core

std::ostream& operator<<(std::ostream &stream, const core::Character &character);

#endif // CHARACTER_H
