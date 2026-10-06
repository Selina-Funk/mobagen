#include "Cat.h"
#include "World.h"
#include <stdexcept>

enum Direction
{
  northEast,
  northWest,
  east,
  west,
  southEast,
  southWest
};

Point2D Cat::Move(CatWorld* world) {
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();
  std::vector<Point2D> path = generatePath(world);
  auto endPosition = path[path.size() - 1];
  int numberOfBlockedTiles = 0;
  Direction dir;

  for (auto neighbor : world->neighbors(pos)) {
    std::cout << neighbor.x << ", " << neighbor.y << std::endl;
  }

  Point2D movementDir = (pos - path[path.size() - 1]);
  if (movementDir == Point2D(0, 1)) dir = northEast;
  else if (movementDir == Point2D(1, 1)) dir = northWest;
  else if (movementDir == Point2D(-1, 0)) dir = east;
  else if (movementDir == Point2D(1, 0)) dir = west;
  else if (movementDir == Point2D(0, -1)) dir = southWest;
  else if (movementDir == Point2D(1, -1)) dir = southEast;

  for (auto neighbor : world->neighbors(endPosition))
  {
    if (world->getContent(neighbor))
    {
      numberOfBlockedTiles++;
    }
  }

  if (numberOfBlockedTiles >= 3)
  {
    switch (dir) {
      case northEast:
        if (!world->getContent(CatWorld::SW(pos))) return CatWorld::SW(pos);
      case northWest:
        if (!world->getContent(CatWorld::SE(pos))) return CatWorld::SE(pos);
      case east:
        if (!world->getContent(CatWorld::W(pos))) return CatWorld::W(pos);
      case west:
        if (!world->getContent(CatWorld::E(pos))) return CatWorld::E(pos);
      case southWest:
        if (!world->getContent(CatWorld::NE(pos))) return CatWorld::NE(pos);
      case southEast:
        if (!world->getContent(CatWorld::NW(pos))) return CatWorld::NW(pos);
      default:
        throw std::runtime_error("random out of range");
    }
  }

  return path[path.size() - 1];
}
