#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <memory>
#include "creatures.h"
namespace core {

// TODO: define Character class.

/**
 * @brief The Character class represents the player
 */
class Character : public creatures::Creature
{
public:
    /**
     * @brief Character default constructor with Character's name
     * @param name character's name
     */
    Character(const std::string &name);

private:

};

} // namespace core

#endif // CHARACTER_H
