//
// Created by l4zy9uy on 3/5/24.
//

#include "Plane.h"

Intersections Plane::local_intersect(const Ray &ray) {
  Intersections result;
  if(fabs(ray.getDirectionVector().y) < (glm::epsilon<double>() * 10000000.0)) {
    return result;
  }
  auto t = -ray.getOriginPoint().y / ray.getDirectionVector().y;
  result.addIntersection(Intersection(t, this));
  return result;
}
glm::dvec4 Plane::local_normal_at(const glm::dvec4 &point) const {
  return {0.0, 1.0, 0.0, 0.0};
}