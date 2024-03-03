//
// Created by l4zy9uy on 2/28/24.
//


#include "Intersection.h"

Intersection::Intersection(float t, Sphere *sphere) : t_(t), sphere_ptr_(sphere) {}

float Intersection::getT() const {
  return t_;
}

void Intersection::setT(float t) {
  t_ = t;
}

const Sphere *Intersection::getSpherePtr() const {
  return sphere_ptr_;
}

void Intersection::setSpherePtr(Sphere *spherePtr) {
  sphere_ptr_ = spherePtr;
}

Computation Intersection::prepare_computations(const Ray &ray) {
  Computation comps(t_,
              sphere_ptr_,
              position(ray, t_),
              -ray.getDirectionVector(),
              sphere_ptr_->normal_at(position(ray, t_)));
  comps.setOverPoint(comps.getPoint() + comps.getNormalVector() * 0.000001f);
  return comps;
}
