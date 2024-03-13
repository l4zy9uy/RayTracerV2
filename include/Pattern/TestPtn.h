//
// Created by l4zy9uy on 3/13/24.
//

#ifndef RAYTRACERV2_INCLUDE_PATTERN_TESTPTN_H
#define RAYTRACERV2_INCLUDE_PATTERN_TESTPTN_H
#include "Pattern.h"

class TestPtn : public Pattern{
public:
  glm::dvec3 pattern_at(const glm::dvec4 &point) const override;
};

#endif //RAYTRACERV2_INCLUDE_PATTERN_TESTPTN_H
