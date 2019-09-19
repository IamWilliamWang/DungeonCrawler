#ifndef DUNGEON_H
#define DUNGEON_H
#include <map>
#include <memory>

namespace core {
namespace dungeon {

class Room;

/*-----------------------------------------------------------------------------------
 * NOTE: to students - DO NOT modify or remove EXISTING members of this class.
 * You will need to ADD methods to this class to implement the gameplay requirements.
 *-----------------------------------------------------------------------------------*/

/**
 * @brief The Dungeon class
 */
class Dungeon
{
public:
  Dungeon();
  virtual ~Dungeon() = default;

private:
//  int _anotherMember; //!< replace this with something real


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
  std::map<int, std::shared_ptr<Room>> _rooms; //!< stores the rooms of the Dungeon
};

} // namespace dungeon
} // namespace core

#endif // DUNGEON_H
