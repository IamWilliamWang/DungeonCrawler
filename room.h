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
 * @brief The Room class
 */
class Room
{
public:
    /**
     * @brief Room 创建房间
     * @param id
     */
	Room(int id);

	/**
	* @brief id Returns the unique integer id of the Room.
	* @return the unique id
	*/
	int id();

    /**
     * @brief addWall 给Room的某个方向增加一堵墙
     * @param direction
     * @param wall
     * @return
     */
    bool addWall(char direction, std::shared_ptr<Wall> wall = std::make_shared<Wall>());

    /**
     * @brief addDoor 给Room的某个方向增加一扇门
     * @param direction
     * @param door
     * @return
     */
	bool addDoor(char direction, std::shared_ptr<Door> door);

    /**
     * @brief getDoor 获得Room特定位置上的门
     * @param direction
     * @return
     */
	std::shared_ptr<dungeon::Door> getDoor(char direction);
    
    /**
     * @brief findDoorDirections 找门所在的方向，返回char list
     * @return
     */
	std::list<char> findDoorDirections();

	/**
	 * @brief getDoorDirections findDoorDirections便捷函数，开发结束时会删除
	 * @return
	 */
    std::list<char> getDoorDirections();

    /**
     * @brief existEntranceOrExit 如果存在入口或者出口
     * @return
     */
	bool existEntranceOrExit();

    /**
     * @brief addEntranceOrExit 为房间添加入口或者出口
     * @param direction 需要添加的方向
     * @param addEntrance 是否要添加的是入口
     */
	void addEntranceOrExit(char direction, bool addEntrance);

    /**
     * @brief getEntranceDirection 获得入口所在的方向
     * @return
     */
	char getEntranceDirection();

    /**
     * @brief getExitDirection 获得出口所在的方向
     * @return
     */
	char getExitDirection();

    /**
     * @brief checkDirection 检查方向char是否合法
     * @param direction
     * @return
     */
	bool checkDirectionVaild(char& direction);

    /**
     * @brief createCreature 使用可能的生物列表随机创建生物
     * @param possibleCreatures
     * @return
     */
	bool createCreature(std::vector<std::shared_ptr<core::creatures::Creature>> possibleCreatures);

    /**
     * @brief createWeapon 根据武器列表为房间随机添加一个武器
     * @param possibleWeapons
     * @return
     */
	bool createWeapon(std::vector<std::shared_ptr<core::weapons::Weapon>> possibleWeapons);

    /**
     * @brief getCreature 获得房间内的生物
     * @return
     */
    std::shared_ptr<core::creatures::Creature> getCreature();

    /**
     * @brief setCreature 设置房间内的生物
     * @param creature
     */
	void setCreature(std::shared_ptr<core::creatures::Creature> creature);

    /**
     * @brief getWeapon 获得房间内的武器（或生物手持的武器）
     * @return
     */
    std::shared_ptr<core::weapons::Weapon> getWeapon();

    /**
     * @brief setWeapon 设置房间内的武器
     * @param weapon
     */
    void setWeapon(std::shared_ptr<core::weapons::Weapon> weapon);

private:
	/**
	 * @brief setEntrance 设置Room的特定方向为牢笼入口
	 * @param direction
	 * @return
	 */
	bool setEntrance(char direction);

	/**
	 * @brief setExit 设置Room的特定方向为牢笼出口
	 * @param direction
	 * @return
	 */
	bool setExit(char direction);

    int _id;
    std::map<char, std::shared_ptr<Wall>> _walls; // the walls of this room
    std::map<char, std::shared_ptr<Door>> _doors;
    std::map<char, std::string> _entranceOrExit; // save the direction of entrance or exit in this room
	std::shared_ptr<core::creatures::Creature> _creature; 
    std::shared_ptr<core::weapons::Weapon> _weapon;
};

} // namespace dungeon
} // namespace core


#endif // ROOM_H
