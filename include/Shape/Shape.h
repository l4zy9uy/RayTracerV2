//
// Created by l4zy9uy on 3/4/24.
//

#ifndef RAYTRACERV2_INCLUDE_SHAPE_H
#define RAYTRACERV2_INCLUDE_SHAPE_H
#include "Intersections.h"
#include "Material.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Ray.h"

struct Material;
class Intersections;

class Shape {
public:
  explicit Shape();
  Shape(const glm::dmat4 &Model, double Radius, const glm::dvec4 &Position, Material Material);
public:
  void setTransform(const glm::dmat4 &transform_matrix);
  void setModel(const glm::dmat4 &model);
  [[nodiscard]] double getRadius() const;
  void setRadius(double radius);
  [[nodiscard]] const glm::dvec4 &getPosition() const;
  void setPosition(const glm::dvec4 &position);
  [[nodiscard]] Material getMaterial() const;
  void setMaterial(const Material &material);
  [[nodiscard]] const glm::dmat4 &getModel() const;
public:
  virtual Intersections local_intersect(const Ray &ray) = 0;
  Intersections intersect(const Ray &ray);
  [[nodiscard]] glm::dvec4 normal_at(const glm::dvec4 &point) const;
  [[nodiscard]] virtual glm::dvec4 local_normal_at(const glm::dvec4 &point) const;
  glm::dvec4 world_to_object(glm::dvec4 point) const;
  glm::dvec4 normal_to_world(glm::dvec4 normal) const;
protected:
  glm::dmat4 model_{1.0};
public:
  const Shape *getParentPtr() const;
  void setParentPtr(const Shape *ParentPtr);
protected:
  double radius_ = 1.0;
  glm::dvec4 position_ = glm::dvec4(0.0, 0.0, 0.0, 1.0);
  Material material_{};
  const Shape* parent_ptr_{};
};

#endif //RAYTRACERV2_INCLUDE_SHAPE_H
