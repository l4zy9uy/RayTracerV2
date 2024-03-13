//
// Created by l4zy9uy on 3/6/24.
//

#include "Pattern/RingPtn.h"
RingPtn::RingPtn(const glm::dvec3 &A, const glm::dvec3 &B) : a(A), b(B) {}

const glm::dvec3 &RingPtn::getA() const {
  return a;
}
void RingPtn::setA(const glm::dvec3 &A) {
  a = A;
}
const glm::dvec3 &RingPtn::getB() const {
  return b;
}
void RingPtn::setB(const glm::dvec3 &B) {
  b = B;
}

glm::dvec3 RingPtn::pattern_at(const glm::dvec4 &point) const {
  double squaredDistance = point.x * point.x + point.z * point.z;
  // Use floor of the squared distance for ring calculation, avoiding sqrt.
  if (static_cast<long>(floor(squaredDistance)) % 2) return b;
  return a;
}
