#include "CohesionRule.h"
#include <glm/glm.hpp>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 cohesionForce(0.0F);

  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.

  // begin solution

  glm::vec2 groupCenter(0.0F, 0.0F);

  if (neighborhood.empty())
  {
    return cohesionForce;
  }

  for (auto neighbor : neighborhood)
  {
    groupCenter += neighbor.position;
  }

  groupCenter /= neighborhood.size();

  cohesionForce = glm::normalize((groupCenter - boid.position));

  // end solution

  return cohesionForce;
}
