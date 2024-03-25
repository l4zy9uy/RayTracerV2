//
// Created by l4zy9uy on 3/22/24.
//

#include "Shape/Triangle.h"
Triangle::Triangle(const glm::dvec4 &p1, const glm::dvec4 &p2, const glm::dvec4 &p3) : p1_(p1), p2_(p2), p3_(p3) {
  e1_ = p2 - p1;
  e2_ = p3 - p1;
  normal_ = {glm::normalize(glm::cross(glm::dvec3(e2_), glm::dvec3(e1_))), 0};
}
Intersections Triangle::local_intersect(const Ray &ray) {
  auto dir_cross_e2 = glm::cross(glm::dvec3(ray.getDirectionVector()),glm::dvec3(e2_));
  auto det = glm::dot(glm::dvec3(e1_), dir_cross_e2);
  Intersections xs;
  if(fabs(det) < 0.00001) return xs;
  auto f = 1/det;
  auto p1_to_origin = ray.getOriginPoint() - p1_;
  auto u = f * glm::dot(glm::dvec3(p1_to_origin), dir_cross_e2);
  if(u < 0 || u > 1) return xs;
  auto origin_cross_e1 = glm::cross(glm::dvec3(p1_to_origin), glm::dvec3(e1_));
  auto v = f * glm::dot(glm::dvec3(ray.getDirectionVector()), origin_cross_e1);
  if(v < 0 || (u+v) > 1) return xs;
  auto t = f * glm::dot(glm::dvec3(e2_), origin_cross_e1);
  xs.addIntersection(t, this);
  return xs;
}
glm::dvec4 Triangle::local_normal_at(const glm::dvec4 &point) const {
  return normal_;
}
const glm::dvec4 &Triangle::getP1() const {
  return p1_;
}
void Triangle::setP1(const glm::dvec4 &P1) {
  p1_ = P1;
}
const glm::dvec4 &Triangle::getP2() const {
  return p2_;
}
void Triangle::setP2(const glm::dvec4 &P2) {
  p2_ = P2;
}
const glm::dvec4 &Triangle::getP3() const {
  return p3_;
}
void Triangle::setP3(const glm::dvec4 &P3) {
  p3_ = P3;
}
const glm::dvec4 &Triangle::getE1() const {
  return e1_;
}
void Triangle::setE1(const glm::dvec4 &E1) {
  e1_ = E1;
}
const glm::dvec4 &Triangle::getE2() const {
  return e2_;
}
void Triangle::setE2(const glm::dvec4 &E2) {
  e2_ = E2;
}
const glm::dvec4 &Triangle::getNormal() const {
  return normal_;
}
void Triangle::setNormal(const glm::dvec4 &Normal) {
  normal_ = Normal;
}
