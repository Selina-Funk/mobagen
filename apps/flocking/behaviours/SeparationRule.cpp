#include "SeparationRule.h"
#include "imgui.h"
#include <glm/glm.hpp>

glm::vec2 SeparationRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 separatingForce(0.f);

  // the header have the desiredMinimalDistance member variable, which is the distance that the boids should try to maintain from each other.
  // glm::length(vec) returns the length of a vector,
  // glm::normalize(vec) returns the normalized vector (length 1) in the same direction as vec.
  // multiply by (desiredMinimalDistance / distance) is the proportionality factor that makes the force stronger when the boids are closer together, and weaker when they are farther apart.

  // begin solution

  // Returns zero if there is no neighbors in the neighborhood
  if (neighborhood.size() <= 0)
  {
    return separatingForce;
  }

  // Goes through each boid in the neighborhood
  for (auto neighbor : neighborhood)
  {
    glm::vec2 targetVec = (boid.position - neighbor.position);

    // Checks to make sure that the boid is not itself
    if (glm::length(targetVec) < 0.0001f)
    {
      continue;
    }

    float force = desiredMinimalDistance / glm::length(targetVec);

    separatingForce += glm::normalize(targetVec) * force;
  }

  // end solution

  return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;
  if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
    valueHasChanged = true;
  }
  return valueHasChanged;
}
