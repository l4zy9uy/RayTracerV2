//
// Created by l4zy9uy on 3/6/24.
//

#include "Pattern/SolidPtn.h"

const std::shared_ptr<Pattern> &SolidPtn::getPtn1Ptr() const {
  return ptn1_ptr_;
}
void SolidPtn::setPtn1Ptr(const std::shared_ptr<Pattern> &Ptn1Ptr) {
  ptn1_ptr_ = Ptn1Ptr;
}
const std::shared_ptr<Pattern> &SolidPtn::getPtn2Ptr() const {
  return ptn2_ptr_;
}
void SolidPtn::setPtn2Ptr(const std::shared_ptr<Pattern> &Ptn2Ptr) {
  ptn2_ptr_ = Ptn2Ptr;
}
SolidPtn::SolidPtn(const glm::dvec3 &A,
                   const glm::dvec3 &B,
                   const std::shared_ptr<Pattern> &Ptn1Ptr,
                   const std::shared_ptr<Pattern> &Ptn2Ptr) : a_(A), b_(B), ptn1_ptr_(Ptn1Ptr), ptn2_ptr_(Ptn2Ptr) {}
glm::dvec3 SolidPtn::pattern_at(const glm::dvec4 &point) const {
  glm::dvec3 color;
  if(static_cast<long>(floor(point.x) + floor(point.y) + floor(point.z)) % 2) {
    auto p = glm::inverse(ptn1_ptr_->getTransformationMatrix()) * point;
    color = ptn1_ptr_->pattern_at(p);
  }
  else {
    auto p = glm::inverse(ptn2_ptr_->getTransformationMatrix()) * point;
    color = ptn2_ptr_->pattern_at(p);
  }

  return color;
}
const glm::dvec3 &SolidPtn::getA1() const {
  return a_;
}
void SolidPtn::setA1(const glm::dvec3 &A) {
  a_ = A;
}
const glm::dvec3 &SolidPtn::getB1() const {
  return b_;
}
void SolidPtn::setB1(const glm::dvec3 &B) {
  b_ = B;
}
