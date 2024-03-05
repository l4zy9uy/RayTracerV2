//
// Created by l4zy9uy on 3/5/24.
//

#ifndef RAYTRACERV2_INCLUDE_PATTERN_H
#define RAYTRACERV2_INCLUDE_PATTERN_H

#include <glm/glm.hpp>
class Pattern {
public:
  Pattern(const glm::dvec3 &A, const glm::dvec3 &B);
  explicit Pattern() = default;
private:
  glm::dvec3 a;
  glm::dvec3 b;
public:
  glm::dvec3 stripe_at(const glm::dvec4 &point) const;
};

#endif //RAYTRACERV2_INCLUDE_PATTERN_H
