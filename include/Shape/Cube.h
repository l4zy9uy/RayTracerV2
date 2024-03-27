//
// Created by l4zy9uy on 3/16/24.
//

#ifndef RAYTRACERV2_INCLUDE_SHAPE_CUBE_H
#define RAYTRACERV2_INCLUDE_SHAPE_CUBE_H
#include "Shape.h"
#include <utility>

class Cube : public Shape {
public:
  Intersections local_intersect(const Ray &ray) override;
  [[nodiscard]] glm::dvec4 local_normal_at(const glm::dvec4 &point, const Intersection &hit) const override;
  std::pair<double, double> check_axis(const double &origin, const double &direction);
};

#endif //RAYTRACERV2_INCLUDE_SHAPE_CUBE_H
