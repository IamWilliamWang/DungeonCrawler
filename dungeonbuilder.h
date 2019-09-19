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

/**
 * @brief The DungeonBuilder class
 */
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
     * @brief parseInt 转换字符串到整形
     * @param intStr
     * @return
     */
	int parseInt(std::string intStr);

    /**
     * @brief loadCreatures 加载所有满足条件的生物信息
     * @return
     */
	bool loadCreatures();

    /**
     * @brief loadWeapons 加载所有满足条件的武器信息
     * @return
     */
	bool loadWeapons();

    /**
     * @brief buildDungeon 构建地牢
     * @return
     */
	std::shared_ptr<Dungeon> buildDungeon();

    /**
     * @brief clone 克隆地牢
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
