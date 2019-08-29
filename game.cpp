#include "game.h"
#include "testingsettings.h"
#include <sstream>

using namespace core;

// TODO: Add additional implementation here



// Do not change/remove the initialisation of _randomGenerator and _realDistribution, otherwise change as needed.
Game::Game()
  : _randomGenerator{uint32_t(time(nullptr))}, _realDistribution{0.0, 1.0}
{

}

// DO NOT modify implementation below this comment

int Game::randomIntBetweenInc(int min, int max) {
#if INPUT_SCRIPT
  return min; // for consistency when using the input script
#else
  if (min == max) return max;
  if (max < min) std::swap(min, max);

  int diff{max + 1 - min};
  return int(_randomGenerator() % unsigned(diff)) + min;
#endif
}

int Game::randomIntBetweenEx(int min, int max) {
#if INPUT_SCRIPT
  return max - 1; // for consistency when using the input script
#else
  if (min == max) return max; // technically invalid for an exclusive range
  if (max < min) std::swap(min, max);

  int diff{max - min};
  return int(_randomGenerator() % unsigned(diff)) + min;
#endif
}

double Game::randomDouble() {
#if INPUT_SCRIPT
  return 1.0; // for consistency when using the input script.
#else
  return _realDistribution(_randomGenerator);
#endif
}
