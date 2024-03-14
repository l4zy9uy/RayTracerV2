//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_MATERIAL_H
#define RAYTRACERV2_MATERIAL_H

#include <glm/vec3.hpp>
#include "Pattern/Pattern.h"
#include <optional>
#include <memory>

struct Material {
  explicit Material() = default;

  glm::dvec3 color_ = glm::dvec3(1.0);
  double ambient_ = 0.1;
  double diffuse_ = 0.9;
  double specular_ = 0.9;
  double shininess_ = 200.0;
  double reflective_ = 0.0;
  double transparency_ = 0.0;
  double refractive_index_ = 1.0;
  std::shared_ptr<Pattern> pattern_ptr_ = nullptr;
};

#endif //RAYTRACERV2_MATERIAL_H
