#include "Catcher.h"
#include "World.h"

#include <complex>

Point2D Catcher::Move(CatWorld* world)
{
  // Trick the cat --> Make cat resiliant to these traps
  // Create heuristic to trap the cat along a path
    std::vector<Point2D> pathway = generatePath(world);
    int placeInVector = 0;
    Point2D endPoint = pathway.at(placeInVector);
    Point2D desiredPoint;
    auto cat = world->getCat();

    float manhattanDist = std::abs(cat.x - endPoint.x) + std::abs(cat.y - endPoint.y);

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

    std::random_device rd;
    std::mt19937 gen(rd());
    Point2D randomPoint;
    while (!world->getContent(randomPoint) && !world->isValidPosition(randomPoint))
    {
      std::uniform_real_distribution<> dis(-world->getWorldSideSize(), world->getWorldSideSize());
      randomPoint = Point2D(dis(gen), dis(gen));
    }
  return randomPoint;
}
