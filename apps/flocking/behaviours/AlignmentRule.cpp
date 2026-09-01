#include "AlignmentRule.h"
#include <glm/glm.hpp>

glm::vec2 AlignmentRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 averageVelocity(0.0F);
  // glm::vec2 can be divided by a float, which will divide each component of the vector by that float.


  // begin solution

  if (neighborhood.empty())
  {
    return averageVelocity;
  }

  averageVelocity = boid.velocity;

  for (auto neighbor : neighborhood)
  {
    averageVelocity += neighbor.velocity;
  }

  averageVelocity = averageVelocity / static_cast<float>(neighborhood.size());

  return averageVelocity;
  // end solution
}
