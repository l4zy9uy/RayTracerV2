//
// Created by l4zy9uy on 2/28/24.
//


#include "Intersection.h"
#include <limits>

Intersection::Intersection(double t, Sphere *sphere) : t_(t), shape_ptr_(sphere) {}

double Intersection::getT() const {
  return t_;
}

void Intersection::setT(double t) {
  t_ = t;
}

const Sphere *Intersection::getSpherePtr() const {
  return shape_ptr_;
}

void Intersection::setSpherePtr(Sphere *spherePtr) {
  shape_ptr_ = spherePtr;
}

Computation Intersection::prepare_computations(const Ray &ray) {
  Computation comps(t_,
                    shape_ptr_,
                    position(ray, t_),
                    -ray.getDirectionVector(),
                    shape_ptr_->local_normal_at(position(ray, t_)));
  comps.setOverPoint(comps.getPoint() + comps.getNormalVector() * std::numeric_limits<double>::epsilon() * 100000.0);
  return comps;
}
