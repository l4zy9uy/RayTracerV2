//
// Created by l4zy9uy on 3/5/24.
//

#include "Pattern/Pattern.h"
#include <cmath>
#include "Shape.h"

const glm::dmat4 &Pattern::getTransformationMatrix() const {
  return transformation_matrix_;
}
void Pattern::setTransformationMatrix(const glm::dmat4 &TransformationMatrix) {
  transformation_matrix_ = TransformationMatrix;
}
const glm::dvec3 &Pattern::getA() const {
  return a;
}
void Pattern::setA(const glm::dvec3 &A) {
  a = A;
}
const glm::dvec3 &Pattern::getB() const {
  return b;
}
void Pattern::setB(const glm::dvec3 &B) {
  b = B;
}

Pattern::Pattern(const glm::dvec3 &A, const glm::dvec3 &B) : a(A), b(B) {
  transformation_matrix_ = glm::dmat4(1.0);
}
glm::dvec3 Pattern::pattern_at_shape(const Shape &shape, const glm::dvec4 &world_position) {
  auto object_point = glm::inverse(shape.getModel()) * world_position;
  auto pattern_point = glm::inverse(transformation_matrix_) * object_point;

  return pattern_at(pattern_point);
}
/*
glm::dvec3 Pattern::pattern_at(const glm::dvec4 &point) const {
  return {point.x, point.y, point.z};
}
glm::dvec3 Pattern::pattern_at_shape(const Shape &shape, const glm::dvec4 &world_position) {
  auto object_point = glm::inverse(shape.getModel()) * world_position;
  auto pattern_point = glm::inverse(transformation_matrix_) * object_point;

  return pattern_at(pattern_point);
}*/
