//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_SPHERE_H
#define RAYTRACERV2_SPHERE_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "Intersections.h"
#include "Ray.h"
#include <memory>
class Intersections;

class Sphere {
public:
  Sphere(const glm::mat4 &model, const float &radius, const glm::vec4 &position);

  explicit Sphere();
  void setTransform(const glm::mat4 &transform_matrix);
  Intersections intersect(const Ray &ray);
private:
  glm::mat4 model_ = glm::identity<glm::mat4>();
  float radius_ = 1.0f;
  glm::vec4 position_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
};

#endif //RAYTRACERV2_SPHERE_H
