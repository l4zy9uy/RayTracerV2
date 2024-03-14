//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_WORLD_H
#define RAYTRACERV2_WORLD_H
#include "Light.h"
#include "Shape.h"
#include "Intersections.h"
#include <vector>
#include <memory>
#include "Computations.h"

class Intersections;
class World {
public:
  void addShape(const std::shared_ptr<Shape>& shape);
  [[nodiscard]] const Light &getLight() const;
  void setLight(const Light &light);
  void setDefault();
  void changeShapeMaterial(size_t shapeIndex, const Material &newMaterial);
  std::shared_ptr<Shape> getShape(const unsigned int &index);
public:
  Intersections intersect_world(const Ray &ray);
  glm::dvec3 shade_hit(const Computations &computation, const int &remaining);
  glm::dvec3 color_at(const Ray &ray, const int &remaining);
  bool isShadowed(const glm::dvec4 &point);
  glm::dvec3 reflected_color(const Computations &computation, const int &remaining);
  glm::dvec3 refracted_color(const Computations &comp, const int &remaining);
private:
  mutable std::vector<std::shared_ptr<Shape>> shape_ptr_list_;
  Light light_;
};

#endif //RAYTRACERV2_WORLD_H
