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
  auto pos = world->getCat();
  std::vector<Point2D> path = generatePath(world);
  auto movePosition = path[path.size() - 1];
  int numberOfBlockedTiles = 0;

  Direction dir = southWest;
  Point2D movementDir = (pos - path[path.size() - 1]);

  for (auto neighbor : world->neighbors(pos))
  {
    if (world->isValidPosition(neighbor))
    {
      if (world->catWinsOnSpace(neighbor) && !world->getContent(neighbor))
      {
        world->lastMove = movePosition;
        return neighbor;
      }
    }
  }

  for (auto neighbor : world->neighbors(path[0]))
  {
    if (world->isValidPosition(neighbor))
    {
      if (world->getContent(neighbor))
      {
        numberOfBlockedTiles++;
      }
    }
  }

  std::vector<Point2D> availableNeighbors;
  std::random_device rd;
  std::mt19937 gen(rd());

  for (auto neighbor : world->neighbors(pos))
  {
    if (world->isValidPosition(neighbor)) availableNeighbors.push_back(neighbor);
  }

  std::uniform_real_distribution<> dis(0, availableNeighbors.size() - 1);


  if (availableNeighbors.capacity() < 4)
  {
    return availableNeighbors[dis(gen)];
  }

  if (movementDir == Point2D(0, 1)) dir = northEast;
  else if (movementDir == Point2D(-1, 1)) dir = northWest;
  else if (movementDir == Point2D(-1, 0)) dir = east;
  else if (movementDir == Point2D(1, 0)) dir = west;
  else if (movementDir == Point2D(1, 1)) dir = southWest;
  else if (movementDir == Point2D(0, -1)) dir = southEast;

  if (numberOfBlockedTiles >= 3)
  {
    switch (dir) {
      case northEast:
        if (world->isValidPosition(CatWorld::SW(pos)))
        {
          if (!world->getContent(CatWorld::SW(pos)))
          {
            world->lastMove = CatWorld::SW(pos);
            return CatWorld::SW(pos);
          }
        }
      case northWest:
        if (world->isValidPosition(CatWorld::SE(pos)))
        {
          if (!world->getContent(CatWorld::SE(pos)))
          {
            world->lastMove = CatWorld::SE(pos);
            return CatWorld::SE(pos);
          }
        }
      case east:
        if ( world->isValidPosition(CatWorld::W(pos)))
        {
          if (!world->getContent(CatWorld::W(pos)))
          {
            world->lastMove = CatWorld::W(pos);
            return CatWorld::W(pos);
          }
        }
      case west:
        if ( world->isValidPosition(CatWorld::E(pos)))
        {
          if (!world->getContent(CatWorld::E(pos)))
          {
            world->lastMove = CatWorld::E(pos);
            return CatWorld::E(pos);
          }
        }
      case southWest:
        if (world->isValidPosition(CatWorld::NE(pos)))
        {
          if (!world->getContent(CatWorld::NE(pos)))
          {
            world->lastMove = CatWorld::NE(pos);
            return CatWorld::NE(pos);
          }
        }
      case southEast:
        if (world->isValidPosition(CatWorld::NW(pos)))
        {
          if (!world->getContent(CatWorld::NW(pos)))
          {
            world->lastMove = CatWorld::NW(pos);
            return CatWorld::NW(pos);
          }
        }
      default:
        break;
    }
  }

  world->lastMove = movePosition;
  return movePosition;
}
