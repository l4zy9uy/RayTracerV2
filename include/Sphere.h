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
  Sphere(const glm::dmat4 &model, const double &radius, const glm::dvec4 &position, const Material &material);

  explicit Sphere();
  void setTransform(const glm::dmat4 &transform_matrix);
  Intersections intersect(const Ray &ray);
  [[nodiscard]] glm::dvec4 normal_at(const glm::dvec4 &point) const;

    [[nodiscard]] const glm::dmat4 &getModel() const;

    void setModel(const glm::dmat4 &model);

    [[nodiscard]] double getRadius() const;

    void setRadius(double radius);

    [[nodiscard]] const glm::dvec4 &getPosition() const;

    void setPosition(const glm::dvec4 &position);

    [[nodiscard]] Material getMaterial() const;

    void setMaterial(const Material &material);

private:
  glm::dmat4 model_ = glm::identity<glm::dmat4>();
  double radius_ = 1.0;
  glm::dvec4 position_ = glm::dvec4(0.0, 0.0, 0.0, 1.0);
  Material material_;
};

#endif //RAYTRACERV2_SPHERE_H
