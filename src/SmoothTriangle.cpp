//
// Created by l4zy9uy on 3/26/24.
//

#include "Shape/SmoothTriangle.h"
SmoothTriangle::SmoothTriangle(const glm::dvec4 &P1,
                               const glm::dvec4 &P2,
                               const glm::dvec4 &P3,
                               const glm::dvec4 &N1,
                               const glm::dvec4 &N2,
                               const glm::dvec4 &N3) : Triangle(P1, P2, P3), n1_(N1), n2_(N2), n3_(N3) {}
Intersections SmoothTriangle::local_intersect(const Ray &ray) {
  return Triangle::local_intersect(ray);
}
glm::dvec4 SmoothTriangle::local_normal_at(const glm::dvec4 &point, const Intersection &hit) const {
  return n2_ * hit.u +
          n3_ * hit.v +
          n1_ * (1 - hit.u - hit.v);
}
