//
// Created by l4zy9uy on 3/6/24.
//

#ifndef RAYTRACERV2_INCLUDE_STRIPEPATTERN_H
#define RAYTRACERV2_INCLUDE_STRIPEPATTERN_H
#include "Pattern.h"

class Shape;
class StripePtn : public Pattern {

public:
  /*const glm::dvec3 &getA() const;
  void setA(const glm::dvec3 &A);
  const glm::dvec3 &getB() const;
  void setB(const glm::dvec3 &B);*/
public:
  StripePtn(const glm::dvec3 &A, const glm::dvec3 &B);
  [[nodiscard]] glm::dvec3 pattern_at(const glm::dvec4 &point) const override;
  //glm::dvec3 pattern_at_shape(const Shape &shape, const glm::dvec4 &world_position) override;

};

#endif //RAYTRACERV2_INCLUDE_STRIPEPATTERN_H
