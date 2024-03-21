//
// Created by l4zy9uy on 3/4/24.
//

#include "Shape/Shape.h"

#include <utility>

Shape::Shape() = default;

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

glm::dvec4 Shape::normal_at(const glm::dvec4 &point) const {
  auto local_point = glm::inverse(model_) * point;
  auto local_normal = local_normal_at(local_point);
  auto world_normal = glm::transpose(glm::inverse(model_)) * local_normal;
  world_normal.w = 0.0;
  return glm::normalize(world_normal);
}
glm::dvec4 Shape::local_normal_at(const glm::dvec4 &point) const {
  return {point.x, point.y, point.z, 0.0};
}
const Shape *Shape::getParentPtr() const {
  return parent_ptr_;
}
void Shape::setParentPtr(const Shape *ParentPtr) {
  parent_ptr_ = ParentPtr;
}


