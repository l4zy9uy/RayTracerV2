//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_WORLD_H
#define RAYTRACERV2_WORLD_H
#include "Light.h"
#include "Sphere.h"
class World {
public:
  World();

private:
  std::vector<Sphere> spheres_;
  Light light_;
public:
  [[nodiscard]] const std::vector<Sphere> &getSpheres() const;

  void setSpheres(const std::vector<Sphere> &spheres);
  void addSphere(const Sphere &sphere);
  [[nodiscard]] const Light &getLight() const;

  void setLight(const Light &light);
  void setDefault();
  Intersections intersect_world(const Ray &ray);
  glm::vec3 shade_hit(const Computation &computation);
  glm::vec3 color_at(const Ray &ray);
  void changeSphereMaterial(size_t sphereIndex, const Material &newMaterial);
  bool isShadowed(const glm::vec4 &point);
};

#endif //RAYTRACERV2_WORLD_H
