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

glm::mat4 view_transform(const glm::vec4 &from, const glm::vec4 &to, const glm::vec4 &up) {
  // Convert glm::vec4 to glm::vec3 for vector operations
  glm::vec3 from3(from), to3(to), up3(up.x, up.y, up.z);

  glm::vec3 forward = glm::normalize(to3 - from3);
  glm::vec3 upNormalized = glm::normalize(up3);
  glm::vec3 left = glm::cross(forward, upNormalized);
  glm::vec3 true_up = glm::cross(left, forward);

  // Construct the orientation matrix
  glm::mat4 orientation = glm::mat4(
      glm::vec4(left, 0.0f),
      glm::vec4(true_up, 0.0f),
      glm::vec4(-forward, 0.0f), // Negate forward vector for view direction
      glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
  );

  // Apply translation to the orientation matrix
  glm::mat4 translation = glm::translate(glm::mat4(1.0f), -from3);

  // The final view matrix is a combination of orientation and translation
  return glm::transpose(orientation) * translation;
}

Projectile::Projectile(const glm::vec3 &position, const glm::vec3 &velocity) : position(position), velocity(velocity) {}

Environment::Environment(const glm::vec3 &gravity, const glm::vec3 &wind) : gravity(gravity), wind(wind) {}
