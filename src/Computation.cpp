//
// Created by l4zy9uy on 3/1/24.
//

#include "Computation.h"

Computation::Computation(const double &t, Shape *shapePtr, const glm::dvec4 &point, const glm::dvec4 &eye_vector,
                         const glm::dvec4 &normal_vector, const glm::dvec4 &reflectv)
    : t_(t), shape_ptr_(shapePtr), point_(point), eye_vector_(eye_vector),
      normal_vector_(normal_vector), reflectv_(reflectv) {
  if (glm::dot(normal_vector, eye_vector) < 0) {
    inside_ = true;
    normal_vector_ = -normal_vector;
  } else
    inside_ = false;
}

const double &Computation::getT() const {
  return t_;
}

void Computation::setT(const double &t) {
  t_ = t;
}

Shape *Computation::getShapePtr() const {
  return shape_ptr_;
}

void Computation::setShapePtr(Shape *shapePtr) {
  shape_ptr_ = shapePtr;
}

const glm::dvec4 &Computation::getPoint() const {
  return point_;
}

void Computation::setPoint(const glm::dvec4 &point) {
  point_ = point;
}

const glm::dvec4 &Computation::getEyeVector() const {
  return eye_vector_;
}

void Computation::setEyeVector(const glm::dvec4 &eye_vector) {
  eye_vector_ = eye_vector;
}

const glm::dvec4 &Computation::getNormalVector() const {
  return normal_vector_;
}

void Computation::setNormalVector(const glm::dvec4 &normal_vector) {
  normal_vector_ = normal_vector;
}

const bool &Computation::isInside() const {
  return inside_;
}

void Computation::setInside(const bool &inside) {
  inside_ = inside;
}
const glm::dvec4 &Computation::getOverPoint() const {
  return over_point_;
}
void Computation::setOverPoint(const glm::dvec4 &OverPoint) {
  over_point_ = OverPoint;
}
const glm::dvec4 &Computation::getReflectv() const {
  return reflectv_;
}
void Computation::setReflectv(const glm::dvec4 &Reflectv) {
  reflectv_ = Reflectv;
}
double Computation::getN1() const {
  return n1_;
}
void Computation::setN1(double N1) {
  n1_ = N1;
}
double Computation::getN2() const {
  return n2_;
}
void Computation::setN2(double N2) {
  n2_ = N2;
}
