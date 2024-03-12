//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTION_H
#define RAYTRACERV2_INTERSECTION_H

#include <memory>
#include "Shape.h"
//#include "Computation.h"
#include "Intersections.h"
//#include "Containers.h"
class Shape;
//class Computation;
class Ray;
class Intersections;

class Intersection {
public:
  double t_;
  const Shape *shape_ptr_;
public:
  Intersection(double t, Shape* shapePtr);
  Intersection(const Intersection& other);
  Intersection& operator=(const Intersection& other);
  Intersection(Intersection&& other) noexcept;
  Intersection& operator=(Intersection&& other) noexcept;
  ~Intersection() = default;

  [[nodiscard]] const double& getT() const;
  void setT(const double& t);
  [[nodiscard]] const Shape* getShapePtr() const;
  void setShapePtr(Shape* shapePtr);
};

#endif //RAYTRACERV2_INTERSECTION_H
