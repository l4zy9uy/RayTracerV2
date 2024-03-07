//
// Created by l4zy9uy on 3/5/24.
//

#ifndef RAYTRACERV2_INCLUDE_PLANE_H
#define RAYTRACERV2_INCLUDE_PLANE_H
#include "Shape.h"

class Plane : public Shape {
public:
  Intersections local_intersect(const Ray &ray) override;
  [[nodiscard]] glm::dvec4 local_normal_at(const glm::dvec4 &point) const override;

};

#endif //RAYTRACERV2_INCLUDE_PLANE_H

