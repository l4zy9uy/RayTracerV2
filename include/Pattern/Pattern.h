//
// Created by l4zy9uy on 3/5/24.
//

#ifndef RAYTRACERV2_INCLUDE_PATTERN_H
#define RAYTRACERV2_INCLUDE_PATTERN_H

#include <glm/glm.hpp>

class Shape;

class Pattern {
public:
  [[nodiscard]] const glm::dmat4 &getTransformationMatrix() const;
  void setTransformationMatrix(const glm::dmat4 &TransformationMatrix);
public:
  [[nodiscard]] virtual glm::dvec3 pattern_at(const glm::dvec4 &point) const = 0;
  glm::dvec3 pattern_at_shape(const Shape &shape, const glm::dvec4 &world_position);
protected:
  glm::dmat4 transformation_matrix_{1.0};
};

#endif //RAYTRACERV2_INCLUDE_PATTERN_H
