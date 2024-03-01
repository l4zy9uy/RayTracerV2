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
#include "Material.h"
class Intersections;

class Sphere {
public:
  Sphere(const glm::mat4 &model, const float &radius, const glm::vec4 &position, const Material &material);

  explicit Sphere();
  void setTransform(const glm::mat4 &transform_matrix);
  Intersections intersect(const Ray &ray);
  [[nodiscard]] glm::vec4 normal_at(const glm::vec4 &point) const;

    [[nodiscard]] const glm::mat4 &getModel() const;

    void setModel(const glm::mat4 &model);

    [[nodiscard]] float getRadius() const;

    void setRadius(float radius);

    [[nodiscard]] const glm::vec4 &getPosition() const;

    void setPosition(const glm::vec4 &position);

    [[nodiscard]] const Material getMaterial() const;

    void setMaterial(const Material &material);

private:
  glm::mat4 model_ = glm::identity<glm::mat4>();
  float radius_ = 1.0f;
  glm::vec4 position_ = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  Material material_;
};

#endif //RAYTRACERV2_SPHERE_H
