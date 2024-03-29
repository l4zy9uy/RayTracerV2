//
// Created by l4zy9uy on 3/16/24.
//

#include "Shape/Cube.h"
#include "myMath.h"

Intersections Cube::local_intersect(const Ray &ray) {
  auto xt = check_axis(ray.getOriginPoint().x, ray.getDirectionVector().x);
  auto yt = check_axis(ray.getOriginPoint().y, ray.getDirectionVector().y);
  auto zt = check_axis(ray.getOriginPoint().z, ray.getDirectionVector().z);
  auto tMin = fmax(xt.first, fmax(yt.first, zt.first));
  auto tMax = fmin(xt.second, fmin(yt.second, zt.second));

  Intersections xs;
  if(tMin > tMax) return xs;
  xs.addIntersection(tMin, this);
  xs.addIntersection(tMax, this);
  return xs;
}

std::pair<double, double> Cube::check_axis(const double &origin, const double &direction) {
  auto tMinNumerator = -1 - origin;
  auto tMaxNumerator = 1 - origin;
  double tMin, tMax;
  if(fabs(direction) > Epsilon) {
    tMin = tMinNumerator / direction;
    tMax = tMaxNumerator / direction;
  }
  else {
    tMin = tMinNumerator * PosInfinity;
    tMax = tMaxNumerator * PosInfinity;
  }
  if(tMin > tMax) std::swap(tMin, tMax);
  return {tMin, tMax};
}
glm::dvec4 Cube::local_normal_at(const glm::dvec4 &point, const Intersection &hit) const {
  auto maxC = fmax(fabs(point.x), fmax(fabs(point.y), fabs(point.z)));
  if(maxC == fabs(point.x)) return {point.x, 0, 0, 1};
  else if(maxC == fabs(point.y)) return {0, point.y, 0, 1};
  return {0, 0, point.z, 1};
}
