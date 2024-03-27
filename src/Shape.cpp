//
// Created by l4zy9uy on 3/4/24.
//

#include "Shape/Shape.h"

#include <utility>

Shape::Shape(const glm::dmat4 &Model, double Radius, const glm::dvec4 &Position, Material Material) : model_(
    Model), radius_(Radius), position_(Position), material_(std::move(Material)) {}

void Shape::setTransform(const glm::dmat4 &transform_matrix) {
  model_ = transform_matrix;
}

const glm::dmat4 &Shape::getModel() const {
  return model_;
}
void Shape::setModel(const glm::dmat4 &model) {

}
double Shape::getRadius() const {
  return radius_;
}
void Shape::setRadius(double radius) {

}
const glm::dvec4 &Shape::getPosition() const {
  return position_;
}
void Shape::setPosition(const glm::dvec4 &position) {

}
Material Shape::getMaterial() const {
  return material_;
}
void Shape::setMaterial(const Material &material) {
  material_ = material;
}

Intersections Shape::intersect(const Ray &ray) {
  auto local_ray = ray.transform(glm::inverse(model_));
  return local_intersect(local_ray);
}

glm::dvec4 Shape::normal_at(const glm::dvec4 &point, const Intersection &hit) const {
  auto local_point = world_to_object(point);
  auto local_normal = local_normal_at(local_point, hit);
  return normal_to_world(local_normal);
}
glm::dvec4 Shape::local_normal_at(const glm::dvec4 &point, const Intersection &hit) const {
  return {point.x, point.y, point.z, 0.0};
}
const Shape *Shape::getParentPtr() const {
  return parent_ptr_;
}
void Shape::setParentPtr(const Shape *ParentPtr) {
  parent_ptr_ = ParentPtr;
}
glm::dvec4 Shape::world_to_object(glm::dvec4 point) const {
  if(parent_ptr_ != nullptr) {
    point = parent_ptr_->world_to_object(point);
  }
  return glm::inverse(model_) * point;
}
glm::dvec4 Shape::normal_to_world(glm::dvec4 normal) const {
  normal = glm::transpose(glm::inverse(model_)) * normal;
  normal.w = 0;
  normal = glm::normalize(normal);
  if(parent_ptr_ != nullptr)
    normal = parent_ptr_->normal_to_world(normal);
  return normal;
}


