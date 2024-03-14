//
// Created by l4zy9uy on 3/14/24.
//

#include <utility>

#include "Pattern/BlendedPtn.h"
glm::dvec3 BlendedPtn::pattern_at(const glm::dvec4 &point) const {
  /*if(
      static_cast<long>(floor(point.x) + floor(point.y) + floor(point.z)) % 2
      ) return a->pattern_at(point);*/
  return (a->pattern_at(point) + b->pattern_at(point)) / 2.0;
}
BlendedPtn::BlendedPtn(const std::shared_ptr<Pattern> &A, const std::shared_ptr<Pattern> &B) : a(A), b(B) {}
//BlendedPtn::BlendedPtn(CheckerPtn A, CheckerPtn B) : a(std::move(A)), b(std::move(B)) {}
