//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTION_H
#define RAYTRACERV2_INTERSECTION_H

#include <memory>
#include "Shape/Shape.h"
#include "Intersections.h"
class Shape;

class Ray;
class Intersections;

struct Intersection {
  Intersection(const double &t, Shape* shapePtr);
  Intersection(const Intersection& other);
  Intersection& operator=(const Intersection& other);
  Intersection(Intersection&& other) noexcept;
  Intersection& operator=(Intersection&& other) noexcept;
  bool operator==(const Intersection &rhs) const;
  ~Intersection() = default;


  double t_;
  const Shape *shape_ptr_;
};

#endif //RAYTRACERV2_INTERSECTION_H
