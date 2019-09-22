#ifndef ROOM_H
#define ROOM_H
#include <map>
#include <memory>
#include <list>
#include <vector>
#include "creatures.h"
#include "weapons.h"
#include "wall.h"

namespace core {
namespace dungeon {

class Wall;
class Door; //predeclaration

/**
 * @brief The Room class represents room
 */
class Room
{
public:
    /**
     * @brief Room Create room with specific id
     * @param id
     */
	Room(int id);

	/**
	* @brief id Returns the unique integer id of the Room.
	* @return the unique id
	*/
	int id();

    /**
     * @brief addWall Adds a wall at specific direcion in this room
     * @param direction direction
     * @param wall a new wall
     * @return
     */
    bool addWall(char direction, std::shared_ptr<Wall> wall = std::make_shared<Wall>());

    /**
     * @brief addDoor Adds a door at specific direcion in this room
     * @param direction direction
     * @param door a door connecting the other rooms
     * @return
     */
	bool addDoor(char direction, std::shared_ptr<Door> door);

    /**
     * @brief getDoor Gets the door at specific direction in this room
     * @param direction direction
     * @return found door
     */
	std::shared_ptr<dungeon::Door> getDoor(char direction);
    
    /**
     * @brief getDoorDirections Finds the direction of the doors
     * @return a char list contains directions
     */
    std::list<char> getDoorDirections();

    /**
     * @brief existEntranceOrExit If there is an entrance or exit
     * @return
     */
	bool existEntranceOrExit();

    /**
     * @brief addEntranceOrExit Adds an entrance or exit to this room
     * @param direction The direction that needs to be added
     * @param addEntrance Whether to add is the entrance
     */
	void addEntranceOrExit(char direction, bool addEntrance);

    /**
     * @brief getEntranceDirection Gets the direction of the entrance in this room
     * @return
     */
	char getEntranceDirection();

    /**
     * @brief getExitDirection Gets the direction of the exit in this room
     * @return
     */
	char getExitDirection();

    /**
     * @brief checkDirectionVaild Checks whether the direction char is valid
     * @param direction direction char
     * @return
     */
	bool checkDirectionVaild(char& direction);

    /**
     * @brief createCreature Creates a creature at random using a list of possible creatures
     * @param possibleCreatures possible creatures list
     * @return
     */
	bool createCreature(std::vector<std::shared_ptr<core::creatures::Creature>> possibleCreatures);

    /**
     * @brief createWeapon Creates a creature at random using a list of possible weapons
     * @param possibleWeapons possible weapons list
     * @return
     */
	bool createWeapon(std::vector<std::shared_ptr<core::weapons::Weapon>> possibleWeapons);

    /**
     * @brief getCreature Gets the creature in this room
     * @return
     */
    std::shared_ptr<core::creatures::Creature> getCreature();

    /**
     * @brief setCreature Sets the creature in this room
     * @param creature
     */
	void setCreature(std::shared_ptr<core::creatures::Creature> creature);

    /**
     * @brief getWeapon Gets weapons in the room (or weapons held by creature)
     * @return
     */
    std::shared_ptr<core::weapons::Weapon> getWeapon();

    /**
     * @brief setWeapon Places weapon in the room and cover them if weapon is already there
     * @param weapon
     */
    void setWeapon(std::shared_ptr<core::weapons::Weapon> weapon);

private:
	/**
     * @brief setEntrance Sets the specific direction of the Room as the dungeon's entrance
     * @param direction direction
	 * @return
	 */
	bool setEntrance(char direction);

	/**
     * @brief setExit Sets the specific direction of the Room as the dungeon's exit
     * @param direction direction
	 * @return
	 */
	bool setExit(char direction);

    int _id; // room's id
    std::map<char, std::shared_ptr<Wall>> _walls; // the walls of this room
    std::map<char, std::shared_ptr<Door>> _doors; // the doors of this room
    std::map<char, std::string> _entranceOrExit; // the direction of entrance or exit in this room
    std::shared_ptr<core::creatures::Creature> _creature; // the creature in this room
    std::shared_ptr<core::weapons::Weapon> _weapon; // the weapon in this room
};

} // namespace dungeon
} // namespace core
#endif // ROOM_H
