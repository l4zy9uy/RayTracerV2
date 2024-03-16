//
// Created by l4zy9uy on 3/14/24.
//

#include <utility>

#include "Pattern/BlendedPtn.h"
glm::dvec3 BlendedPtn::pattern_at(const glm::dvec4 &point) const {
  auto tp = glm::inverse(transformation_matrix_) * point;
  return a->pattern_at(tp) * (1.0 - t_) + b->pattern_at(point) * t_;
}
BlendedPtn::BlendedPtn(const std::shared_ptr<Pattern> &A, const std::shared_ptr<Pattern> &B, const double &t) : a(A), b(B), t_(t) {}
//BlendedPtn::BlendedPtn(CheckerPtn A, CheckerPtn B) : a(std::move(A)), b(std::move(B)) {}
