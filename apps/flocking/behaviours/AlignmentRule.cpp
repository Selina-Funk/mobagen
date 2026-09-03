#include "AlignmentRule.h"
#include <glm/glm.hpp>

glm::vec2 AlignmentRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 averageVelocity(0.0F);
  // glm::vec2 can be divided by a float, which will divide each component of the vector by that float.


  // begin solution

  // Checks if the neighborhood is empty
  if (neighborhood.empty())
  {
    return averageVelocity;
  }

  // Adds the boid's velocity to the average velocity
  averageVelocity = boid.velocity;

  // Adds all neighbor velocities together
  for (auto neighbor : neighborhood)
  {
    averageVelocity += neighbor.velocity;
  }

  // Averages the vel out to align the boid
  averageVelocity = averageVelocity / static_cast<float>(neighborhood.size() + 1);

  return averageVelocity;
  // end solution
}
