//
// Created by l4zy9uy on 3/1/24.
//

#include <glm/ext/matrix_transform.hpp>
#include "World.h"
#include "Shape/Sphere.h"

const Light &World::getLight() const {
  return light_;
}

void World::setLight(const Light &light) {
  light_ = light;
}

std::shared_ptr<Shape> World::getShape(const unsigned int &index) {
  return shape_ptr_list_.at(index);
}

void World::setDefault() {
  light_ = Light(glm::dvec3(1.0), glm::dvec4(-10.0, 10.0, -10.0, 1.0));
  Sphere s1, s2;
  Material material;
  material.color_ = glm::dvec3(0.8, 1.0, 0.6);
  material.ambient_ = 0.1;
  material.diffuse_ = 0.7;
  material.specular_ = 0.2;
  material.shininess_ = 200.0;
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

glm::dvec3 World::shade_hit(const Computations &computation, const int &remaining) {
  auto shadowed = isShadowed(computation.over_point_);
  auto surface = light_.lighting(
      computation.shape_ptr_->getMaterial(),
      *computation.shape_ptr_,
      computation.eye_vector_,
      computation.normal_vector_,
      shadowed,
      computation.over_point_);
  auto reflected = reflected_color(computation, remaining);
  auto refracted = refracted_color(computation, remaining);

  auto material = computation.shape_ptr_->getMaterial();
  if(material.reflective_ > 0 && material.transparency_ > 0) {
    auto reflectance = schlick(computation);
    return  surface + reflected * reflectance + refracted * (1 - reflectance);
  }
  return surface + reflected + refracted;
}

glm::dvec3 World::color_at(const Ray &ray, const int &remaining) {
  auto intersections = intersect_world(ray);
  auto hit = intersections.hit();
  if (hit.has_value()) {
    auto comps = prepare_computations(hit.value(), ray, intersections);
    return shade_hit(comps, remaining);
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
  if(ht.has_value() && ht->t_ < distance)
    return true;
  return false;
}

void World::addShape(const std::shared_ptr<Shape>& shape) {
  shape_ptr_list_.push_back(shape);
}

glm::dvec3 World::reflected_color(const Computations &computation, const int &remaining) {
  if(fabs(computation.shape_ptr_->getMaterial().reflective_ - 0.0) < 0.00001) {
    return {0.0, 0.0, 0.0};
  }
  if(remaining <= 0) return {0.0, 0.0, 0.0};
  auto color = color_at(Ray(computation.over_point_, computation.reflect_vector_), remaining-1);
  return color * computation.shape_ptr_->getMaterial().reflective_;
}

glm::dvec3 World::refracted_color(const Computations &comp, const int &remaining) {
  if(remaining <= 0) return {0.0, 0.0, 0.0};
  auto n_ratio = comp.n1_ / comp.n2_;
  auto cos_i = glm::dot(comp.eye_vector_, comp.normal_vector_);
  auto sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);
  if(sin2_t > 1.0) return {0.0, 0.0, 0.0};
  auto cos_t = sqrt(1.0 - sin2_t);
  auto direction = comp.normal_vector_ * (n_ratio * cos_i - cos_t) - comp.eye_vector_ * n_ratio;
  Ray refracted_ray(comp.under_point_, direction);
  return color_at(refracted_ray, remaining-1) * comp.shape_ptr_->getMaterial().transparency_;

}
