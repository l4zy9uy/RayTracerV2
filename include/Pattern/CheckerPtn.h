//
// Created by l4zy9uy on 3/6/24.
//

#ifndef RAYTRACERV2_INCLUDE_PATTERN_CHECKERPTN_H
#define RAYTRACERV2_INCLUDE_PATTERN_CHECKERPTN_H
#include "Pattern.h"

class CheckerPtn : public Pattern {
public:
  CheckerPtn(const glm::dvec3 &A, const glm::dvec3 &B);
public:
  [[nodiscard]] const glm::dvec3 &getA() const;
  void setA(const glm::dvec3 &A);
  [[nodiscard]] const glm::dvec3 &getB() const;
  void setB(const glm::dvec3 &B);
public:
  [[nodiscard]] glm::dvec3 pattern_at(const glm::dvec4 &point) const override;
private:
  glm::dvec3 a;
  glm::dvec3 b;
};

#endif //RAYTRACERV2_INCLUDE_PATTERN_CHECKERPTN_H
