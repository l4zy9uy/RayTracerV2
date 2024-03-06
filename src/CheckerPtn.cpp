//
// Created by l4zy9uy on 3/6/24.
//

#include "Pattern/CheckerPtn.h"
CheckerPtn::CheckerPtn(const glm::dvec3 &A, const glm::dvec3 &B) : Pattern(A, B) {}
glm::dvec3 CheckerPtn::pattern_at(const glm::dvec4 &point) const {
  if(static_cast<long>(floor(point.x) + floor(point.y) + floor(point.z)) % 2) return b;
  return a;
}
