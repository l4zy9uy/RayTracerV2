//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTION_H
#define RAYTRACERV2_INTERSECTION_H

#include <memory>
#include "Shape.h"
#include "Computation.h"

class Shape;
class Computation;
class Ray;

class Intersection {
private:
  double t_;
public:
  [[nodiscard]] double getT() const;

  void setT(double t);

  [[nodiscard]] const Sphere *getSpherePtr() const;

  void setSpherePtr(Sphere *spherePtr);
  Computation prepare_computations(const Ray &ray);
private:
  Shape *shape_ptr_;
public:
  Intersection(double t, Sphere *sphere);
};

#endif //RAYTRACERV2_INTERSECTION_H
