//
// Created by l4zy9uy on 3/6/24.
//

#ifndef RAYTRACERV2_INCLUDE_GRADIENTPATTERN_H
#define RAYTRACERV2_INCLUDE_GRADIENTPATTERN_H
#include "Pattern.h"
class GradientPtn : public Pattern {
public:
  GradientPtn(const glm::dvec3 &A, const glm::dvec3 &B);
  glm::dvec3 pattern_at(const glm::dvec4 &point) const override;
  //glm::dvec3 pattern_at_shape(const Shape &shape, const glm::dvec4 &world_position) override;

};

#endif //RAYTRACERV2_INCLUDE_GRADIENTPATTERN_H
