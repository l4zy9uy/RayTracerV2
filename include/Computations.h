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

struct Computations {
  explicit Computations() = default;

  double t_;
  const Shape *shape_ptr_;
  glm::dvec4 normal_vector_;
  glm::dvec4 point_;
  glm::dvec4 eye_vector_;
  glm::dvec4 over_point_;
  glm::dvec4 reflect_vector_;
  double n1_;
  double n2_;
  glm::dvec4 under_point_;
  bool inside_;
};

Computations prepare_computations(const Intersection &intersection, const Ray &ray, const Intersections &intersections = Intersections());
double schlick(Computations comps);
#endif //RAYTRACERV2_COMPUTATION_H
