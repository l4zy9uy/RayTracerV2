//
// Created by l4zy9uy on 3/13/24.
//

#include "Pattern/TestPtn.h"
glm::dvec3 TestPtn::pattern_at(const glm::dvec4 &point) const {
  return {point.x, point.y, point.z};
}
