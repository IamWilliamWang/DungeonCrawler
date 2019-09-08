#ifndef DUNGEONBUILDER_H
#define DUNGEONBUILDER_H
#include "dungeon.h"
#include "basicdungeon.h"
namespace core {
namespace dungeon {

class DungeonBuilder
{
public:
    DungeonBuilder();
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
        return std::make_shared<BasicDungeon>();
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
};

}
}
#endif // DUNGEONBUILDER_H
