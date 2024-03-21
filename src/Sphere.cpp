//
// Created by l4zy9uy on 2/28/24.
//

#include "Shape/Sphere.h"

Sphere::Sphere() = default;

Intersections Sphere::local_intersect(const Ray &ray) {
  Intersections result;
  // the vector from the sphere's center, to the ray origin
  // remember: the sphere is centered at the world origin
  auto sphere_to_ray = ray.getOriginPoint() - position_ ;//* glm::transpose(model_);
  auto a = glm::dot(ray.getDirectionVector(), ray.getDirectionVector());
  auto b = 2 * glm::dot(ray.getDirectionVector(), sphere_to_ray);
  auto c = glm::dot(sphere_to_ray, sphere_to_ray) - 1;
  auto discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return result;
  }
  auto t1 = (-b - glm::sqrt(discriminant)) / (2 * a);
  auto t2 = (-b + glm::sqrt(discriminant)) / (2 * a);
  result.addIntersection(t1, this);
  result.addIntersection(t2, this);
  return result;
}

glm::dvec4 Sphere::local_normal_at(const glm::dvec4 &point) const {
  glm::dvec4 res(point);
  res.w = 0.0;
  return res;
}
void Sphere::make_glassy() {
  material_.transparency_ = 1.0;
  material_.refractive_index_ = 1.5;
}

