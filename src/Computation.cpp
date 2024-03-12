//
// Created by l4zy9uy on 3/11/24.
//

#include "Computation.h"
#include <algorithm>

Computation prepare_computations(const Intersection &intersection, const Ray &ray, const Intersections &intersections) {
  auto point = position(ray, intersection.getT());
  auto normal_vector = intersection.getShapePtr()->normal_at(point);
  /*Computation comps;
  comps.t_ = intersection.getT();
  comps.shape_ptr_ = intersection.getShapePtr();
  comps.point_ = point;
  comps.eye_vector_ = -ray.getDirectionVector();
  comps.normal_vector_ = normal_vector;
  comps.reflect_vector_ = glm::reflect(ray.getDirectionVector(), normal_vector);*/
  Computation comps(intersection.getT(),
                    intersection.getShapePtr(),
                    point,
                    -ray.getDirectionVector(),
                    normal_vector,
                    glm::reflect(ray.getDirectionVector(), normal_vector));
  comps.over_point_ = comps.point_ + comps.normal_vector_ * 0.00001;
  comps.under_point_ = comps.point_ - comps.normal_vector_ * 0.00001;

  Containers containers;
  for(const auto &i : intersections.getList()) {
    if(i == intersection) {
      if(containers.getList().empty()) comps.n1_ = 1.0;
      else comps.n1_ = containers.getList().back()->getMaterial().refractive_index_;
    }
    auto include = std::find_if(containers.getList().begin(), containers.getList().end(), [i](const Shape *object) {
      return i.shape_ptr_ == object;
    }) != containers.getList().end();
    if(include) {
      auto rm = std::remove_if(containers.list_.begin(), containers.list_.end(), [i](const Shape *object) {
        return i.shape_ptr_ == object;
      });
      containers.list_.erase(rm, containers.list_.end());
    }
    else {
      containers.list_.push_back(const_cast<Shape*>(i.shape_ptr_));
    }
    if(i == intersection) {
      if(containers.getList().empty()) comps.n2_ = 1.0;
      else comps.n2_ = containers.getList().back()->getMaterial().refractive_index_;
      break;
    }
  }
  /*if (glm::dot(comps.normal_vector_, comps.eye_vector_) < 0) {
    comps.inside_ = true;
    comps.normal_vector_ = -normal_vector;
  } else
    comps.inside_ = false;*/
  return comps;
}

Computation::Computation(const double &t, const Shape *shapePtr, const glm::dvec4 &point, const glm::dvec4 &eye_vector,
                         const glm::dvec4 &normal_vector, const glm::dvec4 &reflect_vector)
    : t_(t), shape_ptr_(shapePtr), point_(point), eye_vector_(eye_vector),
      normal_vector_(normal_vector), reflect_vector_(reflect_vector) {
  if (glm::dot(normal_vector, eye_vector) < 0) {
    inside_ = true;
    normal_vector_ = -normal_vector;
  } else
    inside_ = false;
}
