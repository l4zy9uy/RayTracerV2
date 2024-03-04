//
// Created by l4zy9uy on 2/27/24.
//

#ifndef RAYTRACERV2_EXTdvec3_H
#define RAYTRACERV2_EXTdvec3_H
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
struct Projectile {
  Projectile(const glm::dvec3 &position, const glm::dvec3 &velocity);

  glm::dvec3 position;
  glm::dvec3 velocity;
};

struct Environment {
  Environment(const glm::dvec3 &gravity, const glm::dvec3 &wind);

  glm::dvec3 gravity;
  glm::dvec3 wind;
};

Projectile tick(const Environment &env, const Projectile &proj);
glm::dmat4 view_transform(const glm::dvec4 &from, const glm::dvec4 &to, const glm::dvec4 &up);

#endif //RAYTRACERV2_EXTdvec3_H
