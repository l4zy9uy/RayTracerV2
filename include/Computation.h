//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_COMPUTATION_H
#define RAYTRACERV2_COMPUTATION_H
#include "Shape.h"
#include <glm/glm.hpp>

class Sphere;
class Ray;
class Shape;

class Computation {
private:
  bool inside_;
public:
  const glm::dvec4 &getReflectv() const;
  void setReflectv(const glm::dvec4 &Reflectv);
private:
  double t_;
  Shape *shape_ptr_;
  glm::dvec4 normal_vector_;
  glm::dvec4 point_;
  glm::dvec4 eye_vector_;
  glm::dvec4 over_point_;
  glm::dvec4 reflectv_;
public:
  [[nodiscard]] const glm::dvec4 &getOverPoint() const;
  void setOverPoint(const glm::dvec4 &OverPoint);
  Computation(const double &t,
              Shape *shapePtr,
              const glm::dvec4 &point,
              const glm::dvec4 &eye_vector,
              const glm::dvec4 &normal_vector,
              const glm::dvec4 &reflectv);

  [[nodiscard]] const bool & isInside() const;

  void setInside(const bool &inside);

  [[nodiscard]] const double & getT() const;

  void setT(const double &t);

  [[nodiscard]] Shape *getShapePtr() const;

  void setShapePtr(Shape *shapePtr);

  [[nodiscard]] const glm::dvec4 &getPoint() const;

  void setPoint(const glm::dvec4 &point);

  [[nodiscard]] const glm::dvec4 &getEyeVector() const;

  void setEyeVector(const glm::dvec4 &eye_vector);

  [[nodiscard]] const glm::dvec4 &getNormalVector() const;

  void setNormalVector(const glm::dvec4 &normal_vector);
};

#endif //RAYTRACERV2_COMPUTATION_H
