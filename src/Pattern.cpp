//
// Created by l4zy9uy on 3/5/24.
//

#include "Pattern/Pattern.h"
#include <cmath>
#include "Shape/Shape.h"

const glm::dmat4 &Pattern::getTransformationMatrix() const {
  return transformation_matrix_;
}
void Pattern::setTransformationMatrix(const glm::dmat4 &TransformationMatrix) {
  transformation_matrix_ = TransformationMatrix;
}

glm::dvec3 Pattern::pattern_at_shape(const Shape &shape, const glm::dvec4 &world_position) {
  auto object_point = glm::inverse(shape.getModel()) * world_position;
  auto pattern_point = glm::inverse(transformation_matrix_) * object_point;

  return pattern_at(pattern_point);
}

