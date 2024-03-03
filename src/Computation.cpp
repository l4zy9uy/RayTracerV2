//
// Created by l4zy9uy on 3/1/24.
//

#include "Computation.h"

Computation::Computation(float t, Sphere *spherePtr, const glm::vec4 &point, const glm::vec4 &eye_vector,
                         const glm::vec4 &normal_vector) : t_(t), sphere_ptr(spherePtr), point_(point), eye_vector_(eye_vector),
                                                           normal_vector_(normal_vector) {
  if (glm::dot(normal_vector, eye_vector) < 0) {
    inside_ = true;
    normal_vector_ = -normal_vector;
  } else
    inside_ = false;
}

float Computation::getT() const {
  return t_;
}

void Computation::setT(float t) {
  t_ = t;
}

Sphere *Computation::getSpherePtr() const {
  return sphere_ptr;
}

void Computation::setSpherePtr(Sphere *spherePtr) {
  sphere_ptr = spherePtr;
}

const glm::vec4 &Computation::getPoint() const {
  return point_;
}

void Computation::setPoint(const glm::vec4 &point) {
  point_ = point;
}

const glm::vec4 &Computation::getEyeVector() const {
  return eye_vector_;
}

void Computation::setEyeVector(const glm::vec4 &eye_vector) {
  eye_vector_ = eye_vector;
}

const glm::vec4 &Computation::getNormalVector() const {
  return normal_vector_;
}

void Computation::setNormalVector(const glm::vec4 &normal_vector) {
  normal_vector_ = normal_vector;
}

bool Computation::isInside() const {
  return inside_;
}

void Computation::setInside(bool inside) {
  inside_ = inside;
}
const glm::vec4 &Computation::getOverPoint() const {
  return over_point_;
}
void Computation::setOverPoint(const glm::vec4 &OverPoint) {
  over_point_ = OverPoint;
}
