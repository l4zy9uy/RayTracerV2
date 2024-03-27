//
// Created by l4zy9uy on 3/20/24.
//

#ifndef RAYTRACERV2_INCLUDE_SHAPE_CYLINDER_H
#define RAYTRACERV2_INCLUDE_SHAPE_CYLINDER_H
#include "Shape.h"

class Cylinder : public Shape {
public:
  Intersections local_intersect(const Ray &ray) override;
  [[nodiscard]] glm::dvec4 local_normal_at(const glm::dvec4 &point, const Intersection &hit) const override;
private:
  double minimum_ = -1000000000;
public:
  const bool & isClose() const;
  void setClose(const bool &Close);
private:
  double maximum_ = 1000000000;
  bool close_ = false;
public:
  const double & getMinimum() const;
  void setMinimum(const double &Minimum);
  const double & getMaximum() const;
  void setMaximum(const double &Maximum);
public:
  bool checkCap(const Ray &ray, const double &t);
  void intersect_cap(const Ray &ray, Intersections &xs);
};

#endif //RAYTRACERV2_INCLUDE_SHAPE_CYLINDER_H
