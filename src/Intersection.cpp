//
// Created by l4zy9uy on 2/28/24.
//


#include "Intersection.h"
#include <limits>

Intersection::Intersection(double t, Shape *shapePtr) : t_(t), shape_ptr_(shapePtr) {}

const double & Intersection::getT() const {
  return t_;
}

void Intersection::setT(const double &t) {
  t_ = t;
}

const Shape *Intersection::getShapePtr() const {
  return shape_ptr_;
}

void Intersection::setShapePtr(Shape *shapePtr) {
  shape_ptr_ = shapePtr;
}

Computation Intersection::prepare_computations(const Ray &ray) {
  Computation comps(t_,
                    shape_ptr_,
                    position(ray, t_),
                    -ray.getDirectionVector(),
                    shape_ptr_->normal_at(position(ray, t_)));
  comps.setOverPoint(comps.getPoint() + comps.getNormalVector() * glm::epsilon<double>() * 1000000.0);
  return comps;
}
