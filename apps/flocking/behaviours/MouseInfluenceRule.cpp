#include "MouseInfluenceRule.h"
#include "imgui.h"

glm::vec2 MouseInfluenceRule::computeForce(const std::vector<BoidView>& neighborhood, const BoidView& boid) {
  glm::vec2 force(0.f);

  // ImGui::IsMouseDown(ImGuiMouseButton_Left) returns true if the left mouse button is currently pressed.
  // ImGui::GetIO().MousePos returns the current mouse position as an ImVec2.
  // glm::length(vec) returns the length of a vector

  // begin solution

  // Checks if the mouse is down
  if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
  {
    // Mouse position
    glm::vec2 mousePos = glm::vec2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);

    // Pulls the boids away from the mouse if repulsive
    if (isRepulsive)
    {
      force = glm::vec2(boid.position - mousePos);
    }
    // Pulls the boids towards the mouse if attractive
    else
    {
      force = glm::vec2(mousePos - boid.position);
    }
  }

  // end solution

  return force;
}

bool MouseInfluenceRule::drawImguiRuleExtra() {
  bool valueHasChanged = false;

  if (ImGui::RadioButton("Attractive", !isRepulsive)) {
    isRepulsive = false;
    valueHasChanged = true;
  }
  ImGui::SameLine();
  if (ImGui::RadioButton("Repulsive", isRepulsive)) {
    isRepulsive = true;
    valueHasChanged = true;
  }

  return valueHasChanged;
}
