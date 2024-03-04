//
// Created by l4zy9uy on 2/28/24.
//

#include "Sphere.h"

Sphere::Sphere(const glm::dmat4 &model, const double &radius, const glm::dvec4 &position, const Material &material)
    : model_(model), radius_(radius), position_(position), material_(material) {}

Intersections Sphere::intersect(const Ray &ray) {
  Intersections result;
  auto ray2 = ray.transform(glm::inverse(model_));
  // the vector from the sphere's center, to the ray origin
  // remember: the sphere is centered at the world origin
  auto sphere_to_ray = ray2.getOriginPoint() - position_;
  auto a = glm::dot(ray2.getDirectionVector(), ray2.getDirectionVector());
  auto b = 2 * glm::dot(ray2.getDirectionVector(), sphere_to_ray);
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

Sphere::Sphere()
    : model_(glm::identity<glm::dmat4>()), radius_(1.0), position_(glm::dvec4(0.0, 0.0, 0.0, 1.0)),
      material_(Material()) {}

void Sphere::setTransform(const glm::dmat4 &transform_matrix) {
  model_ = transform_matrix;
}

glm::dvec4 Sphere::normal_at(const glm::dvec4 &point) const {
  auto object_point = glm::inverse(model_) * point;
  auto object_normal = glm::normalize(object_point - glm::dvec4(0.0, 0.0, 0.0, 1.0));
  glm::dvec4 world_normal = glm::transpose(glm::inverse(model_)) * object_normal;
  world_normal.w = 0.0;
  return glm::normalize(world_normal);
}

const glm::dmat4 &Sphere::getModel() const {
  return model_;
}

void Sphere::setModel(const glm::dmat4 &model) {
  model_ = model;
}

double Sphere::getRadius() const {
  return radius_;
}

void Sphere::setRadius(double radius) {
  radius_ = radius;
}

const glm::dvec4 &Sphere::getPosition() const {
  return position_;
}

void Sphere::setPosition(const glm::dvec4 &position) {
  position_ = position;
}

Material Sphere::getMaterial() const {
  return material_;
}

void Sphere::setMaterial(const Material &material) {
  material_ = material;
}