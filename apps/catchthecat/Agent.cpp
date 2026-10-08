#include "Agent.h"
#include <climits>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include "World.h"

using namespace std;

std::vector<Point2D> Agent::getVisitableNeighbors(Point2D point, CatWorld* w)
{
  std::vector<Point2D> neighbors;
  for (auto neighbor : w->neighbors(point))
  {
    if (w->isValidPosition(neighbor))
    {
      if (neighbor != w->getCat() && !w->getContent(neighbor))
      {
        neighbors.push_back(neighbor);
      }
    }
  }
  return neighbors;
}

std::vector<Point2D> Agent::generatePath(CatWorld* w) {
  unordered_map<Point2D, Point2D> cameFrom;  // to build the flowfield and build the path 1ST = LOCATION; 2ND = WHERE IT CAME FROM
  queue<Point2D> frontier;                   // to store next ones to visit
  unordered_set<Point2D> frontierSet;        // OPTIMIZATION to check faster if a point is in the queue
  unordered_map<Point2D, bool> visited;      // use .at() to get data, if the element dont exist [] will give you wrong results
  int shortestValue = 1000;
  Point2D shortestPoint;

  // bootstrap state
  auto catPos = w->getCat();
  Point2D currentPos;
  frontier.emplace(catPos);
  frontierSet.insert(catPos);
  Point2D borderExit = {w->getWorldSideSize(), w->getWorldSideSize()};
  bool earlyBreak = false;

  while (!frontier.empty())
  {
    // get the current from frontier
    // remove the current from frontierset
    // mark current as visited
    // iterate over the neighs:
    // for every neighbor set the cameFrom
    // enqueue the neighbors to frontier and frontierset
    // do this up to find a visitable border and break the loop
    currentPos = frontier.front();
    frontier.pop();
    frontierSet.erase(currentPos);
    visited[currentPos] = true;
    vector<Point2D> neighbors = getVisitableNeighbors(currentPos, w);

    for (auto neighbor : neighbors)
    {
      if (!w->getContent(neighbor) && !visited.contains(neighbor) && !frontierSet.contains(neighbor))
      {
        cameFrom[neighbor] = currentPos;
        frontier.emplace(neighbor);
        frontierSet.insert(neighbor);
        if (w->catWinsOnSpace(neighbor))
        if (std::min((w->getWorldSideSize()/2 - std::abs(catPos.x)), (w->getWorldSideSize()/2 - std::abs(catPos.y))) < shortestValue)
        {
          shortestValue = std::min((w->getWorldSideSize()/2 - std::abs(catPos.x)), (w->getWorldSideSize()/2 - std::abs(catPos.y)));
          shortestPoint = neighbor;
        }
      }
    }
  }

  // if the border is not infinity, build the path from border to the cat using the camefrom map
  // if there isnt a reachable border, just return empty vector
  // if your vector is filled from the border to the cat, the first element is the catcher move, and the last element is the cat move
  if (borderExit.x != INT32_MAX || borderExit.y != INT32_MAX)
  {
    vector<Point2D> path;
    path.push_back(shortestPoint);
    Point2D startPos = shortestPoint;

    while (cameFrom.contains(startPos))
    {
      if (cameFrom[startPos] == catPos) break;
      path.push_back(cameFrom[startPos]);
      startPos = cameFrom[startPos];
    }
    return path;
  }
  return vector<Point2D>();
}