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
  Material material(glm::dvec3(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200.0);
  s1.setMaterial(material);

  shape_ptr_list_.push_back(std::make_shared<Sphere>(s1));
  s2.setTransform(glm::scale(glm::identity<glm::dmat4>(), glm::dvec3(0.5)));
  shape_ptr_list_.push_back(std::make_shared<Sphere>(s2));
}

Intersections World::intersect_world(const Ray &ray) {
  Intersections result;
  for (auto &shape_ptr : shape_ptr_list_) {
    /*auto ray2 = ray.transform(glm::inverse(shape_ptr->getModel()));
    auto sphere_to_ray = ray2.getOriginPoint() - shape_ptr->getPosition();
    auto a = glm::dot(ray2.getDirectionVector(), ray2.getDirectionVector());
    auto b = 2 * glm::dot(ray2.getDirectionVector(), sphere_to_ray);
    auto c = glm::dot(sphere_to_ray, sphere_to_ray) - 1;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
      continue;
    }
    auto t1 = (-b - glm::sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + glm::sqrt(discriminant)) / (2 * a);
    result.addIntersection(t1, shape_ptr.get());
    result.addIntersection(t2, shape_ptr.get());*/
    auto i = shape_ptr->intersect(ray);
    result.addIntersections(i);
  }

  return result;
}


glm::dvec3 World::shade_hit(const Computation &computation) {
  auto shadowed = isShadowed(computation.getOverPoint());
  return light_.lighting(
      computation.getShapePtr()->getMaterial(), *computation.getShapePtr(),
      computation.getEyeVector(),
      computation.getNormalVector(),
      shadowed,
      computation.getPoint());
}

glm::dvec3 World::color_at(const Ray &ray) {
  auto intersections = intersect_world(ray);
  auto hit = intersections.hit();
  if (hit.has_value()) {
    return shade_hit(hit->prepare_computations(ray));
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
void World::addShape(std::shared_ptr<Shape> shape) {
  shape_ptr_list_.push_back(shape);
}
