//
// Created by l4zy9uy on 3/11/24.
//

#include "Computation.h"
#include <algorithm>
Computation prepare_computations(const Intersection &intersection, const Ray &ray, const Intersections &intersections) {
  auto point = position(ray, intersection.t_);
  auto normal_vector = intersection.shape_ptr_->normal_at(point);
  Computation comps{};
  comps.t_ = intersection.t_;
  comps.shape_ptr_ = intersection.shape_ptr_;
  comps.point_ = point;
  comps.eye_vector_ = -ray.getDirectionVector();
  comps.normal_vector_ = normal_vector;
  comps.reflect_vector_ = glm::reflect(ray.getDirectionVector(), normal_vector);

  if (glm::dot(normal_vector, comps.eye_vector_) < 0) {
    comps.inside_ = true;
    comps.normal_vector_ = -normal_vector;
  } else
    comps.inside_ = false;

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

  return comps;
}
