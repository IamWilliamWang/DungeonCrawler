#ifndef GAME_H
#define GAME_H
#include <map>
#include <memory>
#include <random>
#include <string>
#include <ctime>
#include "character.h"
#include "dungeon.h"

namespace core {

/*-----------------------------------------------------------------------------------
 * NOTE: DO NOT modify or remove ALREADY IMPLEMENTED members of this class.
 * You will need to COMPLETE the implementations of the suggested skeleton functions
 * and/or ADD methods to this class to implement the gameplay requirements.
 *
 * To complete the implementations of the suggested functions you will need to
 * fix their return types and/or parameters.
 *
 * The incomplete functions are just suggestions and you are free to implement your
 * own as you see fit. Remember, though, the responsibility of the Game class is to
 * maintain and update the game state, so any member functions you implement must be
 * in fulfillment of that responsibility.
 *-----------------------------------------------------------------------------------*/

/**
 * @brief TODO The Game class
 */
class Game
{
public:

  // TODO implement the Game class
  

  /**
   * @brief player Retrieves the player's Character, if any.
   */
  std::shared_ptr<Character> player()
  {
	  return _character;
  }

  /**
   * @brief setPlayer Sets the current player character for the game.
   */
  void setPlayer(std::shared_ptr<Character> character)
  {
	  _character = character;
  }

  /**
   * @brief dungeon Returns the current dungeon level, if any.
   */
  std::shared_ptr<dungeon::Dungeon> dungeon()
  {
	  return _dungeon;
  }

  std::shared_ptr<dungeon::BasicDungeon> dungeon_basic() // ±ã½Ýº¯Êý
  {
	  return std::static_pointer_cast<dungeon::BasicDungeon>(_dungeon);
  }

  /**
   * @brief createDungeon Initiates the creation of a new dungeon level.
   * Any previous dungeon level is destroyed.
   */
  void createDungeon()
  {
	  _dungeon = std::make_shared<dungeon::BasicDungeon>();
  }

  /**
   * @brief start Initialises the game to the starting state, i.e.,
   * the character has just entered the first room of the dungeon.
   */
  void enterDungeon()
  {
	  auto basicDungeon = dungeon_basic();
	  basicDungeon->setNowRoom(basicDungeon->getEntranceRoom());
  }

  /**
   * @brief currentRoom Answers the current room the player's character is in.
   * @return the Room the player is in
   */
  auto currentRoom()
  {
	  return dungeon_basic()->getNowRoom();
  }

  /**
   * @brief navigate Move the player's character to a neighbouring
   * Room of the current room.
   */
  bool navigate(char direction)
  {
	  auto basic_dungeon = dungeon_basic();
	  auto room = currentRoom();
	  room->checkDirection(direction);
	  auto door = room->getDoor(direction);
	  if (door == nullptr)
		  return false;
	  basic_dungeon->setNowRoom(door->getNeighbourRoom(room));
	  return true;
  }

  /**
   * @brief navigateBack Move the character to the previous room.
   */
  bool navigateBack()
  {
	  auto basic_dungeon = dungeon_basic();
	  basic_dungeon->setNowRoom(basic_dungeon->path(-2));
  }

  /**
   * @brief exitLevel update the game state with successful completion
   * of the current level.
   */
  void exitLevel();

  /**
   * @brief exitDungeon update the game to the state where the character
   * has completely left the dungeon, ready for a completely new dungeon
   * to be created.
   */
  void exitDungeon();

  /**
   * @brief doActionRound Performs a player action (weapon attack, item use,
   * or special ability), including a responding attack by a creature if one is present.
   */
  void doActionRound();

  // Functions with provided implementations are declared below, DO NOT MODIFY

  /**
   * @brief randomIntBetween Returns a random integer between the provided min and max
   * values (inclusive). If max is smaller than low, the values are flipped to be safe.
   *
   * This function is a helper for randomly determining which types of room, item,
   * creature, etc., are present in a dungeon as well as determining damage values.
   *
   * @param min the low value
   * @param max the high value
   * @return the randomly generated integer
   */
  int randomIntBetweenInc(int min, int max);

  /**
   * @brief randomIntBetweenEx Returns a random integer between the provided min and max
   * values (exclusive). If max is smaller than low, the values are flipped to be safe.
   *
   * This function is a helper for randomly determining which types of room, item,
   * creature, etc., are present in a dungeon as well as determining damage values.
   *
   * @param min the low value
   * @param max the high value
   * @return the randomly generated integer
   */
  int randomIntBetweenEx(int min, int max);

  /**
   * @brief randomDouble Returns a random double in the range 0.0 - 1.0
   *
   * This function is a helper for determining whether an attack is dodged,
   * as the dodge chance is a percentage.
   *
   * @return the randomly generated double
   */
  double randomDouble();

  void setDungeon(std::shared_ptr<dungeon::Dungeon> dungeon)
  {
	  _dungeon = dungeon;
	  enterDungeon();
  }

  static std::shared_ptr<Game> instance()
  {
	  return _game;
  }

private:
  Game();
  std::mt19937 _randomGenerator; //!< Mersenne Twister random number generator seeded by current time
  std::uniform_real_distribution<double> _realDistribution; //!< For random numbers between 0.0 & 1.0
  static std::shared_ptr<Game> _game;
  std::shared_ptr<dungeon::Dungeon> _dungeon;
  std::shared_ptr<Character> _character;
};

} // namespace core

#endif // GAME_H
