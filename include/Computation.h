//
// Created by l4zy9uy on 3/1/24.
//

#ifndef RAYTRACERV2_COMPUTATION_H
#define RAYTRACERV2_COMPUTATION_H
#include "Shape.h"
#include "Intersections.h"
#include "Containers.h"
#include <glm/glm.hpp>

class Sphere;
class Ray;
class Shape;

struct Computation {
  double t_;
  const Shape *shape_ptr_;
  glm::dvec4 normal_vector_;
  glm::dvec4 point_;
  glm::dvec4 eye_vector_;
  bool inside_;
  glm::dvec4 over_point_;
  glm::dvec4 reflect_vector_;
  double n1_;
  double n2_;
public:
  /*Computation(const double &t,
              const Shape *shapePtr,
              const glm::dvec4 &point,
              const glm::dvec4 &eye_vector,
              const glm::dvec4 &normal_vector,
              const glm::dvec4 &reflect_vector);*/
};

Computation prepare_computations(const Intersection &intersection, const Ray &ray, const Intersections &intersections = Intersections());
#endif //RAYTRACERV2_COMPUTATION_H
