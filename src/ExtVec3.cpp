//
// Created by l4zy9uy on 2/27/24.
//

#include "ExtVec3.h"
#include <glm/gtc/matrix_transform.hpp>

Projectile tick(const Environment &env, const Projectile &proj) {
  auto position = proj.position + proj.velocity;
  auto velocity = proj.velocity + env.gravity + env.wind;
  return {position, velocity};
}

#include <glm/glm.hpp>

glm::dmat4 view_transform(const glm::dvec4 &from, const glm::dvec4 &to, const glm::dvec4 &up) {
  // Convert glm::dvec4 to glm::dvec3 for vector operations
  glm::dvec3 from3(from), to3(to), up3(up.x, up.y, up.z);

  glm::dvec3 forward = glm::normalize(to3 - from3);
  glm::dvec3 upNormalized = glm::normalize(up3);
  glm::dvec3 left = glm::cross(forward, upNormalized);
  glm::dvec3 true_up = glm::cross(left, forward);

  // Construct the orientation matrix
  glm::dmat4 orientation = glm::dmat4(
      {left, 0.0},
      {true_up, 0.0},
      {-forward, 0.0}, // Negate forward vector for view direction
      {0.0, 0.0, 0.0, 1.0}
  );

  // Apply translation to the orientation matrix
  glm::dmat4 translation = glm::translate(glm::dmat4(1.0), -from3);

  // The final view matrix is a combination of orientation and translation
  return glm::transpose(orientation) * translation;
}

Projectile::Projectile(const glm::dvec3 &position, const glm::dvec3 &velocity) : position(position), velocity(velocity) {}

Environment::Environment(const glm::dvec3 &gravity, const glm::dvec3 &wind) : gravity(gravity), wind(wind) {}
