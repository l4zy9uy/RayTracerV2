//
// Created by l4zy9uy on 3/6/24.
//

#include "Pattern/GradientPtn.h"

GradientPtn::GradientPtn(const glm::dvec3 &A, const glm::dvec3 &B) : a_(A), b_(B) {}

const glm::dvec3 &GradientPtn::getA() const {
  return a_;
}

void GradientPtn::setA(const glm::dvec3 &A) {
  a_ = A;
}

const glm::dvec3 &GradientPtn::getB() const {
  return b_;
}

void GradientPtn::setB(const glm::dvec3 &B) {
  b_ = B;
}

glm::dvec3 GradientPtn::pattern_at(const glm::dvec4 &point) const {
  auto distance = b_ - a_;
  auto fraction = point.x - floor(point.x);
  return a_ + distance * fraction;
}
