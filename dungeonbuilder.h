#ifndef DUNGEONBUILDER_H
#define DUNGEONBUILDER_H
#include "dungeon.h"
#include "basicdungeon.h"
namespace core {
namespace dungeon {

class DungeonBuilder
{
public:
    /**
     * @brief buildDungeon 创建牢笼
     * @return
     */
    virtual std::shared_ptr<Dungeon> buildDungeon() = 0;
    /**
     * @brief clone 克隆牢笼
     * @return
     */
    virtual std::shared_ptr<Dungeon> clone(std::shared_ptr<Dungeon>) = 0;
    virtual ~DungeonBuilder() = default;
};

class BasicDungeonBuilder : public DungeonBuilder
{
public:
    /**
     * @brief buildDungeon
     * @return
     */
    std::shared_ptr<Dungeon> buildDungeon()
    {
		// create objects
        auto basicDungeon = std::make_shared<BasicDungeon>();
		auto room1 = std::make_shared<Room>(1);
		auto room2 = std::make_shared<Room>(2);
		auto room3 = std::make_shared<Room>(3);
		auto room4 = std::make_shared<Room>(4);
		auto room5 = std::make_shared<Room>(5);
		auto room6 = std::make_shared<Room>(6);
		auto room7 = std::make_shared<Room>(7);
		auto room8 = std::make_shared<Room>(8);
		auto room9 = std::make_shared<Room>(9);
		auto door12 = std::make_shared<Door>(room1, room2);
		auto door14 = std::make_shared<Door>(room1, room4);
		auto door25 = std::make_shared<Door>(room2, room5);
		auto door36 = std::make_shared<Door>(room3, room6);
		auto door45 = std::make_shared<Door>(room4, room5);
		auto door56 = std::make_shared<Door>(room5, room6);
		auto door58 = std::make_shared<Door>(room5, room8);
		auto door78 = std::make_shared<Door>(room7, room8);
		auto door89 = std::make_shared<Door>(room8, room9);
		// fill room1
		room1->addEntranceOrExit('N', true);
		room1->addDoor('S', door14);
		room1->addWall('W');
		room1->addDoor('E', door12);
		// fill room2
		room2->addWall('N');
		room2->addDoor('S', door25);
		room2->addDoor('W', door12);
		room2->addWall('E');
		// fill room3
		room3->addWall('N');
		room3->addDoor('S', door36);
		room3->addWall('W');
		room3->addWall('E');
		// fill room4
		room4->addDoor('N', door14);
		room4->addWall('S');
		room4->addWall('W');
		room4->addDoor('E', door45);
		// fill room5
		room5->addDoor('N', door25);
		room5->addDoor('S', door58);
		room5->addDoor('W', door45);
		room5->addDoor('E', door56);
		// fill room6
		room6->addDoor('N', door36);
		room6->addWall('S');
		room6->addDoor('W', door56);
		room6->addWall('E');
		// fill room7
		room7->addWall('N');
		room7->addWall('S');
		room7->addWall('W');
		room7->addDoor('E', door78);
		// fill room8
		room8->addDoor('N', door58);
		room8->addWall('S');
		room8->addDoor('W', door78);
		room8->addDoor('E', door89);
		// fill room9
		room9->addWall('N');
		room9->addWall('S');
		room9->addDoor('W', door89);
		room9->addEntranceOrExit('E', false);
		// add rooms into dungeon
        basicDungeon->addRoom(room1);
        basicDungeon->addRoom(room2);
        basicDungeon->addRoom(room3);
        basicDungeon->addRoom(room4);
        basicDungeon->addRoom(room5);
        basicDungeon->addRoom(room6);
        basicDungeon->addRoom(room7);
        basicDungeon->addRoom(room8);
        basicDungeon->addRoom(room9);
        return std::static_pointer_cast<Dungeon>(basicDungeon);
    }
    /**
     * @brief clone
     * @param dungeon
     * @return
     */
    std::shared_ptr<Dungeon> clone(std::shared_ptr<Dungeon> dungeon)
    {
        // NOT IMPLEMENTED
        return nullptr;
    }
private:
	std::vector<std::shared_ptr<core::creatures::Creature>> creatureList;
	std::vector<std::shared_ptr<core::weapons::Weapon>> weaponList;
	std::vector<std::shared_ptr<core::dungeon::Chamber>> chamberList;
};
}
}
#endif // DUNGEONBUILDER_H
