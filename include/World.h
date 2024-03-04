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

class Intersections;
class World {
public:

private:
  std::vector<std::shared_ptr<Shape>> shape_ptr_list_;
  Light light_;
public:
  void addShapes(std::shared_ptr<Shape> &shape);
  [[nodiscard]] const Light &getLight() const;

  void setLight(const Light &light);
  void setDefault();
  Intersections intersect_world(const Ray &ray);
  glm::dvec3 shade_hit(const Computation &computation);
  glm::dvec3 color_at(const Ray &ray);
  void changeShapeMaterial(size_t shapeIndex, const Material &newMaterial);
  bool isShadowed(const glm::dvec4 &point);
};

#endif //RAYTRACERV2_WORLD_H
