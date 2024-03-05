//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_SPHERE_H
#define RAYTRACERV2_SPHERE_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Shape.h"

class Intersections;

class Sphere : public Shape {
public:

  explicit Sphere();
  Intersections local_intersect(const Ray &ray) override;
  [[nodiscard]] glm::dvec4 local_normal_at(const glm::dvec4 &point) const override;
};

#endif //RAYTRACERV2_SPHERE_H
