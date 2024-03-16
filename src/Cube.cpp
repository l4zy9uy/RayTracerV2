//
// Created by l4zy9uy on 3/16/24.
//

#include "Shape/Cube.h"
Intersections Cube::local_intersect(const Ray &ray) {
  auto xt = check_axis(ray.getOriginPoint().x, ray.getDirectionVector().x);
  auto yt = check_axis(ray.getOriginPoint().y, ray.getDirectionVector().y);
  auto zt = check_axis(ray.getOriginPoint().z, ray.getDirectionVector().z);

  auto tmin = fmax(xt.first, fmax(yt.first, zt.first));
  auto tmax = fmin(xt.second, fmin(yt.second, zt.second));

  Intersections xs;
  if(tmin > tmax) return xs;
  xs.addIntersection(tmin, this);
  xs.addIntersection(tmax, this);
  return xs;
}

std::pair<double, double> Cube::check_axis(const double &origin, const double &direction) {
  auto tmin_numerator = -1 - origin;
  auto tmax_numerator = 1 - origin;
  double tmin, tmax;
  if(fabs(direction) > 0.00001) {
    tmin = tmin_numerator / direction;
    tmax = tmax_numerator / direction;
  }
  else {
    tmin = tmin_numerator * 10000000000;
    tmax = tmax_numerator * 10000000000;
  }
  if(tmin > tmax) std::swap(tmin, tmax);
  return {tmin, tmax};
}
glm::dvec4 Cube::local_normal_at(const glm::dvec4 &point) const {
  auto maxc = fmax(fabs(point.x), fmax(fabs(point.y), fabs(point.z)));
  if(maxc == fabs(point.x)) return {point.x, 0, 0, 1};
  else if(maxc == fabs(point.y)) return {0, point.y, 0, 1};
  return {0, 0, point.z, 1};
}
