#ifndef DUNGEONBUILDER_H
#define DUNGEONBUILDER_H
#include <fstream>
#include <stdlib.h>
#include "dungeon.h"
#include "basicdungeon.h"
#include "csvfile.h"
namespace core {
namespace dungeon {

class Dungeon;

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
     * @brief parseInt
     * @param intStr
     * @return
     */
	int parseInt(std::string intStr);

    /**
     * @brief loadCreatures
     * @return
     */
	bool loadCreatures();

    /**
     * @brief loadWeapons
     * @return
     */
	bool loadWeapons();

    /**
     * @brief buildDungeon
     * @return
     */
	std::shared_ptr<Dungeon> buildDungeon();

    /**
     * @brief clone
     * @param dungeon
     * @return
     */
	std::shared_ptr<Dungeon> clone(std::shared_ptr<Dungeon> dungeon);

private:
	std::vector<std::shared_ptr<core::creatures::Creature>> _creatureList;
	std::vector<std::shared_ptr<core::weapons::Weapon>> _weaponList;
};
}
}
#endif // DUNGEONBUILDER_H
