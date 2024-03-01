//
// Created by l4zy9uy on 2/28/24.
//

#include "Sphere.h"

Sphere::Sphere(const glm::mat4 &model, const float &radius, const glm::vec4 &position, const Material &material)
	: model_(model), radius_(radius), position_(position), material_(material) {}

Intersections Sphere::intersect(const Ray &ray) {
  Intersections result;
  auto ray2 = ray.transform(glm::inverse(model_));
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

Sphere::Sphere() : model_(glm::identity<glm::mat4>()), radius_(1.0f), position_(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)), material_(Material()) {}

void Sphere::setTransform(const glm::mat4 &transform_matrix) {
  model_ = transform_matrix;
}

glm::vec4 Sphere::normal_at(const glm::vec4 &point) const {
    auto object_point = glm::inverse(model_) * point;
    auto object_normal = glm::normalize(object_point - glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    glm::vec4 world_normal = glm::transpose(glm::inverse(model_)) * object_normal;
    world_normal.w = 0.0f;
    return glm::normalize(world_normal);
}

const glm::mat4 &Sphere::getModel() const {
    return model_;
}

void Sphere::setModel(const glm::mat4 &model) {
    model_ = model;
}

float Sphere::getRadius() const {
    return radius_;
}

void Sphere::setRadius(float radius) {
    radius_ = radius;
}

const glm::vec4 &Sphere::getPosition() const {
    return position_;
}

void Sphere::setPosition(const glm::vec4 &position) {
    position_ = position;
}

const Material &Sphere::getMaterial() const {
    return material_;
}

void Sphere::setMaterial(const Material &material) {
    material_ = material;
}