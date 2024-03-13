//
// Created by l4zy9uy on 2/28/24.
//

#ifndef RAYTRACERV2_INTERSECTION_H
#define RAYTRACERV2_INTERSECTION_H

#include <memory>
#include "Shape.h"
#include "Intersections.h"
class Shape;

class Ray;
class Intersections;

struct Intersection {
  double t_;
  const Shape *shape_ptr_;
public:
  Intersection(double t, Shape* shapePtr);
  Intersection(const Intersection& other);
  Intersection& operator=(const Intersection& other);
  Intersection(Intersection&& other) noexcept;
  Intersection& operator=(Intersection&& other) noexcept;
  bool operator==(const Intersection &rhs) const;
  ~Intersection() = default;

  [[nodiscard]] const double& getT() const;
  void setT(const double& t);
  [[nodiscard]] const Shape* getShapePtr() const;
  void setShapePtr(Shape* shapePtr);
};

#endif //RAYTRACERV2_INTERSECTION_H
