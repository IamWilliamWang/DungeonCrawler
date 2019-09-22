#ifndef DUNGEON_H
#define DUNGEON_H
#include <map>
#include <memory>
#include <list>

namespace core {
namespace dungeon {

class Dungeon;
class Room; // predeclaration.

/*-----------------------------------------------------------------------------------
 * NOTE: to students - DO NOT modify or remove EXISTING members of this class.
 * You will need to ADD methods to this class to implement the gameplay requirements.
 *-----------------------------------------------------------------------------------*/

/**
 * @brief The Dungeon class represents the dungeon
 */
class Dungeon
{
public:
  /**
   * @brief BasicDungeon default constructor
   */
  Dungeon();

  /**
   * @brief copy constructor
   * @param oldDungeon old dungeon
   * @return the cloned dungeon
   */
  Dungeon(const Dungeon& oldDungeon);

  /**
   * @brief getEntranceRoom Gets the entrance room in this dungeon
   * @return
   */
  std::shared_ptr<Room> getEntranceRoom();

  /**
   * @brief getNowRoom Gets player's now room
   */
  std::shared_ptr<Room> getNowRoom();

  /**
   * @brief setNowRoom Sets player's now room
   * @param nowRoom
   */
  void setNowRoom(std::shared_ptr<Room> nowRoom);

  /**
   * @brief path Gets index-th room in the path the player has traveled
   * @param index Room index in the path (supporting negative index). 0 is not allowed here.
   * @return
   */
  std::shared_ptr<Room> path(int index);

  /**
   * @brief instanceOf Determines if it is an instance of this dungeon name
   * @param dungeonName dungeon name
   * @return If it is an instance of this dungeon name
   */
  bool instanceOf(std::string dungeonName);

  virtual ~Dungeon() = default;

protected:
    std::list<std::shared_ptr<Room>> _path; // the path the player has traveled
    std::shared_ptr<Room> _nowRoom; // player's now room
    std::string _dungeonType; // dungeon's type name

/*-----------------------------------------------------------------------------------
 * Original members below here, do not modify or remove them.
 *-----------------------------------------------------------------------------------*/

public:
  /**
   * @brief retrieveRoom Retrieve the room with the specified id.
   * @param id the room id to search for
   * @return a shared pointer to the Room or the nullptr if the no such Room exists
   */
  std::shared_ptr<Room> retrieveRoom(int id);

  /**
   * @brief addRoom Adds the new room to the dungeon.
   * @param newRoom the room to add
   * @return true if the room was added, false if a room with the same id was already present
   */
  bool addRoom(std::shared_ptr<Room> newRoom);

protected:
  std::map<int, std::shared_ptr<Room>> _rooms; // stores the rooms of the Dungeon
};

} // namespace dungeon
} // namespace core

#endif // DUNGEON_H
