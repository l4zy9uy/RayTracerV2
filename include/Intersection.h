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
  Shape *shape_ptr_;
public:
  [[nodiscard]] double getT() const;

  void setT(double t);

  [[nodiscard]] const Shape * getShapePtr() const;

  void setShapePtr(Shape *shapePtr);
  Computation prepare_computations(const Ray &ray);
public:
  Intersection(double t, Shape *shape);
};

#endif //RAYTRACERV2_INTERSECTION_H
