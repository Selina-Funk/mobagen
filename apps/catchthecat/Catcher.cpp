#include "Catcher.h"
#include "World.h"

#include <complex>

enum Direction
{
  northEast,
  northWest,
  east,
  west,
  southEast,
  southWest
};

Point2D Catcher::Move(CatWorld* world)
{
  // Trick the cat --> Make cat resiliant to these traps
  // Create heuristic to trap the cat along a path
    std::vector<Point2D> pathway = generatePath(world);
    int placeInVector = 0;
    Point2D endPoint = pathway.at(placeInVector);
    Point2D desiredPoint;
    auto cat = world->getCat();
    int blockedNeighbors = 0;
    Direction dir = southWest;
    Point2D movementDir = (cat - pathway[pathway.size() - 1]);
    std::random_device rd;
    std::mt19937 gen(rd());

    float manhattanDist = std::abs(cat.x - endPoint.x) + std::abs(cat.y - endPoint.y);

  std::vector<Point2D> goodNeighbors;
    for (auto neighbor : world->neighbors(cat))
    {
      if (world->getContent(neighbor))
      {
        blockedNeighbors++;
        if (world->isValidPosition(neighbor)) goodNeighbors.push_back(neighbor);
      }
    }

    if (blockedNeighbors > 2)
    {
      if (movementDir == Point2D(0, 1)) dir = northEast;
      else if (movementDir == Point2D(-1, 1)) dir = northWest;
      else if (movementDir == Point2D(-1, 0)) dir = east;
      else if (movementDir == Point2D(1, 0)) dir = west;
      else if (movementDir == Point2D(1, 1)) dir = southWest;
      else if (movementDir == Point2D(0, -1)) dir = southEast;

      switch (dir)
      {
        case northEast:
          if (world->isValidPosition(CatWorld::NE(cat)))
          {
            if (!world->getContent(CatWorld::NE(cat)))
            {
              world->lastMove = CatWorld::NE(cat);
              return CatWorld::NE(cat);
            }
          }
        case northWest:
          if (world->isValidPosition(CatWorld::NW(cat)))
          {
            if (!world->getContent(CatWorld::NW(cat)))
            {
              world->lastMove = CatWorld::NW(cat);
              return CatWorld::NW(cat);
            }
          }
        case east:
          if ( world->isValidPosition(CatWorld::E(cat)))
          {
            if (!world->getContent(CatWorld::E(cat)))
            {
              world->lastMove = CatWorld::E(cat);
              return CatWorld::E(cat);
            }
          }
        case west:
          if ( world->isValidPosition(CatWorld::W(cat)))
          {
            if (!world->getContent(CatWorld::W(cat)))
            {
              world->lastMove = CatWorld::W(cat);
              return CatWorld::W(cat);
            }
          }
        case southWest:
          if (world->isValidPosition(CatWorld::SW(cat)))
          {
            if (!world->getContent(CatWorld::SW(cat)))
            {
              world->lastMove = CatWorld::SW(cat);
              return CatWorld::SW(cat);
            }
          }
        case southEast:
          if (world->isValidPosition(CatWorld::SE(cat)))
          {
            if (!world->getContent(CatWorld::SE(cat)))
            {
              world->lastMove = CatWorld::SE(cat);
              return CatWorld::SE(cat);
            }
          }
        default:
          break;
      }
    }

    if (manhattanDist <= 4 && !world->getContent(endPoint))
    {
      if (cat != endPoint)
      {
        return endPoint;
      }
    }

    while (desiredPoint != cat)
    {
      if (!world->getContent(Point2D(endPoint.x - 1, endPoint.y)) && world->isValidPosition(Point2D(endPoint.x - 1, endPoint.y)))
      {
        desiredPoint = Point2D(endPoint.x - 1, endPoint.y);
        return desiredPoint;
      }
      else if (!world->getContent(Point2D(endPoint.x + 1, endPoint.y)) && world->isValidPosition(Point2D(endPoint.x + 1, endPoint.y)))
      {
        desiredPoint = Point2D(endPoint.x + 1, endPoint.y);
        return desiredPoint;
      }
      placeInVector++;
      if (placeInVector >= pathway.size()) break;
      endPoint = pathway.at(placeInVector);
    }

    std::vector<Point2D> neighbors = world->neighbors(cat);
    for (auto neighbor : neighbors)
    {
      if (!world->getContent(neighbor) && !std::ranges::contains(pathway, neighbor) && world->isValidPosition(neighbor))
      {
        desiredPoint = neighbor;
        return desiredPoint;
      }
    }

    Point2D randomPoint;
    while (!world->getContent(randomPoint) && !world->isValidPosition(randomPoint))
    {
      std::uniform_real_distribution<> dis(-world->getWorldSideSize(), world->getWorldSideSize());
      randomPoint = Point2D(dis(gen), dis(gen));
    }
  return randomPoint;
}
