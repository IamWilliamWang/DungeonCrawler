#ifndef DUNGEON_H
#define DUNGEON_H
#include <map>
#include <memory>
#include <list>
#include "commondungeon.h"

namespace core {
namespace dungeon {

class Dungeon;
class Room; // predeclaration.

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
  /**
	 * @brief BasicDungeon ��������
	 */
  Dungeon();

  /**
   * @brief ���ƹ��캯��
   * @param nowRoom
   */
  Dungeon(const Dungeon& oldDungeon);

  /**
   * @brief getEntranceRoom �����������ʼRoom
   * @return
   */
  std::shared_ptr<Room> getEntranceRoom();

  /**
   * @brief getNowRoom ��õ�ǰ������ڵ�Room
   */
  std::shared_ptr<Room> getNowRoom();

  /**
   * @brief setNowRoom ���õ�ǰ������ڵ�Room
   * @param nowRoom
   */
  void setNowRoom(std::shared_ptr<Room> nowRoom);

  /**
   * @brief path ����߹�·���ϵڼ���Room��index�����ɸ�
   * @param index
   * @return
   */
  std::shared_ptr<Room> path(int index);

  virtual ~Dungeon() = default;

protected:
	std::list<std::shared_ptr<Room>> _path;
	std::shared_ptr<Room> _nowRoom;

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
