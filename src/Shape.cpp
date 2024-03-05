//
// Created by l4zy9uy on 3/4/24.
//

#include "Shape.h"

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
Shape::Shape(const glm::dmat4 &Model, double Radius, const glm::dvec4 &Position, const Material &Material) : model_(
    Model), radius_(Radius), position_(Position), material_(Material) {}

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
Shape::Shape() = default;
/*
Intersections Shape::local_intersect(const Ray &ray) {
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
glm::dvec4 Shape::local_normal_at(const glm::dvec4 &point) const {
  glm::dvec4 res(point);
  res.w = 0.0;
  return res;
}
*/
