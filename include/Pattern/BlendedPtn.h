//
// Created by l4zy9uy on 3/14/24.
//

#ifndef RAYTRACERV2_INCLUDE_PATTERN_BLENDEDPTN_H
#define RAYTRACERV2_INCLUDE_PATTERN_BLENDEDPTN_H
#include "Pattern.h"
#include <memory>

class BlendedPtn : public Pattern{
public:
  //BlendedPtn(CheckerPtn A, CheckerPtn B);
  [[nodiscard]] glm::dvec3 pattern_at(const glm::dvec4 &point) const override;
private:
  std::shared_ptr<Pattern> a;
  std::shared_ptr<Pattern> b;
  double t_;
public:
  BlendedPtn(const std::shared_ptr<Pattern> &A, const std::shared_ptr<Pattern> &B, const double &t);
};

#endif //RAYTRACERV2_INCLUDE_PATTERN_BLENDEDPTN_H
