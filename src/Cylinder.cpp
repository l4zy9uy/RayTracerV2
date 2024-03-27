//
// Created by l4zy9uy on 3/20/24.
//

#include "Shape/Cylinder.h"
Intersections Cylinder::local_intersect(const Ray &ray) {
  auto o = ray.getOriginPoint();
  auto d = ray.getDirectionVector();
  auto a = d.x * d.x + d.z * d.z;
  double t0 = 0, t1 = 0;
  Intersections xs;
  if(fabs(a - 0.0) > 0.00001) {
    auto b = 2 * o.x * d.x + 2 * o.z * d.z;
    auto c = o.x * o.x + o.z * o.z - 1;
    auto disc = b * b - 4 * a * c;
    if (disc < 0)
      return {};
    t0 = (-b - sqrt(disc)) / (2 * a);
    t1 = (-b + sqrt(disc)) / (2 * a);
    if (t0 > t1)
      std::swap(t0, t1);

    auto y0 = o.y + t0 * d.y;
    if (minimum_ < y0 && y0 < maximum_) {
      xs.addIntersection(t0, this);
    }

    auto y1 = o.y + t1 * d.y;
    if (minimum_ < y1 && y1 < maximum_) {
      xs.addIntersection(t1, this);
    }
  }
  intersect_cap(ray, xs);
  return xs;
}
glm::dvec4 Cylinder::local_normal_at(const glm::dvec4 &point, const Intersection &hit) const {
  auto dist = point.x*point.x + point.z*point.z;
  if(dist < 1 && point.y >= maximum_ - 0.00001) return {0, 1, 0, 0};
  else if(dist < 1 && point.y <= minimum_ + 0.00001) return {0, -1, 0, 0};
  return {point.x, 0, point.z, 0};
}
const double & Cylinder::getMinimum() const {
  return minimum_;
}
void Cylinder::setMinimum(const double &Minimum) {
  minimum_ = Minimum;
}
const double & Cylinder::getMaximum() const {
  return maximum_;
}
void Cylinder::setMaximum(const double &Maximum) {
  maximum_ = Maximum;
}
const bool & Cylinder::isClose() const {
  return close_;
}
void Cylinder::setClose(const bool &Close) {
  close_ = Close;
}
bool Cylinder::checkCap(const Ray &ray, const double &t) {
  auto x = ray.getOriginPoint().x + t*ray.getDirectionVector().x;
  auto z = ray.getOriginPoint().z + t*ray.getDirectionVector().z;
  return (x*x + z*z <= 1.0);
}
void Cylinder::intersect_cap(const Ray &ray, Intersections &xs) {
  if(!close_ || fabs(ray.getDirectionVector().y) < 0.00001)
    return;
  auto t = (minimum_ - ray.getOriginPoint().y) / ray.getDirectionVector().y;
  if(checkCap(ray, t)) xs.addIntersection(t, this);

  t = (maximum_ - ray.getOriginPoint().y) / ray.getDirectionVector().y;
  if(checkCap(ray, t)) xs.addIntersection(t, this);
}
