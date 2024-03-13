//
// Created by l4zy9uy on 3/6/24.
//

#include "Pattern/CheckerPtn.h"
CheckerPtn::CheckerPtn(const glm::dvec3 &A, const glm::dvec3 &B) : a(A), b(B) {}
glm::dvec3 CheckerPtn::pattern_at(const glm::dvec4 &point) const {
  if(static_cast<long>(floor(point.x) + floor(point.y) + floor(point.z)) % 2) return b;
  return a;
}
const glm::dvec3 &CheckerPtn::getA1() const {
  return a;
}
void CheckerPtn::setA1(const glm::dvec3 &A) {
  a = A;
}
const glm::dvec3 &CheckerPtn::getB1() const {
  return b;
}
void CheckerPtn::setB1(const glm::dvec3 &B) {
  b = B;
}
