//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_COMPUTATION_H
#define RAYTRACERV2_COMPUTATION_H
#include "Sphere.h"

class Sphere;
class Ray;

class Computation {
private:
  float t_;
  Sphere *sphere_ptr;
  glm::vec4 normal_vector_;
  glm::vec4 point_;
  glm::vec4 eye_vector_;
  bool inside_;
  glm::vec4 over_point_;
public:
  const glm::vec4 &getOverPoint() const;
  void setOverPoint(const glm::vec4 &OverPoint);
public:
  Computation(float t, Sphere *spherePtr, const glm::vec4 &point, const glm::vec4 &eye_vector, const glm::vec4 &normal_vector);

  [[nodiscard]] bool isInside() const;

  void setInside(bool inside);

  [[nodiscard]] float getT() const;

  void setT(float t);

  [[nodiscard]] Sphere *getSpherePtr() const;

  void setSpherePtr(Sphere *spherePtr);

  [[nodiscard]] const glm::vec4 &getPoint() const;

  void setPoint(const glm::vec4 &point);

  [[nodiscard]] const glm::vec4 &getEyeVector() const;

  void setEyeVector(const glm::vec4 &eye_vector);

  [[nodiscard]] const glm::vec4 &getNormalVector() const;

  void setNormalVector(const glm::vec4 &normal_vector);
};

#endif //RAYTRACERV2_COMPUTATION_H
