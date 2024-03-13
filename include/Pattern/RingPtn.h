//
// Created by l4zy9uy on 3/6/24.
//

#ifndef RAYTRACERV2_INCLUDE_PATTERN_RINGPTN_H
#define RAYTRACERV2_INCLUDE_PATTERN_RINGPTN_H
#include "Pattern.h"
class RingPtn : public Pattern {
public:
  glm::dvec3 pattern_at(const glm::dvec4 &point) const override;
public:
  RingPtn(const glm::dvec3 &A, const glm::dvec3 &B);
private:
  glm::dvec3 a;
public:
  const glm::dvec3 &getA1() const;
  void setA1(const glm::dvec3 &A);
  const glm::dvec3 &getB1() const;
  void setB1(const glm::dvec3 &B);
private:
  glm::dvec3 b;
};

#endif //RAYTRACERV2_INCLUDE_PATTERN_RINGPTN_H
