//
// Created by l4zy9uy on 3/1/24.
//

#include "World.h"

const std::vector<Sphere> &World::getSpheres() const {
  return spheres_;
}

void World::setSpheres(const std::vector<Sphere> &spheres) {
  spheres_ = spheres;
}

const Light &World::getLight() const {
  return light_;
}

void World::setLight(const Light &light) {
  light_ = light;
}

void World::setDefault() {
  light_ = Light(glm::vec3(1.0f), glm::vec4(-10.0f, 10.0f, -10.0f, 1.0f));
  Sphere s1, s2;
  Material material(glm::vec3(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f);
  s1.setMaterial(material);
  spheres_.push_back(s1);
  s2.setTransform(glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.5f)));
  spheres_.push_back(s2);
}

Intersections World::intersect_world(const Ray &ray) {
  Intersections result;
  for (auto &sphere : spheres_) {
    auto ray2 = ray.transform(glm::inverse(sphere.getModel()));
    auto sphere_to_ray = ray2.getOriginPoint() - sphere.getPosition();
    auto a = glm::dot(ray2.getDirectionVector(), ray2.getDirectionVector());
    auto b = 2 * glm::dot(ray2.getDirectionVector(), sphere_to_ray);
    auto c = glm::dot(sphere_to_ray, sphere_to_ray) - 1;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
      continue;
    }
    auto t1 = (-b - glm::sqrt(discriminant)) / (2 * a);
    auto t2 = (-b + glm::sqrt(discriminant)) / (2 * a);
    result.addIntersection(t1, &sphere);
    result.addIntersection(t2, &sphere);
  }
  return result;
}

World::World() : spheres_(), light_() {}

glm::vec3 World::shade_hit(const Computation &computation) {
  auto shadowed = isShadowed(computation.getOverPoint());
  return light_.lighting(
      computation.getSpherePtr()->getMaterial(),
      computation.getPoint(),
      computation.getEyeVector(),
      computation.getNormalVector(),
      shadowed);
}

glm::vec3 World::color_at(const Ray &ray) {
  auto intersections = intersect_world(ray);
  auto hit = intersections.hit();
  if (hit.has_value()) {
    return shade_hit(hit->prepare_computations(ray));
  } else {
    return {0.0f, 0.0f, 0.0f};
  }
}

void World::changeSphereMaterial(size_t sphereIndex, const Material &newMaterial) {
  if (sphereIndex < spheres_.size()) {
    spheres_[sphereIndex].setMaterial(newMaterial);
  }
}

void World::addSphere(const Sphere &sphere) {
  spheres_.push_back(sphere);
}
bool World::isShadowed(const glm::vec4 &point) {
  auto v = light_.getPosition() - point;
  auto distance = glm::length(v);
  auto direction = glm::normalize(v);
  Ray r(point, direction);
  auto intersections = intersect_world(r);
  auto h = intersections.hit();
  if(h.has_value() && h->getT() < distance)
    return true;
  return false;
}
