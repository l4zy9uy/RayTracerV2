//
// Created by l4zy9uy on 3/6/24.
//

#include "Pattern/StripePtn.h"
#include "Shape/Shape.h"

StripePtn::StripePtn(const glm::dvec3 &A, const glm::dvec3 &B) : a(A), b(B) {}

const glm::dvec3 &StripePtn::getA() const {
  return a;
}
void StripePtn::setA(const glm::dvec3 &A) {
  a = A;
}
const glm::dvec3 &StripePtn::getB() const {
  return b;
}
void StripePtn::setB(const glm::dvec3 &B) {
  b = B;
}

glm::dvec3 StripePtn::pattern_at(const glm::dvec4 &point) const {
  if(static_cast<long>(floor(point.x)) % 2 == 0) return a;
  else return b;
}
