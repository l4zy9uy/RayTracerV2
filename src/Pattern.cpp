//
// Created by l4zy9uy on 3/5/24.
//

#include "Pattern.h"
#include <cmath>
glm::dvec3 Pattern::stripe_at(const glm::dvec4 &point) const {
  if(static_cast<long>(floor(point.x)) % 2 == 0) return a;
  else return b;
}
Pattern::Pattern(const glm::dvec3 &A, const glm::dvec3 &B) : a(A), b(B) {}
