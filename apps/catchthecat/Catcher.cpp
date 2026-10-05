#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(CatWorld* world)
{
    std::vector<Point2D> pathway = generatePath(world);
    Point2D p = pathway.at(0);
    auto cat = world->getCat();
    if (!(cat == p) && !world->getContent(p)) return p;
}
