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
