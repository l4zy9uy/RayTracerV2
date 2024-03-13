//
// Created by l4zy9uy on 3/6/24.
//

#include "Pattern/GradientPtn.h"

GradientPtn::GradientPtn(const glm::dvec3 &A, const glm::dvec3 &B) : a(A), b(B) {}

const glm::dvec3 &GradientPtn::getA() const {
  return a;
}

void GradientPtn::setA(const glm::dvec3 &A) {
  a = A;
}

const glm::dvec3 &GradientPtn::getB() const {
  return b;
}

void GradientPtn::setB(const glm::dvec3 &B) {
  b = B;
}

glm::dvec3 GradientPtn::pattern_at(const glm::dvec4 &point) const {
  auto distance = b - a;
  auto fraction = point.x - floor(point.x);
  return a + distance * fraction;
}
