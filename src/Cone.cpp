//
// Created by l4zy9uy on 3/20/24.
//

#include "Shape/Cone.h"
Intersections Cone::local_intersect(const Ray &ray) {
  auto d = ray.getDirectionVector();
  auto o = ray.getOriginPoint();
  auto a = d.x*d.x - d.y*d.y + d.z*d.z;
  auto b = 2*o.x*d.x - 2*o.y*d.y + 2*d.z*o.z;
  auto c = o.x*o.x - o.y*o.y + o.z*o.z;
  double t0, t1;
  Intersections xs;
  if(fabs(a) < Epsilon) {
    if(fabs(b) < Epsilon) return {};
    else {
      t0 = -c / (2*b);
      xs.addIntersection(t0, this);
      //return xs;
    }
  }
  else {
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
glm::dvec4 Cone::local_normal_at(const glm::dvec4 &point, const Intersection &hit) const {
  auto y = sqrt(point.x*point.x + point.z*point.z);
  if(point.y > 0) y = -y;
  return {point.x, y, point.z, 0};
}
const double & Cone::getMinimum() const {
  return minimum_;
}
void Cone::setMinimum(const double &Minimum) {
  minimum_ = Minimum;
}
const double & Cone::getMaximum() const {
  return maximum_;
}
void Cone::setMaximum(const double &Maximum) {
  maximum_ = Maximum;
}
const bool & Cone::isClose() const {
  return close_;
}
void Cone::setClose(bool Close) {
  close_ = Close;
}
bool Cone::checkCap(const Ray &ray, const double &t, const double &y) {
  auto x = ray.getOriginPoint().x + t*ray.getDirectionVector().x;
  auto z = ray.getOriginPoint().z + t*ray.getDirectionVector().z;
  return x*x + z*z <= y*y;
}
void Cone::intersect_cap(const Ray &ray, Intersections &xs) {
  if(!close_ || fabs(ray.getDirectionVector().y) < Epsilon)
    return;
  auto t = (minimum_ - ray.getOriginPoint().y) / ray.getDirectionVector().y;
  if(checkCap(ray, t, minimum_))
    xs.addIntersection(t, this);

  t = (maximum_ - ray.getOriginPoint().y) / ray.getDirectionVector().y;
  if(checkCap(ray, t, maximum_))
    xs.addIntersection(t, this);
}
