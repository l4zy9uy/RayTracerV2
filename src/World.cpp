//
// Created by l4zy9uy on 3/1/24.
//

#include <glm/ext/matrix_transform.hpp>
#include "World.h"
#include "Sphere.h"

const Light &World::getLight() const {
  return light_;
}

void World::setLight(const Light &light) {
  light_ = light;
}

void World::setDefault() {
  light_ = Light(glm::dvec3(1.0), glm::dvec4(-10.0, 10.0, -10.0, 1.0));
  Sphere s1, s2;
  Material material(glm::dvec3(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0, 0.0);
  s1.setMaterial(material);

  shape_ptr_list_.push_back(std::make_shared<Sphere>(s1));
  s2.setTransform(glm::scale(glm::identity<glm::dmat4>(), glm::dvec3(0.5)));
  shape_ptr_list_.push_back(std::make_shared<Sphere>(s2));
}

Intersections World::intersect_world(const Ray &ray) {
  Intersections result;
  for (auto &shape_ptr : shape_ptr_list_) {
    auto i = shape_ptr->intersect(ray);
    result.addIntersections(i);
  }
  result.sort();
  return result;
}


glm::dvec3 World::shade_hit(const Computation &computation, const int &remaining) {
  auto shadowed = isShadowed(computation.getOverPoint());
  auto surface = light_.lighting(
      computation.getShapePtr()->getMaterial(), *computation.getShapePtr(),
      computation.getEyeVector(),
      computation.getNormalVector(),
      shadowed,
      computation.getPoint());
  auto reflected = reflected_color(computation, remaining);
  return surface + reflected;
}

glm::dvec3 World::color_at(const Ray &ray, const int &remaining) {
  auto intersections = intersect_world(ray);
  auto hit = intersections.hit();
  if (hit.has_value()) {
    return shade_hit(hit->prepare_computations(ray, Intersections()), remaining);
  } else {
    return {0.0, 0.0, 0.0};
  }
}

void World::changeShapeMaterial(size_t shapeIndex, const Material &newMaterial) {
  if (shapeIndex < shape_ptr_list_.size()) {
    shape_ptr_list_[shapeIndex]->setMaterial(newMaterial);
  }
}

bool World::isShadowed(const glm::dvec4 &point) {
  auto v = light_.getPosition() - point;
  auto distance = glm::length(v);
  auto direction = glm::normalize(v);
  Ray r(point, direction);
  auto intersections = intersect_world(r);
  std::optional<Intersection> ht = intersections.hit();
  if(ht.has_value() && ht->getT() < distance)
    return true;
  return false;
}
void World::addShape(const std::shared_ptr<Shape>& shape) {
  shape_ptr_list_.push_back(shape);
}
glm::dvec3 World::reflected_color(const Computation &computation, const int &remaining) {
  if(fabs(computation.getShapePtr()->getMaterial().getReflective() - 0.0) < 0.00001) {
    return {0.0, 0.0, 0.0};
  }
  if(remaining <= 0) return {0.0, 0.0, 0.0};
  auto color = color_at(Ray(computation.getOverPoint(), computation.getReflectv()), remaining-1);
  return color * computation.getShapePtr()->getMaterial().getReflective();
}
std::shared_ptr<Shape> World::getShape(const unsigned int &index) {
  return shape_ptr_list_.at(index);
}
