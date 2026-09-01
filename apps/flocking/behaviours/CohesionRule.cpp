#include "CohesionRule.h"
#include <glm/glm.hpp>
#include <iostream>

glm::vec2 CohesionRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 cohesionForce(0.0F);

  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.

  // begin solution

  if (neighborhood.empty())
  {
    return cohesionForce;
  }

  glm::vec2 groupCenter(0.0F, 0.0F);

  for (auto neighbor : neighborhood)
  {
    groupCenter += neighbor.position;
  }
  groupCenter /= neighborhood.size();

  cohesionForce =  groupCenter - boid.position;

  cohesionForce = glm::normalize(cohesionForce) * (glm::length(groupCenter - boid.position) /2);

  // end solution

  return cohesionForce;
}
