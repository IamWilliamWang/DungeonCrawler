#ifndef GAME_H
#define GAME_H
#include <map>
#include <memory>
#include <random>
#include <string>
#include <ctime>
#include "room.h"
#include "character.h"
#include "dungeon.h"
#include "basicdungeon.h"
#include "magicaldungeon.h"
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
 * @brief The Game class represents a number of specific processing operations in the game
 */
class Game
{
public:
    // the Game class
    /**
     * @brief player Retrieves the player's Character, if any.
     */
    std::shared_ptr<Character> player();

    /**
     * @brief setPlayer Sets the current player character for the game.
     */
    void setPlayer(std::shared_ptr<Character> character);

    /**
     * @brief dungeon Returns the current dungeon level, if any.
     */
    std::shared_ptr<dungeon::Dungeon> dungeon();

    /**
     * @brief getBasicDungeon Casts the existing dungeon to basic dungeon and return
     * @return
     */
    std::shared_ptr<dungeon::BasicDungeon> getBasicDungeon();

    /**
     * @brief getMagicalDungeon Casts the existing dungeon to magical dungeon and return
     * @return
     */
    std::shared_ptr<dungeon::MagicalDungeon> getMagicalDungeon();

    /**
     * @brief createDungeon Initiates the creation of a new dungeon level.
     * Any previous dungeon level is destroyed.
     */
    bool createDungeon(std::string dungeonType = "BasicDungeon");

    /**
     * @brief start Initialises the game to the starting state, i.e.,
     * the character has just entered the first room of the dungeon.
     */
    bool enterDungeon();

    /**
     * @brief currentRoom Answers the current room the player's character is in.
     * @return the Room the player is in
     */
    std::shared_ptr<dungeon::Room> currentRoom();

    /**
     * @brief navigate Moves the game character to one direction
     * @param direction direction char of "NSWE"
     * @return
     */
    bool navigate(char direction);

    /**
     * @brief navigateBack Moves the character to the previous room.
     */
    bool navigateBack();

    /**
     * @brief exitLevel Updates the game state with successful completion
     * of the current level.
     */
    void exitLevel();

    /**
     * @brief exitDungeon Updates the game to the state where the character
     * has completely left the dungeon, ready for a completely new dungeon
     * to be created.
     */
    void exitDungeon();

    /**
     * @brief canDodge Determines if the creature can dodge this attack
     * @param creature creature
     * @return
     */
    bool canDodge(std::shared_ptr<creatures::Creature> creature);

    /**
     * @brief doActionRound Performs a player action (weapon attack, item use,
     * or special ability), including a responding attack by a creature if one is present.
     */
    void* doActionRound(char selection);

    /**
     * @brief setDungeon Forces to set dungeon
     * @param dungeon
     */
    void setDungeon(std::shared_ptr<dungeon::Dungeon> dungeon);

    /**
     * @brief getSuccessTimes Gets the number of levels explored completely
     * @return
     */
    int getSuccessTimes();

    /**
     * @brief instance Gets the singleton instance of Game class
     * @return
     */
    static std::shared_ptr<Game> instance();


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

private:
    Game();
    std::mt19937 _randomGenerator; // Mersenne Twister random number generator seeded by current time
    std::uniform_real_distribution<double> _realDistribution; // For random numbers between 0.0 & 1.0
    static std::shared_ptr<Game> _game; // singleton instance of Game class
    std::shared_ptr<dungeon::Dungeon> _dungeon; // currently available dungeon
    std::shared_ptr<Character> _character; // currently available player
    int _dungeonLevel = 1; // dungeon level's count
};

} // namespace core

#endif // GAME_H
