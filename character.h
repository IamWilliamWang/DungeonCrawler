#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

namespace core {

// TODO: define Character class.
// There is some example code in here, but it can be modified if desired.

/**
 * @brief TODO The Complete the Character class, following is just a small example
 */
class Character
{
public:
  Character(const std::string &name);

  const std::string& name() const;

private:
  std::string _name;
};

} // namespace core

std::ostream& operator<<(std::ostream &stream, const core::Character &character);

#endif // CHARACTER_H
