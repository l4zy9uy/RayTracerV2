//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_RAY_H
#define RAYTRACERV2_RAY_H

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

class Ray {
public:
  [[nodiscard]] const glm::dvec4 &getOriginPoint() const;

  void setOriginPoint(const glm::dvec4 &originPoint);

  [[nodiscard]] const glm::dvec4 &getDirectionVector() const;

  void setDirectionVector(const glm::dvec4 &directionVector);

  Ray(const glm::dvec4 &originPoint, const glm::dvec4 &directionVector);

  [[nodiscard]] Ray transform(const glm::dmat4 &transform_matrix) const;

private:
  glm::dvec4 direction_vector_;
  glm::dvec4 origin_point_;
};

glm::dvec4 position(const Ray &ray, const double &t);

#endif //RAYTRACERV2_RAY_H
