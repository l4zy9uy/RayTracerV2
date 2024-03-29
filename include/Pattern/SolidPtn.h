//
// Created by l4zy9uy on 3/6/24.
//

#ifndef RAYTRACERV2_INCLUDE_PATTERN_SOLIDPTN_H
#define RAYTRACERV2_INCLUDE_PATTERN_SOLIDPTN_H
#include "Pattern.h"
#include <memory>
class SolidPtn : public Pattern {
public:
  SolidPtn(const glm::dvec3 &A,
           const glm::dvec3 &B,
           const std::shared_ptr<Pattern> &Ptn1Ptr,
           const std::shared_ptr<Pattern> &Ptn2Ptr);
public:
  [[nodiscard]] const std::shared_ptr<Pattern> &getPtn1Ptr() const;
  void setPtn1Ptr(const std::shared_ptr<Pattern> &Ptn1Ptr);
  [[nodiscard]] const std::shared_ptr<Pattern> &getPtn2Ptr() const;
  void setPtn2Ptr(const std::shared_ptr<Pattern> &Ptn2Ptr);
  [[nodiscard]] const glm::dvec3 &getA1() const;
  void setA1(const glm::dvec3 &A);
  [[nodiscard]] const glm::dvec3 &getB1() const;
  void setB1(const glm::dvec3 &B);
public:
  [[nodiscard]] glm::dvec3 pattern_at(const glm::dvec4 &point) const override;
private:
  glm::dvec3 a_;
  glm::dvec3 b_;
  std::shared_ptr<Pattern> ptn1_ptr_;
  std::shared_ptr<Pattern> ptn2_ptr_;
};


#endif //RAYTRACERV2_INCLUDE_PATTERN_SOLIDPTN_H
