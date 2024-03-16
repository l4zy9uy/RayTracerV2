//
// Created by l4zy9uy on 3/11/24.
//

#include "Computations.h"
#include <algorithm>
Computations prepare_computations(const Intersection &intersection, const Ray &ray, const Intersections &intersections) {
  auto point = ray.at(intersection.t_);
  auto normal_vector = intersection.shape_ptr_->normal_at(point);
  Computations comps{};
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
      if(containers.list_.empty()) comps.n1_ = 1.0;
      else comps.n1_ = containers.list_.back()->getMaterial().refractive_index_;
    }
    auto include = std::find_if(containers.list_.begin(), containers.list_.end(), [i](const Shape *object) {
      return i.shape_ptr_ == object;
    }) != containers.list_.end();
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
      if(containers.list_.empty()) comps.n2_ = 1.0;
      else comps.n2_ = containers.list_.back()->getMaterial().refractive_index_;
      break;
    }
  }

  return comps;
}

double schlick(Computations comps) {
  auto temp_cos = glm::dot(comps.eye_vector_, comps.normal_vector_);

  if(comps.n1_ > comps.n2_) {
    auto n = comps.n1_ / comps.n2_;
    auto sin2_t = n*n * (1 - temp_cos*temp_cos);
    if(sin2_t > 1.0) return 1.0;

    auto cos_t = sqrt(1.0 - sin2_t);
    temp_cos = cos_t;
  }

  auto r0 = ((comps.n1_ - comps.n2_) / (comps.n1_ + comps.n2_)) * ((comps.n1_ - comps.n2_) / (comps.n1_ + comps.n2_));
  return r0 + (1 - r0) * pow(1-temp_cos, 5);
}
