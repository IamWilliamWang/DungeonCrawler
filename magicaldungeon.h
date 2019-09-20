#ifndef MAGICALDUNGEON_H
#define MAGICALDUNGEON_H
#include "commondungeon.h"
#include "dungeon.h"
namespace core {
namespace dungeon {

// TODO: define component classes spcific to the MagicalDungeon type

/**
 * @brief The MagicalDungeon class
 */
class MagicalDungeon : public Dungeon
{
public:
   /**
	* @brief BasicDungeon 基础牢笼
	*/
	MagicalDungeon();

private:

};

/**
 * @brief TODO The EnchantedLibrary class
 */
class EnchantedLibrary
{
public:
 /**
  * @brief EnchantedLibrary
  */
  EnchantedLibrary();
};

/**
 * @brief TODO The AlchemistsLaboratory class
 */
class AlchemistsLaboratory
{
public:
/**
 * @brief AlchemistsLaboratory
 */
  AlchemistsLaboratory();
};

/**
 * @brief TODO The MagicWall class
 */
class MagicWall
{
public:
/**
 * @brief MagicWall
 */
  MagicWall();
};

} // namespace dungeon
} // namespace core

#endif // MAGICALDUNGEON_H
