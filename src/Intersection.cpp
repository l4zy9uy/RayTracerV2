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

/*Computation Intersection::prepare_computations(const Ray &ray, const Intersections &intersections = Intersections()) {
  Containers containers;
  for(const auto &i : intersections.getList()) {
  }
  auto point = position(ray, t_);
  auto normal_vector = shape_ptr_->normal_at(point);
  Computation comps(t_,
                    shape_ptr_,
                    point,
                    -ray.getDirectionVector(),
                    normal_vector,
                    glm::reflect(ray.getDirectionVector(), normal_vector));
  comps.over_point_ = comps.point_ + comps.normal_vector_ * 0.00001;
  return comps;
}*/
