#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <memory>
#include "creatures.h"
namespace core {

// TODO: define Character class.

/**
 * @brief TODO The Complete the Character class, following is just a small example
 */
class Character : public creatures::Creature
{
public:
    /**
     * @brief Character
     * @param name
     */
	Character(const std::string &name);

private:

};

} // namespace core

#endif // CHARACTER_H
