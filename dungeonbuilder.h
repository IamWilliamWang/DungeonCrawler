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
    virtual Dungeon* buildDungeon() = 0;
    virtual Dungeon* clone(Dungeon*) = 0;
    virtual ~DungeonBuilder() = default;
};

class BasicDungeonBuilder : public DungeonBuilder
{
public:
    Dungeon* buildDungeon()
    {
        BasicDungeon *basicDungeon = new BasicDungeon();
        return (Dungeon*)basicDungeon;
    }
    Dungeon* clone(Dungeon* dungeon)
    {
        BasicDungeon* original = (BasicDungeon*)dungeon;
        BasicDungeon* newDungeon = new BasicDungeon();
        return (Dungeon*)newDungeon;
    }
};

}
}
#endif // DUNGEONBUILDER_H
